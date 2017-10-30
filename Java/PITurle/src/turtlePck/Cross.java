package turtlePck;

class Cross extends TurtleGraphicsWindow
  {
 public void initTurtleTree(int bok)
      {
          forward(bok);
      }
      public void myTurtleCmds( )
      {
          forward( 100 );
          back( 200 );
          forward( 100 );
          right( 90 );
          forward( 100 );
          back( 200 );
      }

       public void TurtleFirst( )
      {
          //back(100);
           forward( 100 );
           right(45);
           forward(50);
           right(45);
           forward(25);
           right(45);
           forward(12);
           back(12);
           left(90);
           forward(12);
           back(12);
           right(45);
           back(25);
          //right( 90 );
          //forward( 100 );
         // right( 90 );
         // forward( 100 );
      }

        public void TurtleSierp(int bok, int minBok )
      { if (bok<minBok) {
            return;
        }
          for(int i=1;i<4;i++){
              TurtleSierp(bok/2, minBok);
              forward(bok);
              right(120);
          }
        return;
      }

      public void TurtleTree(int bok, int minBok, double dim )
      { if (bok<minBok) {
           // left(45);
            return;
        }
        right(45);
        forward(bok);
        //right(45);
        TurtleTree((int)Math.floor(bok*dim), minBok, dim);
        //left(45);
        back(bok);
        left(90);
        forward(bok);
        TurtleTree((int)Math.floor(bok*dim), minBok, dim);
        back(bok);
        right(45);
        //forward(bok);
       // back(bok);

        return;
      }
 public void TreeEwa(int bok, int minBok)
      { if (bok<minBok) {
           return;
        }
        //forward(bok);
        right(60);
        forward(bok);
        TreeEwa(bok/2, minBok);
        back(bok);
        left(120);
        forward(bok);
        TreeEwa(bok/2, minBok);
        back(bok);
        right(60);
        return;
      }
       public void TomekTree(int bok, int minBok, double dim )
      { if (bok<minBok) {
           return;
        }
        forward(bok);
        right(60);
        TomekTree((int)Math.floor(bok*dim), minBok, dim);
        left(120);
        TomekTree((int)Math.floor(bok*dim), minBok, dim);
        right(60);
        back(bok);
        return;
      }
      public void TurtleKoch(int bok, int minBok, double dim )
      { if (bok<minBok) {
           // left(45);
            return;
        }
        right(90);
        forward(bok);
        left(60);
        forward(bok);
        right(120);
        forward(bok);
        left(60);
        forward(bok);
        //forward(bok);
       // back(bok);

        return;
      }
             public void KoloTree(int bok, int minBok, double dim )
      { 
         if (bok<minBok) {
           // left(45);
            return;
        }
        left(45);
        forward(bok);
        KoloTree((int)Math.floor(bok*dim), minBok, dim);
        back(bok);
        right(90);
        forward(bok);
        KoloTree((int)Math.floor(bok*dim), minBok, dim);
    back(bok);
       left(45);
       if (bok == 100)  back(100);
        return;
        
      }
public void Brzeski(int bok, int minBok){
      if (bok<minBok) 
           // left(45);
            return;
     
   
       for (int i=1; i<3; i++){
        Brzeski(bok/2, minBok);
        forward(bok);
        right(90);
        forward(bok);
        right(90);
      
        }
       
 }

public void BrzeskiBis(int bok, int minBok){
      if (bok<minBok)
           // left(45);
            return;


       for (int i=1; i<5; i++){
        BrzeskiBis(bok/2, minBok);
        forward(bok);
        right(90);
        //forward(bok);
       // right(90);

        }

 }
      // program starts here
      public static void main ( String[ ] args )
      {
          Cross obj = new Cross( );
          //obj.myTurtleCmds( );
         // obj.TurtleFirst();
          //obj.TurtleSierp(100, 25);
         //obj.initTurtleTree(50);
         //obj.TurtleTree(200, 20, 0.5);
         obj.KoloTree(100, 10, 0.5);
         // obj.TurtleKoch(100, 10, 0.);
      }

  } // end class Cross 