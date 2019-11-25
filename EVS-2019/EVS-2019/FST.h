#pragma once
#pragma warning(disable : 4996)
#include<iostream>

namespace FST {
	struct RELATION {									// ребро:символ -> вершина графа перехода КА
		char symbol;									// символ перехода
		short nnode;									// номер смежной вершины
		RELATION(
			char c = 0x00,							// символ перехода
			short ns = NULL								// новое состояние
		);
	};

	struct NODE											// вершина графа
	{
		short n_relation;								// колияество инцидентных ребер
		RELATION *relations;							// инцидентные ребра
		NODE();
		NODE(
			short n,									// количество инцидентных ребер
			RELATION rel, ...							// список ребер
		);
	};

	struct FST {										// недетерминированный конечный автомат

		char* string;							//цепочка(строка,завершается 0х00)
		short position;									// текущая позиция в цепочке
		short nstates;									// количество состояний автомата
		NODE* nodes;									// граф переходов: [0] -начальное состояние,[nstate-1] - конечное
		short* rstates;									// возможные состояния автомата на данной позиции
		FST(
			char* s,							//цепочка(строка,завершается 0х00)
			short ns,									// количество состояний автомата
			NODE n, ...									// список состояний(граф переходов)
		);
	};

	bool execute(										// выполнить распознование цепочки
		FST& fst										// недетерминированный конечный автомат
	);
}
bool chislovoe(char* c);
bool strokovoe(char* k);
bool function(char* k);
bool variabl(char* k);
bool ret(char* k);
bool print(char* k);
bool mainn(char* k);
bool id(char* k);
bool lit(char* k);
bool literals_integer(char* k);
bool strlenn(char* k);
bool substrr(char* k);
bool vosmer(char* k);
bool rand(char* k);
bool upp(char* k);
bool cycle(char* k);

