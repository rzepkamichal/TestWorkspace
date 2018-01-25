#include <iostream>
#include <fstream>
using namespace std;

int main() {

    ifstream iFile;
    iFile.open("C:\\Users\\sysoper\\Desktop\\dev\\my_workspace\\C++\\testing_TSP_Iput\\file.txt");

    string napis;

    bool flaga = iFile.is_open();

    iFile >> napis;

    cout << napis;

    return 0;
}