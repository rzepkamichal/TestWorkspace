package com.company;

public class Lambda {

    /**
     * Definitions of Lambdas
    (arguments) -> operations
     */

    CalculatorInterface add = (int x, int y) -> x + y;
    CalculatorInterface subtract = (int x, int y) -> x - y;
    CalculatorInterface multiply = (int x, int y) -> x * y;
    CalculatorInterface pow = (int x, int y) -> (int) Math.pow(x,y);


}
