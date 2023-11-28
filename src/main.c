#include <cshell.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char ** argv)
{
    CShellCfg cfg = { .getc_pf = getc, .putc_pf = putc };
    cshell_initialize_cfg(&cfg);
    cshell_start();
    return EXIT_SUCCESS;
}
