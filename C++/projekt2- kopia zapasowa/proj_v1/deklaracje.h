<<<<<<< HEAD
=======
/** @file  **/

/// 
///  Created by sysoper on 2018-01-22.
/// 

>>>>>>> 668d87eec122a1731d6de32721d89c7f66fbb29a
#ifndef PROJ_V1_DEKLARACJE_H
#define PROJ_V1_DEKLARACJE_H
#include <string>
#include <iostream>
using namespace std;

<<<<<<< HEAD
//lista przechowujaca wezly grafu
struct Node{

    int id;
    Node *pNext;//wskaznik na nastepny element
    Node *nbrNext;//lista przechowujaca "sasiadow" kazdego wezla
=======
/// lista przechowujaca wezly grafu
/** @warning KS: Czy ta nazwa jest najszczesliwsza? Struktura reprezentuje JEDEN wezel, a nazwa 
                 jest w liczbie mnogiej. Czy tak ma byc? */
struct Nodes
{

    int id;
    Nodes *pNext;/// wskaznik na nastepny element
    
    /** @warning KS: Tu by sie przydalo jakies wyjasnienie, bo nie bardzo wiem, co jest sasiadem
                 wezla.  */
    Nodes *nbrNext;/// lista przechowujaca "sasiadow" kazdego wezla
>>>>>>> 668d87eec122a1731d6de32721d89c7f66fbb29a
};

/// lista przechowujaca wagi (dystans) pomiedzy sasiednimi wezlami
/** @warning KS: Czy struktury Nodes i Weights sa w jakis sposob powiazane? **/
struct Weights
{

    /** @warning KS: Dlaczego tak? */
    int startId; ///  id wezla wyjsciowego
    int nbrId; ///  id wezla sasiedniego
    double weight; ///  waga- wartosc
    Weights *pNext;///  wskaznik na nastepny

};

/// lista przechowujaca kolejne dane typu string odczytane z pliku
/// @warning KS: Nie bardzo wiem, co po jest ta struktura.
struct stringList
{
    string data;///  zmienna przechowujaca kolejne dane, np: "1->5:6.35"
    stringList *pNext;/// wskaznik na nastepny
};

/// lista przechowujaca id wezlow, w trakcie pracy zorientowalem sie jednak, ze struktura ta jak i powiazanie z nia funkcje sa raczej zbedne i zostana niebawem usuniete
struct IdList
{
    int id;
    IdList *pNext;
};

<<<<<<< HEAD
//FUNKCJE
void pushBack(Node *&pHead, int id);
Node* getLast(Node *&pHead);
void pushBackNbr(Node *&pHead, int nodeId, int nbrId);
int countNodes(Node *pHead);
Node* getNode(Node *&pHead, int index);
void writeNodes( Node *&pHead);
=======
/// FUNKCJE

/** opis funkcji
 * @param pHead opis parametru
 * @param id    opis parametru
 * @date data
 * @author autor
 * @todo Wszystkie funkcje trzeba opisac.
 */
void pushBack(Nodes *&pHead, int id);

/** opis funkcji
 * @param pHead opis parametru
 * @return zwracane wartosci
 * @date data
 * @author autor
 * @todo Wszystkie funkcje trzeba opisac.
 */
Nodes * getLast(Nodes *&pHead);
void pushBackNbr(Nodes *&pHead, int nodeId, int nbrId);
int countNodes(Nodes *pHead);
Nodes* getNode(Nodes *&pHead, int index);
void writeNodes( Nodes *&pHead);
>>>>>>> 668d87eec122a1731d6de32721d89c7f66fbb29a
void writeIdList(IdList *&pHead);
void writeNbrs(Node *&pHead);
void removeIdList( IdList *&pHead);
<<<<<<< HEAD
void removeNodes( Node *&pHead );
bool readData(string data, Node *&nHead, Weights *&wHead, IdList *&idHead);

#endif //PROJ_V1_DEKLARACJE_H
=======
void removeNodes( Nodes *&pHead );
bool readData(string data, Nodes *&nHead, Weights *&wHead, IdList *&idHead);
#endif /// PROJ_V1_DEKLARACJE_H
>>>>>>> 668d87eec122a1731d6de32721d89c7f66fbb29a
