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
#include "LexAnalizator.h"
#include "Mfst.h"
#include "Grebach.h"
#include "PolishNotation.h"

using namespace std;

bool chislovoe(char* k) {								// цепочка return;(?)*((calc | print);) + ?*end;
	FST::FST myfst(
		k,
		10,													//
		FST::NODE(1, FST::RELATION('c', 1)),
		FST::NODE(1, FST::RELATION('h', 2)),
		FST::NODE(1, FST::RELATION('i', 3)),
		FST::NODE(1, FST::RELATION('s', 4)),
		FST::NODE(1, FST::RELATION('l', 5)),
		FST::NODE(1, FST::RELATION('o', 6)),
		FST::NODE(1, FST::RELATION('v', 7)),
		FST::NODE(1, FST::RELATION('o', 8)),
		FST::NODE(1, FST::RELATION('e', 9)),
	
		FST::NODE()
	);
	return (FST::execute(myfst));
}
bool substrr(char* k) {								// цепочка return;(?)*((calc | print);) + ?*end;
	FST::FST myfst(
		k,
		7,													//
		FST::NODE(1, FST::RELATION('s', 1)),
		FST::NODE(1, FST::RELATION('u', 2)),
		FST::NODE(1, FST::RELATION('b', 3)),
		FST::NODE(1, FST::RELATION('s', 4)),
		FST::NODE(1, FST::RELATION('t', 5)),
		FST::NODE(1, FST::RELATION('r', 6)),
		FST::NODE()
	);
	return (FST::execute(myfst));
}
bool strlenn(char* k) {								// цепочка return;(?)*((calc | print);) + ?*end;
	FST::FST myfst(
		k,
		7,													//
		FST::NODE(1, FST::RELATION('s', 1)),
		FST::NODE(1, FST::RELATION('t', 2)),
		FST::NODE(1, FST::RELATION('r', 3)),
		FST::NODE(1, FST::RELATION('l', 4)),
		FST::NODE(1, FST::RELATION('e', 5)),
		FST::NODE(1, FST::RELATION('n', 6)),
		

		FST::NODE()
	);
	return (FST::execute(myfst));
}
bool strokovoe(char* k) {								// цепочка return;(?)*((calc | print);) + ?*end;
	FST::FST myfst(
		k,
		10,													//
		FST::NODE(1, FST::RELATION('s', 1)),
		FST::NODE(1, FST::RELATION('t', 2)),
		FST::NODE(1, FST::RELATION('r', 3)),
		FST::NODE(1, FST::RELATION('o', 4)),
		FST::NODE(1, FST::RELATION('k', 5)),
		FST::NODE(1, FST::RELATION('o', 6)),
		FST::NODE(1, FST::RELATION('v', 7)),
		FST::NODE(1, FST::RELATION('o', 8)),
		FST::NODE(1, FST::RELATION('e', 9)),

		FST::NODE()
	);
	return (FST::execute(myfst));
}

bool function(char* k) {								// цепочка return;(?)*((calc | print);) + ?*end;
	FST::FST myfst(
		k,
		9,													//
		FST::NODE(1, FST::RELATION('f', 1)),
		FST::NODE(1, FST::RELATION('u', 2)),
		FST::NODE(1, FST::RELATION('n', 3)),
		FST::NODE(1, FST::RELATION('c', 4)),
		FST::NODE(1, FST::RELATION('t', 5)),
		FST::NODE(1, FST::RELATION('i', 6)),
		FST::NODE(1, FST::RELATION('o', 7)),
		FST::NODE(1, FST::RELATION('n', 8)),

		FST::NODE()
	);
	return (FST::execute(myfst));
}

bool variabl(char* k) {								// цепочка return;(?)*((calc | print);) + ?*end;
	FST::FST myfst(
		k,
		8,													//
		FST::NODE(1, FST::RELATION('v', 1)),
		FST::NODE(1, FST::RELATION('a', 2)),
		FST::NODE(1, FST::RELATION('r', 3)),
		FST::NODE(1, FST::RELATION('i', 4)),
		FST::NODE(1, FST::RELATION('a', 5)),
		FST::NODE(1, FST::RELATION('b', 6)),
		FST::NODE(1, FST::RELATION('l', 7)),

		FST::NODE()
	);
	return (FST::execute(myfst));
}
bool ret(char * k) {								// цепочка return;(?)*((calc | print);) + ?*end;
	FST::FST myfst(
		k,
		7,													//
		FST::NODE(1, FST::RELATION('r', 1)),
		FST::NODE(1, FST::RELATION('e', 2)),
		FST::NODE(1, FST::RELATION('t', 3)),
		FST::NODE(1, FST::RELATION('u', 4)),
		FST::NODE(1, FST::RELATION('r', 5)),
		FST::NODE(1, FST::RELATION('n', 6)),

		FST::NODE()
	);
	return (FST::execute(myfst));
}

bool print (char* k) {								// цепочка return;(?)*((calc | print);) + ?*end;
	FST::FST myfst(
		k,
		6,													//
		FST::NODE(1, FST::RELATION('p', 1)),
		FST::NODE(1, FST::RELATION('r', 2)),
		FST::NODE(1, FST::RELATION('i', 3)),
		FST::NODE(1, FST::RELATION('n', 4)),
		FST::NODE(1, FST::RELATION('t', 5)),
	
		FST::NODE()
	);
	return (FST::execute(myfst));
}

bool mainn(char* k) {								// цепочка return;(?)*((calc | print);) + ?*end;
	FST::FST myfst(
		k,
		5,													//
		FST::NODE(1, FST::RELATION('m', 1)),
		FST::NODE(1, FST::RELATION('a', 2)),
		FST::NODE(1, FST::RELATION('i', 3)),
		FST::NODE(1, FST::RELATION('n', 4)),

		FST::NODE()
	);
	return (FST::execute(myfst));
}

//bool vosmer(char* k) {								// цепочка return;(?)*((calc | print);) + ?*end;
//	FST::FST myfst(
//		k,
//		3,													//
//		FST::NODE(1, FST::RELATION('e', 1)), \
//		FST::NODE(9, FST::RELATION('0', 1), \
//		FST::RELATION('1', 1), \
//		FST::RELATION('2', 1),   \
//		FST::RELATION('3', 1), \
//		FST::RELATION('4', 1), \
//		FST::RELATION('5', 1), \
//		FST::RELATION('6', 1), \
//		FST::RELATION('7', 1), \
//		FST::RELATION('e', 2)), \
//
//
//		FST::NODE()
//	);
//	return (FST::execute(myfst));
//}

bool vosmer(char* k) {								// цепочка return;(?)*((calc | print);) + ?*end;
	FST::FST myfst(
		k,
		3,													//
		FST::NODE(1, FST::RELATION('8', 1)), \
		FST::NODE(1, FST::RELATION('x', 2)), \
		FST::NODE(8, FST::RELATION('0', 2), \
			FST::RELATION('1', 2), \
			FST::RELATION('2', 2), \
			FST::RELATION('3', 2), \
			FST::RELATION('4', 2), \
			FST::RELATION('5', 2), \
			FST::RELATION('6', 2), \
			FST::RELATION('7', 2)), \
			


		FST::NODE()
	);
	return (FST::execute(myfst));
}

bool id(char* k) {								// цепочка return;(?)*((calc | print);) + ?*end;
	FST::FST myfst(
		k,
		1,
		FST::NODE(27, FST::RELATION('a', 0), \
		FST::RELATION('b', 0), \
		FST::RELATION('c', 0), \
		FST::RELATION('d', 0), \
		FST::RELATION('e', 0), \
		FST::RELATION('f', 0), \
		FST::RELATION('g', 0), \
		FST::RELATION('h', 0), \
		FST::RELATION('i', 0), \
		FST::RELATION('j', 0), \
		FST::RELATION('k', 0), \
		FST::RELATION('l', 0), \
		FST::RELATION('m', 0), \
		FST::RELATION('n', 0), \
		FST::RELATION('o', 0), \
		FST::RELATION('p', 0), \
		FST::RELATION('q', 0), \
		FST::RELATION('r', 0), \
		FST::RELATION('s', 0), \
		FST::RELATION('t', 0), \
		FST::RELATION('u', 0), \
		FST::RELATION('v', 0), \
		FST::RELATION('w', 0), \
		FST::RELATION('x', 0), \
		FST::RELATION('y', 0), \
		FST::RELATION('z', 0), \
		FST::RELATION('_', 0)), \
		FST::NODE()
	);
	return (FST::execute(myfst));
}

bool lit(char* k) {								// цепочка return;(?)*((calc | print);) + ?*end;
	FST::FST myfst(
		k,
		3,													//
		FST::NODE(1, FST::RELATION('"', 1)), \
		FST::NODE(83, FST::RELATION(' ', 1), \
			FST::RELATION('a', 1), \
			FST::RELATION('b', 1), \
			FST::RELATION('c', 1), \
			FST::RELATION('d', 1), \
			FST::RELATION('e', 1), \
			FST::RELATION('f', 1), \
			FST::RELATION('g', 1), \
			FST::RELATION('h', 1), \
			FST::RELATION('i', 1), \
			FST::RELATION('j', 1), \
			FST::RELATION('k', 1), \
			FST::RELATION('l', 1), \
			FST::RELATION('m', 1), \
			FST::RELATION('n', 1), \
			FST::RELATION('o', 1), \
			FST::RELATION('p', 1), \
			FST::RELATION('q', 1), \
			FST::RELATION('r', 1), \
			FST::RELATION('s', 1), \
			FST::RELATION('t', 1), \
			FST::RELATION('u', 1), \
			FST::RELATION('v', 1), \
			FST::RELATION('w', 1), \
			FST::RELATION('x', 1), \
			FST::RELATION('y', 1), \
			FST::RELATION('z', 1), \
			FST::RELATION('0', 1), \
			FST::RELATION('1', 1), \
			FST::RELATION('2', 1), \
			FST::RELATION('3', 1), \
			FST::RELATION('4', 1), \
			FST::RELATION('5', 1), \
			FST::RELATION('6', 1), \
			FST::RELATION('7', 1), \
			FST::RELATION('8', 1), \
			FST::RELATION('9', 1), \
			FST::RELATION('а', 1), \
			FST::RELATION('б', 1), \
			FST::RELATION('в', 1), \
			FST::RELATION('г', 1), \
			FST::RELATION('д', 1), \
			FST::RELATION('е', 1), \
			FST::RELATION('ё', 1), \
			FST::RELATION('ж', 1), \
			FST::RELATION('з', 1), \
			FST::RELATION('и', 1), \
			FST::RELATION('й', 1), \
			FST::RELATION('к', 1), \
			FST::RELATION('л', 1), \
			FST::RELATION('м', 1), \
			FST::RELATION('н', 1), \
			FST::RELATION('о', 1), \
			FST::RELATION('п', 1), \
			FST::RELATION('р', 1), \
			FST::RELATION('с', 1), \
			FST::RELATION('т', 1), \
			FST::RELATION('у', 1), \
			FST::RELATION('ф', 1), \
			FST::RELATION('х', 1), \
			FST::RELATION('ц', 1), \
			FST::RELATION('ч', 1), \
			FST::RELATION('ш', 1), \
			FST::RELATION('щ', 1), \
			FST::RELATION('ь', 1), \
			FST::RELATION('ъ', 1), \
			FST::RELATION('ы', 1), \
			FST::RELATION('э', 1), \
			FST::RELATION('ю', 1), \
			FST::RELATION('я', 1), \
			FST::RELATION('=', 1), \
			FST::RELATION('+', 1), \
			FST::RELATION('-', 1), \
			FST::RELATION('*', 1), \
			FST::RELATION('/', 1), \
			FST::RELATION('(', 1), \
			FST::RELATION(')', 1), \
			FST::RELATION('{', 1), \
			FST::RELATION('}', 1), \
			FST::RELATION(';', 1), \
			FST::RELATION(',', 1), \
			FST::RELATION('"', 2)), \
		FST::NODE()
	);
	return (FST::execute(myfst));
}

bool literals_integer(char* k) {								// цепочка return;(?)*((calc | print);) + ?*end;
	FST::FST myfst(
		k,
		1,													//
		FST::NODE(10, FST::RELATION('0', 0), \
			FST::RELATION('1', 0), \
			FST::RELATION('2', 0), \
			FST::RELATION('3', 0), \
			FST::RELATION('4', 0), \
			FST::RELATION('5', 0), \
			FST::RELATION('6', 0), \
			FST::RELATION('7', 0), \
			FST::RELATION('8',0), \
			FST::RELATION('9', 0)), \
		FST::NODE()
	);
	return (FST::execute(myfst));
}

bool rand(char* k) {								// цепочка return;(?)*((calc | print);) + ?*end;
	FST::FST myfst(
		k,
		5,													//
		FST::NODE(1, FST::RELATION('r', 1)),
		FST::NODE(1, FST::RELATION('a', 2)),
		FST::NODE(1, FST::RELATION('n', 3)),
		FST::NODE(1, FST::RELATION('d', 4)),

		FST::NODE()
	);
	return (FST::execute(myfst));
}

bool upp(char* k) {								// цепочка return;(?)*((calc | print);) + ?*end;
	FST::FST myfst(
		k,
		4,													//
		FST::NODE(1, FST::RELATION('u', 1)),
		FST::NODE(1, FST::RELATION('p', 2)),
		FST::NODE(1, FST::RELATION('p', 3)),

		FST::NODE()
	);
	return (FST::execute(myfst));
}

bool cycle(char* k)
{
	FST::FST myfst(
		k,
		6,													//
		FST::NODE(1, FST::RELATION('c', 1)),
		FST::NODE(1, FST::RELATION('y', 2)),
		FST::NODE(1, FST::RELATION('c', 3)),
		FST::NODE(1, FST::RELATION('l', 4)),
		FST::NODE(1, FST::RELATION('e', 5)),

		FST::NODE()
	);
	return (FST::execute(myfst));
}




int wmain(int argc, wchar_t* argv[])
{
	setlocale(LC_ALL, "rus");


	Log::LOG log = Log::INITLOG;
	Out::OUT out = Out::INITOUT;
	try
	{
		LT::LexTable lextable = LT::Create(1000);
		IT::IdTable idtable = IT::Create(100);
		Parm::PARM parm = Parm::getparm(argc, argv);

		log = Log::getlog(parm.log);
		Log::WriteLine(log, "Тест:", "без ошибок", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);


		In::IN in = In::getin(parm.in);
		lex(in, lextable, idtable);
		Log::WriteIn(log, in);


		out = Out::getout(parm.out);
		

		/*MFST::Mfst mfst(lextable, GRB::getGreibach());
		mfst.start();
		mfst.savededucation();
		mfst.printrules();*/

		PolishNotation(lextable); // сделать для функий маст хэв
		WriteInOut(out, in, lextable, idtable);
		Out::CloseOut(out);

		cout << "Все готово!" << endl;

	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	};
	Log::Close(log);
	system("pause");
	return 0;
}