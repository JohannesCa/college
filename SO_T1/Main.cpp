/*
 * Main.cpp
 *
 *  Created on: 25 de set de 2016
 *      Author: johannes
 */

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <thread>

#include "Job.h"
#include "FCFS.h"
#include "SJF.h"

using namespace std;


/****   Definitions   ****/

typedef vector<Job*> JobList;
typedef vector<Job*>::iterator JobIt;

JobList LoadedJobsList;

bool PrepareJobs(string fName);
void CallFCFS(Scheduler::FCFS* fcfs);
void CallSJF(Scheduler::SJF* sjf);
//void CallFCFS(Scheduler::* fcfs);


/****   Main   ****/

int main(int argc, char** argv)
{
	if(!PrepareJobs("input4")){
		cerr << "[ERROR] The file doesn't exist.\n";
		return -1;
	}

	Scheduler::FCFS sch;

	thread Caller(CallFCFS, &sch);
	thread FCFS(&Scheduler::FCFS::Schedule, sch);

	Caller.join();
	FCFS.join();

	float WaitSumVal = 0;
	float RetSumVal = 0;
	int n = 0;

	for(JobIt it = LoadedJobsList.begin(); it != LoadedJobsList.end(); ++it){
		++n;
		printf("n(%i):Wait [ %f ] += %f\n", n, WaitSumVal, (*it)->getWaitTime());
		WaitSumVal += (*it)->getWaitTime();
		RetSumVal += (*it)->getRetTime();
	}

	float AvgWait = WaitSumVal/n;
	float AvgRet = RetSumVal/n;

	printf("Average Wait time: %3.1f\n", AvgWait);
	printf("Average Ret time: %3.1f\n", AvgRet);

	// Finalizing

	for(JobIt it = LoadedJobsList.begin(); it != LoadedJobsList.end(); ++it)
		delete *it;
	LoadedJobsList.clear();

	return 0;
}


/****   Functions   ****/

bool PrepareJobs(string fName) // Return if the file either exists or not
{
	bool ret = true;

	string line;
	ifstream input;
	input.open(fName, ios::in);

	if(!input)
		ret = false;
	else{
		while(getline(input, line)){
			int i;
			int beg, dur; // Begin, Duration
			string Buff;

			for(i = 0; line[i] != ' '; ++i)
				Buff += line[i];

			beg = stoi(Buff);
			Buff.clear();

			for(++i; line[i] != '\0'; ++i)
				Buff += line[i];

			dur = stoi(Buff);
			LoadedJobsList.push_back(new Job(beg, dur));
		}
	}

	return ret;
}


void CallFCFS(Scheduler::FCFS* fcfs)
{
	for(JobIt it = LoadedJobsList.begin(); it != LoadedJobsList.end(); ++it){
		printf("> sleep for: %i\n", (*it)->getCall());
		usleep((*it)->getCall() * 1000);
		fcfs->InsertJob(*it);
	}
	fcfs->Stop();
}

void CallSJF(Scheduler::SJF* sjf)
{
	for(JobIt it = LoadedJobsList.begin(); it != LoadedJobsList.end(); ++it){
		usleep((*it)->getCall() * 1000);
		sjf->InsertJob(*it);
	}
}
