/*
 * SymbolTable.cpp
 */

#include <iostream>
#include "SymbolTable.h"
using namespace std;

/* Nothing special to do in constructor, yet. */
SymbolTable::SymbolTable()
{
}

/* Destructor responsible for deleting all symbols added to ST and
ST itself. */
SymbolTable::~SymbolTable()
{
	cout << "Destructing..." << endl;
	/* Get an iterator to iterate through the list of scopes. */
	auto listItr = oldScopes.begin();
	while (listItr != oldScopes.end())
	{
		auto hashtableItr = (*listItr)->begin();
		while (hashtableItr != (*listItr)->end())
		{
			cout << (*hashtableItr)->name << ' ';
			delete *hashtableItr;
			hashtableItr++;
		}
		delete *listItr;
		cout << endl;
		listItr++;
	}
}

/* This method is called when a new scope is entered. A new symbol table is 
pushed onto the stack for this scope. */
void SymbolTable::enterNewScope()
{
	activeScopes.push_back(new unordered_set<Symbol *, SymbolHash, SymbolEqual>);
}

/* When a scope is exited, its symbol table is popped off the stack. */
void SymbolTable::leaveScope()
{
	oldScopes.push_back(activeScopes.back());
	activeScopes.pop_back();
}

/* Simply insert next symbol into hash table. */
void SymbolTable::insert(Symbol *newSymbol)
{
	activeScopes.back()->insert(newSymbol);
}

/* To find a symbol in the current scope, we try to find it in the 
hash table. */
Symbol * SymbolTable::find(Symbol *	symbol)
{
	/* Get an iterator to the symbol requested. If not found, return nullptr. */
	auto hashtableItr = activeScopes.back()->find(symbol);
	if (hashtableItr != activeScopes.back()->end())
		return *hashtableItr;
	else
		return nullptr;
}

/* This method attempts to find the requested symbol in all active scopes. */
Symbol * SymbolTable::findAll(Symbol * symbol)
{
	/* Get an iterator to iterate through the list of active scopes. */
	auto listItr = activeScopes.crbegin();
	while (listItr != activeScopes.crend()) 
	{
		auto hashtableItr = (*listItr)->find(symbol);
		if (hashtableItr != (*listItr)->end())
			return *hashtableItr;

		listItr++;
	}
	return nullptr;
}

/* Display all identifiers in all active scopes. */
void SymbolTable::display()
{
	int i = 1;
	auto listItr = activeScopes.cbegin();
	while (listItr != activeScopes.cend())
	{
		cout << "scope " << i++ << ": ";
		auto hashtableItr = (*listItr)->cbegin();
		while (hashtableItr != (*listItr)->cend())
		{
			cout << (*hashtableItr)->name << ' ';
			hashtableItr++;
		}
		cout << endl;
		listItr++;
	}
}

