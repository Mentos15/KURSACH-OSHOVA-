#pragma once
#pragma warning(disable : 4996)
#include <fstream>
#include "In.h"
#include "Parm.h"
#include "ERROR.h"

using namespace std;
namespace Log				// Работа с протоколом
{
	struct LOG			// протокол
	{
		wchar_t logfile[PARM_MAX_SIZE];				// имя файла протокола
		wofstream * stream;							// выходной поток протокола
	};

	static const LOG INITLOG = { L"", NULL };				//структура для начальной инициализации LOG
	LOG getlog(wchar_t logfile[]);							// сформировать структуру LOG
	void WriteLine(LOG log, const char* c, ...);				// вывести в протокол конкатенацию строк
	void WriteLine(LOG log, const wchar_t* c, ...);			// вывести в протокол конкатенацию строк
	void WriteLog(LOG log);									// вывести в протокол заголовок	
	void WriteParm(LOG log, Parm::PARM parm);				// вывести в протокол информацию о выходных	 параметрах
	void WriteIn(LOG log, In::IN in);						// вывести в протокол информацию о выходном потоке
	void WriteError(LOG log, Error::ERROR error);			// вывести в протокол информацию  об ошибке 
	void Close(LOG log);									// закрыть протокол
}