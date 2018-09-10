package com.company;

public class Main {

    public static void main(String[] args) {

        Lambda lambda = new Lambda();

        /**
         * Calling lamdas by using the interface
         */
        System.out.println(lambda.add.calculate(2,5));
        System.out.println(lambda.subtract.calculate(13,15));
        System.out.println(lambda.multiply.calculate(8,8));
        System.out.println(lambda.pow.calculate(2,4));
    }
}
