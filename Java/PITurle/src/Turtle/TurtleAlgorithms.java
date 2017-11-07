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
public void tree(int bok,double minBok,int alfa){

    if(bok<minBok){
        left(40);
        forward((int)(bok/1.2));
        right(80);
        forward((int)(bok/1.2));
        right(100);
        forward((int)(bok/1.2));
        right(80);
        forward((int)(bok/1.2));
        right(140);

        return;

    }

    left(alfa/2);
    forward(bok);
    tree((int)(bok*0.75),minBok,alfa);

    back(bok);
    right(alfa);

    forward(bok);
    tree((int)(bok*0.75),minBok,alfa);
    back(bok);
    left(alfa/2);


}
public void sierpinskiquadrat(int bok, double minBok) {
    if (bok < minBok) {
        return;
    }

    for (int j = 0; j < 4; j++) {
        sierpinskiquadrat((int) (bok / 2), minBok);
        forward(bok);
        right(90);

    }
}
    public void triangles(int bok,int n){

    if(n==1) {
    return;
    }

    triangles((int)(2*bok/3),n-1);

    right(30);
    forward(bok);
    right(120);
    forward(bok);
    right(120);
    forward(bok);
    right(90);

    }

    public void kartkowka(int bok,int minbok,int alpha,double wsp){
        if(bok<minbok){
            return;
        }

        forward((int)(bok/2));
        left(alpha);

        kartkowka(bok*wsp;minbok,alpha,wsp);

        forward((int)(bok/2));
        back(bok);
        right(alpha);
    }






}


