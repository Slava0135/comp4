typedef union {
    int   _const;
    char* _id;
} _Operand;
typedef struct {
    int tag; // 1 for CONST, 2 for ID
    _Operand* data;
} Operand;
Operand *makeOperandConst(int _const);
Operand *makeOperandId(char* _id);

typedef struct _Expression {
    struct _Expression *left;  // if NULL operation is unary
    char* op;                  // if NULL expression is terminal
    struct _Expression *right;
    Operand *operand;          // terminal
} Expression;
Expression *makeExpression(Expression *left, char *op, Expression *right);
Expression *makeExpressionOperand(Operand *op);

typedef struct {
    Expression *left;
    char* op;
    Expression *right;
} Statement;
Statement *makeStatement(Expression *left, char *op, Expression *right);

typedef struct {
    char* type;
    char* id;
    Expression *value;
} Declaration;
Declaration *makeDeclaration(char *type, char *op, Expression *value);

typedef struct {
    char* id;
    Expression *value;
} Assignment;
Assignment *makeAssignment(char *id, Expression *value);

typedef union {
    Assignment  *_assignment;
    Declaration *_declaration;
} _Operation;
typedef struct {
    int tag; // 1 for ASSIGNMENT, 2 for DECLARATION
    _Operation *data;
} Operation;
Operation *makeOperationAssignment(Assignment *_assignment);
Operation *makeOperationDeclaration(Declaration *_declaration);

struct _Block; // forward declaration
typedef struct {
    Operation     *operation;
    Statement     *condition;
    Assignment    *assignment;
    struct _Block *block;
} For;
For *makeFor(Operation *operation, Statement *condition, Assignment *assignment, struct _Block *block);

typedef union {
    Operation *_op;
    For       *_for;
} _Action;
typedef struct {
    int tag; // 1 for OPERATION, 2 for FOR
    _Action *data;
} Action;
Action *makeActionOperation(Operation *op);
Action *makeActionFor(For *f);

typedef struct _Block {
    Action    *act;
    struct _Block *block;
} Block;
Block *makeBlock(Action *act, Block *block);

typedef struct {
    Block *block;
} Tree;
Tree *makeTree(Block *block);

void printTree(Tree* tree);