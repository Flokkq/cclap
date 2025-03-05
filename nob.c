#define NOB_IMPLEMENTATION
#include "nob.h"

int main(int arc, char **argv) {
  NOB_GO_REBUILD_URSELF(arc, argv);

  Nob_Cmd cmd = {0};
  nob_cmd_append(&cmd, "cc", "-Wall", "-Wextra", "-o", "main", "src/main.c");
  if (!nob_cmd_run_sync(cmd)) {
    return 1;
  }

  return 0;
}
