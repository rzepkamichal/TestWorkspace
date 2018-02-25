package com.company;

public class Silnia {

    int Silnia(int n){
        if(n==1){
            return 1;
        }else{
            return (n-3)*Silnia(n-1);
        }
    }
}
