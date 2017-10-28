// iterationxmastree.cpp: Definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"
#include <iostream>

int AskForN() {
	using namespace std;
		cout << "Podaj wysokosc choinki:"<<endl;

	int h; cin >> h; cout << endl;
	return h;
}

void DrawTree(int n) {
		using namespace std;
	
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n+i-1; j++) {

				if(j <= n - i) {
					cout << " ";
				}else{
					cout << "|";
				}
			}
				cout << endl;
			if (i == n) {
				for (int j = 1; j <= n; j++) {
					if (j == n) {
						cout << "|";
						cout << endl;
					}else {
						cout << " ";
					}
				}
			}
		}
	}

int main()
{
	DrawTree(AskForN());
    return 0;
}

