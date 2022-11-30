#include <iostream>
#include "MyString.h"
#include "KMP.h"
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "ERROR_01";
		exit(0);
	}

	KMP K_Match(argv[1], argv[2]);

	cout << K_Match.KMP_Matching();
}