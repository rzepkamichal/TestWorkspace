#include <stdio.h>
#include <malloc.h>
#include <mem.h>

typedef struct BUFFER Bufferek;

struct BUFFER{
    char *nazwa;
    char *email;
    char *telefon;
};

void setBuffer(Bufferek* buff, char* nazwa, char *email, char *telefon){

    (*buff).nazwa = malloc(strlen(nazwa));
    (*buff).email = malloc(strlen(email));
    (*buff).telefon = malloc(strlen(telefon));

    strcpy((*buff).nazwa, nazwa);
    strcpy((*buff).email,email);
    strcpy((*buff).telefon,telefon);

}

void writeBuffer(Bufferek* buff){

    puts((*buff).nazwa);
    puts((*buff).email);
    puts((*buff).telefon);
}

int main(int argc, char* argv[]) {

    /*
    FILE *iFile = fopen(argv[1],"r");
    fseek(iFile,0,SEEK_END);
    long bufferSize = ftell(iFile);
    char *buffer = malloc(bufferSize + 1);
    fseek(iFile,0,SEEK_SET);
    fread(buffer,sizeof(char),bufferSize,iFile);
    buffer[bufferSize] = '\0';
    fclose(iFile);
*/


    char nazwa[] = "Chmurowisko";
    char email[] = "miroburn@gmail.com";
    char telefon[] = "997 998 999";



    Bufferek buff;
/*
    (buff).nazwa = malloc(sizeof(nazwa));
    (buff).email = malloc(sizeof(email));
    (buff).telefon = malloc(sizeof(telefon));

    strcpy((buff).nazwa, nazwa);
    strcpy((buff).email,email);
    strcpy((buff).telefon,telefon);

    puts((buff).nazwa);
    puts((buff).email);
    puts((buff).telefon);
*/

    setBuffer(&buff,nazwa,email,telefon);

    //writeBuffer(&buff);

    puts(buff.nazwa);
    puts(buff.email);
    puts(buff.telefon);



    free(buff.nazwa);
    free(buff.email);
    free(buff.telefon);




    return 0;
}