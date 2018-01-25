
/** @file  **/

#include <iostream>
#include "deklaracje.h"
using namespace std;

int main() {

    Node *graphHead = nullptr;

    pushBackNbr(graphHead,2,3);
    pushBackNbr(graphHead,1,2);
   // pushBackNbr(graphHead,1,5);
   // pushBackNbr(graphHead,2,5);

    writeNodes(graphHead);
    cout << endl << endl;

    writeNodes(graphHead->pNext->nbrNext);
    cout<< endl << endl;

    //writeNodes(graphHead->pNext->nbrNext);
    removeNodes(graphHead);
    return 0;
}
/*
 //funkcja dodaje kolejnego sąsiada do pomocniczej listy sasiadow
void pushBackNbr(Node *&graphHead, Node *&nbrHead, IdList *&idHead){

    auto *idhead = idHead;
    auto *graphhead = graphHead;

    while(idhead){
        while(graphhead){
            if(graphhead-> id == idhead-> id){
                pushBack(nbrHead, idhead-> id);
            }
            graphhead = graphhead-> pNext;
        }
        graphhead = graphHead;
        idhead = idhead-> pNext;
    }
}

void pushBackId(IdList *&pHead, int id){
    if(!pHead){
        pHead = new IdList{id, nullptr};

    }else{
        pushBackId(pHead-> pNext,id);
    }
}

//funkcja podpina pomocnicza liste sasiadow pod odpowiedni wezel
void addNbrList(Node *&pHead, Node *&nbrHead, int id){

    auto *head = pHead;
    while(head-> id != id){
        head = head-> pNext;
    }

    head-> nbrNext = nbrHead;
}
 */
