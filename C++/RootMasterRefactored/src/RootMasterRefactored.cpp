//============================================================================
// Name        : RootMasterRefactored.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

enum InputCase{IODefault,OutputDefault,InputDefault,HelpNeeded,IOGiven,WrongParams};

void SortParams(vector<string> &params){
	vector<string> tmp;//dopracowac funkcje, modyfikuje wektor parametrow do postaci param[0]=Input, param[1]=Output
	for (int i=0;i<params.size-1;i++){
		if(params[i]=="-i"){
			tmp.push_back(params[i+1]);
		}
	}

}
bool IsValidPath(string path){
	fstream file;
	file.open(path);
	if(file.is_open()){
		file.close();
		return true;
	}else{
		file.close();
	}	return false;
}
bool IsValidParam(string param){
	if(param=="-o"||param=="-i")
		return true;
	else
		return false;
}
InputCase CheckParams(vector<string> &params){
	bool CheckA,CheckB,CheckD,CheckE;
	if(params.size()==0||((params.size()==1&&IsValidParam(params[0]))||(params.size()==2&&IsValidParam(params[0])&&IsValidParam(params[1])))){
		return IODefault;
	}else if(params.size()==1&&params[0]=="-h"){
		return HelpNeeded;
	}else{
		for(int i=0;i<params.size()-1;i++){
			if(params[i]=="-i"&&IsValidPath(params[i+1])){
				CheckA=true;
			}
			if(params[i]=="-o"&&IsValidPath(params[i+1])){
				CheckB=true;
			}
		}
		if(CheckA&&CheckB){
			return IOGiven;
		}else if(CheckA&&!CheckB){
			return OutputDefault;
		}else if(!CheckA&&CheckB){
			return InputDefault;
		}
	}
}

int main() {

	return 0;
}
