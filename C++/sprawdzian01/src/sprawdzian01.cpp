
#include <iostream>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <istream>
using namespace std;

bool check(const string &name) {
	ifstream file (name);
	vector<string> lines;
	bool check1;
	string tmp;
	while(getline(file,tmp)){
		lines.push_back(tmp);
	}

	for(int i=0;i<lines.size();i++){
		for(int j=0;j<lines[i].length();j++){
			cout<<lines[i].at(j);
		}
		cout<<endl;
	}




	/*for(int i=0;i<lines.size();i++){
		for(int j=0;j<lines[i].length();j++){

		}
	}*/
}

int main() {
	string name="input.txt";
	check(name);
	return 0;
}
