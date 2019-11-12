#pragma once
#include <iostream>
#include <stack>
#include <locale>
#include "LT.h"			// таблица лексем
#include "IT.h"			// таблица идентификаторов




bool PolishNotation(		// построение польской записи  в таблице  лексем 
	//int		lextable_pos,	// позиция выражения  в lextable
	LT::LexTable& lextable	// таблица лексем
	//IT::IdTable& idtable		// таблица идентификаторов

);
