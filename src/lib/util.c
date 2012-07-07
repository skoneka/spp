#include "util.h"

void
fprintf_v (FILE * out, const char *format, ...)
{
    va_list args;
    va_start (args, format);
    vfprintf (out, format, args);
    va_end (args);
}

char *
util_strip_nl (char *s)
{
    char *c = strrchr (s, '\n');
    if (c) {
        *c = 0;
    }
    return s;
}

int
util_copy_file (FILE * in, FILE * out)
{
    char ch;
    while (!feof (in)) {
        ch = fgetc (in);
        if (ferror (in))
            return 10;
        if (!feof (in))
            fputc (ch, out);
        if (ferror (out))
            return 11;

    }
    return 0;
}
