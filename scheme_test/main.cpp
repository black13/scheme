#include "scheme.h"

int main(int argc, char *argv[])
{
	scheme *vm = scheme_init_new();
	scheme_deinit(vm);
	return 0;
}