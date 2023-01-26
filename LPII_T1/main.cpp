/*
 * main.cpp
 *
 *  Created on: 11 de abr de 2016
 *      Author: johannes
 */

#include "functions.hpp"

int main(void)
{
	std::vector<std::thread> thr;
	std::string aux = "reqs/req1.req";
	std::atomic<bool> *arr, *proc;

	int index;
	int nReqs = 0;


	/* Verify how many requisition files are there */

	while(checkFile(aux)) {
		aux = "reqs/req" + std::to_string(++nReqs + 1) + ".req";

		/* Prepare the arrive and proceed vectors */

		arr = new std::atomic<bool>;
		proc = new std::atomic<bool>;

		arr->store(false);
		proc->store(false);

		arrive.push_back(arr);
		proceed.push_back(proc);

	}

	std::cout << "There are " << nReqs << " requisition files in directory reqs/" << std::endl;


	/* Call monitor thread */

	std::thread mon(monitor, nReqs);


	/* Call other threads */

	for(index = 0; index < nReqs; ++index)
		thr.push_back(std::thread(readReq, index + 1));


	/* Join all threads */

	for(std::vector<std::thread>::iterator it = thr.begin(); it != thr.end(); it++)
		(*it).join();
	mon.join();


	/* Show on screen the number of bytes processed */

	printf("[MAIN-RETURN] %li bytes were processed in total, by all threads.\n", totalBytes);


	/* Delete dynamically allocated booleans and clear vectors */

	for(std::vector<std::atomic<bool>*>::iterator it = arrive.begin(); it != arrive.end(); it++)
		delete (*it);
	arrive.clear();

	for(std::vector<std::atomic<bool>*>::iterator it = proceed.begin(); it != proceed.end(); it++)
		delete (*it);
	proceed.clear();


	return 0;
}
