#include <iostream>
#include <fstream>
#include <string>
#include "AVLtree.hpp"
#include "BinaryTree.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	int size, cnt = 0;
	string typeSort;
	typeSort = argv[2];
	if (typeSort == "AVL")
	{
		string val;
		AVLtree aTree;
		ifstream dataFile(argv[1]);
		dataFile >> size;
		while (dataFile)
		{
			dataFile >> val;
			aTree.insert(val);
		}
		cout << aTree.height() << endl;
		dataFile.close();
		dataFile.open(argv[1]);
		dataFile >> size;
		dataFile >> val;
		while (dataFile)
		{
			if (!aTree.find(val))
				cout << "error";
			dataFile >> val;
		}

	}
	else if (typeSort == "unbalanced")
	{
		string val;
		BinaryTree bTree;
		ifstream dataFile(argv[1]);
		dataFile >> size;
		while (dataFile)
		{
			dataFile >> val;
			bTree.insert(val);
		}
		cout << bTree.height() << endl;
		dataFile.close();
		dataFile.open(argv[1]);
		dataFile >> size;
		dataFile >> val;
		while (dataFile)
		{
			if (!bTree.find(val))
				cout << "error";
			dataFile >> val;
		}
	}
	else
	{
		cout << "Incorrect input for type of tree";
	}
	return 0;
}