/*
 * SymbolTable.h.
 */

#pragma once
#include <string>
#include <unordered_set>
#include <stack>
#include <list>
using namespace std;

/* Each symbol table entry will be of type struct Symbol.  This is easily
expandable to contain more information for each symbol when needed. */
struct Symbol
{
	string name;
	bool operator== (const Symbol & symbol)
	{
		return name == symbol.name;
	}
};

/* SymbolHash is a function object (an object for which the function call
operator is defined) that serves as the hash function for each symbol. */
class SymbolHash
{
public:
	size_t operator() (const Symbol * symbol) const
	{
		return hash<string>()(symbol->name);
	}
};

/* SymbolEqual is a function object that serves as the equivalence criterion
by which two symbols are compared.  */
class SymbolEqual
{
public:
	bool operator() (const Symbol * symbol1, const Symbol * symbol2) const
	{
		return symbol1->name == symbol2->name;
	}
};

class SymbolTable
{
private:
	/* The C++ Standard Library's list data structure is an implementation
	of a doubly-linked list.  This data structure is used instead of a stack
	because the stack data structure only allows access to the top element.
	The findAll method needs to access all the elements starting from the
	back.  Thus, this is a better option.  We do insert and remove only from
	the back of the list, as we would using a stack. 
	
	The unordered_set data structure is implemented as a chained hash table.
	It provides constant time insertion and lookups. 
	
	When a new block/scope is encountered, a pointer to a new unordered_set
	is pushed onto the back of the activeScopes list. 
	
	When a block/scope is closed, it is removed from the activeScopes list
	and saved in the oldScopes list. */

	list<unordered_set<Symbol *, SymbolHash, SymbolEqual> *> activeScopes;
	list<unordered_set<Symbol *, SymbolHash, SymbolEqual> *> oldScopes;

public:
	SymbolTable();
	~SymbolTable();

	void enterNewScope();
	void leaveScope();

	void insert(Symbol *newSymbol);
	Symbol *find(Symbol *symbol);
	Symbol *findAll(Symbol *symbol);
	void display();
};

