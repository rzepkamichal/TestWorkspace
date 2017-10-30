/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Turtle;

/**
 *
 * @author ZTILabPI
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        TurtleAlgorithms alg = new TurtleAlgorithms();
        alg.positioningTurtle(30);
//        alg. sierpinski(bok, minBok);
        alg.sierpinski(300, 50);
//        alg.callSnowFlake(3, 400);
//        alg.snowFlake(3, 400);
    }
    
}
