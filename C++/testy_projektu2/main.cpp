#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

using namespace std;
int main() {

    int numberOfConnects;
    cout << " Podaj liczbe polaczen do wygenerowania: "<< endl;
    cin >> numberOfConnects;
    string output;
    cout << "Podaj sciezke do pliku out" << endl;
    cin >> output;
    ofstream out(output);

    default_random_engine silnik;
    uniform_int_distribution<int> rozklad(1,numberOfConnects);
    auto czas = chrono::system_clock::now();
    auto przedzial = czas.time_since_epoch();
    silnik.seed(przedzial.count());

    default_random_engine silnik2;
    uniform_real_distribution<double> rozklad2(1,10);
    silnik2.seed(przedzial.count());

    for(int i =0; i < numberOfConnects; i++){
        if(i%3 == 0){
            out <<"(" << rozklad(silnik)<<"->"<<rozklad(silnik)<<":"<<rozklad2(silnik)<<")," << endl;
        }else{
            out <<"(" << rozklad(silnik)<<"-"<<rozklad(silnik)<<":"<<rozklad2(silnik)<<")," << endl;
        }
    }

    return 0;
}