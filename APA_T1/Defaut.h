/*
 * Defaut.h
 *
 *  Created on: 25 de ago de 2016
 *      Author: johannes
 */

#ifndef DEFAUT_H_
#define DEFAUT_H_

#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <linux/input.h>
#include <sys/types.h>
#include <algorithm>

using namespace std;

namespace Sort {

class Default {
private:
	unsigned long long int _loadTimeUs;
	unsigned long long int _processTimeUs;
	string _fileName;
	string GetTime(void);
	vector<int> *_input;
	void Sort(void);

public:
	Default(string fName, string fPath);
	~Default();
	void genOutput(void);
	void genLog(void);
};

} /* namespace Sort */

#endif /* DEFAUT_H_ */
