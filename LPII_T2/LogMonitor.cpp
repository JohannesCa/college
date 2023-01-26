/*
 * LogMonitor.cpp
 *
 *  Created on: 16 de jun de 2016
 *      Author: johannes
 */

#include "LogMonitor.h"

LogMonitor::LogMonitor(string FilePath)
{
	this->logPath = FilePath;
}

void LogMonitor::writeLog(string Message)
{
	std::ofstream output;

	this->m.lock();  // Entering critic session

	output.open(this->logPath.c_str(), std::ios::out|std::ios::app);
	output << Message;
	output.close();

	this->m.unlock();  // Exit critic session
}
