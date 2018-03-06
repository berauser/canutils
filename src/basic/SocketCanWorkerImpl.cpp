/*
 * SocketCanWorkerImpl.cpp
 *
 *  Created on: 01.03.2017
 *      Author: rauser
 */

#include "SocketCanWorkerImpl.h"

#include "logger.h"

namespace CanUtils
{

/**
 * Defines a simple less operator for std::map 
 */
bool operator<( const CANFilter& f1, const CANFilter& f2 )
{
    return ( f1.can_id < f2.can_id );
}

SocketCanWorkerImpl::SocketCanWorkerImpl()
{
}

SocketCanWorkerImpl::~SocketCanWorkerImpl()
{
    
}

void SocketCanWorkerImpl::workerLoop()
{
	thread_local CANMessage message;
	while( _input->read( message ) >= 0 )
	{
		for( std::pair<CANFilter,CanBasePtr> entry : _output )
		{
			if( entry.first.matches( message ) )
			{
				/* FIXME if a write blocks, all other blocks */
				entry.second->write( message );
			}
		}
	}
}

int SocketCanWorkerImpl::start()
{
	LOGGER(SOCKETCAN_DEBUG, "SocketCanWorkerImpl::start()");
	if ( isStarted() )
	{
		LOGGER(SOCKETCAN_ERROR, "Worker is already started");
		throw std::logic_error("Worker is already started");
	}
	if ( !_input )
	{
		LOGGER(SOCKETCAN_ERROR, "Cannot start worker: No input");
		throw std::logic_error("Cannot start worker: No input");
	}
	if ( !_output.size() )
	{
		LOGGER(SOCKETCAN_ERROR, "Cannot start worker: No output");
		throw std::logic_error("Cannot start worker: No output");
	}
	return startWorker( std::bind( &SocketCanWorkerImpl::workerLoop, this ) );    
}

int SocketCanWorkerImpl::stop()
{
	LOGGER(SOCKETCAN_DEBUG, "SocketCanWorkerImpl::stop()");
	if (!isStarted())
	{
		LOGGER(SOCKETCAN_ERROR, "Worker is already stopped");
		throw std::logic_error("Worker is already stopped");
	}
	return stopWorker();
}

int SocketCanWorkerImpl::setInput( CanBasePtr input )
{
	if ( isStarted() )
	{
		LOGGER(SOCKETCAN_ERROR, "Cannot add input after start");
		throw std::logic_error("Cannot add input after start");
	}
	if( !input )
	{
		LOGGER(SOCKETCAN_ERROR, "Input is not valid");
		throw std::invalid_argument("Input is not valid");
	}
	_input = input;
	    
	return 0;
}

int SocketCanWorkerImpl::delInput ( CanBasePtr input )
{
	/* currently only one input device is supported, so we can ignore it here */
	(void)input;
	
	if ( isStarted() )
	{
		LOGGER(SOCKETCAN_ERROR, "Cannot delete input after start");
		throw std::logic_error("Cannot delete input after start");
	}
	_input.reset();
	
	return 0;
}

int SocketCanWorkerImpl::addOutput( CanBasePtr output )
{
    CANFilter filter( 0x00, 0x00 );
    return addOutput( output, filter );    
}

int SocketCanWorkerImpl::addOutput( CanBasePtr output, const CANFilter& filter )
{
	if ( isStarted() )
	{
		LOGGER(SOCKETCAN_ERROR, "Cannot add output after start");
		throw std::logic_error("Cannot add output after start");
	}
	if( !output )
	{
		LOGGER(SOCKETCAN_ERROR, "Output is not valid");
		throw std::invalid_argument("Output is not valid");
	}
	(void)filter;
	_output.insert( std::pair<CANFilter,CanBasePtr>( filter, output ) );
	
	return 0;
}

int SocketCanWorkerImpl::addOutput( CanBasePtr output, const std::vector<CANFilter>& filters )
{
	for( CANFilter filter : filters )
	{
		addOutput( output, filter );
	}
	return 0;
}

int SocketCanWorkerImpl::delOutput( CanBasePtr output )
{
	if ( isStarted() )
	{
		LOGGER(SOCKETCAN_ERROR, "Cannot delete output after start");
		throw std::logic_error("Cannot delete output after start");
	}
	if( !output )
	{
		LOGGER(SOCKETCAN_ERROR, "Output is not valid");
		throw std::invalid_argument("Output is not valid");
	}
	
	for(std::multimap<CANFilter,CanBasePtr>::iterator it = _output.begin(); it != _output.end(); ++it )
	{
		if( it->second == output )
		{
			_output.erase( it );
		}
	}
	return 0;
}

} /* namespace CanUtils */
