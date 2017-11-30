//============================================================================
// Name        : testing_roots.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

struct ComplexNum{
	int root;
	double re;
	double im;
};

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
	case 4: alpha = asin(1); break;
	case 5: alpha = asin(-1); break;
	case 6: alpha = 0; break;
	case 7: alpha = acos(-1); break;
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
	double pi=acos(-1);
	int coefficient=100000;
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
			solutions.push_back(round(coefficient*module*cos(alpha + (2 *pi*i / number.root)))/coefficient);
			solutions.push_back(round(coefficient*module*sin(alpha + (2 *pi*i / number.root)))/coefficient);
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
				stream<<"Z = "<<solutions[i];
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
				stream<<"Z = "<<solutions[i];
				if(solutions[i+1]>0){
					stream<<" + ";
					stream<<solutions[i+1]<<"i"<<"  LUB  ";
				}else if(solutions[i+1]<0){
					stream<<" - ";
					stream<<abs(solutions[i+1])<<"i"<<"  LUB  ";
				}else{
					stream<<"  LUB  ";
				}
			}
		}
	}
}

int main() {
	ComplexNum number{3, -3.324, 0};

	vector<double> solutions=CalculateRoot(FindAlpha(CheckCase(number),number),number);
	WriteSolutions(cout,solutions);


	return 0;
}
