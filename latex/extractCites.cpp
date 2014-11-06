#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

void StripBracket(string& line){
	//strip bracket character
	if(line[line.size()-1]=='}') line = line.substr(0,line.size()-1);
}

//generalization for processing a line
void process(string line, char delim, vector<string>& fields){
	stringstream ss(line);
	string field;
	while(getline(ss,field,delim)){
		fields.push_back(field);
	}
}

bool SearchLine(string line, string val){
	if(val.size()>line.size()) return false;
	int loop_end = max((int)(line.size()-val.size()),0);
	for(int i = 0; i <= loop_end; i++){
		if(line.compare(i,val.size(),val)==0){
			//return i+line.size();
			return true;
		}
	}
	//return -1;
	return false;
}

void GetCites(){
	//open text
	string line;
	ifstream infile("mainthesis.aux");
	
	ofstream outfile("cites.txt");
	
	//open & overwrite log file
	//ofstream log("logCites.txt");
	//log << "Logfile:" << endl;
	
	if(infile.is_open()){
		while(getline(infile,line)){
			if(line.compare(0,8,"\\bibcite")==0){
				vector<string> fields;
				process(line,'{',fields);
				StripBracket(fields[1]);
				outfile << fields[1] << endl;
			}
		}
	}
	
	outfile.close();
}

int main(){
	GetCites();
}