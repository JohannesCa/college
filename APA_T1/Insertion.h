/*
 * Insertion.h
 *
 *  Created on: 24 de ago de 2016
 *      Author: johannes
 */

#ifndef INSERTION_H_
#define INSERTION_H_

#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <linux/input.h>
#include <sys/types.h>

using namespace std;

namespace Sort {

class Insertion {
private:
	unsigned long long int _loadTimeUs;
	unsigned long long int _processTimeUs;
	string _fileName;
	string GetTime(void);
	vector<int> *_input;
	void Sort(void);
	void Swap(vector<int>::iterator a, vector<int>::iterator b);

public:
	Insertion(string fName, string fPath);
	~Insertion(void);
	void genOutput(void);
	void genLog(void);
};

} /* namespace Sort */

#endif /* INSERTION_H_ */
