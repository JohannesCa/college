/*
 * SJF.h
 *
 *  Created on: 2 de out de 2016
 *      Author: johannes
 */

#ifndef SJF_H_
#define SJF_H_

#include <iostream>
#include <vector>

#include <thread>
#include <mutex>
#include <unistd.h>
#include <algorithm>

#include "Job.h"

using namespace std;

namespace Scheduler {

typedef vector<Job*>::iterator JobIt;

class SJF {
private:
	static mutex _mute;
	static vector<Job*> _JobsList;
	//bool DurComp(Job* a, Job* b);
public:
	SJF();
	void print(void);
	void InsertJob(Job* in);
	void Schedule(void);
};

} /* namespace Scheduler */

#endif /* SJF_H_ */
