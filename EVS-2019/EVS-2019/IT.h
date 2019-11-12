#pragma once
#include<string>
#define ID_MAXSIZE 5			    // максимальное количество символов в идентификаторе
#define TI_MAXSIZE  4096			// максимальное количество строк в таблице идентификаторов
#define TI_INT_DEFAULT 0x00000000	// значение по умолчанию дл€ типа integer
#define TI_STR_DEFAULT 0x00			// значение по умолчанию дл€ типа string
#define TI_NULLIDX	 0xffffffff		// нет элемента таблицы идентификаторов
#define TI_STR_MAXSIZE 255


namespace IT						// таблица идентификаторов
{
	enum IDDATATYPE {CHISL=1, STOK=2};		// типы данных идентификаторов: integer, string
	enum IDTYPE	{V=1, F=2, P=3, L=4};	// типы идентификаторов: переменна€, функци€, параметр, литерал
	struct Entry					// строка таблицы идентификаторов
	{
		int idxfirstLE;
		char id[ID_MAXSIZE];		// идентификатор (автоматически усекаетс€ до ID_MAXSIZE)
		IDDATATYPE iddatatype;		// тип данных
		IDTYPE	idtype;				// тип идентификатора
		int podschet;
		int litschet;
		char namefun[5];
		union
		{
			int vint;				// значение integer
			struct
			{
				char len;			// количество символов в string
				char str[TI_STR_MAXSIZE - 1];		// символы string
			}vstr;				// значение string
		}value;					// значение иденттификатора
	};

	struct IdTable					// экземпл€р таблицы индентификаторов
	{
		int maxsize;				// Ємкость таблицы идентификаторов < LT_MAXSIZE
		int size;					// текущий размер таблицы идентификаторов < maxsize
		Entry* table;				// массив строк таблицы идентификаторов
		
	};
	IdTable Create(				// создать таблицу идентификаторов
		int size				// Ємкость таблицы идентификаторов < LT_MAXSIZE
	);
	void Add(						// добавить строку в таблицу идентификаторов
		IdTable& idxtable,			// экземпл€р талицы идентификаторов
		Entry entry					// строка таблицы идентификаторов
	);

	Entry GetEntry(					// получить строку таблицы идентификаторов
		IdTable& idtable,		// экземпл€р таблицы идентификаторов
		int n					// номер получаемой строки
	);
	int IsId(					// возврат: номер строки( если есть), TI_NULLIDX( если нет)
		IdTable& idtable,		// экземпл€р таблицы идентификаторов
		char id[ID_MAXSIZE]		//идентификатор
	);
	int IsIdF(					// возврат: номер строки( если есть), TI_NULLIDX( если нет)
		IdTable& idtable,		// экземпл€р таблицы идентификаторов
		char id[ID_MAXSIZE]	,	//идентификатор
		char namefun[ID_MAXSIZE]
	);
	int IsLitSTR(IdTable& idtable, char lit[ID_MAXSIZE]);
	int IsLitINT(IdTable& idtable, char lit[ID_MAXSIZE],int k);
	void Delete(IdTable& lextable);	// удалить таблицу идентификаторов (освободить пам€ть)
};