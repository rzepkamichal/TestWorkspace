//Need to do something with this
#include <iostream>
using namespace std;

typedef int T;


struct element
{
    T wartosc;
    element *pNext;
};


void dodajNaPocz(element*&phead, T wartosc)
{
    phead = new element{ wartosc, phead };
}


void wypiszOdPocz(element*phead)  //pamietac, ze jest tylko kopia
{
    while (phead)
    {
        cout << phead -> wartosc << "\t";
        phead = phead -> pNext;
    }
}


void usunListe(element*&phead)
{
    while (phead)
    {
        auto p = phead;
        phead = phead->pNext;
        delete p;
    }
}


void dodajNaKon(element*&phead, T wartosc)
{
    if (!phead)
    {
        phead = new element{ wartosc, phead };
    }
    else  //juz cos jest
    {								//zagadkowe naruszenie ochrony pamieci
        auto p = phead;				//W R E D N E ! ! !
        while (p->pNext)
        {
            p = p->pNext;
        }
        p->pNext = new element{ wartosc, nullptr };
    }
}


void wypiszOdPoczRek(element*phead)
{
    if (phead)
    {
        cout << phead->wartosc << "   ";
        wypiszOdPoczRek(phead->pNext);
    }
}


void wypiszOdKonRek(element*phead)
{
    if (phead)
    {
        wypiszOdKonRek(phead->pNext);
        cout << phead->wartosc << "   ";
    }
}


void dodajNaKonRek(element*&phead, T wartosc)
{
    if (!phead)
    {
        phead = new element{ wartosc, phead };
    }
    else  //juz cos jest
    {								//zagadkowe naruszenie ochrony pamieci
        dodajNaKonRek(phead->pNext, wartosc);
    }
}




struct pamiec{
    int liczba;
    pamiec *next;
};

void add(pamiec *&lista, int wartosc){
    lista=new pamiec{wartosc,lista};

    if(!lista){
        lista=new pamiec{wartosc,lista};
    }else{
        auto tmp =lista;
        while(tmp->next){
            tmp=tmp->next;
        }
        tmp->next = new pamiec{wartosc, nullptr};
    }

   /* void dodajNaKon(element*&phead, T wartosc)
    {
        if (!phead)
        {
            phead = new element{ wartosc, phead };
        }
        else  //juz cos jest
        {								//zagadkowe naruszenie ochrony pamieci
            auto p = phead;				//W R E D N E ! ! !
            while (p->pNext)
            {
                p = p->pNext;
            }
            p->pNext = new element{ wartosc, nullptr };
        }
    }*/

}

void write(pamiec *&lista){

    if(lista){
        cout<< lista->next;
        write(lista->next);
    }
}

int main()
{
   /* pamiec *lista=nullptr;

    add(lista,5);
    add(lista,8);
    add(lista,68);
    add(lista,463);

    write(lista);
*/
    element* pGlowa = nullptr;
    dodajNaPocz(pGlowa, 1);
    dodajNaPocz(pGlowa, 8);
    dodajNaPocz(pGlowa, 4);
    dodajNaPocz(pGlowa, 2);
    dodajNaPocz(pGlowa, 23);
    dodajNaKon(pGlowa, 2);
    wypiszOdPoczRek(pGlowa);
    /*cout << endl;
    wypiszOdKonRek(pGlowa);
    dodajNaKonRek(pGlowa, 2);
    dodajNaKonRek(pGlowa, 3);
    dodajNaKonRek(pGlowa, 4);
    cout << endl;*/
    //wypiszOdKonRek(pGlowa);
    usunListe(pGlowa);
    usunListe(pGlowa);

    return 0;

}