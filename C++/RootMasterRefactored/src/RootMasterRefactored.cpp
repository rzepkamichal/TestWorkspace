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
// FOR TESTING ONLY
/*void WriteParams(vector<string>&params){
	for(int i=0;i<params.size();i++){
		cout<<endl<<params[i]<<endl;
	}
}*/
enum InputCase{IODefault,OutputDefault,InputDefault,HelpNeeded,IOGiven,WrongParams};


void SortParams(vector<string> &params, InputCase occurence){
	vector<string> tmp;
	for(int i=1;i<params.size();i++){
		if(occurence==OutputDefault&&params[i-1]=="-i"){
			tmp.push_back(params[i]); break;
		}else if(occurence==InputDefault&&params[i-1]=="-o"){
			tmp.push_back(params[i]); break;
		}else if(occurence==IOGiven&&params[i-1]=="-i"&&tmp.size()==0){
			tmp.push_back(params[i]);
			i=0;
		}else if(occurence==IOGiven&&params[i-1]=="-o"&&tmp.size()>0){
			tmp.push_back(params[i]);break;
		}
	}
	params.clear();
	params=tmp;
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
	bool CheckA,CheckB;
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
		}else{
			return WrongParams;
		}
	}
}
vector<string> ReadParams(int number, char *args[]){
	vector<string> tmp;
	for(int i=1;i<number;i++){
		tmp.push_back(args[i]);
	}
	return tmp;
}

int main(int argc, char *argv[]) {

	vector<string> params=ReadParams(argc,argv);

	switch(CheckParams(params)){
		case WrongParams:
			cout<<"Blad. Niepoprawne dane wejsciowe";
			break;
		case HelpNeeded:
			cout<<"HELP";//Zrobic funkcje "display help"
			break;
		case IOGiven:
			SortParams(params,IOGiven);//czytaj i pisz do pliku - stworzyc funkcje!
			cout<<"IOGIVEN!! yeah";
			break;
		case InputDefault:
			cout<<"Nie podano pliku wejsciowego."<<endl<<"Prosze wprowadzic dane ponize:"<<endl;
			SortParams(params,InputDefault);//stworzyc funkcje czytajaca z cmd i wpisujaca do pliku
			break;
		case OutputDefault:
			cout<<"Nie podano pliku wyjsciowego."<<endl<<"Wyniki zostana wyswietlone w konsoli"<<endl;
			SortParams(params,OutputDefault);
			break;//stworzyc funkcje czytajaca z pliku i wpisujaca do konsoli
		case IODefault:
			cout<<"Nie podano sciezek do plikow I/O."<<endl<<"Prosze podac dane wejsciowe ponizej:"<<endl;

	}

	//WriteParams(params);

	return 0;
}



















