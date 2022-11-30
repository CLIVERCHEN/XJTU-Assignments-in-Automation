#include "Tree.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "ERROR_01";
		exit(0);
	}
	if (strlen(argv[1]) < 20)
	{
		cout << "ERROR_02";
		exit(0);
	}

	Tree input;
	input.Create_Tree(argv[1]);
	input.Coding(argv[1]);
	input.Decoding(argv[2]);
	input.Print_Code();
	cout << " ";
	input.Print_Decode();

	cout << endl;
	input.PreOrder();

	exit(0);
}
