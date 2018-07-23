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
	if (args == sc->NIL)
		return sc->F;
	auto flag = args->_flag;
	//first_arg = sc->pair_car(args);

	return args;
}
#define ADJ 32
#define TYPE_BITS 5
#define T_MASKTYPE      31    /* 0000000000011111 */
#define T_SYNTAX      4096    /* 0001000000000000 */
#define T_IMMUTABLE   8192    /* 0010000000000000 */
#define T_ATOM       16384    /* 0100000000000000 */   /* only for gc */
#define CLRATOM      49151    /* 1011111111111111 */   /* only for gc */
#define MARK         32768    /* 1000000000000000 */
#define UNMARK       32767    /* 0111111111111111 */
pointer foreign_set(scheme *sc, pointer args)
{
	pointer     first_arg;
	pointer     ret;
	char       *varname;
	const char *value;
	if (args == sc->NIL)
		return sc->F;
	auto flag = args->_flag;
	int i = list_length(sc,args);

	first_arg = pair_car(args);
	i = (first_arg)->_flag & T_ATOM;
	if (!is_string(first_arg))
		return sc->F;

	first_arg = pair_car(first_arg);

	return sc->T;
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
	scheme_load_string(&sc, "(set-func \"abc\")");
	//set and retrieve the value of a named object in scheme.
	retcode = sc.retcode;
	scheme_deinit(&sc);

	return retcode;
}