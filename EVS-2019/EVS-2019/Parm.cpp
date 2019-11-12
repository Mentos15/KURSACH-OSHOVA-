#include"Parm.h"
#include "ERROR.h"
#include<wchar.h>
namespace Parm
{
	PARM getparm(int argc, wchar_t* argv[])		// argv - имя входного файла argc - количество файлов
	{
		bool in = false, out = false, log = false;
		PARM struc;
		wchar_t* ptr;

		for (int i = 1; i < argc; i++)
		{
			if (wcslen(argv[i]) > PARM_MAX_SIZE)
			{
				throw ERROR_THROW(104);
			}
		}
		for (int i = 1; i < argc; i++)
		{
			if (wcsstr(argv[i], PARM_IN))
			{
				ptr = argv[i];
				ptr += wcslen(PARM_IN);
				wcscpy_s(struc.in, ptr);
				in = true;
			}
			if (wcsstr(argv[i], PARM_OUT))
			{
				ptr = argv[i];
				ptr += wcslen(PARM_OUT);
				wcscpy_s(struc.out, ptr);
				out = true;
			}
			if (wcsstr(argv[i], PARM_LOG))
			{
				ptr = argv[i];
				ptr += wcslen(PARM_LOG);
				wcscpy_s(struc.log, ptr);
				log = true;
			}

		}
		if (!in)
		{
			throw ERROR_THROW(100);
		}
		if (!out)
		{
			wcscpy_s(struc.out, struc.in);
			wcscat_s(struc.out, PARM_OUT_DEFAULT_EXT);
		}
		if (!log)
		{
			wcscpy_s(struc.log, struc.in);
			wcscat_s(struc.log, PARM_LOG_DEFAULT_EXT); //заменяем struc.log на  PARM_LOG_DEFAULT_EXT
		}
		return struc;
	}

}
