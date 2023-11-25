/****************************************************/
/* File: parse.c                                    */
/* The parser implementation for the TINY compiler  */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "parse.h"

#include "globals.h"
#include "scan.h"
#include "util.h"

static TokenType token; /* holds current token */

/* function prototypes for recursive calls */
static TreeNode* stmt_sequence(void);
static TreeNode* statement(void);
static TreeNode* if_stmt(void);
static TreeNode* repeat_stmt(void);
static TreeNode* assign_stmt(void);
static TreeNode* read_stmt(void);
static TreeNode* write_stmt(void);
static TreeNode* exp(void);
static TreeNode* bitor_exp(void);
static TreeNode* bitand_exp(void);
static TreeNode* bitnot_exp(void);
static TreeNode* simple_exp(void);
static TreeNode* mod_term(void);
static TreeNode* term(void);
static TreeNode* pow_factor(void);
static TreeNode* factor(void);
static TreeNode* for_stmt(void);

static void syntaxError(char* message) {
  fprintf(listing, "\n>>> ");
  fprintf(listing, "Syntax error at line %d: %s", lineno, message);
  Error = TRUE;
}

static void match(TokenType expected) {
  if (token == expected)
    token = getToken();
  else {
    fprintf(listing, "%d %d", expected, token);
    syntaxError("unexpected token -> ");
    printToken(token, tokenString);
    fprintf(listing, "      ");
  }
}

TreeNode* stmt_sequence(void) {
  // fprintf(listing, "stmt start: %d\n", token);
  TreeNode* t = statement();
  TreeNode* p = t;
  while ((token != ENDFILE) && (token != END) && (token != ELSE) &&
         (token != UNTIL) && (token != ENDDO)) {
    TreeNode* q;
    match(SEMI);
    // fprintf(listing, "stmt before: %d\n", token);
    q = statement();
    if (q != NULL) {
      if (t == NULL)
        t = p = q;
      else /* now p cannot be NULL either */
      {
        p->sibling = q;
        p = q;
      }
    }
    // fprintf(listing, "stmt after: %d\n", token);
  }
  return t;
}

// P394
// lineno: 961
TreeNode* statement(void) {
  TreeNode* t = NULL;
  switch (token) {
    case IF:
      t = if_stmt();
      break;
    case REPEAT:
      t = repeat_stmt();
      break;
    case ID:
      t = assign_stmt();
      break;
    case READ:
      t = read_stmt();
      break;
    case WRITE:
      t = write_stmt();
      break;
    case FOR:
      t = for_stmt();
      break;
    default:
      // fprintf(listing, "statement: %d\n", token);
      syntaxError("unexpected token -> ");
      printToken(token, tokenString);
      token = getToken();
      break;
  } /* end case */
  return t;
}

// P394
// lineno: 977
TreeNode* if_stmt(void) {
  TreeNode* t = newStmtNode(IfK);
  match(IF);
  if (t != NULL) t->child[0] = exp();
  if (t != NULL) t->child[1] = stmt_sequence();
  if (token == ELSE) {
    TreeNode* p = newExpNode(OpK);
    if (p != NULL) p->attr.op = token;
    if (t != NULL) t->child[2] = p;
    match(ELSE);
    if (t != NULL) t->child[3] = stmt_sequence();
  }
  return t;
}

// P394
// lineno:991
TreeNode* repeat_stmt(void) {
  TreeNode* t = newStmtNode(RepeatK);
  match(REPEAT);
  if (t != NULL) t->child[0] = stmt_sequence();
  match(UNTIL);
  if (t != NULL) t->child[1] = exp();
  return t;
}

TreeNode* assign_stmt(void) {
  TreeNode* t = newStmtNode(AssignK);
  if ((t != NULL) && (token == ID)) t->attr.name = copyString(tokenString);
  match(ID);
  if (token == ASSIGN) {
    match(ASSIGN);
  } else if (token == PLUSASSIGN) {
    match(PLUSASSIGN);
    t->kind.stmt = PlusAssignK;
  }
  if (t != NULL) t->child[0] = exp();
  return t;
}

TreeNode* read_stmt(void) {
  TreeNode* t = newStmtNode(ReadK);
  match(READ);
  if ((t != NULL) && (token == ID)) t->attr.name = copyString(tokenString);
  match(ID);
  return t;
}

TreeNode* write_stmt(void) {
  TreeNode* t = newStmtNode(WriteK);
  match(WRITE);
  if (t != NULL) t->child[0] = exp();
  return t;
}

TreeNode* exp(void) {
  TreeNode* t = bitor_exp();
  if ((token == LT) || (token == EQ) || (token == GT) || (token == LE) ||
      (token == GE) || (token == NE)) {
    TreeNode* p = newExpNode(OpK);
    if (p != NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
    }
    match(token);
    if (t != NULL) t->child[1] = bitor_exp();
  }
  return t;
}

TreeNode* bitor_exp(void) {
  TreeNode* t = bitand_exp();
  while ((token == BITOR)) {
    TreeNode* p = newExpNode(OpK);
    if (p != NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
      match(token);
      t->child[1] = bitand_exp();
    }
  }
  return t;
}

TreeNode* bitand_exp(void) {
  TreeNode* t = bitnot_exp();
  while ((token == BITAND)) {
    TreeNode* p = newExpNode(OpK);
    if (p != NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
      match(token);
      t->child[1] = bitnot_exp();
    }
  }
  return t;
}

TreeNode* bitnot_exp(void) {
  TreeNode *t = NULL, *q;
  while ((token == BITNOT)) {
    TreeNode* p = newExpNode(OpK);
    if (p != NULL) {
      p->attr.op = token;
      if (t == NULL)
        t = p;
      else
        q->child[0] = p;
      q = p;
      match(token);
      if (token == BITNOT) continue;
      q->child[0] = simple_exp();
    }
  }
  if (t == NULL) t = simple_exp();
  return t;
}

TreeNode* simple_exp(void) {
  TreeNode* t = mod_term();
  while ((token == PLUS) || (token == MINUS) || (token == REOR)) {
    TreeNode* p = newExpNode(OpK);
    if (p != NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
      match(token);
      t->child[1] = mod_term();
    }
  }
  return t;
}

TreeNode* mod_term(void) {
  TreeNode* t = term();
  while ((token == MOD)) {
    TreeNode* p = newExpNode(OpK);
    if (p != NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
      match(token);
      p->child[1] = term();
    }
  }
  return t;
}

TreeNode* term(void) {
  TreeNode* t = pow_factor();
  while ((token == TIMES) || (token == OVER) || (token == RECON)) {
    TreeNode* p = newExpNode(OpK);
    if (p != NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
      match(token);
      p->child[1] = pow_factor();
    }
  }
  return t;
}

TreeNode* pow_factor(void) {
  TreeNode* t = factor();
  while ((token == POW) || (token == RECLOSURE) || (token == REOPTION)) {
    TreeNode* p = newExpNode(OpK);
    if (p != NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
      if (token == POW) {
        match(token);
        p->child[1] = factor();
      } else {
        match(token);
      }
    }
  }
  return t;
}

TreeNode* factor(void) {
  TreeNode* t = NULL;
  switch (token) {
    case NUM:
      t = newExpNode(ConstK);
      if ((t != NULL) && (token == NUM)) t->attr.val = atoi(tokenString);
      match(NUM);
      break;
    case ID:
      t = newExpNode(IdK);
      if ((t != NULL) && (token == ID)) t->attr.name = copyString(tokenString);
      match(ID);
      break;
    case LPAREN:
      match(LPAREN);
      t = exp();
      match(RPAREN);
      break;
    default:
      syntaxError("unexpected token -> ");
      printToken(token, tokenString);
      token = getToken();
      break;
  }
  return t;
}

TreeNode* for_stmt(void) {
  TreeNode* t = newStmtNode(ForK);
  match(FOR);
  if (t != NULL) t->child[0] = assign_stmt();
  if (t != NULL) {
    TreeNode* p = newExpNode(OpK);
    if (p != NULL) p->attr.op = token;
    t->child[1] = p;
  }
  if (token == TO)
    match(TO);
  else if (token == DOWNTO)
    match(DOWNTO);
  if (t != NULL) t->child[2] = exp();
  match(DO);
  if (t != NULL) t->child[3] = stmt_sequence();
  match(ENDDO);
  return t;
}

/****************************************/
/* the primary function of the parser   */
/****************************************/
/* Function parse returns the newly
 * constructed syntax tree
 */
TreeNode* parse(void) {
  TreeNode* t;
  token = getToken();
  t = stmt_sequence();
  if (token != ENDFILE) syntaxError("Code ends before file\n");
  return t;
}
