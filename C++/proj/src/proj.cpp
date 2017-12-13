/*
===========================================================================
Program: RootMaster
Autor: Michał Rzepka
Rok Akademicki: 2017/2018
Kierunek: Informatyka
Studia: SSI
Semestr: 1
Grupa: 1
Sekcja: 2
===========================================================================
*/
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// TYPY ZDEFINIOWANE W PROGRAMIE
/*Enumerator InputCase
 * Sluzy do przekazywania informacji o sposobie wprowadzania danych do wiersza polecen przez uzytkownika.
 * 	IODefautl- nie podano zadnych sciezek do plikow lub zadnych parametrow.
 * 	OutputDefault- nie podano sciezki do pliku wyjsciowego.
 * 	InputDefault- nie podano sciezki do pliku wejsciowego.
 * 	IOGiven- podano prawidlowe sciezki do plikow wejscia/wyjscia.
 * 	HelpNeeded- uzytkownik uzyl przelacznika -h lub wpisal bledne dane uruchomieniowe.
 */
enum InputCase
{
    IODefault,
    OutputDefault,
    InputDefault,
    IOGiven,
    HelpNeeded
};
/*Struktura ComplexNum
 * Sluzy do przechowywania wartosci charakteryzujacych liczbe zespolona wprowadzana na wejsciu i zadany pierwiastek.
 * 	int root- zmienna przechowuje wartosc stopnia liczonego pierwiastka.
 * 	double re- przechowuje wartosc czesci rzeczywistej.
 * 	double im- przechowuje wartosc czesci urojonej.
 */
struct ComplexNum
{
    int root;
    double re;
    double im;
};

// FUNKCJE MATEMATYCZNE
/* Funkcja CheckCase
 * Parametr: zmienna typu ComplexNum
 * Czesc rzeczywista i urojona odczytane z argumentu ComplexNum sa zapisywane do zmiennych
 * Zmienna occurence moze przyjmowac wartosci calkowite z przedzialu <0 , 8>.
 * Kazda z ww liczb naturalnych oznacza jeden z przypadkow matmatycznych zaleznych od re oraz im.
 * Przypadek jest sprawdzany za pomoca instrukcji warunkowych. Do zmiennej occurence jest zapisywana odpowiednia wartosc.
 * Funkcja zwraca: occurence.
 */
int CheckCase(ComplexNum number)
{
    double re = number.re;
    double im = number.im;
    int occurence;
    if (re != 0 || im != 0)
    {
        if (re > 0 && im > 0)
        { // arg glowny w I cwiartce
            occurence = 1;
        }
        if (re < 0 && im > 0)
        { // arg glowny w II cwiartce
            occurence = 2;
        }
        if (re > 0 && im < 0)
        { // arg glowny w IV cwiartce
            occurence = 3;
        }
        if (re < 0 && im < 0)
        { // arg glowny w III cwiartce
            occurence = 4;
        }
        if (re == 0)
        { // arg glowny na osi urojonej
            if (im > 0)
                occurence = 5;
            else
                occurence = 6;
        }
        if (im == 0)
        { // arg glowny na osi rzeczywistej
            if (re > 0)
                occurence = 7;
            else
                occurence = 8;
        }
    }
    else
    { // podana liczba jest zerem
        occurence = 0;
    }
    return occurence;
} // funkcja sprawdza na podstawie wartoœci re oraz im, do jakiej æwiartki
/*Funkcja FindAlpha
 * Parametry: int occurence (informacja o przypadku matematycznym zwrócona z funkcji CheckCase), ComplexNum number.
 * Zmienne:
 * 	double module- przechowuje modul liczby zespolonej na podstawie wartosc re oraz im.
 *  double alpha- przechowuje argument glowny liczby zespolonej
 * Argument jest obliczany na podstawie przypadku matematycznego (zmienna occurance) przy uzyciu funkcji cykolmetrycznych.
 * Funkcja zwraca: wartosc zmiennaj double alpha (kat w mierze lukowej)
 */
double FindAlpha(int occurence, ComplexNum number)
{
    double module = sqrt(number.re * number.re + number.im * number.im);
    double alpha;
    switch (occurence)
    {
        case 0:
            alpha = 10;
            break; // wartosc moze byc dowolna, nie moze nalezec do <0, 2pi>
        case 1:
            alpha = asin(number.im / module);
            break;
        case 2:
            alpha = acos(-1) - asin(number.im / module);
            break;
        case 3:
            alpha = -acos(number.re / module);
            break;
        case 4:
            alpha = acos(-1) + acos(abs(number.re / module));
            break;
        case 5:
            alpha = asin(1);
            break;
        case 6:
            alpha = asin(-1);
            break;
        case 7:
            alpha = 0;
            break;
        case 8:
            alpha = acos(-1);
            break;
    }
    return alpha;
}
/*Funkcja CalculateRoot
 *Parametry: double alpha (kat w mierze lukowej), ComplexNum number.
 *Zmienne:
 *	vector<double> solutions- kontener przechowuje rozwiazania, czesci rzeczywiste pod indeksam parz. czesc urojona- pod nparz.
 *	double module- przechowuje wartosc modulu l. zespolonej
 *	double pi- przechowuje wartosc liczby pi
 *	int coefficient- wspolczynnik, od jego wartosci zalezy dogladnosc obliczen. Rozw. jest mnozone przez wsp, zaokraglane i powrotnie dzielone.
 *Funkcja oblicza modul liczb wynikowych, ich czesc rzeczywista i urojna.
 *Jezeli root==1, to pierwiastek jest ta sama liczba, wartosci sa dodawane do kontenera.
 *Jezeli alpha==10- wartosc jest dowolna (i nie bedaca argumentem glownym!), wskazuje na to, ze podana liczba jest zerem. Zatem wynikiem jest tez 0.
 *W innym przypadku pierwiastki sa liczone iteracyjne na podstawie psotaci trygonometrycznej oraz wzoru de Moivre'a
 *Funkcja zwraca: kontener solutions typu double przechowujacy wynik.
 */
vector<double> CalculateRoot(double alpha, ComplexNum number)
{
    vector<double> solutions;
    double module = sqrt(number.re * number.re + number.im * number.im);
    double pi = acos(-1);
    int coefficient = 100000; // wymusza dokladnosc do 5 miejsca po przecinku
    module = pow(module, (1.0 / number.root));
    if (number.root == 1)
    {
        solutions.push_back(number.re);
        solutions.push_back(number.im);
    }
    else if (alpha == 10)
    {
        solutions.push_back(0);
        solutions.push_back(0);
    }
    else
    {
        alpha = alpha / number.root;
        for (int i = 0; i < number.root; i++)
        {
            solutions.push_back(
                round(coefficient * module * cos(alpha + (2 * pi * i / number.root)))
                / coefficient);
            solutions.push_back(
                round(coefficient * module * sin(alpha + (2 * pi * i / number.root)))
                / coefficient);
        }
    }
    return solutions;
}
/*Funkcja WriteSolutions
 *Parametry: strumien wyjsciowy ostream *stream, vector<double> &solutions- rozwiazania zwrocone przez funkcje CalculateRoot
 *Kolejne rozwiazania przechowywane w kontenerze solutions sa przekazywane do strumiena wyjsciowego.
 *Funkcja nic nie zwraca.
 */
void WriteSolutions(ostream& stream, vector<double>& solutions)
{
    if (solutions.size() == 1)
    {
        stream << solutions[0] << endl;
    }
    else
    {
        for (int i = 0; i < solutions.size(); i += 2)
        {
            if (i == solutions.size() - 2)
            {
                stream << "Z = " << solutions[i];
                if (solutions[i + 1] > 0)
                {
                    stream << " + ";
                    stream << solutions[i + 1] << "i" << endl;
                }
                else if (solutions[i + 1] < 0)
                {
                    stream << " - ";
                    stream << abs(solutions[i + 1]) << "i" << endl;
                }
                else
                {
                    stream << endl;
                }
            }
            else
            {
                stream << "Z = " << solutions[i];
                if (solutions[i + 1] > 0)
                {
                    stream << " + ";
                    stream << solutions[i + 1] << "i"
                           << "  LUB  ";
                }
                else if (solutions[i + 1] < 0)
                {
                    stream << " - ";
                    stream << abs(solutions[i + 1]) << "i"
                           << "  LUB  ";
                }
                else
                {
                    stream << "  LUB  ";
                }
            }
        }
    }
}

// FUNKCJE ODCZYTUJACE DANE, PARAMETRY I WYWOLUJACE FUNKCJE MATEMATYCZNE
/*Funkcja IsEmpty
 *Parametry: string &line
 *Funkcja sprawdza, linia zawarta w podanym lancuchu znakow nie jest pusta.
 *Zmienna bool isEmpty przchowuje informacje:
 *	true: linia jest pusta
 *	false: linia nie jest pusta
 *Funkcja zwraca: wartisc zmiennej isEmpty.
 */
bool IsEmpty(string& line)
{
    bool isEmpty = true;
    for (int i = 0; i < line.length(); i++)
    {
        if (iswspace(line[i]))
        {
            continue;
        }
        else
        {
            isEmpty = false;
            break;
        }
    }
    return isEmpty;
}
/*Funkcja IsValidPath
 *Parametry: string &path- lancuch znakow przechowujacy sciezke do pliku
 *Funkcja sprawdza poprawnosc sciezki do pliku przechowywana w podanym lancuchu znakow.
 *Funkcja zwraca:
 *	true, jezeli sciezka jest poprawna
 *	false, jezeli sciezka jest niepoprawna
 */
bool IsValidPath(string& path)
{
    fstream file;
    file.open(path);
    if (file.is_open())
    {
        file.close();
        return true;
    }
    else
    {
        file.close();
    }
    return false;
}
/*Funkcja IsValidParam
 *Parametry: string &param- lancuch znakow przechowujacy parametr.
 *Funkcja sprawdza, czy parametr przechowywany w lancuchu znakow jest poprawny.
 *Funkcja zwraca:
 *	true, jezeli parametr jest poprawny
 *	false, jezeli parametr jest niepoprawny
 */
bool IsValidParam(string& param)
{
    if (param == "-o" || param == "-i")
        return true;
    else
        return false;
}
/*Funkcja CheckParams
 *Parametry: dwa kontenery typu <string>: &params (parametry) oraz &filePaths(sciezki do plikow)
 *Funkcja otrzymuje parametry wpisane do wiersza polecen i sprawdza, jaki jest przypadek.
 *Zmienne:
 *	bool inputGiven- przechowuje informacje, czy jest podana sciezka pliku wej.
 *	bool outputGiven- przechowuje informacje, czy jest podana sciezka do pliku wyj.
 *Jezeli funkcja odczyta sciezki do plikow, zapisuje je do kontenera filePaths w kolejnosci <wej>, <wyj>.
 *Funkcja zwraca typ InputCase, wartosc jest zalezna od wyznaczonego przez funkcje warunkowe przypadku.
 */
InputCase CheckParams(vector<string>& params, vector<string>& filePaths)
{
    bool inputGiven = false, outputGiven = false;
    if (params.size() == 0
        || ((params.size() == 1 && IsValidParam(params[0]))
               || (params.size() == 2 && IsValidParam(params[0]) && IsValidParam(params[1]))))
    {
        return IODefault;
    }
    else if (params.size() == 1 && params[0] == "-h")
    {
        return HelpNeeded;
    }
    else
    {
        for (int i = 0; i < params.size() - 1; i++)
        {
            if (params[i] == "-i" && IsValidPath(params[i + 1]))
            {
                inputGiven = true;
                filePaths.push_back(params[i + 1]);
                if (outputGiven)
                {
                    string tmp = filePaths[0];
                    filePaths.clear();
                    filePaths.push_back(params[i + 1]);
                    filePaths.push_back(tmp);
                }
            }
            if (params[i] == "-o" && IsValidPath(params[i + 1]))
            {
                outputGiven = true;
                filePaths.push_back(params[i + 1]);
            }
        }
        if (inputGiven && outputGiven)
        {
            return IOGiven;
        }
        else if (inputGiven && !outputGiven)
        {
            return OutputDefault;
        }
        else if (!inputGiven && outputGiven)
        {
            return InputDefault;
        }
        else
        {
            return HelpNeeded;
        }
    }
}
/*Funkcja AreNoForbiddenSigns
 *Parametry: string &line- przechowuje zawartosc pobranej linii.
 *Funkcja sprawdza czy w podanej linii nie wystepuja znaki niezgodne z
 *zalozeniami.
 *Zmienna bool areNoForbiddenSigns przyjmuje:
 *	 true, jesli odczytana linia jest poprawna
 *	 false, jesli odczytana linia jest niepoprawna
 *Funkcja zwraca: wartosc zmiennej areNoForbiddenSigns.
 */
bool AreNoForbiddenSigns(string& line)
{
    bool areNoForbiddenSigns;
    for (int i = 0; i < line.length(); i++)
    {
        if (line.at(i) == '+' || line.at(i) == '-' || line.at(i) == 'i' || line.at(i) == '.'
            || (line.at(i) >= 48 && line.at(i) <= 57) || iswspace(line.at(i)))
        {
            areNoForbiddenSigns = true;
        }
        else
        {
            areNoForbiddenSigns = false;
            break;
        }
    }
    return areNoForbiddenSigns;
}
/*Funkcja IsNatural
 *Parametry: string &line- lancuch znakow przechowujacy wartisc liczby.
 *Funkcja sprawdza, czy liczba odczytana z lancucha znakow jest niezerowa i naturalna.
 *Zmienna:
 *	bool isNatural przyjmuje:
 *		true, jezeli liczba jest naturalna
 *		false, jezeli liczba nie jest naturalna
 *	bool isNotZero przyjmuje:
 *		true, jezeli liczba jest niezerowa
 *		false, jezeli liczba jest zerem
 *Funkcja zwraca koniunkcje wartosci isNatural i isNotZero
 */
bool IsNatural(string& line)
{
    bool isNatural;
    bool isNotZero = false;
    for (int i = 0; i < line.length(); i++)
    {
        if (line.at(i) >= 48 && line.at(i) <= 57)
        {
            if (line.at(i) != '0')
            {
                isNotZero = true;
            }
            isNatural = true;
        }
        else
        {
            isNatural = false;
            break;
        }
    }
    return isNatural && isNotZero;
}
/*Funkcja IsComplexNumber
 *Parametry: string &line- lancuch znakow przechowujacy liczbe zespolona.
 *Funkcja sprawdza, czy podany lancuch znakow zawiera poprawnie zapisana liczbe zespolona.
 *Zmienne:
 *	bool imGiven przyjmuje:
 *		true, jesli zostanie odczytana czesc urojona
 *		false, dopoki nie zostanie odczytana czesc urojona
 *	bool reGiven przyjmuje:
 *		true, jesli zostanie odczytana czesc rzeczywista
 *		false, dopoki nie zostanie odczytana czesc rzeczywista
 *	bool operatorExpected przyjmuje:
 *		true, jesli nastepnym odczytanym znakiem powinien byc operator
 *		false- domyslnie
 *	bool isComplex przyjmuje:
 *		true, jesli odczytana liczba jest zespolona, czyli odczytano czesc rzeczywista lub urojona (reGiven || imGiven)
 *		false, jesli odczytana liczba nie jest zespolona, czyli nie odczytano zadnej z czesci
 *Funkcja zwraca wartosc zmiennej isComplex.
 */
bool IsComplexNumber(string& line)
{
    bool isComplex;
    bool imGiven = false;
    bool reGiven = false;
    bool operatorExpected = false;
    for (int i = 0; i < line.length(); i++)
    {
        if (i < line.length() - 1 && operatorExpected && (line.at(i) == '-' || line.at(i) == '+')
            && line.at(i + 1) != '-' && line.at(i + 1) != '+')
        {
            operatorExpected = false;
            continue;
        }
        else if (operatorExpected && (line.at(i) != '-' || line.at(i) != '+'))
        {
            return false;
        }
        else if ((line.at(i) == '-' || line.at(i) == '+'))
        {
            continue;
        }
        else if (line.at(i) == 'i' && !imGiven)
        {
            imGiven = true;
            operatorExpected = true;
            continue;
        }
        else if (isdigit(line[i]))
        {
            int j = i + 1;
            while ((j < line.length() && isdigit(line[j]))
                || (j < line.length() - 1 && line[j] == '.' && isdigit(line[j + 1])))
            {
                j++;
            }
            i = j - 1;

            if (!imGiven && i < line.length() - 1
                && (line.at(i + 1) == 'i' || line.at(i + 1) == '0'))
            {
                imGiven = true;
                operatorExpected = true;
                i++;
                continue;
            }
            else if (!reGiven)
            {
                operatorExpected = true;
                reGiven = true;
                continue;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    if (imGiven || reGiven)
    {
        isComplex = true;
    }
    else
    {
        isComplex = false;
    }
    return isComplex;
}
/*Funkcja CheckInput
 *Parametry: string &line- linia z danymi wejsciowymi
 *Zmienne:
 *	string root- do niej zapisywany jest pierwszy odczytany z linii znak, ktory powinien stanowic stopien pierwiastka
 *	string complexNumber- do niej zapisywany jest lancuch znakow po pierwszym odczytanym znaku, lancuch powinien stanowic liczbe zespolona
 *	bool isValid- przechowuje informacje, czy dane wejsciowe sa poprawne
 *Za pomoca funkcji IsNatural oraz IsComplexNumber sa sprawdzane wartosci zmiennych root oraz complexNumber.
 *Jezeli obie funkcje zwroca wartosc true, zmienna isValid przyjmuje wartosc true.
 *W przeciwnym wypadku- wartosc false.
 *Funkcja zwraca: wartosc zmiennej isValid.
 */
bool CheckInput(string& line)
{
    bool isValid;
    string root;
    string complexNumber;
    stringstream lineStream(line);
    lineStream >> root;

    if (IsNatural(root))
    {
        string tmp;
        while (lineStream >> tmp)
        {
            complexNumber.append(tmp);
        }
        if (IsComplexNumber(complexNumber))
        {
            isValid = true;
        }
        else
        {
            isValid = false;
        }
    }
    else
    {
        isValid = false;
    }
    return isValid;
}
/*Funkcja GetValuesFromInput
 *Parametry: string &line- lancuch przechowujacy zawartosc odczytanej linii.
 *Zmienne:
 *	stringstream linseStream- parametr line jest zapisywany do zmiennej typu stringstream.
 *	string root- do niej zapisywany jest pierwszy odczytany z linii znak, ktory jest stopniem pierwiastka.
 *	string num- do niej zapisywane sa pozostale znaki z linii, ktore stanowia liczbe zespolona.
 *	string tmp- zmienna pomocnicza, sluzy do przeprowadzenia ww operacji.
 *	ComplexNum number- do jej skladowych beda zapisywane odczytywane wartosci stopnia pierwiastka, czesci rzeczywistej i urojonej.
 *	string re- do niej bedzie zapisana odczytana czesc rzeczywista.
 *	strin im- do niej bedzie zapisana odczytana czesc urojona.
 *	string value- zmienna pomocnicza, sluzy do przechowywania aktualnie odczytanej wartosci liczbowej.
 *	string sign- do niej bedzie zapisany odczytany znak.
 *	bool reGiven- przechowuje informacje, czy czesc rzeczywista zostala juz podana.
 *	bool imGiven- przechowuje informacje, czy czesc urojona zostala juz podana.
 *Funkcja odczytuje najpierw stopien pierwiastka.
 *Nastepnie znak po znaku odczytuje operatory/znaki lub liczby.
 *Odczytywane wartosci sa zapisywane do odpowiednych lancuchow znakow.
 *Przy uzyciu fukcji rzutujacych, dane zawarte w lancuchach znakow sa zapisywane do pol zmiennej number.
 *Funkcja zwraca: wartosc zmiennej number (typo ComplexNum)
 */
ComplexNum GetValuesFromInput(string& line)
{
    stringstream lineStream(line);
    string root;
    lineStream >> root;
    string num;
    string tmp;
    while (lineStream >> tmp)
    {
        num.append(tmp);
    }
    ComplexNum number;
    number.root = stoi(root);
    string re;
    string im;
    string value;
    string sign = "+";
    bool reGiven = false;
    bool imGiven = false;
    for (int i = 0; i < num.length(); i++)
    {
        if (num[i] == '-')
        {
            sign = "-";
            continue;
        }
        else if (num[i] == '+')
        {
            sign = "+";
            continue;
        }
        else if (isdigit(num[i]))
        {
            value.push_back(num[i]);
            int j = i + 1;
            while (
                isdigit(num[j]) || (j < num.length() - 1 && num[j] == '.' && isdigit(num[j + 1])))
            {
                value.push_back(num[j]);
                j++;
            }
            i = j - 1;
            if (!imGiven && num[i + 1] == 'i')
            {
                imGiven = true;
                im = sign + value;
                value.clear();
                continue;
            }
            else if (!reGiven)
            {
                reGiven = true;
                re = sign + value;
                value.clear();
                continue;
            }
        }
        else if (num[i] == 'i' && !imGiven)
        {
            im = sign + "1";
            imGiven = true;
            continue;
        }
    }

    if (!imGiven)
    {
        number.im = 0;
    }
    else
    {
        number.im = stod(im);
    }
    if (!reGiven)
    {
        number.re = 0;
    }
    else
    {
        number.re = stod(re);
    }
    return number;
}
/*Funkcja Calculate
 *Parametry: strumien wej &in, strumien wyj &out
 *Zmienne:
 *	string input- do niej zapisywana jest zawartosc odczytanej linii.
 *	vector<double> solutions- do tego kontenera zapisywane sa obliczone rozwiazania.
 *	ComplexNum number- przechowuje aktualnie rozpatrywana liczbe zespolona.
 *Funkcja pobiera dane linia po linii ze strumienia wejsciowego.
 *Dla każdej pobranej linii:
 *	- sprawdza, czy linia nie jest pusta. Jesli tak- pobierana jest kolejna linia.
 *	- sprawdza, czy w podanej linii nie ma zabronionych znakow.
 *	- sprawdza, czy dane w linii sa zapisane poprawnie- zgodne z zalozeniami.
 *	- do zmiennej number zapisuje wartosc zwrocana przez f. GetValuesFromInput(input).
 *	- do kontenera solutions zapisuje rozwiazania obliczone przez zagniezdzone funkcje matematyczne.
 *	- na podany strumien wyjsciowy przekazuje rozwiazania z wykorzystaniem f. WriteSolutions.
 *	- zwalnia kontener, zeby zapisac do niego rozwiazania z nastepnych linii.
 *Funkcja zwraca:
 *	true, jesli wszystkie funkcje sprawdzajace poprawnosc danych zwroca true
 *	false, jesli ktoras z funkcji sprawdzajacych dane zwroci false
 */
bool Calculate(istream& in, ostream& out)
{
    string input;
    vector<double> solutions;
    ComplexNum number;
    while (getline(in, input))
    {
        if (IsEmpty(input))
        {
            continue;
        }
        if (AreNoForbiddenSigns(input))
        {
            if (CheckInput(input))
            {
                number = GetValuesFromInput(input);
                solutions = CalculateRoot(FindAlpha(CheckCase(number), number), number);
                WriteSolutions(out, solutions);
                solutions.clear();
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    return true;
}
/*Funkcja ReadParams
 *Parametry: int number- ilosc parametrow wiersza polecen, char *args[]- parametry wiersza polecen
 *Zmienne: kontener vector<string> params- przechowuje odczytane parametry.
 *Funkcja zapisuje odczytane parametry do kontenera params.
 *Funkcja zwraca kontener params.
 */
vector<string> ReadParams(int number, char* args[])
{
    vector<string> params;
    for (int i = 1; i < number; i++)
    {
        params.push_back(args[i]);
    }
    return params;
}

// FUNKCJA MAIN
/*Funkcja main
 *Parametry: int argc- ilosc parametrow wiersza polecen, char *argv[]- parametry wiersza polecen.
 *Zmienne:
 *	vector<string> params- kontener przechowujace parametry (zawartosc inicjalizowana za pomoca funkcji ReadParams).
 *	vector<string> filePaths- kontener przechowujacy sciezki do plikow (zawartosc inicjalizowana za pomoca funkcji CheckParams).
 *	InputCase occurance- przechowuje informacje o sposobie uruchomienia programu z parametrami.
 *	ifstream iFile- strumien pliku wejsciowego
 *	ofstream oFile- strumien pliku wyjsciowego
 *Wykonywana jest instrukcja switch. W zaleznosci od wartosci occurence, rozpatrywane sa okreslone przypadki.
 *Do funkcji Calculate przekazywany jest odpowiedni strumien wej/wyj.
 *Funkcja Calculate oblicza pierwiastki i przekazuje rozwiazania do strumienia wyj.
 *Jezeli funkcja Calculate zwroci false, wyswietlany jest komunikat o bledzie.
 *Jezeli case: HelpNeeded, wyswietlana jest pomoc.
 */
int main(int argc, char* argv[])
{
    vector<string> params = ReadParams(argc, argv);
    vector<string> filePaths;
    InputCase occurence = CheckParams(params, filePaths);

    switch (occurence)
    {
        case IOGiven:
        {
            ifstream iFile(filePaths[0]);
            ofstream oFile(filePaths[1]);
            if (Calculate(iFile, oFile))
            {
            }
            else
            {
                cout << "Blad! Wprowadzono bledne dane.";
                oFile.clear();
            }
            iFile.close();
            oFile.close();
            break;
        }
        case OutputDefault:
        {
            ifstream iFile(filePaths[0]);
            if (Calculate(iFile, cout))
            {
            }
            else
            {
                cout << "Blad! Nie mozna ukonczyc obliczen. Napotkano bledne dane w "
                        "pliku.";
            }
            iFile.close();
            break;
        }
        case InputDefault:
        {
            ofstream oFile(filePaths[0]);
            if (Calculate(cin, oFile))
            {
            }
            else
            {
                cout << "Blad! Wprowadzono bledne dane.";
            }
            oFile.close();
            break;
        }
        case IODefault:
        {
            if (Calculate(cin, cout))
            {
            }
            else
            {
                cout << "Blad! Wprowadzono bledne dane.";
            }
            break;
        }
        case HelpNeeded:
        {
            cout << endl << "Zapytano o pomoc lub program uruchomiono nieprawidlowo." << endl;
            cout << "Mozliwe dane uruchomieniowe:" << endl;
            cout << "RootMaster -h -- wyswietl pomoc." << endl;
            cout << "RootMaster -i <we> -o <wyj>  -- <we>-sciezka pliku wejsciowego, "
                    "<wyj>-sciezka pliku wyjsciowego."
                 << endl;
            cout << "RootMaster -i <we> -- <we> sciezka pliku wejsciowego, wyjscie "
                    "jest standardowe."
                 << endl;
            cout << "RootMaster -o <wyj> -- wejscie jest standardowe, <wyj>-sciezka "
                    "pliku wyjsciowego."
                 << endl;
            cout << "RootMaster -i -o lub RootMaster -- wejscie i wyjscie sa "
                    "standardowe."
                 << endl;
            cout << "Parametry -i oraz -o mozna uzywac naprzemienie." << endl;
            break;
        }
    }
    return 0;
}
