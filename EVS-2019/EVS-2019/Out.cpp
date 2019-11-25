#include "FST.h"
#include "Out.h"
#include "Error.h"
#include "Parm.h"
#include "LT.h"
#include "IT.h"
#include <ctime>
#include <cstdlib>
#include "PolishNotation.h"

using namespace LT;


namespace Out
{
	OUT getout(wchar_t outfile[])
	{
		OUT out;
		out.stream = new std::wofstream(outfile);
		if (!out.stream)
		{
			throw ERROR_THROW(112);
		}
		else
		{
			wcscpy_s(out.outfile, outfile);
			return out;
		}
	}

	void WriteInOut(OUT out, In::IN in, LT::LexTable &lextable, IT::IdTable &idtable)
	{
		for (int i = 0; i < lextable.table[lextable.size - 1].sn; i++)
		{
			if ((i + 1) < 10)
			{
				*out.stream << '0' << i + 1 << ' ';
			}
			else
			{
				*out.stream << i + 1 << ' ';
			}
			for (int j = 0; j < lextable.size; j++)
			{
				if (lextable.table[j].sn == (i + 1))
				{
					*out.stream << lextable.table[j].lexema[0];
				}
			}
			*out.stream << '\n';

		}

		*out.stream << '\n';
		*out.stream << "\t\t\t\t\t Idintificators Table \t\t" << "\n";

		*out.stream << "_________________________________________________________________________________________________________" << "\n";

		*out.stream << "|" << " Name \t" << " |" << "\t Type ID \t" << " |" << "\t Value \t" << " |" << "\t Type of Date \t" << " |" << "\t Принадлежит функции \t" << "|" << "\n";

		for (int i = 0; i < idtable.size; i++)
		{
			*out.stream << "\n";
			for (int j = 0; j < idtable.table[i].podschet; j++)
			{


				*out.stream << idtable.table[i].id[j];
			}

			if (idtable.table[i].idtype == 1)
			{
				*out.stream << "\t \t Переменная \t \t";

			}
			if (idtable.table[i].idtype == 2)
			{
				*out.stream << "\t \t Функция  \t \t";
			}
			if (idtable.table[i].idtype == 3)
			{
				*out.stream << "\t \t Параметр \t \t";

			}
			*out.stream << "\t\t";
			if (idtable.table[i].idtype == 4)
			{
				*out.stream << " Литерал \t \t";
				if (idtable.table[i].iddatatype == 1)
				{
					if(idtable.table[i].systema == 1)
						*out.stream << idtable.table[i].value.vint.ten << "\t \t";
					if (idtable.table[i].systema == 2)
						*out.stream << idtable.table[i].value.vint.vosmer << "\t \t";

				}
				if (idtable.table[i].iddatatype == 2)
				{
					*out.stream << idtable.table[i].value.vstr.str << "\t \t";

				}

			}


			if (idtable.table[i].iddatatype == 1)
			{
				*out.stream << " chislovoe \t \t";

			}
			if (idtable.table[i].iddatatype == 2)
			{
				*out.stream << "strokovoe \t \t";

			}
			*out.stream << "\t\t";

			*out.stream << idtable.table[i].namefun << "\t \t";

			*out.stream << "\n _________________________________________________________________________________________________________" << "\n";


		}
	/*	for (int i = 0; i < lextable.table[lextable.size - 1].sn; i++)
		{
			if ((i + 1) < 10)
			{
				*out.stream << '0' << i + 1 << ' ';
			}
			else
			{
				*out.stream << i + 1 << ' ';
			}
			for (int j = 0; j < lextable.size; j++)
			{
				if (lextable.table[j].sn == (i + 1))
				{
					*out.stream << lextable.table[j].lexema[0];
				}
			}
			*out.stream << '\n';

		}*/
	}
	
	void CloseOut(OUT out)
	{
		out.stream->close();
	}
}

