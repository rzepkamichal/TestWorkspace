#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
string znajdz_najdluzszy(vector<string> &podciagi){
	string max=podciagi[0];
	for(int i=0;i<podciagi.size();i++){
		if (podciagi[i].length()>max.length()){
			max=podciagi[i];
		}
	}
	return max;
}

string podciag(string &one,string& two){
	vector<string> podciagi;

	for(int i=0;i<one.length();i++){
		for(int j=0;j<two.length();j++){

		}
	}

}

void najdluzszy (const string &inputName,const string &outputName){
	ifstream iFile(inputName);
	ofstream oFile(outputName);
	string line;
	stringstream lineStream;
	string one, two;
	string ciag;

	while(getline(iFile,line)){
		lineStream(line);
		lineStream>>one;
		lineStream>>two;
		ciag=podciag(one,two);
	}
}

int main() {

	return 0;
}
