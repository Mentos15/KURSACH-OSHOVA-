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
#include"PolishNotation.h"


void lex(In::IN in, LT::LexTable &lextable, IT::IdTable &idtable)
{
	int intpr = 0, intmai = 0, dop = 0, schetliteralov = 0, schetchikFun = 0;
	int schetprfigskobok = 0, schetlefigskobok = 0;
	std::string str = "";
	bool flag = false;
	char mass[1000];
	char HelpNameFun[5];					// сюда я поменяю имена функция для того, чтобы определять какие переменные принадлежат какой функции
	int dlinnaFun = 0;
	int k = 0, lines = 1, identificators = 0;
	IT::IDDATATYPE datatype;
	IT::IDTYPE type;
	for (int i = 0; i < in.size; i++)
	{
		mass[i] = '\0';
	}
	k = 0;
	
	for (int i = 0; i < in.size; i++)
	{

		mass[k] = in.text[i];
		k++;
		int cas = 0;

		IT::Entry* temp = new IT::Entry;

		if (chislovoe(mass) == true)
		{
			cas = 1;
		}
		if (strokovoe(mass) == true)
		{
			cas = 2;

		}
		if (function(mass) == true)
		{
			cas = 3;
		}
		if (variabl(mass) == true)
		{
			cas = 4;
		}
		if (ret(mass) == true)
		{
			cas = 5;
		}
		if (print(mass) == true)
		{
			cas = 6;
		}
		if (mainn(mass) == true)
		{
			cas = 7;
		}
		if (strlenn(mass) == true)
		{
			cas = 8;
		}
		if (substrr(mass) == true)
		{
			cas = 9;
		}
		if (vosmer(mass) == true && in.text[i + 1] == ';')
		{
			cas = 10;
		}
		if (rand(mass) == true)
		{
			cas = 11;
		}
		if (upp(mass) == true)
		{
			cas = 12;
		}
		if (cycle(mass) == true)
		{
			cas = 13;
		}
		switch (cas)
		{
		case 1:
		{
			Add(lextable, { LEX_CHISLOVOE , lines, LT_TI_NULLIDX }); flag = true;
			lextable.table[lextable.size - 1].opr = 1;
		} break;
		case 2:
		{
			Add(lextable, { LEX_STROKOVOE , lines, LT_TI_NULLIDX });  flag = true;
			lextable.table[lextable.size - 1].opr = 2;
		} break;

		case 3:
		{
			Add(lextable, { LEX_FUNCTION , lines, LT_TI_NULLIDX });  flag = true;

		} break;
		case 4:
		{
			Add(lextable, { LEX_VARIABL , lines, LT_TI_NULLIDX }); flag = true;

		} break;
		case 5:
		{
			Add(lextable, { LEX_RETURN , lines, LT_TI_NULLIDX, });  flag = true;

		} break;
		case 6:
		{
			Add(lextable, { LEX_PRINT , lines, LT_TI_NULLIDX }); flag = true;

		} break;
		case 7:
		{
			Add(lextable, { LEX_MAIN , lines, LT_TI_NULLIDX }); flag = true;

			for (int j = 0; j < 5; j++)
			{
				temp->namefun[j] = '\0';

			}

			for (int j = 0; j < k; j++)
			{
				temp->namefun[j] = mass[j];
				dlinnaFun++;
			}
			for (int j = 0; j < dlinnaFun; j++)
			{
				HelpNameFun[j] = temp->namefun[j];
			}
			for (int j = 0; j < 5 - dlinnaFun; j++)
			{
				HelpNameFun[j + dlinnaFun] = '\0';

			}
		} break;
		case 8:
		{
			Add(lextable, { LEX_STRLEN, lines,   LT_TI_NULLIDX }); flag = true;

		}break;
		case 9:
		{
			Add(lextable, { LEX_SUBSTR , lines,  LT_TI_NULLIDX }); flag = true;

		}break;
		case 10:
		{
			if (IsLitVosmer(idtable, mass, k) == TI_NULLIDX)
			{
				Add(lextable, { LEX_VOSMER , lines, identificators }); flag = true;
				identificators++;
				for (int i = 0; i < k; i++)
				{
					str += mass[i];
				}
				for (int i = 0; i < dlinnaFun; i++)
				{
					temp->namefun[i] = HelpNameFun[i];
				}
				for (int j = 0; j < 5; j++)
				{
					temp->namefun[j + dlinnaFun] = '\0';
				}
				if (lextable.table[lextable.size - 4].lexema[0] == 't')
				{

					if (lextable.table[lextable.size - 4].opr == 2)
					{
						throw ERROR_THROW_IN(118, lines, lextable.size);
					}

				}
				strcpy(temp->value.vint.vosmer, str.c_str());
				temp->idtype = IT::IDTYPE(4);
				temp->iddatatype = IT::IDDATATYPE(1);
				temp->systema = IT::SystSchisl(2);
				IT::Add(idtable, *temp);
				str = "";
			}
			else
			{
				Add(lextable, { LEX_VOSMER , lines, IsLitSTR(idtable,mass) }); flag = true;
			}
			

		}break;
		case 11:
		{
			Add(lextable, { LEX_RAND , lines,  LT_TI_NULLIDX }); flag = true;
		}break;
		case 12:
		{
			Add(lextable, { LEX_UPP , lines,  LT_TI_NULLIDX }); flag = true;
		}break;
		case 13:
		{
			Add(lextable, { LEX_CYCLE , lines,  LT_TI_NULLIDX }); flag = true;
		}break;
		}


		if (id(mass) == true && flag == false)
		{

			if ((in.text[i + 1] == '*') || (in.text[i + 1] == '/') ||
				(in.text[i + 1] == '-') || (in.text[i + 1] == '+') ||
				(in.text[i + 1] == '=') || (in.text[i + 1] == ' ') ||
				(in.text[i + 1] == ';') || (in.text[i + 1] == '(') ||
				(in.text[i + 1] == ')') || (in.text[i + 1] == ',') || (in.text[i + 1] == '\n'))
			{
				if (k >= 1 && k <= ID_MAXSIZE)
				{


					if (lextable.table[lextable.size - 2].lexema[0] == 'f')
					{
						
						
						for (int j = 0; j < 5; j++)
						{
							temp->namefun[j] = '\0';

						}

						for (int j = 0; j < k; j++)
						{
							temp->namefun[j] = mass[j];
							dlinnaFun++;
						}
						for (int j = 0; j < dlinnaFun; j++)
						{
							HelpNameFun[j] = temp->namefun[j];
						}
						for (int j = 0; j < 5 - dlinnaFun; j++)
						{
							HelpNameFun[j + dlinnaFun] = '\0';

						}

					}

					if (IsId(idtable, mass) == TI_NULLIDX)
					{
						Add(lextable, { LEX_ID , lines, identificators }); flag = true;
						identificators++;
						for (int i = 0; i < 5; i++)
						{
							temp->id[i] = '\0';
						}
						for (int i = 0; i < k; i++)
						{
							temp->id[i] = mass[i];
							dop++;
						}
						for (int i = 0; i < dlinnaFun; i++)
						{
							temp->namefun[i] = HelpNameFun[i];
						}
						
						temp->podschet = dop;
						dop = 0;
						if (lextable.table[lextable.size - 3].lexema[0] == 'f')
						{
							temp->idtype = IT::IDTYPE(2);
							if (lextable.table[lextable.size - 2].opr == 1)
							{
								temp->iddatatype = IT::IDDATATYPE(1);
							}
							if (lextable.table[lextable.size - 2].opr == 2)
							{
								temp->iddatatype = IT::IDDATATYPE(2);
							}
							if (lextable.table[lextable.size - 3].lexema[0] != 't') // проверка на наличие типа функции		
							{
								/*throw ERROR_THROW_IN(117, lines, lextable.size);*/
							}
						}

						if (lextable.table[lextable.size - 2].lexema[0] == 't' && lextable.table[lextable.size - 3].lexema[0] != 'f')
						{
							temp->idtype = IT::IDTYPE(1);
							if (lextable.table[lextable.size - 2].opr == 1)
							{
								temp->iddatatype = IT::IDDATATYPE(1);
							}
							if (lextable.table[lextable.size - 2].opr == 2)
							{
								temp->iddatatype = IT::IDDATATYPE(2);
							}
						}

						

						//if (lextable.table[lextable.size - 2].lexema[0] != 't') // проверка на наличие типа идентификатора
						//{
						//	throw ERROR_THROW(114);
						//}

						if ((lextable.table[lextable.size - 3].lexema[0] == ',') ||
							(lextable.table[lextable.size - 3].lexema[0] == '('))
						{
							temp->idtype = IT::IDTYPE(3);

						}

						for (int j = 0; j < 5; j++)
						{
							temp->namefun[j + dlinnaFun] = '\0';
						}
						temp->value.vint.ten = TI_INT_DEFAULT;
						
						temp->value.vstr.len = 0;
						temp->value.vstr.str[0] = TI_STR_DEFAULT;
						IT::Add(idtable, *temp);

					}
					else if (IsIdF(idtable, mass, HelpNameFun) == TI_NULLIDX) //дописать доп условие для повторки функции. Нужно добавить переменную  bool,буду ставить тру когда mass будет функцией и в этом ифе я должен добавить условие на true
					{
						Add(lextable, { LEX_ID , lines, identificators }); flag = true;
						for (int j = 0; j < schetchikFun; j++)
						{
							if (strcmp(idtable.table[j].namefun, HelpNameFun) != 0)
							{

								identificators++;
								for (int i = 0; i < 5; i++)
								{
									temp->id[i] = '\0';
								}
								for (int i = 0; i < k; i++)
								{
									temp->id[i] = mass[i];
									dop++;
								}
								for (int i = 0; i < dlinnaFun; i++)
								{
									temp->namefun[i] = HelpNameFun[i];
								}

								temp->podschet = dop;
								dop = 0;
								if (lextable.table[lextable.size - 2].lexema[0] == 't')
								{
									temp->idtype = IT::IDTYPE(1);
									if (lextable.table[lextable.size - 2].opr == 1)
									{
										temp->iddatatype = IT::IDDATATYPE(1);
									}
									if (lextable.table[lextable.size - 2].opr == 2)
									{
										temp->iddatatype = IT::IDDATATYPE(2);
									}
								}
								//if (lextable.table[lextable.size - 2].lexema[0] != 't') // проверка на наличие типа идентификатора
								//{
								//	throw ERROR_THROW_IN(114,lines,lextable.size);
								//}
								if (lextable.table[lextable.size - 3].lexema[0] == 'f')
								{
									temp->idtype = IT::IDTYPE(2);
									if (lextable.table[lextable.size - 3].opr == 1)
									{
										temp->iddatatype = IT::IDDATATYPE(1);
									}
									if (lextable.table[lextable.size - 3].opr == 2)
									{
										temp->iddatatype = IT::IDDATATYPE(2);
									}
								}

								if ((lextable.table[lextable.size - 3].lexema[0] == ',') ||
									(lextable.table[lextable.size - 3].lexema[0] == '('))
								{
									temp->idtype = IT::IDTYPE(3);

								}

								for (int j = 0; j < 5; j++)
								{
									temp->namefun[j + dlinnaFun] = '\0';
								}
								IT::Add(idtable, *temp); break;
							}

						}
					}
					else
					{

						int numb;
						for (int i = 0; i < idtable.size; i++)
						{
							if ((strcmp(idtable.table[i].namefun, HelpNameFun) == 0 && strcmp(mass, idtable.table[i].id) == 0 && idtable.table[i].idtype != 2) || (strcmp(idtable.table[i].id, idtable.table[i].namefun) == 0 && strcmp(mass, idtable.table[i].id) == 0))
							{
								numb = i;
								break;
							}
						}
						Add(lextable, { LEX_ID , lines, numb }); flag = true;
					}

				}
			}

		}

		if (literals_integer(mass) == true)
		{
			if ((in.text[i + 1] == ' ') || (in.text[i + 1] == ';') || (in.text[i + 1] == '(') || (in.text[i + 1] == ')') || (in.text[i + 1] == ',') || (in.text[i + 1] == '+') || (in.text[i + 1] == '/') || (in.text[i + 1] == '*') || (in.text[i + 1] == '-'))
			{

				if (IsLitINT(idtable, mass, k) == TI_NULLIDX)
				{
					Add(lextable, { LEX_LITERAL , lines, identificators }); flag = true;
					identificators++;
					for (int i = 0; i < k; i++)
					{
						str += mass[i];
					}
					for (int i = 0; i < dlinnaFun; i++)
					{
						temp->namefun[i] = HelpNameFun[i];
					}
					for (int j = 0; j < 5; j++)
					{
						temp->namefun[j + dlinnaFun] = '\0';
					}
					if (lextable.table[lextable.size - 4].lexema[0] == 't')
					{

						if (lextable.table[lextable.size - 4].opr == 2)
						{
							throw ERROR_THROW_IN(118, lines, lextable.size);
						}

					}
					temp->value.vint.ten = atoi(str.c_str());
					temp->idtype = IT::IDTYPE(4);
					temp->iddatatype = IT::IDDATATYPE(1);
					temp->systema = IT::SystSchisl(1);
					IT::Add(idtable, *temp);
					str = "";
				}
				else
				{
					Add(lextable, { LEX_LITERAL , lines, IsLitSTR(idtable,mass) }); flag = true;
				}



			}
		}
		if (lit(mass) == true)
		{
			if ((in.text[i + 1] == ';') || (in.text[i + 1] == '(') || (in.text[i + 1] == ')') || (in.text[i + 1] == ','))
			{
				if (IsLitSTR(idtable, mass) == TI_NULLIDX)
				{


					Add(lextable, { LEX_LITERAL , lines, identificators }); flag = true;

					identificators++;
					for (int i = 0; i < k; i++)
					{
						str += mass[i];

					}
					for (int i = 0; i < dlinnaFun; i++)
					{
						temp->namefun[i] = HelpNameFun[i];
					}
					for (int j = 0; j < 5; j++)
					{
						temp->namefun[j + dlinnaFun] = '\0';
					}
					strcpy(temp->value.vstr.str, str.c_str()); // закидываю строку в массив 
					temp->idtype = IT::IDTYPE(4);
					temp->iddatatype = IT::IDDATATYPE(2);
					IT::Add(idtable, *temp);
					str = "";
				}
				else
				{
					Add(lextable, { LEX_LITERAL , lines, IsLitSTR(idtable,mass) }); flag = true;
				}
			}
		}

		if (mass[k - 1] == ';') cas = 14;
		if (mass[k - 1] == ',') cas = 15;
		if (mass[k - 1] == ')') cas = 16;
		if (mass[k - 1] == '+') cas = 17;
		if (mass[k - 1] == '-') cas = 18;
		if (mass[k - 1] == '*') cas = 19;
		if (mass[k - 1] == '/') cas = 20;
		if (mass[k - 1] == '=') cas = 21;
		if (mass[k - 1] == '{') cas = 22;
		if (mass[k - 1] == '}') cas = 23;
		if (mass[k - 1] == '(') cas = 24;
		if (mass[k - 1] == '$') cas = 25;
		if (mass[k - 1] == ' ')
		{
			flag = true;
			if (mass[0] == '"')
			{
				flag = false;
			}
		}
		if (mass[k - 1] == '\n')
		{
			lines++; flag = true;
		}

		switch (cas)
		{


		case 14:
		{
			Add(lextable, { LEX_SEMICOLON, lines, LT_TI_NULLIDX,';' }); flag = true;
		}break;
		case 15:
		{
			Add(lextable, { LEX_COMMA, lines, LT_TI_NULLIDX,',' }); flag = true;
		}break;
		case 16:
		{
			Add(lextable, { LEX_RIGHTHESIS, lines, LT_TI_NULLIDX, ')' }); flag = true;
		}break;
		case 17:
		{
			Add(lextable, { LEX_PLUS, lines, LT_TI_NULLIDX, '+' }); flag = true;
		}break;
		case 18:
		{
			Add(lextable, { LEX_MINUS, lines, LT_TI_NULLIDX, '-' }); flag = true;
		}break;
		case 19:
		{
			Add(lextable, { LEX_STAR, lines, LT_TI_NULLIDX ,'*'}); flag = true;
		}break;
		case 20:
		{
			Add(lextable, { LEX_DIRSLASH, lines, LT_TI_NULLIDX,'/' }); flag = true;
		}break;
		case 21:
		{
			Add(lextable, { LEX_EQUALLY, lines, LT_TI_NULLIDX, '=' }); flag = true;
		}break;
		case 22:
		{
			Add(lextable, { LEX_LEFTBRACE, lines, LT_TI_NULLIDX,'{' }); flag = true;
			schetlefigskobok++;
		}break;
		case 23:
		{
			Add(lextable, { LEX_BRACELET, lines, LT_TI_NULLIDX,'}' }); flag = true;
			dlinnaFun = 0;
			schetchikFun++;
			schetprfigskobok++;
		}break;
		case 24:
		{
			Add(lextable, { LEX_LEFTHESIS, lines, LT_TI_NULLIDX,'(' }); flag = true;
		}break;
		case 25:
		{
			Add(lextable, { LEX_$, lines, LT_TI_NULLIDX,'$' }); flag = true;
		}break;
		}

		if (flag)
		{
			for (int i = 0; i < k; i++)
			{
				mass[i] = '\0';
			}
			k = 0;
			flag = false;
		}
		if (in.text[i + 1] == '}')
		{
			for (int j = 0; j < 5; j++)
			{
				HelpNameFun[j] = '\0';
			}

		}

		delete temp;
	}
	/*int p=0;
	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexema[0] == 'i')
		{
			if (lextable.table[i + 1].lexema[0] == '(')
			{
				p = i;
				p++;
				while (lextable.table[p].lexema[0] != ')')
				{
					if (lextable.table[i+2].lexema[0] == ')')
					{
						KolParFun = 0;
						break;
					}
					else
					{
						if ((lextable.table[p + 2].lexema[0] == 'i' || lextable.table[p + 1].lexema[0] == 'i') && (lextable.table[p + 2].lexema[0] == ')' || lextable.table[p + 3].lexema[0] == ')'))
						{
							KolParFun++;
						}
						if (lextable.table[p].lexema[0] == ',')
						{
							KolParFun++;
						}
					}
					p++;
				}

				idtable.table[lextable.table[i].idxTI].kolparfun = KolParFun;
			}
		}
	}*/
	char upp[] = { 'u', 'p', 'p', '\0' };
	char ran[] = { 'r', 'a', 'n', 'd', '\0' };
	int KolParFun = 0;
	int numfun;
	for (int i = 0; i < idtable.size; i++)
	{
		if (idtable.table[i].idtype == IT::F &&
			strcmp(idtable.table[i].id, upp) != 0 &&
			strcmp(idtable.table[i].id, ran) != 0)
		{
			numfun = i;
			i++;
			while (idtable.table[i].idtype == IT::P)
			{
				KolParFun++;
				i++;
			}
			idtable.table[numfun].kolparfun = KolParFun;
			KolParFun = 0;
			
		}
	}
	if (schetlefigskobok > schetprfigskobok)
	{
		throw ERROR_THROW(115, lines, lextable.size);
	}
	if (schetprfigskobok > schetlefigskobok)
	{
		throw ERROR_THROW(116, lines, lextable);
	}
}