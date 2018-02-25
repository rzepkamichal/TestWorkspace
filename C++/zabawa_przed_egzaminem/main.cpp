#include <iostream>
#include <vector>
#include <cmath>
#include <afxres.h>
#include <fstream>
#include <iomanip>

using namespace std;




int main() {

    ofstream plik("C:\\Users\\sysoper\\Desktop\\output.txt");

    for(int i = 0; i < 68; i ++){

        if((i+1)%10 == 0 && i < 67){
            plik << endl;
        }

        plik <<  (i+1) << setw(7);
    }


    return 0;
}