/*
 * Insertion.cpp
 *
 *  Created on: 24 de ago de 2016
 *      Author: johannes
 */

#include "Insertion.h"

namespace Sort {

Insertion::Insertion(string fName, string fPath): _fileName(fName)
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


void Insertion::Swap(vector<int>::iterator a, vector<int>::iterator b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}


void Insertion::Sort(void)
{
	for(vector<int>::iterator i = this->_input->begin(); i != this->_input->end(); i++){
		vector<int>::iterator j = i;

		while((j != this->_input->begin()) && (*(j-1) > *j)){
			Swap(j-1, j);
			j--;
		}
	}
}


Insertion::~Insertion()
{
	delete this->_input;
}


void Insertion::genOutput(void)
{
	ofstream output;
	string outFile = this->_fileName + ".out";
	string path = "Outputs/" + outFile;

	output.open(path.c_str(), std::ios::out);
	for(unsigned int i = 0; i < this->_input->size(); i++)
		output << to_string((*this->_input)[i]) << endl;
	output.close();
}


void Insertion::genLog(void)
{
	ofstream output;
	string fName = "Logs/Insertion.log";
	string Date = this->GetTime();
	string Log = "Generated in: " + Date +
				 "\nInput file name: " + this->_fileName +
				 "\nLoading time (us): " + to_string(this->_loadTimeUs) +
				 "\nProcessing time (us): " + to_string(this->_processTimeUs) + "\n\n";

	output.open(fName.c_str(), std::ios::out|std::ios::app);
	output << Log;
	output.close();
}


string Insertion::GetTime(void)
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
