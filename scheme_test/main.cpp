# include <math.h>

#include <limits.h>
#include <float.h>
#include <ctype.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "unistd.h"
#include "scheme.h"
#include "scheme-private.h"
#define banner "TinyScheme 1.41"
#if 0
int main(int argc, char *argv[])
{
	//scheme *vm = scheme_init_new();
	struct scheme sc;
	scheme_init(&sc);
	//scheme_load" init.scm
	FILE* fin = fopen("init.scm", "r");
	scheme_load_file(&sc, fin);
	//create a list programatically.
	pointer symbol=nullptr;
	symbol=mk_symbol(&sc, "integer-value");
	scheme_define(&sc,sc.envir,symbol,mk_integer(&sc, 1));
	//setimmutable(symbol);


	scheme_deinit(&sc);
	return 0;
}

#endif
# define InitFile "init.scm"

pointer foreign_get(scheme *sc, pointer args)
{
	pointer     first_arg;
	pointer     ret;
	char       *varname;
	const char *value;

	return args;
}

pointer foreign_set(scheme *sc, pointer args)
{
	pointer     first_arg;
	pointer     ret;
	char       *varname;
	const char *value;

	return args;
}

int main(int argc, char **argv) {

	scheme sc;
	FILE *fin = NULL;
	const char *file_name = InitFile;
	int retcode;
	int isfile = 1;
	scheme_init(&sc);
	fin = fopen(file_name, "r");
	scheme_load_named_file(&sc, fin, file_name);

	scheme_set_output_port_file(&sc, stdout);
	pointer symbol = nullptr;

	scheme_define(&sc,sc.envir,mk_symbol(&sc, "set-func"),mk_foreign_func(&sc, foreign_set));

	symbol = mk_symbol(&sc, "integer-value");
	scheme_define(&sc, sc.envir, symbol, mk_integer(&sc, 1));
	//scheme_load_string(&sc, "(define i 1)");
	scheme_load_string(&sc, "(write integer-value)");
	//set and retrieve the value of a named object in scheme.
	retcode = sc.retcode;
	scheme_deinit(&sc);

	return retcode;
}