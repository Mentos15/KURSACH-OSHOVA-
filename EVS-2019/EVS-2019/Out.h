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
	struct OUT			// ��������
	{
		wchar_t outfile[PARM_MAX_SIZE];			// ��� ����� ���������
		std::wofstream * stream;				// �������� ����� ���������
	};

	static OUT INITOUT = { L"", NULL };				//��������� ��� ��������� ������������� LOG
	OUT getout(wchar_t outfile[]);					// ������������ ��������� OUT
	void WriteInOut(OUT out, In::IN in, LT::LexTable &lextable, IT::IdTable &idtable);				// ������� � �������� ���������	
	void CloseOut(OUT out);							// ������� ��������
}
