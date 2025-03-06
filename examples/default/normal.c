#include <ctype.h>
#include <stdio.h>
#include <string.h>

typedef enum FileType { PDF, HTML, IMG } FileType;

/// Turns a string into a [`FileType`].
/// Returns a negative `int` if the conversion failed.
int strtoft(char *src, FileType *ft) {
  for (int i = 0; src[i]; i++) {
    src[i] = tolower(src[i]);
  }

  if (strcmp(src, "pdf") == 0) {
    *ft = PDF;
  } else if (strcmp(src, "html") == 0) {
    *ft = HTML;
  } else if (strcmp(src, "img") == 0) {
    *ft = IMG;
  } else {
    return -1;
  }

  return 0;
}

/// Converts a [`FileType`] to its string representation.
const char *fttostr(FileType ft) {
  printf("FT: %d\n", ft);
  switch (ft) {
  case PDF:
    return "pdf";
  case HTML:
    return "html";
  case IMG:
    return "img";
  default:
    return "unknown";
  }
}

int parse_args(char **argv, char **path, FileType *ft) {
  if (strcmp(argv[1], "-i") == 0) {
    if (strlen(argv[2]) > 64) return -1;
    *path = argv[2];

    if (strcmp(argv[3], "-f") == 0) {
      if (strtoft(argv[4], ft) < 0) return -1;
    } else {
      return -1;
    }
    return 0;
  }

  if (strcmp(argv[1], "-f") == 0) {
    if (strtoft(argv[2], ft) < 0) return -1;

    if (strcmp(argv[3], "-i") == 0) {
      if (strlen(argv[4]) > 64) return -1;
      *path = argv[4];
    } else {
      return -1;
    }
    return 0;
  }
  return -1;
}

int main(int argc, char **argv) {
  if (argc < 5) {
    fprintf(stderr, "Not enough arguments provided.\nUsage: ./main -i <in> -f "
                    "<format>[PDF, HTML, IMG]\n");
    return -1;
  }

  FileType ft;
  char *path = NULL;
  if (parse_args(argv, &path, &ft) < 0) return -1;

  printf("Path: %s\n", path);
  printf("FileType: %s\n", fttostr(ft));
  return 0;
}
