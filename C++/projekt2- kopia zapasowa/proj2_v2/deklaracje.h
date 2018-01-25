#ifndef PROJ2_V2_DEKLARACJE_H
#define PROJ2_V2_DEKLARACJE_H
#include <string>
#include <fstream>

using namespace std;
struct Node;
struct Nbr;
struct Path;
struct Solution;
struct SolutionId;

//element listy przechowujajcej infomacje o bezposrednich polaczeniach z danym wezlem
struct Nbr{
    Node *nbr;//wezel docelowy
    double distance;//odleglosc od wezla wyjsciowego
    Nbr *pNext;//wskaznik na nastepny element
};
//element listy przechowujacej wezly grafu i liste bezposrednich polaczen z sasiednimi wierzcholkami
struct Node{
    int id;//id wezla
    Nbr *nbrs;//lista palaczen z innymi wierchalkami- "sasiadami"
    Node *pNext;//wskaznik na nastepny element listy
};
//lista przechowujaca sciezke - tzn kolejne wezly sciezki i ich odleglosci od poprzedniego
struct Path{
    Node *node;
    double distance;
    Path *pNext;
};
struct SolutionId{
    int id;
    SolutionId *pNext;
};
// lista przechowujaca rozwiazania - wszystkie zamkniete sciezki zawierajace wszystkie wezly
struct Solution{
    SolutionId *ids;
    double sumDistance;
    Solution *pNext;
};

enum InputCase {ShowHelp, IOGiven};
enum ConnectionStatus { IsAlready, IsDifferent, NoConnection};

void pushBackNode(Node *&pHead, int id);
Node* getLast(Node *&pHead);
void addNbr(Node *&pHead, int nodeId, int nbrId, double distance);
void pushBackNbr(Nbr *&pHead, Node *node, double distance);
void removeNbrs(Nbr *&pHead);
void removeNodes(Node *&pHead);

ConnectionStatus findConnection(Node *&pHead, int firstNodeId, int secondNodeId, double distance);

bool IsNatural(string line);
bool isReal(string line);

InputCase ReadParams(int number, char *argv[], string &inputPath, string &outputPath);
bool addDataToList(Node *&pHead, string data);
bool ReadData(Node *&pHead, istream &iFile);

void pushBackId(SolutionId *&pHead, int id);

void addToPath(Path *&pHead, Node *&node, double distance);
void removeLastFromPath(Path *&pHead);
bool isEnclosedPath(Path *&pHead, int numOfNodes);
void removePath(Path *&pHead);
double sumDistances(Path *&pHead);
bool isOnPath(Path *&pHead, Nbr *&nbrHead);
void addPathToSolutions(Solution *&sHead, Path *&pHead, double sumDistance);
void seekPathForSingleNode(Nbr *&nHead, Solution *&sHead, Path *&pHead, int numOfNodes);
void seekPath(Node *&pHead, Solution *&sHead, int numOfNodes);


double countNodes(Node *&pHead);
void writeIds(SolutionId *pHead, ostream &out);
void writeSolutions(Solution *&pHead, ostream &out);
void writePath(Path *&pHead);
void writeNodeIds(Node *&pHead, ostream &out);
void writeConnections(Nbr *&pHead);
void writeNbrs(Node *&pHead);
void removeSolutionList(Solution *&pHead);
void removeIdList(SolutionId *&pHead);
void calculateSolution(Node *&nodesHead, Solution *&solutionsHead, ostream &out);
Solution* getShortest(Solution *&pHead);
#endif //PROJ2_V2_DEKLARACJE_H
