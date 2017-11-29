#include <fstream>
#include <iostream>
using namespace std;

void f(ostream& stream) {
	stream << "XD";
}

int main()
{

	f(cout);

	return 0;
}
