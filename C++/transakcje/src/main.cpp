#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

int main(){

ifstream iFile;
iFile.open("C:\Users\sysoper\Desktop\dev\my_workspace\C++\transakcje\Debug\konta.txt");

 if(iFile.is_open());
	 cout<<"OPEN";
 }else{
	 cout<<"FUCK";
 }



	return 0;

}

