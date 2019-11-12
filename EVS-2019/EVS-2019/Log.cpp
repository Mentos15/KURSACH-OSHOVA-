#include "Log.h"
#include "Error.h"
#include "Parm.h"
#include <ctime>
#include <cstdlib>


namespace Log
{
	LOG getlog(wchar_t logfile[])
	{
		LOG lg;
		lg.stream = new std::wofstream(logfile);
		if (!lg.stream)
		{
			throw ERROR_THROW(112);
		}
		else
		{
			wcscpy_s(lg.logfile, logfile);
			return lg;
		}
	}
	void WriteLine(LOG log, const char* c, ...)
	{
		const char **p = &c;
		int k = 0;
		while (p[k] != "")
		{
			*log.stream << p[k];
			k++;
		}
	}
	void WriteLine(LOG log, const wchar_t* c, ...)
	{
		char p[100];
		int k = 0;
		const wchar_t** ptr = &c;
		while (ptr[k] != L"")
		{
			wcstombs(p, ptr[k], 50);
			*log.stream << p;
			k++;
		}

	}
	void WriteLog(LOG log)
	{
		*log.stream << "\n---- �������� ---- ����: ";
		time_t rawtime;
		struct tm * timeinfo;
		char buffer[80];                              // ������, � ������� ����� ��������� ������� �����
		time(&rawtime);                               // ������� ���� � ��������
		timeinfo = localtime(&rawtime);               // �������������� ������ � ��������� �����
		strftime(buffer, 20, "%x %X", timeinfo);      // �������������� ���� � ������
		*log.stream << buffer;
		*log.stream << " ----\n";
	}
	void WriteParm(LOG log, Parm::PARM parm)
	{
		*log.stream << "---- ��������� ----\n";
		*log.stream << "-in: " << parm.in << "\n-out: " << parm.out << "\n-log: " << parm.log << "\n";
	}
	void WriteIn(LOG log, In::IN in)
	{
		*log.stream << "---- �������� ������ ----\n";
		*log.stream << "���������� ��������: " << in.size << "\n���������������: " << in.ignor << "\n���������� �����: " << in.lines << "\n";
	}
	void WriteError(LOG log, Error::ERROR error)
	{
		*log.stream << "������ " << error.id << ": " << error.message;
		*log.stream << ", ������: " << error.inext.line << ", �������: " << error.inext.col;
	}
	void Close(LOG log)
	{
		log.stream->close();
	}
}