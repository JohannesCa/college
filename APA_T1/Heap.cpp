/*
 * Heap.cpp
 *
 *  Created on: 25 de ago de 2016
 *      Author: johannes
 */

#include "Heap.h"

namespace Sort {

Heap::Heap(string fName, string fPath): _fileName(fName)
{
	this->_input = new vector<int>;

	ifstream input;
	string line;

	string filePath = fPath + fName;

	struct timeval initTime, finalTime;
	gettimeofday(&initTime, NULL);

	input.open(filePath, std::ios::in);
	while(getline(input, line))
		this->_input->push_back(stoi(line));

	input.close();
	gettimeofday(&finalTime, NULL);
	this->_loadTimeUs = (finalTime.tv_sec - initTime.tv_sec) * 1000000 + (finalTime.tv_usec - initTime.tv_usec);

	gettimeofday(&initTime, NULL);
	this->Sort();

	gettimeofday(&finalTime, NULL);
	this->_processTimeUs = (finalTime.tv_sec - initTime.tv_sec) * 1000000 + (finalTime.tv_usec - initTime.tv_usec);

	this->genOutput();
}


Heap::~Heap()
{
	delete this->_input;
}


int Heap::FindParent(int i)
{
	return floor((i-1)/2);
}


int Heap::FindLChild(int i)
{
	return (2*i + 1);
}


void Heap::Swap(int a, int b)
{
	int aux = (*this->_input)[a];
	(*this->_input)[a] = (*this->_input)[b];
	(*this->_input)[b] = aux;
}


void Heap::Sort()
{
	this->PrepHeap();

	int End = this->_input->size()-1;
	while(End > 0){
		Swap(0, End);
		End--;

		this->SiftDown(0, End);
	}
}


void Heap::PrepHeap()
{
	int begin = this->FindParent(this->_input->size()-1);

	while(begin >= 0){
		this->SiftDown(begin, this->_input->size()-1);
		begin--;
	}
}


void Heap::SiftDown(int Begin, int End)
{
	int root = Begin;

	while(FindLChild(root) <= End){
		int child = FindLChild(root);
		int auxi = root;

		if((*this->_input)[auxi] < (*this->_input)[child])
			auxi = child;

		if((child+1 <= End) && ((*this->_input)[auxi] < (*this->_input)[child+1]))
			auxi = child + 1;

		if(auxi == root)
			return;
		else{
			this->Swap(root, auxi);
			root = auxi;
		}

	}
}


void Heap::genOutput(void)
{
	ofstream output;
	string outFile = this->_fileName + ".out";
	string path = "Outputs/" + outFile;

	output.open(path.c_str(), std::ios::out);
	for(unsigned int i = 0; i < this->_input->size(); i++)
		output << to_string((*this->_input)[i]) << endl;
	output.close();
}


void Heap::genLog(void)
{
	ofstream output;
	string fName = "Logs/Heap.log";
	string Date = this->GetTime();
	string Log = "Generated in: " + Date +
				 "\nInput file name: " + this->_fileName +
				 "\nLoading time (us): " + to_string(this->_loadTimeUs) +
				 "\nProcessing time (us): " + to_string(this->_processTimeUs) + "\n\n";

	output.open(fName.c_str(), std::ios::out|std::ios::app);
	output << Log;
	output.close();
}


string Heap::GetTime(void)
{
	const string WeekDay[]={"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	const string MonthName[]={"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	time_t Time = time(NULL);
	struct tm *aTime = localtime(&Time);

	int day = aTime->tm_mday;
	int wday = aTime->tm_wday;
	int month = aTime->tm_mon;
	int year = aTime->tm_year + 1900;
	int hour = aTime->tm_hour;
	int min = aTime->tm_min;
	int sec = aTime->tm_sec;

	return WeekDay[wday] + ", " + to_string(day) + " " + MonthName[month] + " " + to_string(year) + " " + to_string(hour) + ":" + to_string(min) + ":" + to_string(sec) + " BRT";
}

} /* namespace Sort */
