#include "CodeGen.h"
#include "IT.h"
#include <iostream>
#include <stack>

using namespace std;

void CodeGeneration(LT::LexTable t, IT::IdTable idif, Out::OUT out)
{
	char RandN[] = { 'R', 'a', 'n', 'd', 'N', 'u', 'm', '\0' };
	char Unicode[] = { 'U', 'n', 'i', 'c', 'o', 'd', 'e', '\0' };
	*out.stream << ".586P\n.MODEL FLAT, stdcall\nincludelib libucrt.lib\nincludelib kernel32.lib\nincludelib ../Debug/SDA-2019lib.lib\nExitProcess PROTO : DWORD";
	*out.stream << "\n\nEXTRN Unicode: PROC\nEXTRN RandNum: PROC\nEXTRN WriteInConsoleChar: PROC\nEXTRN WriteInConsoleUnint: PROC\n\n";
	for (int ll = 0; ll < idif.size; ll++)
	{
		if ((idif.table[ll].idtype == IT::F) &&
			(strcmp(idif.table[ll].id, Unicode) != 0) &&
			(strcmp(idif.table[ll].id, RandN) != 0))
		{
			*out.stream << idif.table[ll].id << " PROTO";
			int nump = idif.table[ll].numOfPar;
			while (nump != 0)
			{
				ll++;
				nump--;
				if (nump != 0)
				{
					if (idif.table[ll].iddatatype == IT::UNI)
						*out.stream << ": DWORD, ";
					else if (idif.table[ll].iddatatype == IT::CH)
						*out.stream << ": SDWORD, "; // BYTE ????????
				}

				else if (nump == 0)
				{
					{
						if (idif.table[ll].iddatatype == IT::UNI)
							*out.stream << ": DWORD\n";
						else if (idif.table[ll].iddatatype == IT::CH)
							*out.stream << ": SDWORD\n";
					}
					break;
				}
			}
		}
	}
	*out.stream << "\n.STACK 8192\n\n";
	*out.stream << ".CONST\n\n";
	for (int i = 0; i < idif.size; i++)
	{
		if (idif.table[i].idtype == IT::L)
		{
			if (idif.table[i].iddatatype == IT::CH)
			{
				*out.stream << "\t" << idif.table[i].id << " SDWORD " << idif.table[i].value.vstr.str << ", 0" << "\n";
			}
			else if (idif.table[i].iddatatype == IT::UNI)
			{
				if (idif.table[i].value.vint.predst == IT::TEN)
				{
					*out.stream << "\t" << idif.table[i].id << " DWORD " << idif.table[i].value.vint.Ten << '\n';
				}
				else if (idif.table[i].value.vint.predst == IT::SIXTEEN)
				{
					*out.stream << "\t" << idif.table[i].id << " DWORD " << idif.table[i].value.vint.Six << "h\n";
				}
			}
		}
	}
	*out.stream << "\n.DATA\n\n";
	for (int i = 0; i < idif.size; i++)
	{

		if ((idif.table[i].idtype == IT::F) &&
			(strcmp(idif.table[i].id, Unicode) != 0) &&
			(strcmp(idif.table[i].id, RandN) != 0))
		{
			if (idif.table[i].iddatatype == IT::UNI)
				*out.stream << "\tret_" << idif.table[i].id << " DWORD ?" << '\n';
			else if (idif.table[i].iddatatype == IT::CH)
				*out.stream << "\tret_" << idif.table[i].id << " SDWORD ?" << '\n';
		}
	}
	for (int i = 0; i < idif.size; i++)
	{

		if (idif.table[i].idtype == IT::V)
		{
			if (idif.table[i].iddatatype == IT::CH)
			{
				*out.stream << "\t" << idif.table[i].fun.namefun << idif.table[i].id << " SDWORD ?\n";
			}
			else if (idif.table[i].iddatatype == IT::UNI)
			{
				*out.stream << "\t" << idif.table[i].fun.namefun << idif.table[i].id << " DWORD ?\n";
			}
		}
	}
	*out.stream << "\n.CODE\n\n";
	for (int i = 0; i < t.size; i++)
	{
		if (t.table[i].idxTI < 100)
		{
			if ((idif.table[t.table[i].idxTI].idtype == IT::F) &&
				(strcmp(idif.table[t.table[i].idxTI].id, Unicode) != 0) &&
				(strcmp(idif.table[t.table[i].idxTI].id, RandN) != 0) &&
				(t.table[i - 2].lexema[0] == 'f'))
			{
				int fnumer = t.table[i].idxTI;
				int nump = idif.table[t.table[i].idxTI].numOfPar;
				*out.stream << idif.table[t.table[i].idxTI].fun.namefun << " PROC ";
				for (int j = 0; j < idif.size; j++)
				{
					if (idif.table[j].idtype == IT::P && (strcmp(idif.table[t.table[i].idxTI].id, idif.table[j].fun.namefun) == 0))
					{
						nump--;
						if (nump != 0)
						{
							if (idif.table[j].iddatatype == IT::UNI)
								*out.stream << idif.table[j].id << ": DWORD, ";
							else if (idif.table[j].iddatatype == IT::CH)
								*out.stream << idif.table[j].id << ": SDWORD, ";
						}

						else if (nump == 0)
						{
							{
								if (idif.table[j].iddatatype == IT::UNI)
									*out.stream << idif.table[j].id << ": DWORD\n";
								else if (idif.table[j].iddatatype == IT::CH)
									*out.stream << idif.table[j].id << ": SDWORD\n";
							}
							break;
						}
					}
				}
				while (t.table[i].lexema[0] != '}')
				{
					if (t.table[i - 1].lexema[0] == '=')
					{
						LT::Entry lex = t.table[i - 2];
						int pos1 = i;
						while (t.table[i].lexema[0] != ';')
						{
							if (t.table[i].lexema[0] == 'i')
							{
								if (idif.table[t.table[i].idxTI].idtype == IT::V)
								{
									*out.stream << "\tpush " << idif.table[t.table[i].idxTI].fun.namefun << idif.table[t.table[i].idxTI].id << "\n";
								}
								else if (idif.table[t.table[i].idxTI].idtype == IT::P)
								{
									*out.stream << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
								}
								else if (idif.table[t.table[i].idxTI].idtype == IT::F)
								{
									int numofp = idif.table[t.table[i].idxTI].numOfPar;
									int l = i;
									i++; // ??????????????? ÊÎÃÄÀ ÂÛÇÛÂÀÅØÜ ÔÓÍÊÖÈÞ, ÃÄÅ ÕÐÀÍÈÒÑß ÐÅÇÓËÜÒÀÒ?
									/*for (int k = l + 1; k < (l + 1 + numofp); k++, i++)
									{
										*out.stream << "\tpush " << idif.table[t.table[k].idxTI].id << "\n";
									}*/
									while (t.table[i].lexema[0] != '@')
									{
										if (idif.table[t.table[i].idxTI].idtype == IT::P || idif.table[t.table[i].idxTI].idtype == IT::L)
										{
											*out.stream << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
										}
										else if (idif.table[t.table[i].idxTI].idtype == IT::V)
										{
											*out.stream << "\tpush " << idif.table[t.table[i].idxTI].fun.namefun << idif.table[t.table[i].idxTI].id << "\n";
										}
										i++;
									}
									*out.stream << "\tcall " << idif.table[t.table[l].idxTI].fun.namefun << "\n";
									if (strcmp(idif.table[t.table[l].idxTI].id, RandN) == 0 ||
										strcmp(idif.table[t.table[l].idxTI].id, Unicode) == 0)
									{
										*out.stream << "\tpush eax\n";
									}
									else
									{
										*out.stream << "\tpush " << "ret_" << idif.table[t.table[l].idxTI].id;
									}
								}
							}
							if (t.table[i].lexema[0] == 'l')
							{
								*out.stream << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
							}
							if (t.table[i].operators[0] == '+')
							{
								*out.stream << "\tpop eax\n\tpop ebx\n\tadd eax, ebx\n\tpush eax\n";
							}
							else if (t.table[i].operators[0] == '-')
							{
								*out.stream << "\tpop eax\n\tpop ebx\n\tsub ebx, eax\n\tpush ebx\n";
							}
							else if (t.table[i].operators[0] == '*')
							{
								*out.stream << "\tpop eax\n\tpop ebx\n\tmul ebx\n\tpush eax\n";
							}
							else if (t.table[i].operators[0] == '/')
							{
								*out.stream << "\tpop ebx\n\tpop eax\n\tdiv ebx\n\tpush eax\n";
							}
							else if (t.table[i].operators[0] == '>')
							{
								*out.stream << "\tpop ebx\n\tpop eax\n\tshr eax, ebx\n\tpush eax\n";
							}
							else if (t.table[i].operators[0] == '<')
							{
								*out.stream << "\tpop ebx\n\tpop eax\n\tshl eax, ebx\n\tpush eax\n";
							}
							i++;
						}
						*out.stream << "\tpop " << idif.table[lex.idxTI].fun.namefun << idif.table[lex.idxTI].id << "\n";
					}
					if (t.table[i].lexema[0] == 'c')
					{
						if (idif.table[t.table[i + 2].idxTI].value.vint.predst == IT::TEN)
							*out.stream << "\tmov ecx, " << idif.table[t.table[i + 2].idxTI].value.vint.Ten << '\n';
						else if (idif.table[t.table[i + 2].idxTI].value.vint.predst == IT::SIXTEEN)
							*out.stream << "\tmov ecx, " << idif.table[t.table[i + 2].idxTI].value.vint.Six << '\n';
						while (t.table[i].lexema[0] != '}')
						{
							if (t.table[i - 1].lexema[0] == '=')
							{
								LT::Entry lex = t.table[i - 2];
								int pos1 = i;
								while (t.table[i].lexema[0] != ';')
								{
									if (t.table[i].lexema[0] == 'i')
									{
										if (idif.table[t.table[i].idxTI].idtype == IT::V)
										{
											*out.stream << "\tpush " << idif.table[t.table[i].idxTI].fun.namefun << idif.table[t.table[i].idxTI].id << "\n";
										}
										else if (idif.table[t.table[i].idxTI].idtype == IT::P)
										{
											*out.stream << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
										}
										else if (idif.table[t.table[i].idxTI].idtype == IT::F)
										{
											int numofp = idif.table[t.table[i].idxTI].numOfPar;
											int l = i;
											i++; // ??????????????? ÊÎÃÄÀ ÂÛÇÛÂÀÅØÜ ÔÓÍÊÖÈÞ, ÃÄÅ ÕÐÀÍÈÒÑß ÐÅÇÓËÜÒÀÒ?
											/*for (int k = l + 1; k < (l + 1 + numofp); k++, i++)
											{
												*out.stream << "\tpush " << idif.table[t.table[k].idxTI].id << "\n";
											}*/
											while (t.table[i].lexema[0] != '@')
											{
												if (idif.table[t.table[i].idxTI].idtype == IT::P || idif.table[t.table[i].idxTI].idtype == IT::L)
												{
													*out.stream << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
												}
												else if (idif.table[t.table[i].idxTI].idtype == IT::V)
												{
													*out.stream << "\tpush " << idif.table[t.table[i].idxTI].fun.namefun << idif.table[t.table[i].idxTI].id << "\n";
												}
												i++;
											}
											*out.stream << "\tcall " << idif.table[t.table[l].idxTI].fun.namefun << "\n";
											if (strcmp(idif.table[t.table[l].idxTI].id, RandN) == 0 ||
												strcmp(idif.table[t.table[l].idxTI].id, Unicode) == 0)
											{
												*out.stream << "\tpush eax\n";
											}
											else
											{
												*out.stream << "\tpush " << "ret_" << idif.table[t.table[l].idxTI].id << '\n';
											}
										}
									}
									if (t.table[i].lexema[0] == 'l')
									{
										*out.stream << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
									}
									if (t.table[i].operators[0] == '+')
									{
										*out.stream << "\tpop eax\n\tpop ebx\n\tadd eax, ebx\n\tpush eax\n";
									}
									else if (t.table[i].operators[0] == '-')
									{
										*out.stream << "\tpop eax\n\tpop ebx\n\tsub ebx, eax\n\tpush ebx\n";
									}
									else if (t.table[i].operators[0] == '*')
									{
										*out.stream << "\tpop eax\n\tpop ebx\n\tmul ebx\n\tpush eax\n";
									}
									else if (t.table[i].operators[0] == '/')
									{
										*out.stream << "\tpop ebx\n\tpop eax\n\tdiv ebx\n\tpush eax\n";
									}
									else if (t.table[i].operators[0] == '>')
									{
										*out.stream << "\tpop ebx\n\tpop eax\n\tshr eax, ebx\n\tpush eax\n";
									}
									else if (t.table[i].operators[0] == '<')
									{
										*out.stream << "\tpop ebx\n\tpop eax\n\tshl eax, ebx\n\tpush eax\n";
									}
									i++;
								}
								*out.stream << "\tpop " << idif.table[lex.idxTI].fun.namefun << idif.table[lex.idxTI].id << "\n";
							}
							if (t.table[i].lexema[0] == 'o')
							{
								*out.stream << "\tpush " << idif.table[t.table[i + 1].idxTI].fun.namefun << idif.table[t.table[i + 1].idxTI].id << '\n';
								if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::CH)
									*out.stream << "\tcall WriteInConsoleChar\n";
								else if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::UNI)
									*out.stream << "\tcall WriteInConsoleUnint\n";
							}
							i++;
						}
						*out.stream << "LOOP CYRCLE\n";
					}
					if (t.table[i].lexema[0] == 'e')
					{
						*out.stream << "\tpush " << idif.table[t.table[i + 1].idxTI].fun.namefun << idif.table[t.table[i + 1].idxTI].id << '\n';
						*out.stream << "\tpop " << "ret_" << idif.table[t.table[i + 1].idxTI].fun.namefun << '\n';
					}
					i++;
				}
				*out.stream << "ret\n";
				*out.stream << idif.table[fnumer].id << " ENDP\n\n";
			}

			if (t.table[i].lexema[0] == 'm')
			{
				*out.stream << "main PROC\nSTART:\n";
				while (t.table[i].lexema[0] != '}')
				{
					if (t.table[i - 1].lexema[0] == '=')
					{
						LT::Entry lex = t.table[i - 2];
						int pos1 = i;
						while (t.table[i].lexema[0] != ';')
						{
							if (t.table[i].lexema[0] == 'i')
							{
								if (idif.table[t.table[i].idxTI].idtype == IT::V)
								{
									*out.stream << "\tpush " << idif.table[t.table[i].idxTI].fun.namefun << idif.table[t.table[i].idxTI].id << "\n";
								}
								else if (idif.table[t.table[i].idxTI].idtype == IT::P)
								{
									*out.stream << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
								}
								else if (idif.table[t.table[i].idxTI].idtype == IT::F)
								{
									int numofp = idif.table[t.table[i].idxTI].numOfPar;
									int l = i;
									i++; // ??????????????? ÊÎÃÄÀ ÂÛÇÛÂÀÅØÜ ÔÓÍÊÖÈÞ, ÃÄÅ ÕÐÀÍÈÒÑß ÐÅÇÓËÜÒÀÒ?
									/*for (int k = l + 1; k < (l + 1 + numofp); k++, i++)
									{
										*out.stream << "\tpush " << idif.table[t.table[k].idxTI].id << "\n";
									}*/
									while (t.table[i].lexema[0] != '@')
									{
										if (idif.table[t.table[i].idxTI].idtype == IT::P || idif.table[t.table[i].idxTI].idtype == IT::L)
										{
											*out.stream << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
										}
										else if (idif.table[t.table[i].idxTI].idtype == IT::V)
										{
											*out.stream << "\tpush " << idif.table[t.table[i].idxTI].fun.namefun << idif.table[t.table[i].idxTI].id << "\n";
										}
										i++;
									}
									*out.stream << "\tcall " << idif.table[t.table[l].idxTI].fun.namefun << "\n";
									if (strcmp(idif.table[t.table[l].idxTI].id, RandN) == 0 ||
										strcmp(idif.table[t.table[l].idxTI].id, Unicode) == 0)
									{
										*out.stream << "\tpush eax\n";
									}
									else
									{
										*out.stream << "\tpush " << "ret_" << idif.table[t.table[l].idxTI].id << '\n';
									}
								}
							}
							if (t.table[i].lexema[0] == 'l')
							{
								*out.stream << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
							}
							if (t.table[i].operators[0] == '+')
							{
								*out.stream << "\tpop eax\n\tpop ebx\n\tadd eax, ebx\n\tpush eax\n";
							}
							else if (t.table[i].operators[0] == '-')
							{
								*out.stream << "\tpop eax\n\tpop ebx\n\tsub ebx, eax\n\tpush ebx\n";
							}
							else if (t.table[i].operators[0] == '*')
							{
								*out.stream << "\tpop eax\n\tpop ebx\n\tmul ebx\n\tpush eax\n";
							}
							else if (t.table[i].operators[0] == '/')
							{
								*out.stream << "\tpop ebx\n\tpop eax\n\tdiv ebx\n\tpush eax\n";
							}
							else if (t.table[i].operators[0] == '>')
							{
								*out.stream << "\tpop ebx\n\tpop eax\n\tshr eax, ebx\n\tpush eax\n";
							}
							else if (t.table[i].operators[0] == '<')
							{
								*out.stream << "\tpop ebx\n\tpop eax\n\tshl eax, ebx\n\tpush eax\n";
							}
							i++;
						}
						*out.stream << "\tpop " << idif.table[lex.idxTI].fun.namefun << idif.table[lex.idxTI].id << "\n";
					}
					if (t.table[i].lexema[0] == 'c')
					{
						if (idif.table[t.table[i + 2].idxTI].value.vint.predst == IT::TEN)
							*out.stream << "\tmov ecx, " << idif.table[t.table[i + 2].idxTI].value.vint.Ten << '\n';
						else if(idif.table[t.table[i + 2].idxTI].value.vint.predst == IT::SIXTEEN)
							*out.stream << "\tmov ecx, " << idif.table[t.table[i + 2].idxTI].value.vint.Six << '\n';
						*out.stream << "CYRCLE:\n";
						while (t.table[i].lexema[0] != ']')
						{
							if (t.table[i - 1].lexema[0] == '=')
							{
								LT::Entry lex = t.table[i - 2];
								int pos1 = i;
								while (t.table[i].lexema[0] != ';')
								{
									if (t.table[i].lexema[0] == 'i')
									{
										if (idif.table[t.table[i].idxTI].idtype == IT::V)
										{
											*out.stream << "\tpush " << idif.table[t.table[i].idxTI].fun.namefun << idif.table[t.table[i].idxTI].id << "\n";
										}
										else if (idif.table[t.table[i].idxTI].idtype == IT::P)
										{
											*out.stream << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
										}
										else if (idif.table[t.table[i].idxTI].idtype == IT::F)
										{
											int numofp = idif.table[t.table[i].idxTI].numOfPar;
											int l = i;
											i++; // ??????????????? ÊÎÃÄÀ ÂÛÇÛÂÀÅØÜ ÔÓÍÊÖÈÞ, ÃÄÅ ÕÐÀÍÈÒÑß ÐÅÇÓËÜÒÀÒ?
											/*for (int k = l + 1; k < (l + 1 + numofp); k++, i++)
											{
												*out.stream << "\tpush " << idif.table[t.table[k].idxTI].id << "\n";
											}*/
											while (t.table[i].lexema[0] != '@')
											{
												if (idif.table[t.table[i].idxTI].idtype == IT::P || idif.table[t.table[i].idxTI].idtype == IT::L)
												{
													*out.stream << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
												}
												else if (idif.table[t.table[i].idxTI].idtype == IT::V)
												{
													*out.stream << "\tpush " << idif.table[t.table[i].idxTI].fun.namefun << idif.table[t.table[i].idxTI].id << "\n";
												}
												i++;
											}
											*out.stream << "\tcall " << idif.table[t.table[l].idxTI].fun.namefun << "\n";
											if (strcmp(idif.table[t.table[l].idxTI].id, RandN) == 0 ||
												strcmp(idif.table[t.table[l].idxTI].id, Unicode) == 0)
											{
												*out.stream << "\tpush eax\n";
											}
											else
											{
												*out.stream << "\tpush " << "ret_" << idif.table[t.table[l].idxTI].id << '\n';
											}
										}
									}
									if (t.table[i].lexema[0] == 'l')
									{
										*out.stream << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
									}
									if (t.table[i].operators[0] == '+')
									{
										*out.stream << "\tpop eax\n\tpop ebx\n\tadd eax, ebx\n\tpush eax\n";
									}
									else if (t.table[i].operators[0] == '-')
									{
										*out.stream << "\tpop eax\n\tpop ebx\n\tsub ebx, eax\n\tpush ebx\n";
									}
									else if (t.table[i].operators[0] == '*')
									{
										*out.stream << "\tpop eax\n\tpop ebx\n\tmul ebx\n\tpush eax\n";
									}
									else if (t.table[i].operators[0] == '/')
									{
										*out.stream << "\tpop ebx\n\tpop eax\n\tdiv ebx\n\tpush eax\n";
									}
									else if (t.table[i].operators[0] == '>')
									{
										*out.stream << "\tpop ebx\n\tpop eax\n\tshr eax, ebx\n\tpush eax\n";
									}
									else if (t.table[i].operators[0] == '<')
									{
										*out.stream << "\tpop ebx\n\tpop eax\n\tshl eax, ebx\n\tpush eax\n";
									}
									i++;
								}
								*out.stream << "\tpop " << idif.table[lex.idxTI].fun.namefun << idif.table[lex.idxTI].id << "\n";
							}
							if (t.table[i].lexema[0] == 'o')
							{
								*out.stream << "\tpush " << idif.table[t.table[i + 1].idxTI].fun.namefun << idif.table[t.table[i + 1].idxTI].id << '\n';
								if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::CH)
									*out.stream << "\tcall WriteInConsoleChar\n";
								else if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::UNI)
									*out.stream << "\tcall WriteInConsoleUnint\n";
							}
							i++;
						}
						*out.stream << "LOOP CYRCLE\n";
					}
					if (t.table[i].lexema[0] == 'e')
					{
						*out.stream << "\n\tpush " << idif.table[t.table[i + 1].idxTI].id << '\n';
						*out.stream << "\tcall ExitProcess\n";
					}
					if (t.table[i].lexema[0] == 'o')
					{
						*out.stream << "\tpush " << idif.table[t.table[i + 1].idxTI].fun.namefun << idif.table[t.table[i + 1].idxTI].id << '\n';
						if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::CH)
							*out.stream << "\tcall WriteInConsoleChar\n";
						else if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::UNI)
							*out.stream << "\tcall WriteInConsoleUnint\n";
					}
					i++;
				}
				*out.stream << "main" << " ENDP\n\nend main";
			}
		}
	}
}