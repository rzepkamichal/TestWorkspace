package com.company;

public class Jakas_Rekurencja {

    int Licz(int n){
        if(n==1){
            return -1;
        }else{
            return (-n)*Licz(n-1)-3;
        }
    }
}
