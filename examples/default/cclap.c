#define CCLAP_IMPLEMENTATION
#include "../../cclap.h"

typedef enum FileType { PDF, HTML, IMG } FileType;

// X‑macro mapping for FileType.
#define FILE_TYPE_LIST(X)                                                      \
  X(PDF, "pdf")                                                                \
  X(HTML, "html")                                                              \
  X(IMG, "img")

// Auto-generate the conversion functions for FileType.
ENUM_DEFINE_CONVERTERS(FileType, FILE_TYPE_LIST)

int main(int argc, char **argv) {
  FileType ft;
  char *path = NULL;

  // Define arguments
  cclap_arg args[] = {{.arg_name = {"input", true, true},
                       .type = CCLAP_ARG_TYPE_STRING,
                       .help = "Input file",
                       .dst = &path,
                       .conv = NULL},
                      {.arg_name = {"format", true, true},
                       .type = CCLAP_ARG_TYPE_ENUM,
                       .help = "Output file type (pdf, html, img)",
                       .dst = &ft,
                       .conv = (cclap_enum_conv)FileType_from_string}};

  // Initialize the parser context.
  cclap_context ctx;
  cclap_init(&ctx, argv[0],
             "Example program using cclap with enum support and cclap_arg_name",
             args, sizeof(args) / sizeof(args[0]));

  // Parse the command-line arguments.
  if (cclap_parse(&ctx, argc, argv) != 0) {
    return -1;
  }

  printf("Path: %s\n", path);
  printf("FileType: %s\n", FileType_to_string(ft));
  cclap_print_help(&ctx);

  return 0;
}
