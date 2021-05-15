#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double printd(double x)
{
    printf("\n  %f", x);
    return x;
}

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

// typedef unsigned char int;

double calc_self(op *unit)
{
    return printd(unit->data.number);
}

double calc_abs(op *unit)
{
    return printd(fabs(unit->child[0]->get_value(unit->child[0])));
}

double calc_ln(op *unit)
{
    return printd(log(unit->child[0]->get_value(unit->child[0])));
}

double calc_sin(op *unit)
{
    return printd(sin(unit->child[0]->get_value(unit->child[0])));
}

double calc_cos(op *unit)
{
    return printd(cos(unit->child[0]->get_value(unit->child[0])));
}

double calc_tan(op *unit)
{
    return printd(tan(unit->child[0]->get_value(unit->child[0])));
}

double calc_arcsin(op *unit)
{
    return printd(asin(unit->child[0]->get_value(unit->child[0])));
}

double calc_arccos(op *unit)
{
    return printd(acos(unit->child[0]->get_value(unit->child[0])));
}

double calc_arctan(op *unit)
{
    return printd(atan(unit->child[0]->get_value(unit->child[0])));
}

double calc_percent(op *unit)
{
    return printd(unit->child[0]->get_value(unit->child[0]) / 100);
}

double calc_add(op *unit) // +
{
    return printd(unit->child[0]->get_value(unit->child[0]) + unit->child[1]->get_value(unit->child[1]));
}

double calc_minus(op *unit) // -
{
    return printd(unit->child[0]->get_value(unit->child[0]) - unit->child[1]->get_value(unit->child[1]));
}

double calc_mult(op *unit) // *
{
    return printd(unit->child[0]->get_value(unit->child[0]) * unit->child[1]->get_value(unit->child[1]));
}

double calc_divid(op *unit) // /
{
    double a = unit->child[0]->get_value(unit->child[0]), b = unit->child[1]->get_value(unit->child[1]);
    printf("!!!a:%f,b:%f", a, b);
    return printd(a / b);
}

double calc_pow(op *unit) // ^
{
    return printd(pow(unit->child[0]->get_value(unit->child[0]), unit->child[1]->get_value(unit->child[1])));
}

double calc_root(op *unit) // q √(宽字符)
{
    return printd(pow(unit->child[0]->get_value(unit->child[0]), 1 / unit->child[1]->get_value(unit->child[1])));
}

double calc_log(op *unit) // q √(宽字符)
{
    return printd(log(unit->child[0]->get_value(unit->child[0])) / log(unit->child[1]->get_value(unit->child[1])));
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
        unit->data.symple[0] = '@';
        unit->data.symple[1] = '+';
        unit->data.symple[2] = '\0'; //手动终止符
        unit->get_value = calc_add;
        break;
    }
    case '-':
    {
        unit->data.symple[0] = '@';
        unit->data.symple[1] = '-';
        unit->data.symple[2] = '\0'; //手动终止符
        unit->get_value = calc_minus;
        break;
    }
    case '*':
    {
        unit->data.symple[0] = '@';
        unit->data.symple[1] = '*';
        unit->data.symple[2] = '\0'; //手动终止符
        unit->get_value = calc_mult;
        break;
    }
    case '/':
    {
        unit->data.symple[0] = '@';
        unit->data.symple[1] = '/';
        unit->data.symple[2] = '\0'; //手动终止符
        unit->get_value = calc_divid;
        break;
    }
    case '\\':
    {
        unit->data.symple[0] = '@';
        unit->data.symple[1] = '\\';
        unit->data.symple[2] = '\0'; //手动终止符
        unit->get_value = calc_divid;
        break;
    }
    case '^':
    {
        unit->data.symple[0] = '@';
        unit->data.symple[1] = '^';
        unit->data.symple[2] = '\0'; //手动终止符
        unit->get_value = calc_pow;
        break;
    }
    case '`': //√(宽字符)
    {
        unit->data.symple[0] = '@';
        unit->data.symple[1] = '`';
        unit->data.symple[2] = '\0'; //手动终止符
        unit->get_value = calc_root;
        break;
    }
    case '~': //log
    {
        unit->data.symple[0] = '@';
        unit->data.symple[1] = '~';
        unit->data.symple[2] = '\0'; //手动终止符
        unit->get_value = calc_log;
        break;
    }
    case 's': //sin
    {
        unit->data.symple[0] = '@';
        unit->data.symple[1] = 's';
        unit->data.symple[2] = '\0'; //手动终止符
        unit->get_value = calc_sin;
        break;
    }
    case 'c': //√(宽字符)
    {
        unit->data.symple[0] = '@';
        unit->data.symple[1] = 'c';
        unit->data.symple[2] = '\0'; //手动终止符
        unit->get_value = calc_cos;
        break;
    }
    case 't': //log
    {
        unit->data.symple[0] = '@';
        unit->data.symple[1] = 't';
        unit->data.symple[2] = '\0'; //手动终止符
        unit->get_value = calc_tan;
        break;
    }
    case '_':
    {
        switch (string[1])
        {
        case 's': //sin
        {
            unit->data.symple[0] = '@';
            unit->data.symple[1] = '_';
            unit->data.symple[2] = 's';
            unit->data.symple[3] = '\0'; //手动终止符
            unit->get_value = calc_arcsin;
            break;
        }
        case 'c': //√(宽字符)
        {
            unit->data.symple[0] = '@';
            unit->data.symple[1] = '_';
            unit->data.symple[2] = 'c';
            unit->data.symple[3] = '\0'; //手动终止符
            unit->get_value = calc_arccos;
            break;
        }
        case 't': //log
        {
            unit->data.symple[0] = '@';
            unit->data.symple[1] = '_';
            unit->data.symple[2] = 't';
            unit->data.symple[3] = '\0'; //手动终止符
            unit->get_value = calc_arctan;
            break;
        }
        default:
            break;
        }
    }
    case '%': //log
    {
        unit->data.symple[0] = '@';
        unit->data.symple[1] = '%';
        unit->data.symple[2] = '\0'; //手动终止符
        unit->get_value = calc_percent;
        break;
    }
    default:
        unit->data.number = atof(tmp_char);
        unit->get_value = calc_self;
        break;
    }
    free(tmp_char);
}

op *new_op(char *string, int len)
{
    op *tmp_op = (struct op *)malloc(sizeof(struct op));
    op_setting(tmp_op, string, len);
    tmp_op->child[0] = NULL;
    tmp_op->child[1] = NULL;
    return tmp_op;
}