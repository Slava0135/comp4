#include "tree.h"
#include "stdio.h"
#include "string.h"
#include "malloc.h"

Operand *makeOperandConst(int _const) {
    _Operand *data = malloc(sizeof(_Operand));
    data->_const = _const;
    Operand *operand = malloc(sizeof(Operand));
    *operand = (Operand) {1, data};
    return operand;
}

Operand *makeOperandId(char* _id) {
    _Operand *data = malloc(sizeof(_Operand));
    data->_id = strdup(_id);
    Operand *operand = malloc(sizeof(Operand));
    *operand = (Operand) {2, data};
    return operand;
}

Expression *makeExpression(Expression *left, char *op, Expression *right) {
    Expression *expression = malloc(sizeof(Expression));
    *expression = (Expression) {left, op, right, 0};
    return expression;
}

Expression *makeExpressionOperand(Operand *op) {
    Expression *expression = malloc(sizeof(Expression));
    *expression = (Expression) {0, 0, 0, op};
    return expression;
}

Statement *makeStatement(Expression *left, char *op, Expression *right) {
    Statement *statement = malloc(sizeof(Statement));
    *statement = (Statement) {left, op, right};
    return statement;
}

Declaration *makeDeclaration(char *type, char *op, Expression *value) {
    Declaration *declaration = malloc(sizeof(Declaration));
    *declaration = (Declaration) {type, op, value};
    return declaration;
}

Assignment *makeAssignment(char *id, Expression *value) {
    Assignment *assignment = malloc(sizeof(Assignment));
    *assignment = (Assignment) {id, value};
    return assignment;
}

Operation *makeOperationAssignment(Assignment *_assignment) {
    _Operation *data = malloc(sizeof(_Operation));
    data->_assignment = _assignment;
    Operation *operation = malloc(sizeof(Operation));
    *operation = (Operation) {1, data};
    return operation;
}

Operation *makeOperationDeclaration(Declaration *_declaration) {
    _Operation *data = malloc(sizeof(_Operation));
    data->_declaration = _declaration;
    Operation *operation = malloc(sizeof(Operation));
    *operation = (Operation) {2, data};
    return operation;
}

For *makeFor(Operation *operation, Statement *condition, Assignment *assignment, Block *block) {
    For *f = malloc(sizeof(For));
    *f = (For) {operation, condition, assignment, block};
    return f;
}

Action *makeActionOperation(Operation *op) {
    _Action *data = malloc(sizeof(_Action));
    data->_op = op;
    Action *action = malloc(sizeof(Action));
    *action = (Action) {1, data};
    return action;
}

Action *makeActionFor(For *f) {
    _Action *data = malloc(sizeof(_Action));
    data->_for = f;
    Action *action = malloc(sizeof(Action));
    *action = (Action) {2, data};
    return action;
}

Block *makeBlock(Action *act, Block *block) {
    Block *b = malloc(sizeof(Block));
    *b = (Block) {act, block};
    return b;
}

Tree *makeTree(Block *block) {
    Tree *tree = malloc(sizeof(Tree));
    *tree = (Tree) {block};
    return tree;
}

static void printAction(Action *act, int offset);
static void printFor(For *f, int offset);
static void printOperation(Operation *op, int offset);
static void printStatement(Statement *st, int offset);
static void printAssignment(Assignment *a, int offset);
static void printBlock(Block *b, int offset);
static void printDeclaration(Declaration *d, int offset);
static void printExpression(Expression *ex, int offset);
static void printOperand(Operand *op, int offset);

void printTree(Tree *tree) {
    fprintf(stderr, "TREE:\n");
    printBlock(tree->block, 0);    
}

static void printAction(Action *act, int offset) {
    if (act->tag == 1) printOperation(act->data->_op, offset);
    if (act->tag == 2) printFor(act->data->_for, offset);
}

static void printFor(For *f, int offset) {
    fprintf(stderr, "%*s%s\n", offset, "", "for");
    if (f->operation)  printOperation(f->operation, offset+1);
    if (f->condition)  printStatement(f->condition, offset+1);
    if (f->assignment) printAssignment(f->assignment, offset+1);
    if (f->block)      printBlock(f->block, offset+1);
}

static void printOperation(Operation *op, int offset) {
    if (op->tag == 1) printAssignment(op->data->_assignment, offset);
    if (op->tag == 2) printDeclaration(op->data->_declaration, offset);
}

static void printStatement(Statement *st, int offset) {
    fprintf(stderr, "%*s%s\n", offset, "", "statement");
    if (st->left)  printExpression(st->left, offset+1);
    if (st->op)    fprintf(stderr, "%*s%s\n", offset, "", st->op);
    if (st->right) printExpression(st->right, offset+1);
}

static void printAssignment(Assignment *a, int offset) {
    fprintf(stderr, "%*s%s\n", offset, "", "assignment");
    if (a->id)    fprintf(stderr, "%*s%s\n", offset, "", a->id);
    if (a->value) printExpression(a->value, offset+1);
}

static void printDeclaration(Declaration *d, int offset) {
    fprintf(stderr, "%*s%s\n", offset, "", "declaration");
    if (d->type)  fprintf(stderr, "%*s%s\n", offset, "", d->type);
    if (d->id)    fprintf(stderr, "%*s%s\n", offset, "", d->id);
    if (d->value) printExpression(d->value, offset+1);
}

static void printBlock(Block *b, int offset) {
    if (b->act)   printAction(b->act, offset);
    if (b->block) printBlock(b->block, offset);
}

static void printExpression(Expression *ex, int offset) {
    if (ex->left)    printExpression(ex->left, offset+1);
    if (ex->op)      fprintf(stderr, "%*s%s\n", offset, "", ex->op);
    if (ex->right)   printExpression(ex->right, offset+1);
    if (ex->operand) printOperand(ex->operand, offset+1);
}

static void printOperand(Operand *op, int offset) {
    if (op->tag == 1) fprintf(stderr, "%*s%d\n", offset, "", op->data->_const);
    if (op->tag == 2) fprintf(stderr, "%*s%s\n", offset, "", op->data->_id);
}