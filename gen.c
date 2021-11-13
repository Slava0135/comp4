#include "gen.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_LABEL_LENGTH 32
#define INT_SIZE 4
#define TEMP_REGISTERS 7

static void compilationError() {
    exit(0);
}

static void genBlock(Block *block);
static void genAction(Action *act);
static void genOperation(Operation *op);
static void genAssignment(Assignment *assignment);
static void genDeclaration(Declaration *declaration);
static void genFor(For *f);

static void genStatement(Statement *statement);
static void genCondition(Statement *statement, char* label);
static void genExpression(Expression *exp, char* target, char* recover);

typedef struct _Var {
    char* id;
    int   index;
    int   hasValue;
    struct _Var *next;
} Var;

typedef struct _Scope {
    int offset;
    struct _Scope *prev;
    struct _Scope *next;
    Var *vars;
} Scope;

static Scope *root;
static Scope *top;

static int stack_offset = 0;

static void addScope() {
    Scope *scope = malloc(sizeof(Scope));
    *scope = (Scope) {stack_offset, top, NULL, NULL};
    top->next = scope;
    top = scope;
}

static void popScope() {
    Scope *scope = top;
    top = top->prev;
    stack_offset = scope->offset;
}

static Var *addVar(char* name) {

    Var *var = top->vars;
    while (var) {
        if (!strcmp(var->id, name)) {
            fprintf(stderr, "Variable %s was declared twice!\n", name);
            compilationError();
        }
        var = var->next;
    }

    var = malloc(sizeof(Var));
    *var = (Var) {name, stack_offset++, 0, NULL};
    if (top->vars) {
        Var *v = top->vars;
        while(v->next) {
            v = v->next;
        }
        v->next = var;
    } else {
        top->vars = var;
    }

    return var;
}

static Var *findVar(char* name) {
    Scope *scope = top;
    while (scope) {
        Var *var = scope->vars;
        while (var) {
            if (!strcmp(var->id, name)) {
                return var;
            }
            var = var->next;
        }
        scope = scope->prev;
    }
    return NULL;
}

static char* makeLabel() {
    static int n = 0;
    char* label = malloc(MAX_LABEL_LENGTH);
    sprintf(label, "LABEL%d", ++n);
    return label;
}


static void genPrologue();
static void genEpilogue();
void generateCode(char* name, Tree *tree) {
    genPrologue(name);
    genBlock(tree->block);
    genEpilogue();
}

static void genPrologue() {
    printf(".globl main\n\n");
    printf(".text\n\n");
    printf("main:\n");
    printf("\n");

    root = malloc(sizeof(Scope));
    *root = (Scope) {0, NULL, NULL, NULL};
    top = root;
}

static void genEpilogue() {
    printf("\n");
    printf("li\ta0, 10\n");
    printf("ecall\n");  
}

static void genBlock(Block *block) {
    genAction(block->act);
    if (block->block) genBlock(block->block);
}

static void genAction(Action *act) {
    if (act->tag == 1) genOperation(act->data->_op);
    if (act->tag == 2) genFor(act->data->_for);
}

static void genOperation(Operation *op) {
    if (op->tag == 1) genAssignment(op->data->_assignment);
    if (op->tag == 2) genDeclaration(op->data->_declaration);
}

static void genAssignment(Assignment *assignment) {
    Var *var = findVar(assignment->id);
    if (var) {
        char* target = "t0";
        genExpression(assignment->value, target, "t1");
        printf("sw\t%s,%d(sp)\n", target, -var->index*INT_SIZE);
        var->hasValue = 1;
    } else {
        fprintf(stderr, "Unknown variable %s\n", assignment->id);
        compilationError();
    }
}

static void genDeclaration(Declaration *declaration) {
    Var *var = addVar(declaration->id);
    if (declaration->value) {
        char* target = "t0";
        genExpression(declaration->value, target, "t1");
        var->hasValue = 1;
        printf("sw\t%s,%d(sp)\n", target, -var->index*INT_SIZE);
    }
}

static void genFor(For *f) {
    addScope();

    if (f->operation) genOperation(f->operation);
    
    char* condition = makeLabel();
    printf("j\t%s\n", condition);   
    char* loop = makeLabel();
    printf("\n%s:\n", loop);

    genBlock(f->block);
    if (f->assignment) genAssignment(f->assignment);
    
    printf("\n%s:\n", condition);
    genCondition(f->condition, loop);

    popScope();
}

static void genCondition(Statement *statement, char* label) {
    if (statement) {
        genStatement(statement);
        char* op = statement->op;
        if      (!strcmp(op, "==")) printf("beq\tt0,t1,%s\n", label);
        else if (!strcmp(op, "!=")) printf("bne\tt0,t1,%s\n", label);
        else if (!strcmp(op, ">=")) printf("bge\tt0,t1,%s\n", label);
        else if (!strcmp(op, "<=")) printf("ble\tt0,t1,%s\n", label);
        else if (!strcmp(op, ">"))  printf("bgt\tt0,t1,%s\n", label);
        else if (!strcmp(op, "<"))  printf("blt\tt0,t1,%s\n", label);
    } else {
        printf("j\t%s\n", label);
    }
}

static void genStatement(Statement *statement) {
    genExpression(statement->left,  "t0", "t2");
    genExpression(statement->right, "t1", "t2");
}

static void genExpression(Expression *exp, char* target, char* recover) {
    if (exp->op == NULL) {
        if        (exp->operand->tag == 1) {
            printf("li\t%s,%d\n", target, exp->operand->data->_const);
        } else if (exp->operand->tag == 2) {
            Var* var = findVar(exp->operand->data->_id);
            if (var) {
                if (var->hasValue) {
                    printf("lw\t%s,%d(sp)\n", target, -var->index*INT_SIZE);
                } else {
                    fprintf(stderr, "Variable %s is not initialised\n", var->id);
                    compilationError();
                }
            } else {
                fprintf(stderr, "Unknown variable %s\n", exp->operand->data->_id);
                compilationError();
            }
        }
    } else if (exp->left == NULL) {
        genExpression(exp->right, target, recover);
        printf("neg\t%s,%s\n", target, target);
    } else {
        genExpression(exp->left, target, recover);
        printf("sw\t%s,%d(sp)\n", target, -INT_SIZE*stack_offset);
        stack_offset++;
        genExpression(exp->right, target, recover);
        stack_offset--;
        printf("lw\t%s,%d(sp)\n", recover, -INT_SIZE*stack_offset);
        if      (!strcmp(exp->op, "-")) printf("sub\t%s,%s,%s\n", target, recover, target);
        else if (!strcmp(exp->op, "+")) printf("add\t%s,%s,%s\n", target, recover, target);
        else if (!strcmp(exp->op, "/")) printf("div\t%s,%s,%s\n", target, recover, target);
        else if (!strcmp(exp->op, "*")) printf("mul\t%s,%s,%s\n", target, recover, target);
    }
}
