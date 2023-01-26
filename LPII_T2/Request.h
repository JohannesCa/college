/*
 * Request.h
 *
 *  Created on: 17 de jun de 2016
 *      Author: johannes
 */

#ifndef REQUEST_H_
#define REQUEST_H_

#include "LogMonitor.h"

class Request{
private:
	string Command;
	string File;
	string FileType;

	bool CheckCmd();
	bool CheckFile();
	string getTime();
	string getType();
	string getContent();
public:
	Request(string FullRequest);
	string GetAnswer();
};

#endif /* REQUEST_H_ */
