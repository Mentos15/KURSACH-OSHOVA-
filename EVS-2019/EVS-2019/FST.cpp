
#include "FST.h"
#include <string.h>
#include <utility>
#include <wchar.h>
#include <iostream>

using namespace std;

namespace FST {
	FST::FST(char* s, short ns, NODE n, ...)
	{
		string = s;					// цепочка
		position = 0;				// текущая позиция в цепочке
		nstates = ns;				// количество состояний
		NODE *p = &n;
		nodes = new NODE[ns];
		for (int k = 0; k < ns; k++) nodes[k] = p[k];
		rstates = new short[nstates];
		memset(rstates, 0xff, sizeof(short)*nstates);
		rstates[0] = 0;
		position = -1;
	}
	NODE::NODE() {
		n_relation = 0;
		RELATION *relations = NULL;
	}
	NODE::NODE(short n, RELATION rel, ...)
	{
		n_relation = n;
		RELATION *p = &rel;
		relations = new	RELATION[n];
		for (short i = 0; i < n; i++) relations[i] = p[i];
	}
	RELATION::RELATION(char c, short ns)
	{
		symbol = c;			// символ перехода
		nnode = ns;			// новое состояние
	}


	bool step(FST&fst, short* &rstates) {												// один шаг автомата
		bool rc = false;
		std::swap(rstates, fst.rstates);												// смена массивов
		for (short i = 0; i < fst.nstates; i++) {										// все состояния
			if (rstates[i] == fst.position)												// если количество возможных сост на д позициц = текущей позиции
				for (short j = 0; j < fst.nodes[i].n_relation; j++) {					// NODE структура смежных ребер
					if (fst.nodes[i].relations[j].symbol == fst.string[fst.position]) { // = нашему передоваемому символу
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1; // позицию смешаем на 1 во временном массиве
						rc = true;
					};
				};
		};

		return rc;
	};

	bool execute(FST & fst)							// вополнить распознование цепочки
	{
		short * rstates = new short[fst.nstates];			// верменный массив
		memset(rstates, 0xff, sizeof(short)* fst.nstates); // заполняем вр массив -1, nstates размер
		short lstring = strlen(fst.string);				// размер нашей цепочке
		bool rc = true;
		for (short i = 0; i < lstring && rc; i++) {
			fst.position++;							// продвинули позицию
			rc = step(fst, rstates);				// один шаг автомата
		}
		delete[] rstates;
		return (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
	}
}