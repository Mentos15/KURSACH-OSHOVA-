#include "IT.h"
#include <cstring>

namespace IT
{
	IdTable Create(int size) {
		Entry* entries = new Entry[size];
		IdTable mytable = IdTable{ size, 0, entries };
		return mytable;
	}

	void Add(IdTable& idtable, Entry entry) {
		Entry* entries = idtable.table;
		entries[idtable.size] = entry;
		idtable.size++;
	}

	Entry GetEntry(IdTable& idtable, int n) {
		return idtable.table[n];
	}

	int IsId(IdTable& idtable, char id[ID_MAXSIZE]) {
		for (int i = 0; i < idtable.size; i++) {
			if (strcmp(idtable.table[i].id, id) == 0)
				return i;
		}
		return TI_NULLIDX;
	}
	int IsIdF(IdTable& idtable, char id[ID_MAXSIZE], char namefun[ID_MAXSIZE]) {
		for (int i = 0; i < idtable.size; i++) {
			if ((strcmp(idtable.table[i].id, id) == 0) && (strcmp(idtable.table[i].namefun,namefun))==0)
				return i;
		}
		return TI_NULLIDX;
	}
	int IsLitSTR(IdTable& idtable, char lit[ID_MAXSIZE]) {
		for (int i = 0; i < idtable.size; i++) {
			if (strcmp(idtable.table[i].value.vstr.str, lit) == 0)
				return i;
		}
		return TI_NULLIDX;
	}
	int IsLitINT(IdTable& idtable, char lit[ID_MAXSIZE], int k) {
		std::string str = "";
		for (int i = 0; i < k; i++)
		{
			str += lit[i];
		}
		int time = atoi(str.c_str());
		for (int i = 0; i < idtable.size; i++) {
			if (idtable.table[i].value.vint.ten == time )
				return i;
		}
		return TI_NULLIDX;
	}
	int IsLitVosmer(IdTable& idtable, char lit[ID_MAXSIZE], int k) {
		std::string str = "";
		int q = 0;
		for (int i = 0; i < k; i++)
		{
			str += lit[i];
		
		}
		for (int i = 0; i < idtable.size; i++) {
			if (idtable.table[i].value.vint.vosmer == str)
			{
				return i;
			}
		}
		return TI_NULLIDX;
	}

	void Delete(IdTable& idtable) {
		for (int i = idtable.size; i > 0; i--)
			delete &(idtable.table[i]);
		delete& idtable;
	}
}