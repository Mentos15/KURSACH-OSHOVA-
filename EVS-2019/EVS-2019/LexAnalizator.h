#pragma once

#include <iostream>
#include <locale>
#include <cwchar>


#include"ERROR.h" // ��������� ������
#include"Parm.h"  // ��������� ����������
#include"Log.h"   // ������ � ����������
#include"In.h"    // ���� ��������� �����
#include"Out.h"	  // ������ � ������ out
#include"FST.h"
#include "LT.h"
#include "IT.h"

void lex(In::IN in, LT::LexTable &lextable, IT::IdTable &idtable);
