/*
 * Job.cpp
 *
 *  Created on: 1 de out de 2016
 *      Author: johannes
 */

#include "Job.h"

Job::Job(int start, int duration):
	_duration(duration),
	_call(start)
{
	;
}

void Job::Init(void)
{
	gettimeofday(&this->_begin, NULL);
}

void Job::Process(void)
{
	gettimeofday(&this->_exec, NULL);
}

void Job::End(void)
{
	gettimeofday(&this->_ret, NULL);
}

float Job::getWaitTime(void)
{
	float ret;
	unsigned int usec;

	// Get time in microseconds
	usec = (this->_exec.tv_sec - this->_begin.tv_sec) * 1000000 + (this->_exec.tv_usec - this->_begin.tv_usec);

	// Convert microseconds to milliseconds
	ret = usec * 0.001;
	return ret;
}

float Job::getRetTime(void)
{
	float ret;
	unsigned int usec;

	// Get time in microseconds
	usec = (this->_ret.tv_sec - this->_begin.tv_sec) * 1000000 + (this->_ret.tv_usec - this->_begin.tv_usec);

	// Convert microseconds to milliseconds
	ret = usec * 0.001;
	return ret;
}
