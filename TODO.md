TODOs and FIXMEs

* Read and store can message receive timestamps
* Fix CANMessage operators (see FIXME in CANMessage.h)
* Fix/Implement tests
* * [  FAILED  ] CANUtilsPriortiyQueueTest.priority_mixed
* * [  FAILED  ] CANErrorTest.flag_bit_operator_and
* * [  FAILED  ] SocketCanTest.filter_basic
* * [  FAILED  ] CANUtilsRingBufferTest.override_write_async
* Write tests for CANStatistics and CANDeviceInfo
* Write test for netsocket library
* Improve test coverage ( 18.03.2018 -> ~75% )
* Implement CAN for Windows
* Implement transmit filters (For example, you can "turn off" certain CAN messages without changing the logic of the application)
* Implement performance test to identify which lines of code can be improved
* Improve SocketCanWorker to read from multiple devices and buffers
* Change compiler dependend registration method  ( \_\_attribute\_\_((constructor)) / ... ), to a non compiler dependend method
* Refactor cmake to disable unused parts of the library
* Implement platform independ commandline utils like the linux "can-utils" (e.g candump,cansend,...)