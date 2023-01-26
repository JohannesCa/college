/*
 * functions.hpp
 *
 *  Created on: 11 de abr de 2016
 *      Author: johannes
 */

#ifndef FUNCTIONS_HPP_
#define FUNCTIONS_HPP_

#include <iostream>
#include <stdlib.h>

#include <pthread.h>
#include <thread>
#include <string>
#include <fstream>

#include <vector>
#include <atomic>


/* Global and Volatile variables */


std::vector<std::atomic<bool>*> arrive;
std::vector<std::atomic<bool>*> proceed;

volatile std::atomic_flag lock = ATOMIC_FLAG_INIT;

volatile long int totalBytes = 0;  // Number of Bytes processed in total.


/* Functions */


void Lock(int &index)
{
    while(lock.test_and_set()) // Test and activate the lock
    	printf("[THREAD %i] Blocked!\n", index);
}


void Unlock()
{
	lock.clear();
}


long int processData(std::string &fPath, int index) // Process the data and return how many bytes were processed
{
	std::ifstream input;
	std::ofstream output;
	std::string answerFile = "ans-req" + std::to_string(index) + ".ans";
	std::string line, fBuffer = "";

	input.open(fPath, std::ios::binary);
	while(getline(input, line))
		fBuffer += line + "\n";
	input.close();

	output.open("answ/" + answerFile, std::ios::out);
	output << fBuffer;
	output.close();

	return static_cast<long int>(fBuffer.size());
}


bool checkFile(std::string &fName) // Verify if the file exists.
{
	std::ifstream input(fName.c_str());
	if(!input)
		return false;
	else return true;
}


void readReq(int index) // Threads' index
{
	long int bytes;

	std::ifstream request;
	std::ofstream answer;

	std::string cmd = ""; // Command
	std::string cmdFile = ""; // Command file operand
	std::string out, line, ofName; // Output file name
	std::string ifName = "reqs/req" + std::to_string(index) + ".req";

	request.open(ifName.c_str());
	getline(request, line);

	int i;

	/* Get command */

	for(i = 0; line[i] != ' '; i++)
		cmd += line[i];


	/* Get file operand */

	for(++i; line[i] != '\0'; i++)
		cmdFile += line[i];


	/* Add the complete path */

	cmdFile = "files/" + cmdFile;


	/* Verify requisition command and file */

	if(cmd != "GET"){

		/* If command is invalid */

		ofName = "answ/ans-req" + std::to_string(index) + ".ans";
		answer.open(ofName, std::ios::out);
		out = "ERROR #2: Command '" + cmd + "' is invalid!\n";
		printf("[THREAD %i] %s", index, out.c_str());
		answer << out;
		answer.close();


		/* Calculate total of bytes written in output file */

		printf("[THREAD %i] Attempt to access critical session.\n", index);
		Lock(index);
		printf("[THREAD %i] Accessing critical session.\n", index);
		totalBytes += static_cast<long int>(out.size());
		printf("[THREAD %i] Exiting critical session. %li bytes processed.\n", index, static_cast<long int>(out.size()));
		Unlock();

	}else if(!checkFile(cmdFile)){

		/* If specified file does not exist */

		ofName = "answ/ans-req" + std::to_string(index) + ".ans";
		answer.open(ofName, std::ios::out);
		out = "ERROR #1: Could not find file '" + cmdFile + "'.\n";
		printf("[THREAD %i] %s", index, out.c_str());
		answer << out;
		answer.close();


		/* Calculate total of bytes written in output file */

		printf("[THREAD %i] Attempt to access critical session.\n", index);
		Lock(index);
		printf("[THREAD %i] Accessing critical session.\n", index);
		totalBytes += static_cast<long int>(out.size());
		printf("[THREAD %i] Exiting critical session. %li bytes processed.\n", index, static_cast<long int>(out.size()));
		Unlock();

	}else{

		/* Process data */

		bytes = processData(cmdFile,index);


		/* Prepare for critical session */

		printf("[THREAD %i] Attempt to access critical session.\n", index);
		Lock(index);
		printf("[THREAD %i] Accessing critical session.\n", index);
		totalBytes += bytes;
		printf("[THREAD %i] Exiting critical session. %li bytes processed.\n", index, bytes);
		Unlock();
	}

	std::vector<std::atomic<bool>*>::iterator it1 = arrive.begin();
	std::vector<std::atomic<bool>*>::iterator it2 = proceed.begin();

	for(int i = 0; i < index-1; i++){it1++; it2++;}

	(*it1)->store(true);
	printf("[THREAD %i] Arrived at the Barrier (arrival[%i] set as %s).\n",
			index, index, (*it1)->load() ? "true" : "false");

	while((*it2)->load() == false)
		printf("[THREAD %i] Locked at the Barrier.\n", index);

	printf("[THREAD %i] Barrier crossed.\n", index);

	(*it2)->store(false);

	request.close();
}


void monitor(int nThr)
{
	printf("[MONITOR] Initializing monitor thread...\n");

	for(int i = 0; i < nThr; i++){
		while((*arrive[i]).load() == false);
		(*arrive[i]).store(false);
	}
	for(int i = 0; i < nThr; i++){
		(*proceed[i]).store(true);
		printf("[MONITOR] Granted passage to thread %i (proceed[%i] set as %s).\n",
				i+1, i+1, (*proceed[i]).load() ? "true" : "false");
	}
}


#endif /* FUNCTIONS_HPP_ */
