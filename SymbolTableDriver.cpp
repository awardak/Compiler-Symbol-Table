/*
 * Driver for Symbol Table
 */

#include <iostream>
#include <string>
#include <fstream>
#include "SymbolTable.h"
using namespace std;

int main() 
{
	ifstream inputFile("input.txt");
	SymbolTable ST;
	string str;

	if (!inputFile) 
	{
		cout << "Unable to open input file." << endl;
		return -1;
	}
	
	/* Read tokens from input file. They will either be the
	opening and closing braces, or an identifier. */
	while (inputFile >> str)
	{
		if (str == "{")
		{
			/* In case of a new scope, we notify ST so that it may push
			a new table onto the stack of scopes */
			ST.enterNewScope();
			cout << "-- entered new scope --" << endl;
		}
		else if (str == "}")
		{
			/* When a scope is being closed, current scope is popped */
			ST.leaveScope();
			cout << "-- exited scope --" << endl;
		}
		else
		{
			/* New identifier is seen. */
			cout << "-- seen: " << str << " --" << endl;

			/* Create new symbol and insert into ST. 
			Deallocation of memory is left to the ST.  */

			Symbol *newSymbol = new Symbol{ str };
			Symbol *temp = ST.find(newSymbol);
			if (temp)
				cout << "  find: " << temp->name << endl;
			temp = ST.findAll(newSymbol);
			if (temp)
				cout << "  findAll: " << temp->name << endl;

			ST.insert(newSymbol);
		}

		ST.display();
		cout << endl;
	}
}