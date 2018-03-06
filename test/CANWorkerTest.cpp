/*
 * CANWorkerTest.cpp
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#include "CANWorkerTest.h"

#include "SocketCanFactory.h"

#include <stdexcept>

namespace CanUtils
{
namespace Test
{

void CANWorkerTest::SetUp()
{  
}

void CANWorkerTest::TearDown()
{
}

TEST_F( CANWorkerTest, init )
{
    SocketCanFactory factory;
    SocketCanWorkerPtr worker = factory.createSocketCanWorker();
    
    EXPECT_FALSE( worker->isStarted() );
    EXPECT_THROW( worker->start(), std::logic_error );
}

TEST_F( CANWorkerTest, add_input )
{
    SocketCanFactory factory;
    CanBufferPtr buffer_in = factory.createCanBuffer("Queue");
    CanBufferPtr buffer_out = factory.createCanBuffer("Queue");
    SocketCanWorkerPtr worker = factory.createSocketCanWorker();
    
    EXPECT_EQ(0, worker->setInput ( buffer_in  ) );
    EXPECT_EQ(0, worker->addOutput( buffer_out ) );
    
    EXPECT_EQ(0, worker->start() );
    
    EXPECT_THROW( worker->setInput( buffer_in ), std::logic_error ); 
    EXPECT_THROW( worker->delInput( buffer_in ), std::logic_error );
    
    EXPECT_EQ(0, worker->stop()  );
    
    EXPECT_EQ(0, worker->delInput ( buffer_in  ) );
    EXPECT_EQ(0, worker->delOutput( buffer_out ) );
}

TEST_F( CANWorkerTest, add_output )
{
    SocketCanFactory factory;
    CanBufferPtr buffer_in = factory.createCanBuffer("Queue");
    CanBufferPtr buffer_out = factory.createCanBuffer("Queue");
    SocketCanWorkerPtr worker = factory.createSocketCanWorker();
    
    EXPECT_EQ(0, worker->setInput ( buffer_in  ) );
    EXPECT_EQ(0, worker->addOutput( buffer_out ) );
    
    EXPECT_EQ(0, worker->start() );
    
    EXPECT_THROW( worker->addOutput( buffer_out ), std::logic_error ); 
    EXPECT_THROW( worker->delOutput( buffer_out ), std::logic_error );
    
    EXPECT_EQ(0, worker->stop()  );
    
    EXPECT_EQ(0, worker->delOutput( buffer_out ) );
    EXPECT_EQ(0, worker->delInput ( buffer_in  ) );
}

TEST_F( CANWorkerTest, simple_read )
{
    SocketCanFactory factory;
    CanBufferPtr buffer_in = factory.createCanBuffer("Queue");
    CanBufferPtr buffer_out = factory.createCanBuffer("Queue");
    SocketCanWorkerPtr worker = factory.createSocketCanWorker();
    
    EXPECT_EQ(0, worker->setInput ( buffer_in  ) );
    EXPECT_EQ(0, worker->addOutput( buffer_out ) );
    
    EXPECT_EQ(0, worker->start() );
    
    CANMessage msg1;
    CANMessage msg2;
    CANMessage msg3;
    
    CANMessage message1( 0x123, CANMessage::CANFrameType::Standard, 8, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 );
    CANMessage message2( 0x123, CANMessage::CANFrameType::Standard, 8, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22 );
    CANMessage message3( 0x123, CANMessage::CANFrameType::Standard, 8, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33 );
    
    // write all to buffer_in
    EXPECT_EQ(0, buffer_in->write( message1 ) );
    EXPECT_EQ(0, buffer_in->write( message2 ) );
    EXPECT_EQ(0, buffer_in->write( message3 ) );
    
    // read the message, no reorder
    EXPECT_EQ(0, buffer_out->read(msg1) );
    EXPECT_EQ(0, buffer_out->read(msg2) );
    EXPECT_EQ(0, buffer_out->read(msg3) );

    EXPECT_EQ( message1, msg1 );
    EXPECT_EQ( message2, msg2 );
    EXPECT_EQ( message3, msg3 );
    
    EXPECT_EQ(0, worker->stop()  );
    
    EXPECT_EQ(0, worker->delOutput( buffer_out ) );
    EXPECT_EQ(0, worker->delInput ( buffer_in  ) );
}

TEST_F( CANWorkerTest, filter_simple )
{
    SocketCanFactory factory;
    CanBufferPtr buffer_in = factory.createCanBuffer("Queue");
    CanBufferPtr buffer_out = factory.createCanBuffer("Queue");
    SocketCanWorkerPtr worker = factory.createSocketCanWorker();
    
    // accept only 0x123
    CANFilter filter ( 0x123, 0x7FF );
    EXPECT_EQ(0, worker->setInput ( buffer_in  ) );
    EXPECT_EQ(0, worker->addOutput( buffer_out, filter ) );
    
    EXPECT_EQ(0, worker->start() );
    
    CANMessage msg1;
    CANMessage msg2;
    
    CANMessage message1( 0x123, CANMessage::CANFrameType::Standard, 8, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 );
    CANMessage message2( 0x100, CANMessage::CANFrameType::Standard, 8, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22 );
    CANMessage message3( 0x123, CANMessage::CANFrameType::Standard, 8, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33 );
    
    // write all to buffer_in
    EXPECT_EQ(0, buffer_in->write( message1 ) );
    EXPECT_EQ(0, buffer_in->write( message2 ) );
    EXPECT_EQ(0, buffer_in->write( message3 ) );
    
    // read the message, no reorder
    EXPECT_EQ(0, buffer_out->read(msg1) );
    EXPECT_EQ(0, buffer_out->read(msg2) );

    // fails if the second message is in tge output buffer
    EXPECT_EQ( message1, msg1 );
    EXPECT_EQ( message3, msg2 );
    
    EXPECT_EQ(0, worker->stop()  );
    
    EXPECT_EQ(0, worker->delOutput( buffer_out ) );
    EXPECT_EQ(0, worker->delInput ( buffer_in  ) );
}

TEST_F( CANWorkerTest, filter_list )
{
    SocketCanFactory factory;
    CanBufferPtr buffer_in = factory.createCanBuffer("Queue");
    CanBufferPtr buffer_out = factory.createCanBuffer("Queue");
    SocketCanWorkerPtr worker = factory.createSocketCanWorker();
    
    // accept 0x120-0x12F and 0x700
    std::vector<CANFilter> filterList;
    CANFilter filter1 ( 0x123, 0x7F0 );
    CANFilter filter2 ( 0x700, 0x7FF );
    filterList.push_back(filter1);
    filterList.push_back(filter2);
    
    EXPECT_EQ(0, worker->setInput ( buffer_in  ) );
    EXPECT_EQ(0, worker->addOutput( buffer_out, filterList ) );
    
    EXPECT_EQ(0, worker->start() );
    
    CANMessage msg1;
    CANMessage msg2;
    
    CANMessage message1( 0x123, CANMessage::CANFrameType::Standard, 8, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 );
    CANMessage message2( 0x100, CANMessage::CANFrameType::Standard, 8, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22 );
    CANMessage message3( 0x130, CANMessage::CANFrameType::Standard, 8, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33 );
    CANMessage message4( 0x700, CANMessage::CANFrameType::Standard, 8, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33 );
    CANMessage message5( 0x723, CANMessage::CANFrameType::Standard, 8, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33 );
    
    // write all to buffer_in
    EXPECT_EQ(0, buffer_in->write( message1 ) );
    EXPECT_EQ(0, buffer_in->write( message2 ) );
    EXPECT_EQ(0, buffer_in->write( message3 ) );
    EXPECT_EQ(0, buffer_in->write( message4 ) );
    EXPECT_EQ(0, buffer_in->write( message5 ) );

    // read the message, no reorder
    EXPECT_EQ(0, buffer_out->read(msg1) );
    EXPECT_EQ(0, buffer_out->read(msg2) );

    // fails if the second message is in tge output buffer
    EXPECT_EQ( message1, msg1 );
    EXPECT_EQ( message4, msg2 );
    
    EXPECT_EQ(0, worker->stop()  );
    
    EXPECT_EQ(0, worker->delOutput( buffer_out ) );
    EXPECT_EQ(0, worker->delInput ( buffer_in  ) );
}

TEST_F( CANWorkerTest, double_out )
{
    SocketCanFactory factory;
    CanBufferPtr buffer_in = factory.createCanBuffer("Queue");
    CanBufferPtr buffer_out_1 = factory.createCanBuffer("Queue");
    CanBufferPtr buffer_out_2 = factory.createCanBuffer("Queue");
    SocketCanWorkerPtr worker = factory.createSocketCanWorker();
    
    EXPECT_EQ(0, worker->setInput ( buffer_in  ) );
    
    // accept 0x120-0x12F
    CANFilter filter1 ( 0x120, 0x7F0 );
    EXPECT_EQ(0, worker->addOutput( buffer_out_1, filter1 ) );
    
    // accpet 0x1X0
    CANFilter filter2 ( 0x100, 0x70F );
    EXPECT_EQ(0, worker->addOutput( buffer_out_2, filter2 ) );
    
    EXPECT_EQ(0, worker->start() );
    
    CANMessage msg1_1;
    CANMessage msg1_2;
    CANMessage msg2_1;
    CANMessage msg2_2;
    
    CANMessage message1( 0x123, CANMessage::CANFrameType::Standard, 8, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 );
    CANMessage message2( 0x120, CANMessage::CANFrameType::Standard, 8, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22 );
    CANMessage message3( 0x130, CANMessage::CANFrameType::Standard, 8, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33 );
    
    // write all to buffer_in
    EXPECT_EQ(0, buffer_in->write( message1 ) );
    EXPECT_EQ(0, buffer_in->write( message2 ) );
    EXPECT_EQ(0, buffer_in->write( message3 ) );

    // read the message, no reorder
    EXPECT_EQ(0, buffer_out_1->read(msg1_1) );
    EXPECT_EQ(0, buffer_out_1->read(msg1_2) );

    EXPECT_EQ(0, buffer_out_2->read(msg2_1) );
    EXPECT_EQ(0, buffer_out_2->read(msg2_2) );
    
    // fails if the second message is in tge output buffer
    EXPECT_EQ( message1, msg1_1 );
    EXPECT_EQ( message2, msg1_2 );
    
    EXPECT_EQ( message2, msg2_1 );
    EXPECT_EQ( message3, msg2_2 );
    
    EXPECT_EQ(0, worker->stop()  );
    
    EXPECT_EQ(0, worker->delOutput( buffer_out_1 ) );
    EXPECT_EQ(0, worker->delOutput( buffer_out_2 ) );
    EXPECT_EQ(0, worker->delInput ( buffer_in  ) );
}

TEST_F( CANWorkerTest, same_filter )
{
    SocketCanFactory factory;
    CanBufferPtr buffer_in = factory.createCanBuffer("Queue");
    CanBufferPtr buffer_out_1 = factory.createCanBuffer("Queue");
    CanBufferPtr buffer_out_2 = factory.createCanBuffer("Queue");
    SocketCanWorkerPtr worker = factory.createSocketCanWorker();
    
    EXPECT_EQ(0, worker->setInput ( buffer_in  ) );
    
    // accept 0x120-0x12F
    CANFilter filter ( 0x120, 0x7F0 );
    EXPECT_EQ(0, worker->addOutput( buffer_out_1, filter ) );
    EXPECT_EQ(0, worker->addOutput( buffer_out_2, filter ) );
    
    EXPECT_EQ(0, worker->start() );
    
    CANMessage msg1_1;
    CANMessage msg1_2;
    CANMessage msg2_1;
    CANMessage msg2_2;
    
    CANMessage message1( 0x123, CANMessage::CANFrameType::Standard, 8, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 );
    CANMessage message2( 0x120, CANMessage::CANFrameType::Standard, 8, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22 );
    CANMessage message3( 0x130, CANMessage::CANFrameType::Standard, 8, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33 );
    
    // write all to buffer_in
    EXPECT_EQ(0, buffer_in->write( message1 ) );
    EXPECT_EQ(0, buffer_in->write( message2 ) );
    EXPECT_EQ(0, buffer_in->write( message3 ) );

    // read the message, no reorder
    EXPECT_EQ(0, buffer_out_1->read(msg1_1) );
    EXPECT_EQ(0, buffer_out_1->read(msg1_2) );

    EXPECT_EQ(0, buffer_out_2->read(msg2_1) );
    EXPECT_EQ(0, buffer_out_2->read(msg2_2) );
    
    // fails if the second message is in tge output buffer
    EXPECT_EQ( message1, msg1_1 );
    EXPECT_EQ( message2, msg1_2 );
    
    EXPECT_EQ( message1, msg2_1 );
    EXPECT_EQ( message2, msg2_2 );
    
    EXPECT_EQ(0, worker->stop()  );
    
    EXPECT_EQ(0, worker->delOutput( buffer_out_1 ) );
    EXPECT_EQ(0, worker->delOutput( buffer_out_2 ) );
    EXPECT_EQ(0, worker->delInput ( buffer_in  ) );
}

} /* namespace Test */
} /* namespace CanUtils */
