#ifndef CSHELL_H
#define CSHELL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define CSHELL_CMDLINE_MAX_BUFFER_SIZE 128

typedef int32_t (*cshell_getc_pf)();
typedef int32_t (*cshell_putc_pf)(int32_t ch);

struct tagCShellCfg {
    cshell_getc_pf getc_pf;
    cshell_putc_pf putc_pf;
};
typedef struct tagCShellCfg CShellCfg;
bool cshell_initialize_cfg(CShellCfg * cfg);

void cshell_start();

#endif
