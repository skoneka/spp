#include "ui_text.h"

int
main (argc, argv)
     int argc;
     char **argv;
{
  int ret;
  ret = ui_run (argc, argv);
  if(ret)
    fprintf (stderr, "%s:%d ! E:  ERROR in ui_run No. %d\n", __FILE__, __LINE__ , ret);
  return ret;
}
