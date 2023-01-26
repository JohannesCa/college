/*
 * FCFS.cpp
 *
 *  Created on: 1 de out de 2016
 *      Author: johannes
 */

#include "FCFS.h"

namespace Scheduler{

mutex Scheduler::FCFS::_mute;
mutex Scheduler::FCFS::_lmute;
vector<Job*> Scheduler::FCFS::_JobsList;
bool Scheduler::FCFS::_loop;

FCFS::FCFS()
{
	_lmute.lock();
	_loop = true;
	_lmute.unlock();
}

void FCFS::InsertJob(Job* in)
{
	_mute.lock();

	in->Init();
	_JobsList.push_back(in);

	_mute.unlock();
}

void FCFS::Schedule(void)
{
	//printf("helohelo\n");
	bool loop = true;

	while(loop){
		while(!_JobsList.empty()){
			Job* aux = (*_JobsList.begin());
			JobIt beg = _JobsList.begin();

			_mute.lock();

			aux->Process();
			_JobsList.erase(beg);

			_mute.unlock();

			printf(">> sleep for: %ims\n\n", aux->getDuration());
			usleep(aux->getDuration() * 1000);
			aux->End();
		}
		_lmute.lock();
		loop = _loop? true : false;
		_lmute.unlock();
	}
}

void FCFS::Stop(void)
{
	_lmute.lock();
	_loop = false;
	_lmute.unlock();
}

} /* namespace Scheduler */
