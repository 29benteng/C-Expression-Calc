#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expression_calc.h"

// void split(char *tmp, char *string, unsigned char start, unsigned char end)
// {
//     for (unsigned char i = start; i < end; ++i)
//     {
//         tmp[i - start] = string[i];
//     }
// }

op *analyze(char *string, SHORT len)
{
    // char *tmp_char = (char *)malloc(255 * sizeof(char));//临时缓存区文本
    for (SHORT i = 0, tmp = 0; i < len + 1; ++i)
    {
        if (string[i] == '(') //累加左括号数量
        {
            tmp++;
        }
        else if (string[i] == ')') //累减右括号数量
        {
            tmp--;    //积累括号
            if (!tmp) //左右括号匹配
            {
                op *tmp_ch = analyze(string + 1, i - 1); //左表达式递归解析 // (>(a)+(b)<)+...
                char tmp_symbol = string[i + 1];
                op *tmp_op = new_op(string + i + 1, 1); //本层级运算符 // ((a)+(b))>+<...
                if (tmp_symbol == 's' || tmp_symbol == 'c' || tmp_symbol == 'g')
                {
                    tmp_op->child[0] = tmp_ch;
                }
                else
                {
                    tmp_op->child[0] = tmp_ch;
                    tmp_op->child[1] = analyze(string + i + 3, len - 1); //)+(>123<)
                }
                return tmp_op;
            };
        }
    }
    return new_op(string, len); //递归底层返回op //>123<
}

void op_print(op *unit)
{
    (unit->data.symple[0] == '@') ? printf("\nop:%p content:%c", unit, unit->data.symple[1]) : printf("\nop:%p content:%f", unit, unit->data.number);
    if (unit->child[0] != NULL)
    {
        op_print(unit->child[0]);
    }
    if (unit->child[1] != NULL)
    {
        op_print(unit->child[1]);
    }
}

// double op_calc(op *unit)
// {
//     return unit->get_value(unit);
// }

void op_clean(op *unit)
{
    if (unit->child[0] != NULL)
    {
        op_clean(unit->child[0]);
    }
    if (unit->child[1] != NULL)
    {
        op_clean(unit->child[1]);
    }
    free(unit);
}

int main()
{
    char tmp[] = "(3.14)+((1.414)*((1.427)+(0.333)))";
    for (int i = 0; i < 100; ++i)
    {
        op *final = analyze(tmp, strlen(tmp) - 1); //be->ed
        op_print(final);
        printf("\n\nResult: %f Answer: %f", final->get_value(final), (3.14) + ((1.414) * ((1.427) + (0.333))));
        // printf("\nSize of Data: %d", sizeof(Data));
        op_clean(final);
    }
    return 0;
}
