#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  fprintf(1, "\033[2J\033[1:1H");
  exit(0);
}
