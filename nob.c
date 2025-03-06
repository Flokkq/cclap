#define NOB_IMPLEMENTATION
#define NOB_EXPERIMENTAL_DELETE_OLD
#include "nob.h"

#define COMMON_CFLAGS "-Wall", "-Wextra"

void build_normal_example(Nob_Cmd *cmd, Nob_Procs *procs, const char *name) {
  const char *src = nob_temp_sprintf("examples/%s/normal.c", name);

  nob_cmd_append(cmd, "cc", COMMON_CFLAGS, "-o",
                 nob_temp_sprintf("bin/%s_normal", name), src);
  nob_da_append(procs, nob_cmd_run_async_and_reset(cmd));
}

void build_cclap_example(Nob_Cmd *cmd, Nob_Procs *procs, const char *name) {
  const char *src = nob_temp_sprintf("examples/%s/cclap.c", name);

  nob_cmd_append(cmd, "cc", COMMON_CFLAGS, "-o",
                 nob_temp_sprintf("bin/%s_cclap", name), src);
  nob_da_append(procs, nob_cmd_run_async_and_reset(cmd));
}

int main(int argc, char **argv) {
  NOB_GO_REBUILD_URSELF(argc, argv);

  Nob_Cmd cmd = {0};
  Nob_Procs procs = {0};

  const char *out_path = "bin";
  nob_mkdir_if_not_exists(out_path);

  const char *names[] = {"default"};
  size_t thread_count = 6;

  for (size_t i = 0; i < NOB_ARRAY_LEN(names); ++i) {
    build_normal_example(&cmd, &procs, names[i]);
    if (procs.count >= thread_count) {
      if (!nob_procs_wait_and_reset(&procs)) return 1;
    }
  }

  for (size_t i = 0; i < NOB_ARRAY_LEN(names); ++i) {
    build_cclap_example(&cmd, &procs, names[i]);
    if (procs.count >= thread_count) {
      if (!nob_procs_wait_and_reset(&procs)) return 1;
    }
  }
  return 0;
}
