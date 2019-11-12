#pragma once

#include <iostream>
#include <locale>
#include <cwchar>


#include"ERROR.h" // обработка ошибок
#include"Parm.h"  // обработка параметров
#include"Log.h"   // работа с протоколом
#include"In.h"    // ввод исходного файла
#include"Out.h"	  // работа с файлом out
#include"FST.h"
#include "LT.h"
#include "IT.h"

void lex(In::IN in, LT::LexTable &lextable, IT::IdTable &idtable);
