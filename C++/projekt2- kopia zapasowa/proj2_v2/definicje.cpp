#include "deklaracje.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void pushBackNode(Node *&pHead, int id){
    if(!pHead){
        pHead = new Node{ id, nullptr, nullptr };
    }else {
        pushBackNode(pHead-> pNext, id);
    }
}
Node* getLast(Node *&pHead){
    if(!pHead-> pNext){
        return pHead;
    }else{
        getLast(pHead-> pNext);
    }
}
void pushBackNbr(Nbr *&pHead, Node *node, double distance){
    if(!pHead){
        pHead = new Nbr{node, distance, nullptr};
    }else{
        pushBackNbr(pHead-> pNext, node, distance);
    }
}
void addNbr(Node *&pHead, int nodeId, int nbrId, double distance){
    bool nodeExists = false;
    bool nbrNodeExists = false;
    auto *tmpHead = pHead;

    while(tmpHead){
        if(tmpHead-> id == nodeId){
            nodeExists = true;
            break;
        }else{
            tmpHead = tmpHead-> pNext;
        }
    }
    auto *pNode = tmpHead;
    tmpHead = pHead;

    while(tmpHead){
        if(tmpHead-> id == nbrId){
            nbrNodeExists = true;
            break;
        }else{
            tmpHead = tmpHead-> pNext;
        }
    }
    auto *pNbrNode = tmpHead;
    tmpHead = pHead;

    if(!nodeExists){
        pushBackNode(pHead, nodeId);
        pNode = getLast(pHead);
    }
    if(!nbrNodeExists){
        pushBackNode(pHead, nbrId);
        pNbrNode = getLast(pHead);
    }
    pNode-> nbrs;
    auto *tmpNbrsHead = pNode-> nbrs;

    pushBackNbr(tmpNbrsHead, pNbrNode, distance);
    pNode-> nbrs = tmpNbrsHead;
}

void removeNbrs(Nbr *&pHead){
    if(!pHead->pNext){
        delete pHead;
    }else{
        removeNbrs(pHead-> pNext);
        delete pHead;
    }
}
void removeNodes(Node *&pHead){
    if(!pHead){
        return;
    }
    if(!pHead->pNext){
        if(pHead-> nbrs){
            removeNbrs(pHead-> nbrs);
        }
        delete pHead;
    }else{
        removeNodes(pHead-> pNext);
        if(pHead-> nbrs){
            removeNbrs(pHead-> nbrs);
        }
        delete pHead;
    }
}
ConnectionStatus findConnection(Node *&pHead, int firstNodeId, int secondNodeId, double distance){

    bool theSameConnection = false;
    bool theSameDistance = false;
    auto *head = pHead;

    while(head){
        if(head-> id == firstNodeId) {
            auto *nbrsHead = head->nbrs;
            while (nbrsHead) {
                if (nbrsHead->nbr->id == secondNodeId) {
                    theSameConnection = true;
                    if (nbrsHead->distance == distance) {
                        theSameDistance = true;
                        break;
                    }
                }
                nbrsHead = nbrsHead->pNext;

            }
            break;
        }
        head = head-> pNext;
    }

    if(theSameConnection){
        if(theSameDistance){
            return IsAlready;
        }else{
            return IsDifferent;
        }
    }else{
        return NoConnection;
    }

}

bool IsNatural(string line){

    bool isNatural;
    bool isNotZero = false;
    for (int i = 0; i < line.length(); i++)
    {
        if (line.at(i) >= 48 && line.at(i) <= 57)
        {
            if (line.at(i) != '0')
            {
                isNotZero = true;
            }
            isNatural = true;
        }
        else
        {
            isNatural = false;
            break;
        }
    }
    return isNatural && isNotZero;
}
bool isReal(string line){
    if(IsNatural(line)){
        return true;
    }else{
        bool isReal;
        bool pointAppeared = false;
        bool isNotZero = false;
        for(int i = 0; i < line.length(); i++){
            if(i !=  0 && i != line.at(line.length()-1) && line.at(i) == '.' && !pointAppeared){
                pointAppeared = true;
            }else if(line.at(i) >= 48 && line.at(i) <= 57){
                if (line.at(i) != '0'){
                    isNotZero = true;
                }
                isReal = true;
            }else{
                isReal = false;
                break;
            }
        }
        return isReal && isNotZero;
    }
}

InputCase ReadParams(int number, char *argv[], string &inputPath, string &outputPath){
    string param;
    if(number == 1) {
        return ShowHelp;

    }else{
        if (number == 5){
            bool inputGiven = false;
            bool outputGiven = false;

            for(int i = 1; i < number; i++){
                param = argv[i];

                if(param == "-i" && i < number-1 && !inputGiven){
                    i++;
                    param = argv[i];
                    ifstream tmpInput(param);
                    if(tmpInput.is_open()){
                        inputPath = param;
                        inputGiven = true;
                        tmpInput.close();
                    }
                }

                if(param == "-d" && i < number-1 && !outputGiven){
                    i++;
                    param = argv[i];
                    fstream tmpOutput(param);
                    if(tmpOutput.is_open()){
                        outputPath = param;
                        outputGiven = true;
                        tmpOutput.close();
                    }
                }
            }

            if(inputGiven && outputGiven){
                return IOGiven;
            }else{
                return ShowHelp;
            }

        }else {
            return ShowHelp;
        }
    }
}
bool addDataToList(Node *&pHead, string data){
    bool isOneWay;
    int indexStartOfSecondNum,indexEndOfFirstNum,indexStartOfDistance,indexEndOfSecondNum;
    int firstNum, secondNum;
    double distance;

    for(int i = 1; i < data.length(); i++){//badamy pierwsza liczbe (lewy wezel)
        if(i < data.length()-1 && data.at(i) == '-' && isdigit(data.at(i+1))){
            isOneWay = false;
            indexStartOfSecondNum = i+1;
            indexEndOfFirstNum = i-1;
            break;
        }else if(i < data.length()-1 && data.at(i) == '-' && data.at(i+1) == '>'){
            isOneWay = true;
            indexStartOfSecondNum = i+2;
            indexEndOfFirstNum = i-1;
            break;
        }
    }
    if(IsNatural(data.substr(0,indexEndOfFirstNum+1))){//badamy druga liczbe (lewy wezel)
        firstNum = stoi(data.substr(0,indexEndOfFirstNum+1));

        for(int i = indexStartOfSecondNum; i < data.length(); i++) {
            if (data.at(i) == ':' && i > 0) {
                indexEndOfSecondNum = i - 1;
                break;
            }
        }
                if(IsNatural(data.substr(indexStartOfSecondNum,indexEndOfSecondNum - indexStartOfSecondNum+1))){
                    secondNum = stoi(data.substr(indexStartOfSecondNum,indexEndOfSecondNum-indexStartOfSecondNum+1));
                    if(indexEndOfSecondNum+2 < data.length() && isReal(data.substr(indexEndOfSecondNum+2))){
                        distance = stold(data.substr(indexEndOfSecondNum+2));
                        //<linia do testowani> cout << endl << "lewy: " << firstNum << endl << "prawy: " << secondNum << endl << "dystans: " << distance << endl;
                        if(isOneWay){
                            ConnectionStatus statusOneWay = findConnection(pHead, firstNum,secondNum,distance);
                            if(statusOneWay == IsAlready){
                                return true;
                            }else if(statusOneWay == IsDifferent){
                                return false;
                            }else if(statusOneWay == NoConnection) {
                                addNbr(pHead, firstNum, secondNum, distance);
                            }
                        }else{
                            ConnectionStatus statusThere, statusBack;
                            statusThere = findConnection(pHead, firstNum,secondNum,distance);
                            statusBack = findConnection(pHead, secondNum, firstNum,distance);

                            if(statusThere == IsAlready && statusBack == IsAlready){
                                return true;
                            }else if(statusThere ==IsDifferent || statusBack == IsDifferent){
                                return false;
                            }else if(statusThere == NoConnection && statusBack == NoConnection){
                                addNbr(pHead,firstNum,secondNum,distance);
                                addNbr(pHead,secondNum,firstNum,distance);
                            }else{
                                return false;
                            }
                        }
                        return true;
                    }else{
                        return false;
                    }
                }else{
                    return false;
                }


    }else{
        return false;
    }


}
bool ReadData(Node *&pHead, istream &iFile){

    string tmpLine; // przechowuje bezposrednio pobrana linie z bialymi znakami
    string safeLine; // przechowuje "urwane" czesci danych,  zeby dopisac je do nowej lini
    bool oneLineRead = false;
    bool readDataStarted = false;
    bool skipFirstBracket = false;
    while(getline(iFile,tmpLine)){
        oneLineRead = true;
        stringstream tmpStream(tmpLine); // sstream - za jego pomoca z linii zostana usuniete biale znaki
        string tmpString;//sluzy do przechowywania "kawalkow" odczytanych przez sstream
        string line;// przechowuje linie wyjsciowa juz bez bialych znakow

        line.append(safeLine);
        safeLine.clear();
        while(tmpStream >> tmpString){
                    line.append(tmpString);
        }

        while(line.length()){

            if(line.at(0) == '(' || skipFirstBracket){
                skipFirstBracket = false;
                readDataStarted = true;
                int indexBracketEnd;
                bool foundBracketEnd = false;

                for(int i = 1; i < line.length(); i++){
                    if(line.at(i) == ')'){
                        indexBracketEnd = i;
                        foundBracketEnd = true;
                        break;
                    }
                }

                if(foundBracketEnd){
                    foundBracketEnd = false;

                    if(indexBracketEnd + 1 < line.length() && line.at(indexBracketEnd + 1) == ','){
                        if(addDataToList(pHead, line.substr(1,indexBracketEnd - 1))){
                            line.erase(0,indexBracketEnd + 2);
                            readDataStarted = false;
                            continue;
                        }else{
                            return false;
                        }

                    }else{

                        if(iFile.eof()){
                            if(line.length() > indexBracketEnd +1 && addDataToList(pHead, line.substr(1,indexBracketEnd -1))){
                                line.erase(0,indexBracketEnd + 2);
                                readDataStarted = false;
                                continue;
                            }else if(addDataToList(pHead, line.substr(1,indexBracketEnd -1))){
                                readDataStarted = false;
                                return true;
                            }else{
                                return false;
                            }
                        }else{
                            safeLine = line;
                            line.clear();
                            continue;
                        }
                    }

                }else{
                    if(iFile.eof()){
                        return false;
                    }else{
                        safeLine = line;
                        line.clear();
                        continue;
                    }
                }

            }else{
                if(readDataStarted){
                    skipFirstBracket = true;
                    continue;
                }else{
                    return false;
                }
            }
        }

    }
    if(oneLineRead) {
        return true;
    }else{
        return false;
    }

}
void pushBackId(SolutionId *&pHead, int id){
    if(!pHead){
        pHead = new SolutionId{id, nullptr};
    }else{
        pushBackId(pHead-> pNext, id);
    }
}
void removeLastFromPath(Path *&pHead){
    if(!pHead){
        return;
    }
    if(!pHead-> pNext){
        delete pHead;
        pHead = nullptr;
    }else{
        removeLastFromPath(pHead-> pNext);
    }
}
bool isEnclosedPath(Path *&pHead, int numOfNodes){
    int count = 0;
    int idHead = pHead-> node-> id;
    auto *head = pHead;
    auto *headLast = pHead;
    while(head){
        count++;
        headLast = head;
        head = head-> pNext;
    }

    if(count == numOfNodes && headLast-> node-> id == idHead){
        return true;
    }else{
        return false;
    }
}
void addToPath(Path *&pHead, Node *&node, double distance){
    if(!pHead){
        pHead = new Path{node, distance, nullptr};
    }else{
        addToPath(pHead-> pNext, node, distance);
    }
}
void removePath(Path *&pHead){
    if(!pHead){
    return;
    }
    if(!pHead-> pNext){
        delete pHead;
        pHead = nullptr;
    }else{
        removePath(pHead-> pNext);
        delete pHead;
        pHead = nullptr;
    }
}
void addPathToSolutions(Solution *&sHead, Path *&pHead, double sumDistance){

    if(!sHead){
        sHead = new Solution{nullptr, sumDistance, nullptr};
        auto *tmpHead = pHead;
        while(tmpHead){
            pushBackId(sHead-> ids,tmpHead-> node-> id);
            tmpHead = tmpHead-> pNext;
        }

    }else{
        addPathToSolutions(sHead-> pNext, pHead, sumDistance);
    }
}
double sumDistances(Path *&pHead){
    double sum = 0;
    auto *head = pHead;

    while(head){
        sum += head-> distance;
        head = head-> pNext;
    }

    return sum;
}
bool isOnPath(Path *&pHead, Nbr *&nbrHead){

    auto *pathHead = pHead;
    while(pathHead){
        if(pathHead-> node-> id == nbrHead-> nbr-> id){
            return true;
        }
        pathHead = pathHead -> pNext;
    }
    return false;
}



void seekPathForSingleNode(Nbr *&nHead, Solution *&sHead, Path *&pHead, int numOfNodes){
    if(nHead){
        if(isOnPath(pHead,nHead)){
            addToPath(pHead,nHead-> nbr, nHead->distance);
            if(isEnclosedPath(pHead,numOfNodes + 1)){
                addPathToSolutions(sHead, pHead, sumDistances(pHead));
            }
            removeLastFromPath(pHead);
            seekPathForSingleNode(nHead-> pNext, sHead, pHead, numOfNodes);
        }else{
            addToPath(pHead, nHead-> nbr, nHead-> distance);
            seekPathForSingleNode(nHead-> nbr-> nbrs, sHead, pHead, numOfNodes);
            seekPathForSingleNode(nHead-> pNext, sHead, pHead, numOfNodes);
        }
    }else{

        if(isEnclosedPath(pHead, numOfNodes + 1)) {
            addPathToSolutions(sHead, pHead, sumDistances(pHead));
        }
        removeLastFromPath(pHead);
        return;
    }
}

void seekPath(Node *&pHead, Solution *&sHead, int numOfNodes){
    auto *nodesHead = pHead;
    while (nodesHead){ // powtarzaj dla kazdego wezla z listy

        if(nodesHead->nbrs) {
            Path *pathHead = new Path{nodesHead, 0, nullptr};
            seekPathForSingleNode(nodesHead->nbrs, sHead, pathHead, numOfNodes);
            removePath(pathHead);
        }

        nodesHead = nodesHead-> pNext;// przejdz do nastepnego wezla glownej listy
    }

}
double countNodes(Node *&pHead){
    int count = 0;
    auto *head = pHead;
    while(head){
        count++;
        head = head-> pNext;
    }
    return count;
}
void writeSolutions(Solution *&pHead, ostream &out){
    if(!pHead){
        out << endl << "brak!" << endl;
        return;
    }
    if(!pHead->pNext){
        out << "droga: ";
        writeIds(pHead-> ids, out);
        out <<"| dystans: " << pHead-> sumDistance;
        out << endl;
    }else{
        out << "droga: ";
        writeIds(pHead-> ids, out);
        out <<"| dystans: " << pHead-> sumDistance;
        out << endl;
        writeSolutions(pHead-> pNext, out);
    }
}
void writeIds(SolutionId *pHead, ostream &out){
    if(!pHead){
        out << "blad";
    }else {
        out << pHead->id << "  ";
        writeIds(pHead->pNext, out);
    }

}
void removeIdList(SolutionId *&pHead){
    if(!pHead){
        return;
    }
    if(!pHead-> pNext){
        delete pHead;
        pHead = nullptr;
    }else{
        removeIdList(pHead-> pNext);
        delete pHead;
        pHead = nullptr;
    }
}
void removeSolutionList(Solution *&pHead){
    if(!pHead){
        return;
    }
    if(!pHead-> pNext){
        removeIdList(pHead-> ids);
        delete pHead;
        pHead = nullptr;
    }else{
        removeSolutionList(pHead-> pNext);
        removeIdList(pHead-> ids);
        delete pHead;
        pHead = nullptr;
    }
}
void writeNodeIds(Node *&pHead, ostream &out){
    if(!pHead-> pNext){
        out << pHead-> id;
    }else{
        out << pHead-> id << endl;
        writeNodeIds(pHead-> pNext, out);
    }
}
void writeConnections(Nbr *&pHead){
    if(!pHead-> pNext){
        cout << "   wezel: " << pHead-> nbr-> id << ", odleglosc: " << pHead-> distance << endl;
    }else{
        cout << "   wezel: " << pHead-> nbr-> id << ", odleglosc: " << pHead-> distance << endl;
        writeConnections(pHead-> pNext);
    }
}
void writeNbrs(Node *&pHead){
    if(!pHead){
        return;
    }
    if(!pHead-> pNext){
        cout << pHead-> id << " : " << endl;
        if (!pHead->nbrs) {
            cout << "   brak sasiednich wezlow" << endl;
        }else {
            writeConnections(pHead-> nbrs);
        }
    }else {
        cout << pHead->id << " : " << endl;
        if (!pHead->nbrs) {
            cout << "   brak sasiednich wezlow" << endl;
        }else {
            writeConnections(pHead-> nbrs);
        }
        writeNbrs(pHead-> pNext);
    }
}
void writePath(Path *&pHead){
    if(!pHead-> pNext){
        cout << pHead-> node-> id << "   ";
    }else{
        cout << pHead-> node-> id << "   ";
        writePath(pHead-> pNext);

    }
}
Solution* getShortest(Solution *&pHead){
    auto *head = pHead;
    auto *tmpHead = pHead;
    if(head){
        double min = head-> sumDistance;
        head = head-> pNext;
        while(head){
            if(head-> sumDistance < min){
                min = head-> sumDistance;
                tmpHead = head;
            }
            head = head-> pNext;
        }
    }
    return tmpHead;
}
void calculateSolution(Node *&nodesHead, Solution *&solutionsHead, ostream &out){
    seekPath(nodesHead, solutionsHead, countNodes(nodesHead));
    Solution *theShortest = getShortest(solutionsHead);
    if(theShortest){
        writeIds(theShortest-> ids,out);
        out << "| dystans: " << theShortest-> sumDistance;
    }else{
        out << "nie znaleziono drog spelniajacych wymagania!";
    }

}

















