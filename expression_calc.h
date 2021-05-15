#include <math.h>

typedef union Data
{
    double number;
    char symple[4];
} Data;

// typedef double (*func)(op *);

typedef struct op
{
    Data data;
    // double value, grad;//先注释掉
    struct op *child[2];
    double (*get_value)(struct op *);
    double (*get_gard)(struct op *);
} op;

typedef unsigned char SHORT;

double calc_self(op *unit)
{
    return unit->data.number;
}

double calc_add(op *unit) // +
{
    return unit->child[0]->get_value(unit->child[0]) + unit->child[1]->get_value(unit->child[1]);
}

double calc_minus(op *unit) // -
{
    return unit->child[0]->get_value(unit->child[0]) - unit->child[1]->get_value(unit->child[1]);
}

double calc_mult(op *unit) // *
{
    return unit->child[0]->get_value(unit->child[0]) * unit->child[1]->get_value(unit->child[1]);
}

double calc_divid(op *unit) // /
{
    return unit->child[0]->get_value(unit->child[0]) / unit->child[1]->get_value(unit->child[1]);
}

double calc_pow(op *unit) // ^
{
    return pow(unit->child[0]->get_value(unit->child[0]), unit->child[1]->get_value(unit->child[1]));
}

double calc_sqrt(op *unit) // q √(宽字符)
{
    return sqrt(unit->child[0]->get_value(unit->child[0]));
}

void op_setting(op *unit, char *string, SHORT len)
{

    char *tmp_char = (char *)malloc(len+1 * sizeof(char)); //临时缓存区文本
    memcpy(tmp_char, string, len);
    tmp_char[len] = '\0'; //终止符
    switch (string[0])
    {
    case '+':
        unit->data.symple[0] = '@';
        unit->data.symple[1] = '+';
        unit->data.symple[2] = '\0'; //手动终止符
        unit->get_value = calc_add;
        break;
    case '-':
        unit->data.symple[0] = '@';
        unit->data.symple[1] = '-';
        unit->data.symple[2] = '\0'; //手动终止符
        unit->get_value = calc_minus;
        break;
    case '*':
        unit->data.symple[0] = '@';
        unit->data.symple[1] = '*';
        unit->data.symple[2] = '\0'; //手动终止符
        unit->get_value = calc_mult;
        break;
    case '/':
        unit->data.symple[0] = '@';
        unit->data.symple[1] = '/';
        unit->data.symple[2] = '\0'; //手动终止符
        unit->get_value = calc_divid;
        break;
    case '^':
        unit->data.symple[0] = '@';
        unit->data.symple[1] = '^';
        unit->data.symple[2] = '\0'; //手动终止符
        unit->get_value = calc_pow;
        break;
    case 'q'://√(宽字符)
        unit->data.symple[0] = '@';
        unit->data.symple[1] = 'q';
        unit->data.symple[2] = '\0'; //手动终止符
        unit->get_value = calc_sqrt;
        break;
    default:
        unit->data.number = atof(tmp_char);
        unit->get_value = calc_self;
        break;
    }
    free(tmp_char);
}

op *new_op(char *string, SHORT len)
{
    op *tmp_op = (struct op *)malloc(sizeof(struct op));
    op_setting(tmp_op, string, len);
    tmp_op->child[0] = NULL;
    tmp_op->child[1] = NULL;
    return tmp_op;
}