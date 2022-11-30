#include <iostream>
#include "My_Stack.h"
#include "solving.h"
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "ERROR_01";
		exit(0);
	}
	solving s;
	cout << s.solving_m_exp(argv[1]);
}