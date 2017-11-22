// RootMaster.cpp : by Michal Rzepka

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include<string>

using namespace std;

enum InputCase {DefaultIO=1,DefaultInput=2,DefaultOutput=3,IOGiven=4,HelpParam=5,WrongParams=6};//lista wyliczeniowa zawieraj±ca etykiety nazw dla poszczególnych przypadków danych wpisanych przez u¿ytkownika jako prze³±czniki

int CheckCase(double re, double im) {
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
}//funkcja sprawdza na podstawie warto¶ci re oraz im, do jakiej æwiartki nale¿y arg g³ówny b±d¼ na której pó³prostej uk³adu wspó³rzêdnych siê on znajduje
double FindAlpha(int occurence, double re, double im, double &module) {
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
}//na podstawie danych przekazanych przez funkcjê CheckCase, funkcja FindAlpha wyznacza argument g³ówny przy wykorzystaniu w³asno¶ci funkcji cyklometrycznych
vector<double> CalculateRoot(double alpha, double &module, int root) {
	vector<double> solutions;
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
}//Funkcja FindAlpha przekazuje do funkcji CalculateRoot argument g³ówny. Na tej podstawie, funkcja wyznacza pierwiastki liczby zespolonej. (Na podstawie w³asno¶ci liczby zespolonej w postaci trygonometrycznej oraz twierdzenia De Moivre'a)
void WriteSolutions(vector<double> solutions, int root) {
	if (solutions[0] == 0 && solutions[1] == 0) {
		cout << "Z= 0";
	}
	else {
		for (int i = 0; i < 2 * root - 1; i += 2) {
			cout << "Z= " << solutions[i] << " + " << solutions[i + 1] << "i";
			cout << endl;
		}
	}
}//Funkcja wypisuje na wyj¶cie standardowe wyniki przekazane jako argument przez funkcjê CalculateRoot

int InteprateParams(int number, vector<string> &arg) {//funkcja odczytuj±ca prze³±czniki podane przez u¿ytkownika i okre¶laj±ca przypadek
	int occurence;
	ifstream file;

	if (number == 1 || (number == 3 && ((arg[1] == "-i" && arg[2] == "-o") || (arg[2] == "-i" && arg[1] == "-o"))))
    {//brak parametrów lub "-i -o" lub "-o -i"
		occurence = DefaultIO;
	}
	else if (number == 5 && ((arg[1] == "-o" && arg[3] == "-i") || (arg[3] == "-o" && arg[1] == "-i")) && arg[2] != arg[4]) {//oczekiwane parametry "-i sciezka1 -o sciezka2" lub "-o sciezka1 -i sciezka2"
		file.open(arg[2]);
		if (file.is_open())
        {
			file.close();
			file.open(arg[4]);
			if (file.is_open())
            {
				file.close();
				occurence = IOGiven;
			}
			else
            {
				occurence = WrongParams;
			}
		}
		else
        {
			occurence = WrongParams;
		}
	}
	else if ((number == 4 && ((arg[1] == "-i"&&arg[2] == "-o")||(arg[1]=="-o"&&arg[3]=="-i")))||(number==3&&arg[1]=="-o")) {//parametrwy w postaci "-i -o sciezka" lub "-o sciezka -i"
		file.open(arg[2]);
		if (file.is_open()) {
			occurence = DefaultInput;
			file.close();
		}else {
			file.close();
			file.open(arg[3]);
			if (file.is_open()) {
				occurence = DefaultInput;
			}
			else {
				occurence = WrongParams;
			}
		}
	}
	else if ((number == 4 && ((arg[1] == "-i"&&arg[3] == "-o") || (arg[1] == "-o"&&arg[2] == "-i")))||(number==3&&arg[1]=="-i")) {//parametry w postaci "-o -i sciezka" lub "-i sciezka -o" lub "-i sciezka"
		file.open(arg[2]);
		if (file.is_open()) {
			occurence = DefaultOutput;
			file.close();
		}
		else {
			file.close();
			file.open(arg[3]);
			if (file.is_open()) {
				occurence = DefaultOutput;
			}
			else {
				occurence = WrongParams;
			}
		}
	}
	else if (number == 2 && arg[1] == "-h") {
		occurence = HelpParam;
	}
	else {
		occurence = WrongParams;
	}
	return occurence;
}
void HandleIfDefaultIO() {//funkcja wykonywana, gdy u¿ytkownik nie poda prze³±czników okre¶laj±cych ¶ciê¿kê I/O
	cout << "Nie wskazano plikow I/O" << endl;
	//Sleep(1000);
	cout << "Program zapyta o dane wejsciowe." << endl;
	int root;
	double re, im,module;
	//Sleep(2000);
	cout << "Prosze podac stopien pierwiastka:" << endl;
	cin >> root;
	cout << "Prosze podac czesc rzeczywista" << endl;
	cin >> re;
	cout << "Prosze podac czesc urojona:" << endl;
	cin >> im;
	module = sqrt(im*im + re*re);
	WriteSolutions(CalculateRoot(FindAlpha(CheckCase(re, im), re, im, module), module, root), root);

}
void HandleIfDefaultInput(vector<string> &arg) {//funkcja wykonywana, gdy u¿ytkownik nie poda prze³±cznika okre¶laj±cego ¶cie¿kê Input
	cout << "Nie wskazano pliku, z ktorego beda czytane dane." << endl;
	//Sleep(1000);
	cout << "Program zapyta o dane wejsciowe." << endl;
	int root;
	double re, im, module;
	//Sleep(2000);
	cout << "Prosze podac stopien pierwiastka:" << endl;
	cin >> root;
	cout << "Prosze podac czesc rzeczywista:" << endl;
	cin >> re;
	cout << "Prosze podac czesc urojona:" << endl;
	cin >> im;
	module = sqrt(im*im + re*re);

	ofstream file;

	if (arg[2] == "-o") // znowu sa sprawdzene parametry!
    {
		file.open(arg[3]);
	}else {
		file.open(arg[2]);
	}
	vector<double> solutions=CalculateRoot(FindAlpha(CheckCase(re, im), re, im, module), module, root);
	if (solutions[0] == 0 && solutions[1] == 0) {
		file << "Z= 0";
	}else {
		for (int i = 0; i < 2 * root - 1; i += 2) {
			file << "Z= " << solutions[i] << " + " << solutions[i + 1] << "i";
			file << endl;
			file << endl;
		}
	}
	file.close();
	cout << "Wyniki zapisano w podanym pliku";
}
void HandleIfDefaultOutput(vector<string> &arg) {//funkcja wykonywana, gdy u¿ytnkownik nie poda prze³±cznika okre¶laj±cego ¶cie¿kê Output
	cout << "Nie podano pliku wyjsciowego." << endl;
	//Sleep(1000);
	cout << "Wyniki zostana wyswietlone w konsoli." << endl;
	//Sleep(2000);
	ifstream file;
	if (arg[2] == "-i") {
		file.open(arg[3]);
	}
	else {
		file.open(arg[2]);
	}

	int root;
	double re, im, module;
	file >> root;
	file.ignore();
	file >> re;
	file.ignore();
	file >> im;
	file.close();

	module = sqrt(im*im + re*re);
	WriteSolutions(CalculateRoot(FindAlpha(CheckCase(re, im), re, im, module), module, root), root);

}//! narazie wszystkie dane wejsciowe traktowane sa jako pojedyncze znaki!
void HandleIfGiven(vector<string> &arg) {//funkcja wykonywana, gdy u¿ytkownik poprawnie poda wszystkie parametry okre¶laj±ce ¶cie¿ki I/O
	ifstream iFile;
	ofstream oFile;

	if (arg[1] == "-i") {
		iFile.open(arg[2]);
		oFile.open(arg[4]);
	}
	else {
		iFile.open(arg[4]);
		oFile.open(arg[2]);
	}

	int root;
	double re, im, module;

	iFile >> root;

	iFile >> re;

	iFile >> im;

	module = sqrt(im*im + re*re);
	vector<double> solutions = CalculateRoot(FindAlpha(CheckCase(re, im), re, im, module), module, root);

	if (solutions[0] == 0 && solutions[1] == 0) {
		oFile << "Z= 0";
	}
	else {
		for (int i = 0; i < 2 * root - 1; i += 2) {
			oFile << "Z= " << solutions[i] << " + " << solutions[i + 1] << "i";
			oFile << endl;
			oFile << endl;
		}
	}

	iFile.close();
	oFile.close();

}
void HandleFileStream(int value,vector <string> &arg) {//na podstawie warto¶ci przekazanej z funkcji InteprateParams, funkcja HandleFileStream wywo³uje odpowiednie funkcje
	switch (value) {
	case DefaultIO: HandleIfDefaultIO();
		break;
	case DefaultInput: HandleIfDefaultInput(arg);
		break;
	case DefaultOutput: HandleIfDefaultOutput(arg);
		break;
	case IOGiven: HandleIfGiven(arg);
		break;
	case HelpParam: cout << "Help"; break;
	case WrongParams: cout << "Blad. Prosze wprowadzic poprawne dane!"; break;
	default:cout << "Blad. Cos poszlo nie tak.";
	}
}


int main(int argc, char *argv[])
{
    // cala komunikacja z uzytkownkiem

    // kominikaty, gdy niepoprawne parametry

	vector<string> args;//wektor typu string przechowuj±cy parametry podane przez u¿ytkownika
	for (int i = 0; i < argc; i++) {//wype³nienie wektora odpowiednimi warto¶ciami
		args.push_back(argv[i]);
	}
	HandleFileStream(InteprateParams(argc,args),args);//wywo³anie funkcji opisanych powy¿ej
    return 0;

    // sprawdzenie argumentow

    // jezeli argumenety da ok
    // czytamy linia po linii   (getlinie(plik, linia) dla ifstream plik, jezeli standardowe IO, getline(cin, linia)
    //   dla kazdej linii odczytujemy wartosic
    //   ... i przekazujemy do funkcji wyznaczajacej pierwiastki
    //   zapisujemy do pliku wynikowego  // jezeli jest plik, to plik << wynik, jezeli standardowe IO: cout << wynik

    // finito!

}







