package com.company;

public class Inna_Rekurencja {

    double Licz(int n){
        if(n==1)
            return 1.0;
        if(n==2)
            return 0.5;

            return (-Licz(n-1)*Licz(n-2));

    }
}
