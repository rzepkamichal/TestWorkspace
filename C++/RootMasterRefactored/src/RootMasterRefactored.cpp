#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
/*
 * Enumerator InputCase
 * Zawiera etykiety nadane przypadkom wystepowania parametrow podanych przy uruchamianiu
 * IODefault- uzytkownik nie podal sciezek IO
 * OutPutDefault- uzytkownik nie podal sciezki wyjscia
 * InputDefault- uzytkonik nie podal sciezki wejsci
 * IOGiven- uzytkownik podal poprawne sciezki wej/wyj
 * HelpNeeded- uzytkownik podal bledne parametry lub uzyl przelacznika -h w celu uzyskania pomocy
 */
enum InputCase{IODefault,OutputDefault,InputDefault,HelpNeeded,IOGiven};
/*
 * Struktura ComplexNum
 * Reprezentuje liczbe zespolona pod pierwiastkiem
 * Jej sk³adowe przechowuja kolejno: stopien pierwiastka, czesc rzeczywista, czesc urojona
 */
struct ComplexNum{
	int root;
	double re;
	double im;
};

//FUNKCJE WYKONUJACE OBLICZENIA MATEMATYCZNE

/*Funkcja CheckCase
 * Jej argumentem jest obiekt typu ComplexNum
 * Na podstawie skladowych obiektu ComplexNum wyznaczany jest przypadek matematyczny (omowione w sprawozdaniu)
 * Funkcja zwraca typ int (zmienna occurence, ktora moze przechowywac wartosc od 0-7)
 */
int CheckCase(ComplexNum number) {
	double re=number.re;
	double im=number.im;
	int occurence;
	if (re != 0 || im != 0) {
		if (re > 0 && im > 0) {
			occurence = 1;
		}
		if (re < 0 && im > 0) {
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
/*Funkcja FindAlpha
 *Na podstawie skladowych obiektu ComplexNum i przypadku zwroconego z funkcji CheckCase
 *funkcja oblicza argument glowny liczby zespolonej (double alpha), ktory nastepnie jest zwracany
 */
double FindAlpha(int occurence, ComplexNum number) {
	double module=sqrt(number.re*number.re+number.im*number.im);
	double alpha;
	switch (occurence) {
	case 0: alpha = acos(-1) + 1; break;
	case 1: alpha = asin(number.im / module); break;
	case 2: alpha = acos(-1) - asin(number.im / module); break;
	case 3: alpha = -acos(number.re / module); break;
	case 4: alpha = 0; break;
	case 5: alpha = acos(-1); break;
	case 6: alpha = acos(-1) / 2; break;
	case 7: alpha = -acos(-1) / 2; break;
	}
	return alpha;
}//na podstawie danych przekazanych przez funkcjê CheckCase, funkcja FindAlpha wyznacza argument g³ówny przy wykorzystaniu w³asnoœci funkcji cyklometrycznych
/*Funkcja CalculateRoot
 * Na podstawie skladowych obiektu ComplexNum oraz przekazanego argumentu glownego (double alpha)
 * funkcja oblicza kolejne pierwiastki i przechowuje je w obiekcie vector<double> solutions
 * Pod indeksami parzystymi zapisywane sa czesci rzeczywiste kolejnych pierwiastkow.
 * Pod indeksami nieparzystymi zapisywane sa czesci urojone kolejnych pierwiastkow.
 */
vector<double>CalculateRoot(double alpha, ComplexNum &number) {
	vector<double> solutions;
	double module=sqrt(number.re*number.re+number.im*number.im);
	module = pow(module, (1.0 / number.root));
	if(number.root==1){
		solutions.push_back(number.re);
		solutions.push_back(number.im);
	}else if (alpha == acos(-1) + 1) {
		solutions.push_back(0);
		solutions.push_back(0);
	}
	else {
		alpha = alpha / number.root;
		for (int i = 0; i < number.root; i++) {
			solutions.push_back(module*cos(alpha + (2 * acos(-1)*i / number.root)));
			solutions.push_back(module*sin(alpha + (2 * acos(-1)*i / number.root)));
		}
	}
	return solutions;
}//Funkcja FindAlpha przekazuje do funkcji CalculateRoot argument g³ówny. Na tej podstawie, funkcja wyznacza pierwiastki liczby zespolonej. (Na podstawie w³asnoœci liczby zespolonej w postaci trygonometrycznej oraz twierdzenia De Moivre'a)

//INTERPRETACJA DANYCH I WYSWIETLANIE WYNIKOW

void WriteSolutions(ostream &stream,vector<double> &solutions) {
	if(solutions.size()==1){
		stream<<solutions[0]<<endl;
	}else{
		for(int i=0;i<solutions.size();i+=2){
			if(i==solutions.size()-2){
				stream<<"Z= "<<solutions[i];
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
				stream<<"Z= "<<solutions[i];
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
bool IsEmpty(string &line){
	bool isEmpty=true;
	for(int i=0;i<line.length();i++){
		if(iswspace(line[i])){
			continue;
		}else{
			isEmpty=false;
			break;
		}
	}
	return isEmpty;
}
bool IsValidPath(string &path){
	fstream file;
	file.open(path);
	if(file.is_open()){
		file.close();
		return true;
	}else{
		file.close();
	}	return false;
}
bool IsValidParam(string &param){
	if(param=="-o"||param=="-i")
		return true;
	else
		return false;
}
InputCase CheckParams(vector<string> &params,vector<string> &filePaths){
	bool inputGiven=false,outputGiven=false;
	if(params.size()==0||((params.size()==1&&IsValidParam(params[0]))||(params.size()==2&&IsValidParam(params[0])&&IsValidParam(params[1])))){
		return IODefault;
	}else if(params.size()==1&&params[0]=="-h"){
		return HelpNeeded;
	}else{
		for(int i=0;i<params.size()-1;i++){
			if(params[i]=="-i"&&IsValidPath(params[i+1])){
				inputGiven=true;
				filePaths.push_back(params[i+1]);
				if(outputGiven){
					string tmp=filePaths[0];
					filePaths.clear();
					filePaths.push_back(params[i+1]);
					filePaths.push_back(tmp);
				}
			}
			if(params[i]=="-o"&&IsValidPath(params[i+1])){
				outputGiven=true;
				filePaths.push_back(params[i+1]);
			}
		}
		if(inputGiven&&outputGiven){
			return IOGiven;
		}else if(inputGiven&&!outputGiven){
			return OutputDefault;
		}else if(!inputGiven&&outputGiven){
			return InputDefault;
		}else{
			return HelpNeeded;
		}
	}
}
vector<string> ReadParams(int number, char *args[]){
	vector<string> params;
	for(int i=1;i<number;i++){
		params.push_back(args[i]);
	}
	return params;
}
bool AreNoForbiddenSigns(string &line){
	bool areNoForbiddenSigns;
	for(int i=0;i<line.length();i++){
		if(line.at(i)=='+'||line.at(i)=='-'||line.at(i)=='i'||line.at(i)=='.'||(line.at(i)>=48&&line.at(i)<=57)||iswspace(line.at(i))){
			areNoForbiddenSigns=true;
		}else{
			areNoForbiddenSigns=false;
			break;
		}
	}
	return areNoForbiddenSigns;
}
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
			while((j<line.length()&&isdigit(line[j]))||(j<line.length()-1&&line[j]=='.'&&isdigit(line[j+1]))){
				j++;
			}
			i=j-1;

			if(!imGiven&&i<line.length()-1&&(line.at(i+1)=='i'||line.at(i+1)=='0')){
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
bool Calculate(istream &in,ostream &out){
	string input;
	vector <double> solutions;
	ComplexNum number;
	while(getline(in,input)){
		if(IsEmpty(input)){
			continue;
		}
		if(AreNoForbiddenSigns(input)){
			if(CheckInput(input)){
				number=GetValuesFromInput(input);
				solutions=CalculateRoot(FindAlpha(CheckCase(number),number),number);
				WriteSolutions(out,solutions);
				solutions.clear();
			}else{
				return false;
			}

		}else{
			return false;
		}
	}
	return true;
}
int main(int argc, char *argv[]) {
	vector<string> params=ReadParams(argc,argv);
	vector<string> filePaths;
	InputCase occurence=CheckParams(params,filePaths);

	// OSTATECZNIE PONIZEJ ZNAJDZIE SIE SWITCH, (jest if bo wczesnie byly problemy ze switchem)
	if(occurence==IOGiven){
			ifstream iFile(filePaths[0]);
			ofstream oFile(filePaths[1]);
			if(Calculate(iFile,oFile)){
			}else{
				cout<<"Blad! Wprowadzono bledne dane.";
				oFile.clear();
			}
			iFile.close();
			oFile.close();
		}else if(occurence==OutputDefault){
			ifstream iFile(filePaths[0]);
			if(Calculate(iFile,cout)){
			}else{
				cout<<"Blad! Nie mozna ukonczyc obliczen. Napotkano bledne dane w pliku.";
			}
			iFile.close();
		}else if(occurence==InputDefault){
			ofstream oFile(filePaths[0]);
			if(Calculate(cin,oFile)){
			}else{
				cout<<"Blad! Wprowadzono bledne dane.";
			}
			oFile.close();
		}else if(occurence==IODefault){
			if(Calculate(cin,cout)){
			}else{
				cout<<"Blad! Wprowadzono bledne dane.";
			}
		}else if(occurence==HelpNeeded){
				cout<<endl<<"Zapytano o pomoc lub program uruchomiono nieprawidlowo"<<endl;
				cout<<"Mozliwe dane uruchomieniowe:"<<endl;
				cout<<"RootMaster -h --wyswietl pomoc."<<endl;
				cout<<"RootMaster -i <we> -o <wyj>  --<we>-sciezka pliku wejsciowego, <wyj>-sciezka pliku wyjsciowego"<<endl;
				cout<<"RootMaster -i <we> --<we> sciezka pliku wejsciowego, wyjscie jest standardowe"<<endl;
				cout<<"RootMaster -o <wyj> --wejscie jest standardowe, <wyj>-sciezka pliku wyjsciowego"<<endl;
				cout<<"RootMaster -i -o lub RootMaster --wejscie i wyjscie sa standardowe"<<endl;
				cout<<"Parametry -i oraz -o mozna uzywac naprzemienie"<<endl;
		}
	return 0;
}















