/*
 * Selection.cpp
 *
 *  Created on: 24 de ago de 2016
 *      Author: johannes
 */

#include "Selection.h"

namespace Sort {

Selection::Selection(string fName, string fPath): _fileName(fName) // Lembrar de passar o caminho completo
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


Selection::~Selection()
{
	delete this->_output;
	delete this->_input;
}


void Selection::Sort(void)
{
	while(!this->_input->empty()){
		vector<int>::iterator min = this->_input->begin();
		vector<int>::iterator j;

		for(j = this->_input->begin()+1; j < this->_input->end(); j++){
			if(*min > *j)
				min = j;
		}
		if(min != j){
			this->_output->push_back(*min);
			this->_input->erase(min);
		}
	}
}


void Selection::genOutput(void)
{
	ofstream output;
	string outFile = this->_fileName + ".out";
	string path = "Outputs/" + outFile;

	output.open(path.c_str(), std::ios::out);
	for(unsigned int i = 0; i < this->_output->size(); i++)
		output << to_string((*this->_output)[i]) << endl;
	output.close();
}


void Selection::genLog(void)
{
	ofstream output;
	string fName = "Logs/Selection.log";
	string Date = this->GetTime();
	string Log = "Generated in: " + Date +
				 "\nInput file name: " + this->_fileName +
				 "\nLoading time (us): " + to_string(this->_loadTimeUs) +
				 "\nProcessing time (us): " + to_string(this->_processTimeUs) + "\n\n";

	output.open(fName.c_str(), std::ios::out|std::ios::app);
	output << Log;
	output.close();
}


string Selection::GetTime(void)
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
