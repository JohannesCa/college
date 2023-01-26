/*
 * Quick.h
 *
 *  Created on: 25 de ago de 2016
 *      Author: johannes
 */

#ifndef QUICK_H_
#define QUICK_H_

#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <linux/input.h>
#include <sys/types.h>

using namespace std;

namespace Sort {

class Quick {
private:
	unsigned long long int _loadTimeUs;
	unsigned long long int _processTimeUs;
	string _fileName;
	string GetTime(void);
	vector<int> *_input;
	void Swap(int a, int b);
	void Sort(int Lo, int Hi);
	int Part(int Lo, int Hi);

public:
	Quick(string fName, string fPath);
	~Quick();
	void genOutput(void);
	void genLog(void);
};

} /* namespace Sort */

#endif /* QUICK_H_ */
