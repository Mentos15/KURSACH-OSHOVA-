#pragma once
#include <iostream>
#include "Grebach.h"
#include "LT.h"
#include "Log.h"
#include <stack>

#define MFST_DIAGN_MAXSIZE	2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3

typedef std::stack<short> MFSTSTSTACK;	// ���� ��������
namespace MFST
{
	struct MfstState				// ��������� �������� (��� ����������)
	{
		short lenta_position;		// ������� �� �����
		short nrulechain;			// ����� �������� �������
		short nrule;				// ����� ������� ������� �������� �������
		MFSTSTSTACK st;				// ���� ��������
		MfstState();
		MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain);
		MfstState(
			short pposition,       // ������� �� �����
			MFSTSTSTACK pst,       // ���� ��������
			short pnrule,          // ����� �������� �������
			short pnrulechain      // ����� ������� �������
		);
	};
	struct Mfst						// ���������� �������
	{
		enum RC_STEP {						// ��� �������� ������� step
			NS_OK,					// ������� ������� � �������, ������� �������� � ����
			NS_NORULE,				// �� ������� ������� ���������� (������ � ����������)
			NS_NORULECHAIN,			// �� ������� ���������� ������� ������� (������ � �������� ����)
			NS_ERROR,				// ����������� �������������� ������ ����������
			TS_OK,					// ���. ������ ����� == ������� �����, ������������ �����, pop �����
			TS_NOK,					// ���. ������ ����� != ������� �����, ������������� ��������� 
			LENTA_END,				// ������� ������� ����� >= lenta_size
			SURPRISE				// ����������� ��� �������� (������ � step)
		};

		struct MfstDiagnosis		 // �����������
		{
			short lenta_position;			// ������� �� �����
			RC_STEP rc_step;				// ��� ���������� ����
			short nrule;					// ����� �������
			short nrule_chain;				// ����� ������� �������
			MfstDiagnosis();
			MfstDiagnosis(			 // �����������
				short plenta_position,	// ������� �� �����
				RC_STEP prc_step,		// ��� ���������� ����
				short pnrule,			// ����� ������� 
				short pnrule_chain		// ����� ������� �������
			);
		} diagnosis[MFST_DIAGN_NUMBER];			// ��������� ����� �������� ���������
		GRBALPHABET* lenta;					// ���������������� (TS/NS) ����� (�� LEX)
		short lenta_position;				// ������� ������� �� �����
		short nrule;						// ����� �������� �������
		short nrulechain;					// ����� ������� ������� �������� �������
		short lenta_size;					// ������ �����
		GRB::Greibach grebach;				// ���������� �������
		LT::LexTable lex;						// ��������� ������ ������������ �����������
		MFSTSTSTACK st;							// ���� ��������
		std::stack<MfstState> storestate;	// ���� ��� ���������� ���������
		Mfst();
		Mfst(
			LT::LexTable plex,			// ��������� ������ ������������ �����������
			GRB::Greibach pgrebach			// ���������� �������
		);
		char* getCSt(char* buf);			// �������� ���������� �����
		char* getCLenta(char* buf, short pos, short n = 25);	// �����: n �������� � pos
		char* getDiagnosis(short n, char* buf);		// �������� n-�� ������ ����������� ��� 0�00
		bool savestate();		// ��������� ��������� ��������
		bool reststate();		// ������������ ��������� ��������
		bool push_chain(						// ��������� ������� ������� � ����
			GRB::Rule::Chain chain		// ������� ������
		);
		Mfst::RC_STEP step();	// ��������� ��� ��������
		bool start();	// ��������� �������
		bool savediagnosis(
			RC_STEP pprc_step	// ��� ���������� ����
		);
		void printrules();// ������� ������������������ ������ (������ �������)

		struct Deducation					// �����
		{
			short size;							// ���������� ����� � ������
			short* nrules;						// ������ ������ ����������
			short* nrulechains;					// ������ ������� ������ ���������� (nrules)
			Deducation() { size = 0; nrules = 0; nrulechains = 0; };
		} deducation;
		bool savededucation();					// ��������� ������ ������ (������ �������)
	};
}