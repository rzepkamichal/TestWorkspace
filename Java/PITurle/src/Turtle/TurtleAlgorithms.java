package Turtle;


import turtlePck.TurtleGraphicsWindow;



/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author ZTILabPI
 */
public class TurtleAlgorithms extends TurtleGraphicsWindow{
    
    public void positioningTurtle(int angle){
        right(angle);
    }

     
    public void sierpinski(int bok, int minBok ){
         if (bok<minBok) {
            return;
        }
          for(int i=1;i<4;i++){
              sierpinski(bok/2, minBok);
              forward(bok);
              right(120);
          }
      }

    
  
public void snowFlake(int n, int bok){
    if (n==0){
        forward(bok);
        return;
    }
    snowFlake(n-1, bok/3);
    right(60);
    snowFlake(n-1, bok/3);
    left(120);
    snowFlake(n-1, bok/3);
    right(60);
    snowFlake(n-1, bok/3);

}


public void callSnowFlake(int n, int bok){
    for(int i=1; i<4; i++){
      snowFlake(n, bok);
      left(120);
    }
}

}
