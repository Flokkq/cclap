#ifdef CCLAP_H_
#define CCLAP_H_

#endif // CCLAP_H_

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef enum {
  CCLAP_ARG_TYPE_NONE, // No value, used for flags.
  CCLAP_ARG_TYPE_BOOL, // Boolean flag (automatically true if provided).
  CCLAP_ARG_TYPE_INT,
  CCLAP_ARG_TYPE_FLOAT,
  CCLAP_ARG_TYPE_STRING,
  CCLAP_ARG_TYPE_ENUM,
} cclap_arg_type;

typedef struct {
  const char *name;
  bool long_;
  bool short_;
} cclap_arg_name;

typedef int (*cclap_enum_conv)(const char *src, void *dst);
typedef struct {
  cclap_arg_name arg_name;
  cclap_arg_type type;
  const char *help;
  void *dst;

  // Optional: pointer to a conversion function for enums.
  cclap_enum_conv conv;
} cclap_arg;

typedef struct {
  const char *pname;
  const char *desc;
  cclap_arg *argv;
  int argc;
} cclap_context;

void cclap_init(cclap_context *ctx, const char *pname, const char *desc,
                cclap_arg *argv, int argc);

int cclap_parse(cclap_context *ctx, int argc, char **argv);

void cclap_print_help(const cclap_context *ctx);

// These helper macros are used by the main conversion macro.
#define ENUM_TO_STRING_CASE(val, str)                                          \
  case val:                                                                    \
    return str;
#define ENUM_FROM_STRING_IF(val, str)                                          \
  if (strcmp(buf, str) == 0) {                                                 \
    *e = val;                                                                  \
    return 0;                                                                  \
  } else

// The macro that generates both the to-string and from-string functions.
// 'type' is the enum type, and 'list_macro' is a macro that, when given a macro
// X, calls X(value, "string") for each enum value.
#define ENUM_DEFINE_CONVERTERS(type, list_macro)                               \
  /* to-string conversion */                                                   \
  static const char *type##_to_string(type e) {                                \
    switch (e) { list_macro(ENUM_TO_STRING_CASE) default : return "unknown"; } \
  }                                                                            \
  /* from-string conversion (case-insensitive) */                              \
  static int type##_from_string(const char *s, type *e) {                      \
    char buf[64];                                                              \
    int i;                                                                     \
    for (i = 0; s[i] && i < (int)sizeof(buf) - 1; i++) {                       \
      buf[i] = (char)tolower(s[i]);                                            \
    }                                                                          \
    buf[i] = '\0';                                                             \
    list_macro(ENUM_FROM_STRING_IF) fprintf(                                   \
        stderr, "Error: Unsupported " #type ": '%s'. Supported types: ", s);   \
    list_macro(ENUM_PRINT_SUPPORTED) fprintf(stderr, "\n");                    \
    return -1;                                                                 \
  }

// Helper macro for printing supported types.
#define ENUM_PRINT_SUPPORTED(val, str) fprintf(stderr, "%s ", str);

#ifdef CCLAP_IMPLEMENTATION

void cclap_init(cclap_context *ctx, const char *pname, const char *desc,
                cclap_arg *argv, int argc) {
  return;
}

int cclap_parse(cclap_context *ctx, int argc, char **argv) { return 1; }

void cclap_print_help(const cclap_context *ctx) { return; }

#endif // CCLAP_IMPLEMENTATION
