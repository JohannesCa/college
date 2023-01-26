/*
 * SJF.cpp
 *
 *  Created on: 2 de out de 2016
 *      Author: johannes
 */

#include "SJF.h"

namespace Scheduler {

mutex Scheduler::SJF::_mute;
vector<Job*> Scheduler::SJF::_JobsList;

bool DurComp(Job* a, Job* b)
{
	return (a->getDuration()) < (b->getDuration());
}
/*
bool operator<(Job a, Job b)
{
    return a.getDuration() < b.getDuration();
}
*/
SJF::SJF()
{
	;
}

void SJF::InsertJob(Job* in)
{
	_mute.lock();

	in->Init();
	_JobsList.push_back(in);
	sort(_JobsList.begin(), _JobsList.end(), DurComp);

	_mute.unlock();
}

void SJF::Schedule(void)
{
	for(JobIt it = _JobsList.begin(); it != _JobsList.end(); ++it){
		Job* aux = *it;

		_mute.lock();

		aux->Process();
		_JobsList.erase(it);

		_mute.unlock();

		usleep(aux->getDuration()); // Milliseconds to Microseconds
		aux->End();
	}
}

void SJF::print(void)
{
	for(JobIt it = _JobsList.begin(); it != _JobsList.end(); ++it)
		printf("%i, %i\n", (*it)->getCall(), (*it)->getDuration());
}

} /* namespace Scheduler */
