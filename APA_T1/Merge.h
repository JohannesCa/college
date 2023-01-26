/*
 * Merge.h
 *
 *  Created on: 24 de ago de 2016
 *      Author: johannes
 */

#ifndef MERGE_H_
#define MERGE_H_

#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <linux/input.h>
#include <sys/types.h>

using namespace std;

namespace Sort {

class Merge {
private:
	unsigned long long int _loadTimeUs;
	unsigned long long int _processTimeUs;
	string _fileName;
	string GetTime(void);
	vector<int> *_input;
	vector<int> *_output;
	void Sort(void);
	void Split(int Begin, int End);
	void Comp(int Begin, int Middle, int End);

public:
	Merge(string fName, string fPath);
	~Merge();
	void genOutput(void);
	void genLog(void);
};

} /* namespace Sort */

#endif /* MERGE_H_ */
