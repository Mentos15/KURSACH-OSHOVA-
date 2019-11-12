#pragma once
#pragma warning(disable : 4996)
#include <fstream>
#include "In.h"
#include "Parm.h"
#include "ERROR.h"

using namespace std;
namespace Log				// ������ � ����������
{
	struct LOG			// ��������
	{
		wchar_t logfile[PARM_MAX_SIZE];				// ��� ����� ���������
		wofstream * stream;							// �������� ����� ���������
	};

	static const LOG INITLOG = { L"", NULL };				//��������� ��� ��������� ������������� LOG
	LOG getlog(wchar_t logfile[]);							// ������������ ��������� LOG
	void WriteLine(LOG log, const char* c, ...);				// ������� � �������� ������������ �����
	void WriteLine(LOG log, const wchar_t* c, ...);			// ������� � �������� ������������ �����
	void WriteLog(LOG log);									// ������� � �������� ���������	
	void WriteParm(LOG log, Parm::PARM parm);				// ������� � �������� ���������� � ��������	 ����������
	void WriteIn(LOG log, In::IN in);						// ������� � �������� ���������� � �������� ������
	void WriteError(LOG log, Error::ERROR error);			// ������� � �������� ����������  �� ������ 
	void Close(LOG log);									// ������� ��������
}