#pragma once
#pragma warning(disable : 4996)
#include<iostream>

namespace FST {
	struct RELATION {									// �����:������ -> ������� ����� �������� ��
		char symbol;									// ������ ��������
		short nnode;									// ����� ������� �������
		RELATION(
			char c = 0x00,							// ������ ��������
			short ns = NULL								// ����� ���������
		);
	};

	struct NODE											// ������� �����
	{
		short n_relation;								// ���������� ����������� �����
		RELATION *relations;							// ����������� �����
		NODE();
		NODE(
			short n,									// ���������� ����������� �����
			RELATION rel, ...							// ������ �����
		);
	};

	struct FST {										// ������������������� �������� �������

		char* string;							//�������(������,����������� 0�00)
		short position;									// ������� ������� � �������
		short nstates;									// ���������� ��������� ��������
		NODE* nodes;									// ���� ���������: [0] -��������� ���������,[nstate-1] - ��������
		short* rstates;									// ��������� ��������� �������� �� ������ �������
		FST(
			char* s,							//�������(������,����������� 0�00)
			short ns,									// ���������� ��������� ��������
			NODE n, ...									// ������ ���������(���� ���������)
		);
	};

	bool execute(										// ��������� ������������� �������
		FST& fst										// ������������������� �������� �������
	);
}
bool chislovoe(char* c);
bool strokovoe(char* k);
bool function(char* k);
bool variabl(char* k);
bool ret(char* k);
bool print(char* k);
bool mainn(char* k);
bool id(char* k);
bool lit(char* k);
bool literals_integer(char* k);
bool strlenn(char* k);
bool substrr(char* k);
bool vosmer(char* k);
bool rand(char* k);
bool upp(char* k);
bool cycle(char* k);

