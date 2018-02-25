package sample;

import java.util.ArrayList;
import java.util.List;

public class Translator {

    public static void Translate(String wyrazenie){
        List<Character> stos=new ArrayList<Character>();
        List<Character> output=new ArrayList<Character>();
        int stos_size;
        for(int i=0;i<wyrazenie.length();i++){

            stos_size=stos.size();
//1 mnozenie, 2 dodawanie, 3 odejmowanie, 4 dzielenie
            if(wyrazenie.charAt(i)!='('&&wyrazenie.charAt(i)!=')'&&wyrazenie.charAt(i)!='+'&&wyrazenie.charAt(i)!='-'&&wyrazenie.charAt(i)!='*'&&wyrazenie.charAt(i)!='/'){
                output.add(wyrazenie.charAt(i));continue;
            }else if(wyrazenie.charAt(i)=='('){
                stos.add(wyrazenie.charAt(i));continue;
            }else if(wyrazenie.charAt(i)==')'){
                for(int j=stos_size;stos.get(j)=='(';j--){
                    output.add(stos.get(j));
                    stos.remove(j);continue;
                }
            }else if(wyrazenie.charAt(i)=='+'){
                if(stos.get(stos.size()-1)=='*'||stos.get(stos.size()-1)=='/'){

                }
            }

        }

    }
}
