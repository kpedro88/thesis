#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

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

void GetCites(vector<string>& cites){
	//open text
	string line;
	ifstream infile("cites.txt");
	
	if(infile.is_open()){
		while(getline(infile,line)){
			if(line.size()>0){
				cites.push_back(line);
			}
		}
	}
	
	infile.close();
}

void GetBib(){
	//open text
	string line;
	ifstream infile("mybib.bib");
	
	ofstream outfile("mybib.txt");
	
	//open & overwrite log file
	ofstream log("logBib.txt");
	log << "Logfile:" << endl;	

	//get list of cites
	vector<string> cites;
	GetCites(cites);
	
	bool started = false;
	if(infile.is_open()){
		while(getline(infile,line)){
			if(line[0]=='@'){
				started = false;
				for(unsigned i = 0; i < cites.size(); i++){
					if(SearchLine(line,cites[i])){
						started = true;
						break;
					}
				}
			}
			
			if(started){
				outfile << line << endl;
			}
			else {
				log << line << endl;
			}
		}
	}

	infile.close();
	outfile.close();
	log.close();
}

int main(){
	GetBib();
}