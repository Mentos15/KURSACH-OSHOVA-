#pragma once
#include<string>
#define ID_MAXSIZE 5			    // ������������ ���������� �������� � ��������������
#define TI_MAXSIZE  4096			// ������������ ���������� ����� � ������� ���������������
#define TI_INT_DEFAULT 0x00000000	// �������� �� ��������� ��� ���� integer
#define TI_STR_DEFAULT 0x00			// �������� �� ��������� ��� ���� string
#define TI_NULLIDX	 0xffffffff		// ��� �������� ������� ���������������
#define TI_STR_MAXSIZE 255


namespace IT						// ������� ���������������
{
	enum IDDATATYPE {CHISL=1, STOK=2};		// ���� ������ ���������������: integer, string
	enum IDTYPE	{V=1, F=2, P=3, L=4};	// ���� ���������������: ����������, �������, ��������, �������
	struct Entry					// ������ ������� ���������������
	{
		int idxfirstLE;
		char id[ID_MAXSIZE];		// ������������� (������������� ��������� �� ID_MAXSIZE)
		IDDATATYPE iddatatype;		// ��� ������
		IDTYPE	idtype;				// ��� ��������������
		int podschet;
		int litschet;
		char namefun[5];
		union
		{
			int vint;				// �������� integer
			struct
			{
				char len;			// ���������� �������� � string
				char str[TI_STR_MAXSIZE - 1];		// ������� string
			}vstr;				// �������� string
		}value;					// �������� ���������������
	};

	struct IdTable					// ��������� ������� ����������������
	{
		int maxsize;				// ������� ������� ��������������� < LT_MAXSIZE
		int size;					// ������� ������ ������� ��������������� < maxsize
		Entry* table;				// ������ ����� ������� ���������������
		
	};
	IdTable Create(				// ������� ������� ���������������
		int size				// ������� ������� ��������������� < LT_MAXSIZE
	);
	void Add(						// �������� ������ � ������� ���������������
		IdTable& idxtable,			// ��������� ������ ���������������
		Entry entry					// ������ ������� ���������������
	);

	Entry GetEntry(					// �������� ������ ������� ���������������
		IdTable& idtable,		// ��������� ������� ���������������
		int n					// ����� ���������� ������
	);
	int IsId(					// �������: ����� ������( ���� ����), TI_NULLIDX( ���� ���)
		IdTable& idtable,		// ��������� ������� ���������������
		char id[ID_MAXSIZE]		//�������������
	);
	int IsIdF(					// �������: ����� ������( ���� ����), TI_NULLIDX( ���� ���)
		IdTable& idtable,		// ��������� ������� ���������������
		char id[ID_MAXSIZE]	,	//�������������
		char namefun[ID_MAXSIZE]
	);
	int IsLitSTR(IdTable& idtable, char lit[ID_MAXSIZE]);
	int IsLitINT(IdTable& idtable, char lit[ID_MAXSIZE],int k);
	void Delete(IdTable& lextable);	// ������� ������� ��������������� (���������� ������)
};