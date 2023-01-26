/*
 * Heap.h
 *
 *  Created on: 25 de ago de 2016
 *      Author: johannes
 */

#ifndef HEAP_H_
#define HEAP_H_

#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <math.h>
#include <linux/input.h>
#include <sys/types.h>

using namespace std;

namespace Sort {

class Heap {
private:
	unsigned long long int _loadTimeUs;
	unsigned long long int _processTimeUs;
	string _fileName;
	string GetTime(void);
	vector<int> *_input;
	int FindParent(int i);
	int FindLChild(int i);
	void Swap(int a, int b);
	void Sort(void);
	void PrepHeap(void);
	void SiftDown(int Begin, int End);

public:
	Heap(string fName, string fPath);
	~Heap();
	void genOutput(void);
	void genLog(void);
};

} /* namespace Sort */

#endif /* HEAP_H_ */
