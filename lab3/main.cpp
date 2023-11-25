/****************************************************/
/* File: main.c                                     */
/* Main program for TINY compiler                   */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "parse.h"
#include "scan.h"
#include "util.h"

/* set NO_PARSE to TRUE to get a scanner-only compiler */
static int NO_PARSE = 0;

/* allocate global variables */
int lineno = 0;
FILE* source;
FILE* listing;
FILE* code;

/* allocate and set tracing flags */
int EchoSource = FALSE;
int TraceScan = FALSE;
int TraceParse = TRUE;
int TraceAnalyze = FALSE;
int TraceCode = FALSE;

int Error = FALSE;

int main(int argc, char* argv[]) {
  TreeNode* syntaxTree;
  char flag[120]; /* flag of program */
  char pgm[120];  /* source code file name */

  if (argc != 3) {
    fprintf(stderr, "usage: %s <flag> <filename>\n", argv[0]);
    exit(1);
  }

  strcpy(flag, argv[1]);
  if (strcmp(flag, "-p") == 0 || strcmp(flag, "--parse") == 0) {
    NO_PARSE = FALSE;
  } else if (strcmp(flag, "-s") == 0 || strcmp(flag, "--scan") == 0) {
    NO_PARSE = TRUE;
  } else {
    fprintf(stderr, "<flag> should be `-p` / `--parse` or `-s` / `--scan`");
    exit(2);
  }

  strcpy(pgm, argv[2]);
  if (strchr(pgm, '.') == NULL) strcat(pgm, ".tny");
  source = fopen(pgm, "r");
  if (source == NULL) {
    fprintf(stderr, "File %s not found\n", pgm);
    exit(1);
  }
  listing = stdout; /* send listing to screen */
  fprintf(listing, "\nTINY COMPILATION: %s\n", pgm);

  if (NO_PARSE) {
    TokenType token;
    while ((token = getToken()) != ENDFILE) {
      printToken(token, tokenString);
    }
  } else {
    syntaxTree = parse();
    if (TraceParse) {
      fprintf(listing, "\nSyntax tree:\n");
      // printTree(syntaxTree);
      printSyntaxTree(syntaxTree);
    }
  }
  fclose(source);
  return 0;
}
