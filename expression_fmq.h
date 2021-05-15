#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>

// typedef double (*func)(op *);

typedef struct op
{
    double number;
    char symple[3];
    // double value, grad;//先注释掉
    struct op *child[2];
    double (*get_value)(struct op *);
    double (*get_gard)(struct op *);
} op;

// typedef unsigned char int;

double calc_self(op *unit)
{
    return unit->number;
}

double calc_abs(op *unit)
{
    return fabs(unit->child[0]->get_value(unit->child[0]));
}

double calc_neg(op *unit)
{
    return 0 - unit->child[0]->get_value(unit->child[0]);
}

double calc_ln(op *unit)
{
    return log(unit->child[0]->get_value(unit->child[0]));
}

double calc_sin(op *unit)
{
    return sin(unit->child[0]->get_value(unit->child[0]));
}

double calc_cos(op *unit)
{
    return cos(unit->child[0]->get_value(unit->child[0]));
}

double calc_tan(op *unit)
{
    return tan(unit->child[0]->get_value(unit->child[0]));
}

double calc_arcsin(op *unit)
{
    return asin(unit->child[0]->get_value(unit->child[0]));
}

double calc_arccos(op *unit)
{
    return acos(unit->child[0]->get_value(unit->child[0]));
}

double calc_arctan(op *unit)
{
    return atan(unit->child[0]->get_value(unit->child[0]));
}

double calc_percent(op *unit)
{
    return unit->child[0]->get_value(unit->child[0]) / 100;
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

double calc_root(op *unit) // q √(宽字符)
{
    return pow(unit->child[0]->get_value(unit->child[0]), 1 / unit->child[1]->get_value(unit->child[1]));
}

double calc_log(op *unit) // q √(宽字符)
{
    return log(unit->child[0]->get_value(unit->child[0])) / log(unit->child[1]->get_value(unit->child[1]));
}

void op_setting(op *unit, char *string, int len)
{
    char *tmp_char = (char *)malloc((len + 1) * sizeof(char)); //临时缓存区文本
    memcpy(tmp_char, string, len);
    tmp_char[len] = '\0'; //终止符
    switch (string[0])
    {
    case '+':
    {
        unit->symple[0] = '@';
        unit->symple[1] = '+';
        unit->symple[2] = '\0'; //手动终止符
        unit->get_value = calc_add;
        break;
    }
    case '-':
    {
        unit->symple[0] = '@';
        unit->symple[1] = '-';
        unit->symple[2] = '\0'; //手动终止符
        unit->get_value = calc_minus;
        break;
    }
    case '*':
    {
        unit->symple[0] = '@';
        unit->symple[1] = '*';
        unit->symple[2] = '\0'; //手动终止符
        unit->get_value = calc_mult;
        break;
    }
    case '/':
    {
        unit->symple[0] = '@';
        unit->symple[1] = '/';
        unit->symple[2] = '\0'; //手动终止符
        unit->get_value = calc_divid;
        break;
    }
    case '\\':
    {
        unit->symple[0] = '@';
        unit->symple[1] = '\\';
        unit->symple[2] = '\0'; //手动终止符
        unit->get_value = calc_divid;
        break;
    }
    case '^':
    {
        unit->symple[0] = '@';
        unit->symple[1] = '^';
        unit->symple[2] = '\0'; //手动终止符
        unit->get_value = calc_pow;
        break;
    }
    case '`': //√(宽字符)
    {
        unit->symple[0] = '@';
        unit->symple[1] = '`';
        unit->symple[2] = '\0'; //手动终止符
        unit->get_value = calc_root;
        break;
    }
    case '~': //log
    {
        unit->symple[0] = '@';
        unit->symple[1] = '~';
        unit->symple[2] = '\0'; //手动终止符
        unit->get_value = calc_log;
        break;
    }
    case 's': //sin
    {
        unit->symple[0] = '@';
        unit->symple[1] = 's';
        unit->symple[2] = '\0'; //手动终止符
        unit->get_value = calc_sin;
        break;
    }
    case 'c': //√(宽字符)
    {
        unit->symple[0] = '@';
        unit->symple[1] = 'c';
        unit->symple[2] = '\0'; //手动终止符
        unit->get_value = calc_cos;
        break;
    }
    case 't': //log
    {
        unit->symple[0] = '@';
        unit->symple[1] = 't';
        unit->symple[2] = '\0'; //手动终止符
        unit->get_value = calc_tan;
        break;
    }
    case '_':
    {
        switch (string[1])
        {
        case 's': //sin
        {
            unit->symple[0] = '@';
            unit->symple[1] = '_';
            unit->symple[2] = 's';
            unit->symple[3] = '\0'; //手动终止符
            unit->get_value = calc_arcsin;
            break;
        }
        case 'c': //√(宽字符)
        {
            unit->symple[0] = '@';
            unit->symple[1] = '_';
            unit->symple[2] = 'c';
            unit->symple[3] = '\0'; //手动终止符
            unit->get_value = calc_arccos;
            break;
        }
        case 't': //log
        {
            unit->symple[0] = '@';
            unit->symple[1] = '_';
            unit->symple[2] = 't';
            unit->symple[3] = '\0'; //手动终止符
            unit->get_value = calc_arctan;
            break;
        }
        default:
            break;
        }
    }
    case '%': //log
    {
        unit->symple[0] = '@';
        unit->symple[1] = '%';
        unit->symple[2] = '\0'; //手动终止符
        unit->get_value = calc_percent;
        break;
    }
    case 'A': //log
    {
        unit->symple[0] = '@';
        unit->symple[1] = 'A';
        unit->symple[2] = '\0'; //手动终止符
        unit->get_value = calc_percent;
        break;
    }
    case 'B': //log
    {
        unit->symple[0] = '@';
        unit->symple[1] = 'B';
        unit->symple[2] = '\0'; //手动终止符
        unit->get_value = calc_percent;
        break;
    }
    case 'C': //log
    {
        unit->symple[0] = '@';
        unit->symple[1] = 'C';
        unit->symple[2] = '\0'; //手动终止符
        unit->get_value = calc_percent;
        break;
    }
    case 'D': //log
    {
        unit->symple[0] = '@';
        unit->symple[1] = 'D';
        unit->symple[2] = '\0'; //手动终止符
        unit->get_value = calc_percent;
        break;
    }
    case 'E': //log
    {
        unit->symple[0] = '@';
        unit->symple[1] = 'E';
        unit->symple[2] = '\0'; //手动终止符
        unit->get_value = calc_percent;
        break;
    }
    case 'F': //log
    {
        unit->symple[0] = '@';
        unit->symple[1] = 'F';
        unit->symple[2] = '\0'; //手动终止符
        unit->get_value = calc_percent;
        break;
    }
    case 'X': //log
    {
        unit->symple[0] = '@';
        unit->symple[1] = 'X';
        unit->symple[2] = '\0'; //手动终止符
        unit->get_value = calc_percent;
        break;
    }
    case 'Y': //log
    {
        unit->symple[0] = '@';
        unit->symple[1] = 'Y';
        unit->symple[2] = '\0'; //手动终止符
        unit->get_value = calc_percent;
        break;
    }
    case 'M': //log
    {
        unit->symple[0] = '@';
        unit->symple[1] = 'M';
        unit->symple[2] = '\0'; //手动终止符
        unit->get_value = calc_percent;
        break;
    }
    }
    free(tmp_char);
}
void op_init(op *unit)
{
    unit->number = 0;
    unit->symple[0] = '\0';
    unit->get_value = NULL;
    unit->get_gard = NULL;
    unit->child[0] = NULL;
    unit->child[1] = NULL;
}
op *new_op(char *string, int len)
{
    op *tmp_op = (struct op *)malloc(sizeof(struct op));
    op_init(tmp_op);
    op_setting(tmp_op, string, len);
    return tmp_op;
}
op *new_num(char *string, int len)
{
    op *tmp_op = (struct op *)malloc(sizeof(struct op));

    char *tmp_char = (char *)malloc((len + 1) * sizeof(char)); //临时缓存区文本
    memcpy(tmp_char, string, len);
    tmp_char[len] = '\0'; //终止符
    op_init(tmp_op);
    tmp_op->number = atof(tmp_char);
    tmp_op->get_value = calc_self;
    return tmp_op;
}