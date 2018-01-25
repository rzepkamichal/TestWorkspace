#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include "deklaracje.h"
using namespace std;

int main(int argc, char *argv[]) {
    string iPath, oPath;
    InputCase status = ReadParams(argc, argv, iPath, oPath);

    Node *nodesHead = nullptr;
    Solution *solutionHead = nullptr;

    ifstream iFile(iPath);
    ofstream oFile(oPath);

    switch(status){
        case IOGiven:
            if(ReadData(nodesHead, iFile)){
                calculateSolution(nodesHead, solutionHead, oFile);
                cout << "Gotowe!" << endl;
            }else{
                cout << "Wprowadzono bledne dane!" << endl;
            }
            break;
        case ShowHelp:
            cout << "Blad! Mozliwe przyczyny:" << endl;
            cout << "- poproszono o pomoc" <<endl;
            cout << "- wprowadzono bledne parametry" << endl;
            cout << "- wprowadzono bledne sciezki do plikow" << endl;
            break;
    }

    removeNodes(nodesHead);
    removeSolutionList(solutionHead);
    return 0;
}

/* */

/*Node *nodesHead = nullptr;
    Solution *solutionHead = nullptr;

    ofstream oFile("C:\\Users\\sysoper\\Desktop\\wyniki.txt");

    ifstream iFile("C:\\Users\\sysoper\\Desktop\\dev\\Michal-Rzepka-gr02-repo\\projekt-02\\proj2_v2\\dat\\iFile.txt");

    ReadData(nodesHead, iFile);

    calculateSolution(nodesHead, solutionHead, oFile);
    writeNodeIds(nodesHead,cout);
    cout << endl;
    writeNbrs(nodesHead);
    removeNodes(nodesHead);
    removeSolutionList(solutionHead);*/