#include "deklaracje.h"


void pushBack(Node *&pHead, int id){

    if(!pHead){

        pHead = new Node{ id, nullptr, nullptr };

    }else {

        pushBack(pHead-> pNext, id);

    }
}

Node* getLast(Node *&pHead){
    if(!pHead-> pNext){
        return pHead;
    }else{
        getLast(pHead-> pNext);
    }
}

void pushBackNbr(Node *&pHead, int nodeId, int nbrId){
    bool nodeExists = false;
    bool nbrNodeExists = false;
    auto *head = pHead;

    //sprawdzam, czy podany wezel glowny istnieje
    while(head){
        if(head-> id == nodeId){
            nodeExists = true;
            break;
        }else{
            head = head-> pNext;
        }
    }

    auto *pNode = head;
    head = pHead;

    while(head){//sprawdzam, czy podany wezel sasiedni istnieje
        if(head-> id == nbrId){
            nbrNodeExists = true;
            break;
        }else{
            head = head-> pNext;
        }
    }

    auto *pNbrNode = head;
    head = pHead;

    cout << endl << nodeExists << endl;
    cout << endl << nbrNodeExists << endl;

    if(!nodeExists) { // jezeli wezel glowny nie istnieje, to dodaj go do istniejacej listy wezlow
        pushBack(pHead,nodeId);
        pNode = getLast(pHead);
    }

    if(!nbrNodeExists){//jezeli wezel sasiedni nie istnieje, to go dodaje
        pushBack(pHead, nbrId);
        pNbrNode = getLast(pHead);
    }

    pNode = pNode->nbrNext;


}

int countNodes(Node *pHead){

    int calculate = 0;
    while(pHead){
        calculate++;
        pHead = pHead-> pNext;
    }

    return calculate;
}

Node* getNode(Node *&pHead, int index){
    auto *node = pHead;
    for(int i = 0; i<index;i++){
        node = node-> pNext;
    }
    return node;
}

void writeNodes( Node *&pHead){

    if(!pHead-> pNext){
        cout << pHead-> id;
    }else{
        cout << pHead-> id << endl;
        writeNodes(pHead-> pNext);
    }
}

void writeIdList( IdList *&pHead){

    if(!pHead-> pNext){
        cout << pHead-> id << endl;
    }else{
        cout << pHead-> id << endl;
        writeIdList(pHead-> pNext);
    }
}

void writeNbrs(Node *&pHead){
    if(!pHead->pNext){
        cout << "Sasiedzi wezla " << pHead-> id << endl;
        writeNodes(pHead-> nbrNext);
        cout << endl;
    }else{
        cout << "Sasiedzi wezla " << pHead-> id << endl;
        writeNodes (pHead-> nbrNext);
        cout << endl;
        writeNbrs( pHead-> pNext);
    }
}

void removeIdList( IdList *&pHead){

    if(!pHead-> pNext){
        delete pHead;
    }else{
        removeIdList(pHead-> pNext);
        delete pHead;
    }
}

void removeNodes( Node *&pHead ){

    if(!pHead){
        delete pHead;
    }else{
        removeNodes(pHead-> pNext);
        delete pHead;
    }
}

bool readData(string data, Node *&nHead, Weights *&wHead, IdList *&idHead){

    bool leftNodeStarted = false;//zaczeto odczytywanie pierwszego wezla
    bool rightNodeStarted = false;//zaczeto odczytywanie drugiego wezla
    bool nodesRead = false;
    bool weightStarted = false;
    bool onlyOneDot = true;
    bool oneWay = false;//droga jednokierunkowa
    bool twoWay = false;//droga dwukierunkowa
    int leftNodeBeg = 0;//indeks poczatku id pierwszego wezla
    int leftNodeEnd = 0;//indeks konca id pierwszego wezla
    int rightNodeBeg = 0;//indeks poczatku id drugiego wezla
    int rightNodeEnd = 0;//indeks konca id drugiego wezla
    int weightBeg = 0;//indeks poczatku dystansu
    int weightEnd = 0;//indeks konca dystansu

    for(int i=0; i<data.length(); i++){
        if(isdigit(data.at(i)) && !leftNodeStarted && !rightNodeStarted){//zaczyna sie id pierwszego wezla
            leftNodeBeg = i;
            leftNodeStarted = true;
        }else if (isdigit(data.at(i)) && leftNodeStarted && !rightNodeStarted){
            leftNodeEnd = i;
        }else if ((i<data.length()-1) && leftNodeStarted && !rightNodeStarted && data.at(i) == '-' && isdigit(data.at(i+1))){
            twoWay = true;
            i++;
            rightNodeStarted = true;
            rightNodeBeg = i;
        }else if ((i<data.length()-2) && leftNodeStarted && !rightNodeStarted && data.at(i) == '-' && data.at(i+1) == '>' && isdigit(data.at(i+2))){
            oneWay = true;
            i+=2;
            rightNodeStarted = true;
            rightNodeBeg = i;
        }else if(isdigit(data.at(i) && leftNodeStarted && rightNodeStarted)){
            rightNodeEnd = i;
        }else if(leftNodeStarted && rightNodeStarted && data.at(i) == ':'){
            nodesRead = true;
        }else if(nodesRead && isdigit(data.at(i))){
            weightStarted = true;
            weightBeg = i;
        }else if(weightStarted && isdigit(data.at(i)) || (weightStarted && onlyOneDot && (i+1 < data.length()) && isdigit(data.at(i+1)))){
            onlyOneDot = false;
            weightEnd = i;
        }else{
            return false;
        }
    }

    if(twoWay){
        int leftNodeId = stoi(data.substr(leftNodeBeg, leftNodeEnd));
        int rightNodeId = stoi(data.substr(rightNodeBeg, rightNodeEnd));

    }else if(oneWay){
        int nodeId = stoi(data.substr(leftNodeBeg, leftNodeEnd));
        int nbrId = stoi(data.substr(rightNodeBeg, rightNodeEnd));
    }
}
