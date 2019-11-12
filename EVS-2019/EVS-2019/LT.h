#pragma once
#define LEXEMA_FIXSIZE 1			// ������������� ������ �������
#define LT_MAXSIZE  4096			// ������������ ���������� ����� � ������� ������
#define LT_TI_NULLIDX 0xfffffff		// ��� �������� ������� ���������������
#define LEX_CHISLOVOE	't'			// ������� ��� integer
#define LEX_STROKOVOE	't'			// ������� ��� string
#define LEX_ID			'i'			// ������� ��� ��������������
#define LEX_LITERAL		'l'			// ������� ��� ��������
#define LEX_MAIN		'm'			// ������� ��� main
#define LEX_FUNCTION	'f'			// ������� ��� function	
#define LEX_VARIABL		'k'			// ������� ��� variabl
#define LEX_RETURN		'r'			// ������� ��� return
#define LEX_PRINT		'p'			// ������� ��� print
#define LEX_SEMICOLON	';'			// ������� ��� ;
#define LEX_COMMA		','			// ������� ��� ,
#define LEX_LEFTBRACE	'{'			// ������� ��� {
#define LEX_BRACELET	'}'			// ������� ��� }
#define LEX_LEFTHESIS	'('			// ������� ��� (
#define LEX_RIGHTHESIS	')'			// ������� ��� )
#define LEX_PLUS		'v'			// ������� ��� +
#define LEX_MINUS		'v'			// ������� ��� -
#define LEX_STAR		'v'			// ������� ��� *
#define LEX_DIRSLASH	'v'			// ������� ��� /
#define LEX_EQUALLY		'='			// ������� ��� =
#define LEX_SUBSTR		'i'
#define LEX_STRLEN		'i'
#define LEX_VOSMER		'l'
#define LEX_RAND		'i'
#define LEX_UPP			'i'

namespace LT						// ������� ������
{
	struct Entry					// ������ ������� ������
	{
		char lexema[LEXEMA_FIXSIZE];	// �������
		int sn;						// ����� ������ � �������� ������
		int idxTI;					// ������ � ������� ��������������� ��� LT_TI_NULLIDX
		char znak[1];
		int opr;					// �������� �������� integer �� string
	};

	struct LexTable					// ��������� ������� ������
	{
		int maxsize;				// ������� ������� ������ < LT_MAXSIZE
		int size;					// ������� ������ ������� ������ < maxsize
		Entry* table;				// ������ ����� ������� ������
	};
	LexTable Create(				// ������� ������� ������
			int size				// ������� ������� ������ < LT_MAXSIZE
	);
	void Add(						// �������� ������ � ������� ������
		LexTable& lextable,			// ��������� ������ ������
		Entry entry					// ������ ������� ������
	);

	Entry GetEntry(					// �������� ������ ������� ������
			LexTable& lextable,		// ��������� ������� ������
			int n					// ����� ���������� ������
	);
	void Delete(LexTable& lextable);	// ������� ������� ������ (���������� ������)
};