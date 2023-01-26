/*
 * Merge.cpp
 *
 *  Created on: 24 de ago de 2016
 *      Author: johannes
 */

#include "Merge.h"

namespace Sort {

Merge::Merge(string fName, string fPath): _fileName(fName)
{
	this->_input = new vector<int>;
	this->_output = new vector<int>;

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


Merge::~Merge()
{
	delete this->_output;
	delete this->_input;
}


void Merge::Sort()
{
	this->_output->resize(this->_input->size());
	this->Split(0, this->_input->size());
}

void Merge::Split(int Begin, int End)
{
	if(End - Begin >= 2){
		unsigned int Middle = (Begin + End)/2;
		this->Split(Begin, Middle);
		this->Split(Middle, End);
		this->Comp(Begin, Middle, End);
	}
}


void Merge::Comp(int Begin, int Middle, int End)
{
	int i = Begin;
	int j = Middle;

	for(int k = Begin; k < End; k++){
		if((i < Middle) && ((j >= End) || ((*this->_input)[i] <= (*this->_input)[j])))
			(*this->_output)[k] = (*this->_input)[i++];
		else
			(*this->_output)[k] = (*this->_input)[j++];
	}

	for(int k = Begin; k < End; k++)
		(*this->_input)[k] = (*this->_output)[k];
}


void Merge::genOutput(void)
{
	ofstream output;
	string outFile = this->_fileName + ".out";
	string path = "Outputs/" + outFile;

	output.open(path.c_str(), std::ios::out);
	for(unsigned int i = 0; i < this->_output->size(); i++)
		output << to_string((*this->_output)[i]) << endl;
	output.close();
}


void Merge::genLog(void)
{
	ofstream output;
	string fName = "Logs/Merge.log";
	string Date = this->GetTime();
	string Log = "Generated in: " + Date +
				 "\nInput file name: " + this->_fileName +
				 "\nLoading time (us): " + to_string(this->_loadTimeUs) +
				 "\nProcessing time (us): " + to_string(this->_processTimeUs) + "\n\n";

	output.open(fName.c_str(), std::ios::out|std::ios::app);
	output << Log;
	output.close();
}


string Merge::GetTime(void)
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
