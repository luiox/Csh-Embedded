#include <cshell.h>
#include <string.h>
#include <stdlib.h>

/*
 * If it is initialized ,then set to true.
 */
static bool cshell_initialize_flag = false;

static cshell_getc_pf cshell_getc_func;

static cshell_getc_pf cshell_putc_func;

// Initialize the corresponding IO interface
bool
cshell_initialize_cfg(CShellCfg * cfg)
{
    if (NULL == cfg)
        return false;
    if (NULL == cfg->getc_pf)
        return false;
    if (NULL == cfg->putc_pf)
        return false;
    cshell_getc_func = cfg->getc_pf;
    cshell_putc_func = cfg->putc_pf;
    return true;
}

void
cshell_readline(int8_t * buf, uint32_t maxlen)
{
    if (!cshell_initialize_flag)
        return;

    int i = 0;
    do {
        int8_t ch = cshell_getc_func();
        buf[i] = ch;
    } while (buf[i++] != '\n' && i < maxlen);
    buf[i] = '\0';
}

// simply split the command line into a string array using spaces and return.
int8_t **
cshell_parse_cmdline(int8_t* cmdline)
{
    int8_t ** args = NULL; // store parsed command-line parameters
    int8_t * token = NULL; // tags used to split the command line
    int8_t * delimiters = " ";
    int32_t token_count = 0; // the number of command line parameters

    // using the strtok function to split the command line
    token = strtok(cmdline, delimiters);
    while (token != NULL) {
        args = (int8_t **)realloc(args, (token_count + 1) * sizeof(int8_t *));
        if (args == NULL) {
            // memory allocation failed
            return NULL;
        }
        args[token_count++] = token;
        token = strtok(NULL, delimiters);
    }

    // add the end tag of the parameter array
    args = (int8_t **)realloc(args, (token_count + 1) * sizeof(int8_t *));
    if (args == NULL) {
        // memory allocation failed
        return NULL;
    }
    args[token_count] = NULL;

    return args;
}

// Perform initialization work.
void
cshell_init()
{
    // Now is nothing to do.
}

int32_t
cshell_execute(int8_t ** args)
{
    if(strcmp(args[0], "exit") == 0)
        return 0;
    else
        return 1;
}

void
cshell_start()
{
    int8_t buf[CSHELL_CMDLINE_MAX_BUFFER_SIZE] = { 0 };
    int8_t** args;
    int32_t ret;
    cshell_init();
    do
    {
        cshell_readline(buf, CSHELL_CMDLINE_MAX_BUFFER_SIZE);
        args = cshell_parse_cmdline(buf);
        ret = cshell_execute(args);
        memset(buf, 0, CSHELL_CMDLINE_MAX_BUFFER_SIZE);
    } while (ret);
}
