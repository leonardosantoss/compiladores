
// AST definitions
#ifndef __ast_h__
#define __ast_h__

// AST for expressions


struct _Attrib{
  enum{
    E_ATTRIB,
    E_ATTRIBCT,
    E_NONATTRIB
  }kind;
  union{
    struct{
      struct _Expr* value;
      char* name;
    }att;
    struct{
      struct _Expr* value;
      char* name;
    }attct;
    char* name;
  }attr;
};

struct _Expr {
  enum { 
    E_INTEGER,
    E_VAR,
    E_OPERATION
  } kind;
  union {
    int value; // for integer values
    char* var;
    struct { 
      int operator; // PLUS, MINUS, etc 
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
  } attr;
};

struct _BoolExpr {
  enum{
    E_BOOL,
    E_BOOLOPERATION
  }kind;
  union{
    struct _Expr* value;
    struct{
      int operator;
      struct _Expr* left;
      struct _Expr* right;
    }op;
  }attr;
};

struct _While {
  enum{
    E_WHILE_EXPR,
    E_WHILE_BOOLEXPR
  }kind;
  union{
    struct _BoolExpr* valueBoolExpr;
    struct _Expr *valueExpr;
  }type;
  struct _CmdList *test;
};

struct _If {
  enum {
    E_IF_EXPR,
    E_IF_BOOLEXPR
  }kind;
  union {
    struct _BoolExpr* valueBoolExpr;
    struct _Expr *valueExpr;
  }type;
  struct _CmdList *test;
};

struct _CharList {
  char* value;
  struct _CharList* next;
};

struct _Printf {
  char *value;
  struct _CharList* varList;
};

struct _Scanf {
  char* value;
  struct _CharList* varList;
};

struct _Cmd
{
  enum{
    E_ATTRIB,
    E_WHILE,
    E_PRINTF,
    E_SCANF,
    E_IF
  }kind;
  union{
    struct _Attrib *Attrib;
    struct _While *While;
    struct _Printf *Printf;
    struct _Scanf *Scanf;
    struct _If *If;
  }type;
};

struct _CmdList
{
  struct _Cmd *Cmd;
  struct _CmdList *next;
};



typedef struct _Expr Expr; // Convenience typedef
typedef struct _BoolExpr BoolExpr;
typedef struct _Attrib Attrib;
typedef struct _While While;
typedef struct _CharList CharList;
typedef struct _Printf Printf;
typedef struct _Cmd Cmd;
typedef struct _CmdList CmdList;
typedef struct _Scanf Scanf;
typedef struct _If If;



// Constructor functions (see implementation in ast.c)

Expr* ast_integer(int v);
Expr* ast_expr_var(char *name);
Expr* ast_operation(int operator, Expr* left, Expr* right);
BoolExpr* ast_boolean(Expr *expr);
BoolExpr* ast_boolean_expr(int operator, Expr* left, Expr* right);
Attrib* ast_attrib_expr_ct(char* name, Expr* expr );
Attrib* ast_attrib_expr(char* name, Expr* expr );
Attrib* ast_non_attrib(char* name);
While* ast_cmd_while_expr(Expr* expr, CmdList* cmdlist);  //Shouldn´t be attrib, needs to be a cmdlist
While* ast_cmd_while_boolexpr(BoolExpr* boolexpr, CmdList* cmdlist);
If* ast_cmd_if_expr(Expr* expr, CmdList* cmdList);
If* ast_cmd_if_boolexpr(BoolExpr* boolexpr, CmdList* cmdList);
CmdList* ast_cmdList(Cmd* cmd, CmdList* cmdList);
Cmd* ast_cmd_attrib(Attrib* attrib);
Cmd* ast_cmd_while(While* whileExpr);
Cmd* ast_cmd_printf(Printf* printfExpr);
Cmd* ast_cmd_scanf(Scanf* scanfExpr);
Cmd* ast_cmd_if(If* ifExpr);
Printf* ast_cmd_printf_expr(char* value, CharList* charList);
Scanf* ast_cmd_scanf_expr(char* value, CharList* charList);
CharList* ast_cmd_charList(char* name, CharList* next);

#endif
