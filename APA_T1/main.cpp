/*
 * main.cpp
 *
 *  Created on: 24 de ago de 2016
 *      Author: johannes
 */

#include <iostream>
#include "Selection.h"
#include "Insertion.h"
#include "Merge.h"
#include "Quick.h"
#include "Heap.h"
#include "Defaut.h"

using namespace std;

void help(const char *prog)
{
	cout << "\nUse: " << prog << " <method_name> <input_file_name>\n\n"
			"Available sorting methods:\n"
			"\t- selection\n"
			"\t- insertion\n"
			"\t- merge\n"
			"\t- quick\n"
			"\t- heap\n"
			"\t- default (stl default)\n\n";

}

int main(int argc, char** argv)
{

	if(argc != 3){
		help(argv[0]);
		return -1;
	}

	string method = argv[1];
	string fName = argv[2];
	string fPath = "Resources/";

	string filePath = fPath + fName;
	ifstream input(filePath.c_str());
	if(!input){
		cerr << "[ERROR] Could not find file <" << fName << ">\n";
		help(argv[0]);
		return -1;
	}


	if(method == "selection"){
		Sort::Selection sort(fName, fPath);
		sort.genLog();

	}else if(method == "insertion"){
		Sort::Insertion sort(fName, fPath);
		sort.genLog();

	}else if(method == "merge"){
		Sort::Merge sort(fName, fPath);
		sort.genLog();

	}else if(method == "quick"){
		Sort::Quick sort(fName, fPath);
		sort.genLog();

	}else if(method == "heap"){
		Sort::Heap sort(fName, fPath);
		sort.genLog();

	}else if(method == "default"){
		Sort::Default sort(fName, fPath);
		sort.genLog();

	}else{
		help(argv[0]);
		return -1;
	}

	return 0;
}
