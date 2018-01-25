#include <iostream>
using namespace std;



struct Lyrics{
    int id;
    Lyrics *pNext;
};

void addSong(Lyrics *&teksty, int id){
    if(!teksty){
        teksty = new Lyrics{id,teksty};
    }else{
        addSong(teksty->pNext,id);
    }
}

void writeId(Lyrics *&teksty){
    if(teksty){
        cout<<teksty->id<<endl;
        writeId(teksty->pNext);
    }

}

void clearList(Lyrics *&teksty){
    if(teksty){
        clearList(teksty->pNext);
        delete teksty;
    }
}

int main() {

    Lyrics *teksty=nullptr;

    addSong(teksty,23);
    addSong(teksty,50);
    addSong(teksty,54);
    writeId(teksty);
    clearList(teksty);


    return 0;
}