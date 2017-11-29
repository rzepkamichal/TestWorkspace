//============================================================================
// Name        : testing_streams.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;
struct ComplexNum{
	int root;
	double re;
	double im;
	double module=sqrt(re*re+im*im);
};
bool IsNatural(string &line){
	bool isNatural;
	bool isNotZero=false;
	for(int i=0;i<line.length();i++){
		if(line.at(i)>=48&&line.at(i)<=57){
			if(line.at(i)!='0'){
				isNotZero=true;
			}
			isNatural=true;
		}else{
			isNatural=false;
			break;
		}
	}
	return isNatural&&isNotZero;
}
bool IsComplexNumber(string &line){
	bool isComplex;
	bool imGiven=false;
	bool reGiven=false;
	bool operatorExpected=false;
	for(int i=0;i<line.length();i++){
		if(i<line.length()-1&&operatorExpected&&(line.at(i)=='-'||line.at(i)=='+')&&line.at(i+1)!='-'&&line.at(i+1)!='+'){
			operatorExpected=false;
			continue;
		}else if(operatorExpected&&(line.at(i)!='-'||line.at(i)!='+')){
			return false;
		}else if((line.at(i)=='-'||line.at(i)=='+')){
			continue;
		}else if(line.at(i)=='i'&&!imGiven){
			imGiven=true;
			operatorExpected=true;
			continue;
		}else if(isdigit(line[i])){
			int j=i+1;
			while(j<line.length()&&isdigit(line[j])){
				j++;
			}
			i=j-1;

			if(!imGiven&&i<line.length()-1&&line.at(i+1)=='i'){
				imGiven=true;
				operatorExpected=true;
				i++;
				continue;
			}else if(!reGiven) {
				operatorExpected=true;
				reGiven=true;
				continue;
			}else{
				return false;
			}
		}else{
			return false;
		}
	}

	if(imGiven||reGiven){
		isComplex=true;
	}else{
		isComplex=false;
	}
	return isComplex;
}
bool CheckInput(string &line){
	bool isValid;
	string root;
	string complexNumber;
	stringstream lineStream(line);

	lineStream>>root;

	if(IsNatural(root)){
		string tmp;
		while(lineStream>>tmp){
			complexNumber.append(tmp);
		}
		if(IsComplexNumber(complexNumber)){
			isValid=true;
		}else{
			isValid=false;
		}
	}else{
		isValid=false;
	}

	return isValid;
}
ComplexNum GetValuesFromInput(string &line){
	stringstream lineStream(line);
	string root;
	lineStream>>root;
	string num;
	string tmp;
	while(lineStream>>tmp){
		num.append(tmp);
	}
	ComplexNum number;
	number.root=stoi(root);
	string re;
	string im;
	string value;
	bool reGiven=false;
	bool imGiven=false;
	string sign="+";
	for(int i=0;i<num.length();i++){
		if(num[i]=='-'){
			sign="-";
			continue;
		}else if(num[i]=='+'){
			sign="+";
			continue;
		}else if(isdigit(num[i])){
			value.push_back(num[i]);
			int j=i+1;
			while(isdigit(num[j])||(j<num.length()-1&&num[j]=='.'&&isdigit(num[j+1]))){
				value.push_back(num[j]);
				j++;
			}
			i=j-1;
			if(!imGiven&&num[i+1]=='i'){
				imGiven=true;
				im=sign+value;
				value.clear();
				continue;
			}else if(!reGiven){
				reGiven=true;
				re=sign+value;
				value.clear();
				continue;
			}
		}else if(num[i]=='i'&&!imGiven){
			im=sign+"1";
			imGiven=true;
			continue;
		}
	}

	if(!imGiven){
		number.im=0;
	}else{
		number.im=stod(im);
	}
	if(!reGiven){
		number.re=0;
	}else{
		number.re=stod(re);
	}

	return number;
}

int CheckCase(ComplexNum &number) {
	double re=number.re;
	double im=number.im;
	int occurence;
	if (re != 0 || im != 0) {
		if (re > 0 && im > 0) {
			occurence = 1;
		}
		if (re < 0 && im>0) {
			occurence = 2;
		}
		if (re > 0 && im < 0) {
			occurence = 3;
		}
		if (re == 0) {
			if (im > 0)
				occurence = 4;
			else
				occurence = 5;
		}
		if (im == 0) {
			if (re > 0)
				occurence = 6;
			else
				occurence = 7;
		}
	}
	else {
		occurence = 0;
	}
	return occurence;
}//funkcja sprawdza na podstawie wartoœci re oraz im, do jakiej æwiartki nale¿y arg g³ówny b¹dŸ na której pó³prostej uk³adu wspó³rzêdnych siê on znajduje
double FindAlpha(int occurence, ComplexNum &number) {
	double re=number.re;
	double im=number.im;
	double module=number.module;
	double alpha;
	switch (occurence) {
	case 0: alpha = acos(-1) + 1; break;
	case 1: alpha = asin(im / module); break;
	case 2: alpha = acos(-1) - asin(im / module); break;
	case 3: alpha = -acos(re / module); break;
	case 4: alpha = 0; break;
	case 5: alpha = acos(-1); break;
	case 6: alpha = acos(-1) / 2; break;
	case 7: alpha = -acos(-1) / 2; break;
	}
	return alpha;
}//na podstawie danych przekazanych przez funkcjê CheckCase, funkcja FindAlpha wyznacza argument g³ówny przy wykorzystaniu w³asnoœci funkcji cyklometrycznych
vector<double>CalculateRoot(double alpha, ComplexNum &number) {
	vector<double> solutions;
	double module=number.module;
	int root=number.root;
	module = pow(module, (1.0 / root));

	if (alpha == acos(-1) + 1) {
		solutions.push_back(0);
		solutions.push_back(0);
	}
	else {
		alpha = alpha / root;
		for (int i = 0; i < root; i++) {
			solutions.push_back(module*cos(alpha + (2 * acos(-1)*i / root)));
			solutions.push_back(module*sin(alpha + (2 * acos(-1)*i / root)));
		}
	}
	return solutions;
}
void WriteSolutions(ostream& stream,vector<double> &solutions) {
	if(solutions.size()==1){
		stream<<solutions[0]<<endl;
	}else{
		for(int i=0;i<solutions.size();i+=2){
			if(i==solutions.size()-2){
				stream<<solutions[i];
				if(solutions[i+1]>0){
					stream<<" + ";
					stream<<solutions[i+1]<<"i"<<endl;
				}else if(solutions[i+1]<0){
					stream<<" - ";
					stream<<abs(solutions[i+1])<<"i"<<endl;
				}else{
					stream<<endl;
				}
			}else{
				stream<<solutions[i];
				if(solutions[i+1]>0){
					stream<<" + ";
					stream<<solutions[i+1]<<"i"<<" LUB ";
				}else if(solutions[i+1]<0){
					stream<<" - ";
					stream<<abs(solutions[i+1])<<"i"<<" LUB ";
				}else{
					stream<<endl;
				}
			}
		}
	}
}
int main() {
	/*ifstream file("testing.txt");
	string line;
	getline(file,line);
	stringstream lineTmp(line);
	string root;
	lineTmp>>root;
	cout<<root<<endl;
	string re;
	lineTmp>>re;
	cout<<re<<endl;
	string sign;
	lineTmp>>sign;
	cout<<sign<<endl;
	string im;
	lineTmp>>im;
	cout<<im<<endl;
	string next;
	lineTmp>>next;
	cout<<next<<endl;*/

	/*string napis="3 +5i-4";
	stringstream napisStream(napis);
	vector <string> linia;
	string tmp;
	while (napisStream>>tmp){
		linia.push_back(tmp);
		linia.push_back("|");
	}

	for(int i=0;i<linia.size();i++){
		cout<<linia[i];
	}*/

/*string root="3";
string number="3 65.32+67.3462i";

ComplexNum compnum=GetValuesFromInput(number);

cout<<"re: "<<compnum.re<<endl;
cout<<"im: "<<compnum.im<<endl;
cout<<"root: "<<compnum.root<<endl;*/

	ComplexNum num={3,2,1};

	vector<double> soluts=CalculateRoot(FindAlpha(CheckCase(num),num),num);

	WriteSolutions(cout,soluts);

	return 0;
}
