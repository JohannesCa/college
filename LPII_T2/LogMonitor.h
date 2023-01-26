/*
 * LogMonitor.h
 *
 *  Created on: 16 de jun de 2016
 *      Author: johannes
 */

#ifndef LOGMONITOR_H_
#define LOGMONITOR_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <time.h>

#include <thread>
#include <mutex>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>

using namespace std;

class LogMonitor{
	mutex m;
	string logPath;
public:
	LogMonitor(string FilePath);
	void writeLog(string Message);
};

#endif /* LOGMONITOR_H_ */
