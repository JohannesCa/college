/*
 * Selection.h
 *
 *  Created on: 24 de ago de 2016
 *      Author: johannes
 */

#ifndef SELECTION_H_
#define SELECTION_H_

#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <linux/input.h>
#include <sys/types.h>

using namespace std;

namespace Sort {

class Selection {
private:
	unsigned long long int _loadTimeUs;
	unsigned long long int _processTimeUs;
	string _fileName;
	string GetTime(void);
	vector<int> *_input;
	vector<int> *_output;
	void Sort(void);

public:
	Selection(string fName, string fPath);
	~Selection();
	void genOutput(void);
	void genLog(void);
};

} /* namespace Sort */

#endif /* SELECTION_H_ */
