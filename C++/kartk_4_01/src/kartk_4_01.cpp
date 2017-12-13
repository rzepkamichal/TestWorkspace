//============================================================================
//
//
//
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

struct osoba{
	string imie;
	int wiek;
	int wzrost;
	int liczba_glosow;
};

osoba najmniejszy(vector<osoba> &osoby, int *funkcja(osoba,osoba)){
	osoba min=osoby[0];
		for(int i=1;i<osoby.size();i++){
			if(funkcja(min,osoby[i])==1){
				min=osoby[i];
			}
		}
		return min;
}

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
