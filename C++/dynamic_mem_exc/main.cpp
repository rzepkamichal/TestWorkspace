#include <iostream>
#include <cmath>
using namespace std;

// LISTA JEDNOKIERUNKOWA
/*
struct Element{
    int value;
    Element *pNext;
};

void pushBack( Element *&pHead, int value){
    if(!pHead){
        pHead = new Element {value,nullptr};
    }else{
        pushBack(pHead-> pNext, value);
    }
}

void pushFront( Element *&pHead, int value){
    pHead =  new Element{value, pHead};
}

void writeBack(Element *&pHead){
    if(!pHead-> pNext){
        cout<< pHead-> value <<endl;
    }else{
        writeBack(pHead->pNext);
        cout<< pHead-> value <<endl;
    }
}

void writeForward( Element *&pHead){
    if(!pHead-> pNext){
        cout<< pHead-> value<<endl;
    }else{
        cout<< pHead-> value<< endl;
        writeForward ( pHead-> pNext );
    }
}

void clearList ( Element *&pHead){
    if(!pHead-> pNext){
        delete pHead;
    }else{
        clearList ( pHead-> pNext);
        delete pHead;
    }
}

int main() {

    Element *mylist = nullptr;

    pushFront(mylist,8);
    pushBack(mylist, 4);
    pushBack(mylist,15);
    //pushBack(mylist, 49);
    pushFront(mylist,3);
    //pushFront(mylist,38);
    //pushBack(mylist, -15);
    //pushFront(mylist, -241);

    //writeBack(mylist);
    writeForward(mylist);
    clearList( mylist );

    return 0;
}*/


// LISTA DWUKIERUNKOWA

struct Element{
    int value;
    Element *pPrev;
    Element *pNext;
};

void pushBack( Element *&pHead, Element *&pTail, int value){
    if(!(pHead && pTail)){
        pHead= new Element{value,nullptr,nullptr};
        pTail= pHead;
    }else {
        Element *tmp = pTail;
        pTail= new Element{value,pTail,nullptr};
        tmp-> pNext= pTail;
    }
}

void pushFront( Element *&pHead, Element *&pTail, int value){
    if(!(pHead && pTail)){
        pHead= new Element{value,pTail,nullptr};
        pTail= pHead;
    }else{
        Element *tmp= pHead;
        pHead= new Element{value, nullptr, pHead};
        tmp-> pPrev = pHead;
    }
}

void writeForward(Element *&pHead) {
    if (!pHead-> pNext) {
        cout << pHead->value << endl;
    } else {
        cout << pHead->value << endl;
        writeForward(pHead->pNext);

    }
}

void writeBack(Element *&pTail){
    if(!(pTail-> pPrev)){
        cout<< pTail-> value<< endl;
    }else{
        cout<< pTail-> value<<endl;
        writeBack(pTail-> pPrev);
    }

}

void clearList(Element *&pHead){
    if(!pHead-> pNext){
        delete pHead;
    }else{
        clearList(pHead-> pNext);
        delete pHead;
    }
}


int main(){

    Element *listaHead = nullptr;
    Element *listaTail = nullptr;

    pushBack (listaHead, listaTail, 3);
    pushBack (listaHead,listaTail, 45);
    pushBack (listaHead,listaTail, 57);
    pushFront(listaHead, listaTail, -34);
    pushBack(listaHead,listaTail,-12);
    pushFront(listaHead,listaTail,-935);

    writeForward(listaHead);
    cout<< endl;
    writeBack(listaTail);
    clearList(listaHead);
    return 0;
}