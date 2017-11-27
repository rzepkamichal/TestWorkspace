//============================================================================
// Name        : testing_getline.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

int main() {

	ifstream file("test.txt");

	if(file.is_open()){
		cout<<"xd";
	}else{
		cout<<"FUCK";
	}
	string line;

	while(getline(file,line)){
			cout<<endl<<line;
	}

	//string line="   -5.3   6   3";
	//stringstream line2(line);

	//double n;

	//line2>>n;

	//cout<<n;

	//line2>>n;



	//while(getline(cin,line)){
		//cout<<line;
	//}

	//cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
