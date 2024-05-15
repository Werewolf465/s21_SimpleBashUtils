#define _GNU_SOURCE
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int b, n, s, E, T, v;
} arguments;

arguments flags_parser(int argc, char** argv) {
  arguments arg = {0};
  struct option long_options[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                  {"number", no_argument, NULL, 'n'},
                                  {"squeeze-blank", no_argument, NULL, 's'},
                                  {0, 0, 0, 0}};
  int opt;
  while ((opt = getopt_long(argc, argv, "beEnsTtv", long_options, 0)) != -1) {
    switch (opt) {
      case 'b':
        arg.b = 1;
        break;
      case 'e':
        arg.E = 1;
        arg.v = 1;
        break;
      case 'E':
        arg.E = 1;
        break;
      case 'n':
        arg.n = 1;
        break;
      case 's':
        arg.s = 1;
        break;
      case 't':
        arg.T = 1;
        arg.v = 1;
        break;
      case 'T':
        arg.T = 1;
        break;
      case '?':
        perror("ERROR");
        exit(1);
        break;
      default:;
        break;
    }
  }
  if ((arg.n == 1) && (arg.b == 1)) arg.n = 0;
  return arg;
}

char print_unprintable_v(char ch) {
  if (ch == '\n' || ch == '\t') return ch;
  if (ch <= 31) {
    putchar('^');
    ch += 64;
  } else if (ch == 127) {
    putchar('^');
    ch = '?';
  }
  return ch;
}

void outline(arguments* arg, char* line, int n) {
  for (int i = 0; i < n; i++) {
    if (arg->T && line[i] == '\t')
      printf("^I");
    else {
      if (arg->b == 0 && arg->E && line[i] == '\n') putchar('$');
      if (arg->b == 1 && arg->E && line[0] == '\n') {
        char ch1 = ' ';
        char ch = '$';
        printf("%6c\t%c", ch1, ch);
      }
      if (arg->b == 1 && arg->E && line[0] != '\n' && line[i] == '\n')
        putchar('$');
      if (arg->v) line[i] = print_unprintable_v(line[i]);
      putchar(line[i]);
    }
  }
}

void output(arguments* arg, char** argv) {
  FILE* f = fopen(argv[optind], "r");
  char* line = NULL;
  size_t nemline = 0;
  int read = 0;

  int line_count = 1;
  int empty_count = 0;
  read = getline(&line, &nemline, f);
  while (read != -1) {
    if (line[0] == '\n')
      empty_count++;
    else
      empty_count = 0;
    if (arg->s && empty_count > 1) {
    } else {
      if (arg->n || arg->b) {
        if (arg->b && line[0] != '\n') {
          printf("%6d\t", line_count);
          line_count++;
        } else if (arg->n) {
          printf("%6d\t", line_count);
          line_count++;
        }
      }
      outline(arg, line, read);
    }
    read = getline(&line, &nemline, f);
  }
  free(line);
  fclose(f);
}

int main(int argc, char* argv[]) {
  arguments arg = flags_parser(argc, argv);
  output(&arg, argv);
  return 0;
}
