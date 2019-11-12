#pragma once
#define LEXEMA_FIXSIZE 1			// фиксированный размер лексемы
#define LT_MAXSIZE  4096			// максимальное количество строк в таблице лексем
#define LT_TI_NULLIDX 0xfffffff		// нет элемента таблици идентификаторов
#define LEX_CHISLOVOE	't'			// лексема для integer
#define LEX_STROKOVOE	't'			// лексема для string
#define LEX_ID			'i'			// лексема для идентификатора
#define LEX_LITERAL		'l'			// лексема для литерала
#define LEX_MAIN		'm'			// лексема для main
#define LEX_FUNCTION	'f'			// лексема для function	
#define LEX_VARIABL		'k'			// лексема для variabl
#define LEX_RETURN		'r'			// лексема для return
#define LEX_PRINT		'p'			// лексема для print
#define LEX_SEMICOLON	';'			// лексема для ;
#define LEX_COMMA		','			// лексема для ,
#define LEX_LEFTBRACE	'{'			// лексема для {
#define LEX_BRACELET	'}'			// лексема для }
#define LEX_LEFTHESIS	'('			// лексема для (
#define LEX_RIGHTHESIS	')'			// лексема для )
#define LEX_PLUS		'v'			// лексема для +
#define LEX_MINUS		'v'			// лексема для -
#define LEX_STAR		'v'			// лексема для *
#define LEX_DIRSLASH	'v'			// лексема для /
#define LEX_EQUALLY		'='			// лексема для =
#define LEX_SUBSTR		'i'
#define LEX_STRLEN		'i'
#define LEX_VOSMER		'l'
#define LEX_RAND		'i'
#define LEX_UPP			'i'

namespace LT						// таблица лексем
{
	struct Entry					// строка таблицы лексем
	{
		char lexema[LEXEMA_FIXSIZE];	// лексема
		int sn;						// номер строки в исходном тексте
		int idxTI;					// индекс в таблице идентификаторов или LT_TI_NULLIDX
		char znak[1];
		int opr;					// помогает отличить integer от string
	};

	struct LexTable					// экземпляр таблицы лексем
	{
		int maxsize;				// ёмкость таблицы лексем < LT_MAXSIZE
		int size;					// текущий размер таблицы лексем < maxsize
		Entry* table;				// массив строк таблицы лексем
	};
	LexTable Create(				// создать таблицу лексем
			int size				// ёмкость таблицы лексем < LT_MAXSIZE
	);
	void Add(						// добавить строку в таблицу лексем
		LexTable& lextable,			// экземпляр талицы лексем
		Entry entry					// строка таблицы лексем
	);

	Entry GetEntry(					// получить строку таблицы лексем
			LexTable& lextable,		// экземпляр таблицы лексем
			int n					// номер получаемой строки
	);
	void Delete(LexTable& lextable);	// удалить таблицу лексем (освободить память)
};