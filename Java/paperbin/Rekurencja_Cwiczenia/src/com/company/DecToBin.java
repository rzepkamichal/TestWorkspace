package com.company;

public class DecToBin {

    void Calculate(int number){
        if(number>0) {
        Calculate((-number % 2 + number) / 2);
        System.out.print(number%2);
    }

    }
}
