#pragma once
#pragma warning(disable : 4996)
#include <fstream>
#include "In.h"
#include "Parm.h"
#include "Error.h"
#include "LT.h"
#include "IT.h"

namespace Out
{
	struct OUT			// протокол
	{
		wchar_t outfile[PARM_MAX_SIZE];			// имя файла протокола
		std::wofstream * stream;				// выходной поток протокола
	};

	static OUT INITOUT = { L"", NULL };				//структура для начальной инициализации LOG
	OUT getout(wchar_t outfile[]);					// сформировать структуру OUT
	void WriteInOut(OUT out, In::IN in, LT::LexTable &lextable, IT::IdTable &idtable);				// вывести в протокол заголовок	
	void CloseOut(OUT out);							// закрыть протокол
}
