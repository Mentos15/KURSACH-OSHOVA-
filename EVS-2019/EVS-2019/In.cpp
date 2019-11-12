
#include "In.h"
#include "ERROR.h"
#include <string>
#include<fstream>
#include<wchar.h>

using namespace std;

namespace In
{
	unsigned char arr[IN_MAX_LEN_TEXT];
	IN getin(wchar_t infile[])
	{

		IN p;
		ifstream file;
		char a;
		p.lines = 0;
		p.ignor = 0;
		p.size = 0;
		int size = 0;
		unsigned int code;
		unsigned char A = 'À';
		char min[] = "-";

		file.open(infile);
		if (!file)
		{
			throw ERROR_THROW(110);
		}
		while (file.get(a))
		{
			code = (unsigned char)a;
			if (a == IN_CODE_ENDL)
			{
				p.lines++;

			}
			if (p.code[code] == IN::T)
			{
				p.size++;
				arr[size] = a;
				size++;
			}
			else if (p.code[code] == IN::F)
			{
				throw ERROR_THROW_IN(111, p.lines, p.size);
			}
			else if (p.code[code] == IN::I)
			{
				p.ignor++;
			}
			else if (code == (int)A)
			{
				p.size++;
				arr[size] = min[0];
				size++;
			}

		}
		file.close();
		p.lines++;
		p.text = arr;
		return p;
	}
}
