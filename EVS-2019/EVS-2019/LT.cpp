#include "LT.h"
#include <cstring>
#include <iostream>
int n = 0;

namespace LT
{
	LexTable Create(int size) 
	{
		Entry *entr = new Entry[size];
		LexTable MyTable = LexTable{ size, 0, entr };
		return MyTable;
	}

	void Add(LexTable& lextable, Entry entry) 
	{
		Entry* entries = lextable.table;
		entries[lextable.size] = entry;
		lextable.size++;
	}

	Entry GetEntry(LexTable& lextable, int n) 
	{
		return lextable.table[n];
	}


	void Delete(LexTable& lextable)
	{
		for (int i = lextable.size; i > 0; i--)
			delete& (lextable.table[i]);
		delete &lextable;
	}
}