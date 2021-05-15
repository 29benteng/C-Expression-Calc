#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expression_fmq.h"

// void split(char *tmp, char *string, unsigned char start, unsigned char end)
// {
//     for (unsigned char i = start; i < end; ++i)
//     {
//         tmp[i - start] = string[i];
//     }
// }

int Is_Format(char *string, int len) //判断结构是否匹配
{
    int tmp_circle = 0, tmp_square = 0;
    for (int i = 0; i < len; ++i)
    {
        switch (string[i])
        {
        case '(':
            tmp_circle++;
            break;
        case ')':
            tmp_circle--;
            if (tmp_circle < 0)
                return 0;
            break;
        case '[':
            tmp_square++;
            break;
        case ']':
            tmp_square--;
            if (tmp_square < 0)
                return 0;
            break;
            break;
        default:
            break;
        }
    }
    return !(tmp_circle + tmp_square); //递归底层返回op //>123<
}

int Get_Double_Left(char *string, int len, int local) //获取二元运算符左边
{
    if (local < 1 || local > len - 2)
        return -1;
    int tmp_bit = string[local - 1];
    if ((tmp_bit > 47 && tmp_bit < 58) || tmp_bit == 46) // 0123456789.
    {
        for (int i = local - 2; i > -1; --i)
        {
            if (!((string[i] > 47 && string[i] < 58) || string[i] == 45 || string[i] == 46)) //! 0123456789-.
            {
                tmp_bit = i + 1;
                break;
            }
        }
    }
    else if ((tmp_bit > 64 && tmp_bit < 71) || tmp_bit == 77 || tmp_bit == 88 || tmp_bit == 89 || tmp_bit == 101 || tmp_bit == 110)
        tmp_bit = local - 1; // ABCDEFMXY
    else if (tmp_bit == ')' || tmp_bit == ']')
    {
        int tmp = -1;
        for (int i = local - 2; i > -1; --i)
        {
            switch (string[i])
            {
            case '(':
                tmp++;
                break;
            case ')':
                tmp--;
                break;
            case '[':
                tmp++;
                break;
            case ']':
                tmp--;
                break;
            default:
                break;
            }
            if (!tmp)
            {
                tmp_bit = i;
                break;
            }
        }
    }
    else
        return -1;
    return tmp_bit;
}

int Get_Double_Right(char *string, int len, int local) //获取二元运算符左边
{
    if (local < 1 || local > len - 2)
        return -1;
    int tmp_bit = string[local + 1];
    if ((tmp_bit > 47 && tmp_bit < 58) || tmp_bit == 45 || tmp_bit == 46) // 0123456789-.
    {
        for (int i = local + 2; i < len; ++i)
        {
            if (!((string[i] > 47 && string[i] < 58) || string[i] == 46)) //! 0123456789.
            {
                tmp_bit = i - 1;
                break;
            }
        }
    }
    else if ((tmp_bit > 64 && tmp_bit < 71) || tmp_bit == 77 || tmp_bit == 88 || tmp_bit == 89 || tmp_bit == 101 || tmp_bit == 110)
        tmp_bit = local + 1;                   // ABCDEFMXY
    else if (tmp_bit == '(' || tmp_bit == '[') // ()[]
    {
        int tmp = 1;
        for (int i = local + 2; i < len; ++i)
        {
            switch (string[i])
            {
            case '(':
                tmp++;
                break;
            case ')':
                tmp--;
                break;
            case '[':
                tmp++;
                break;
            case ']':
                tmp--;
                break;
            default:
                break;
            }
            if (!tmp)
            {
                tmp_bit = i;
                break;
            }
        }
    }
    else
        return -1;
    return tmp_bit;
}

op *analyze(char *string, int len)
{
    int tmp_circle = 0, tmp_square = 0;
    for (int i = 0; i < len; ++i)
    {
        switch (string[i])
        {
        case '(':
            tmp_circle++;
            break;
        case ')':
            tmp_circle--;
            break;
        case '[':
            tmp_square++;
            break;
        case ']':
            tmp_square--;
            break;
        default:
            if (!(tmp_circle + tmp_square))
            {
                switch (string[i])
                {
                case '+': // A+B
                    op *tmp_op = new_op('+', 1);
                    tmp_op->child[0] = analyze(string[Get_Double_Left(string, len, i)], i - Get_Double_Left(string, len, i));
                    tmp_op->child[1] = analyze(string[i + 1], Get_Double_Right(string, len, i) - i);
                    return tmp_op;
                    break;
                case '-': // A-B
                    op *tmp_op = new_op('-', 1);
                    tmp_op->child[0] = analyze(string[Get_Double_Left(string, len, i)], i - Get_Double_Left(string, len, i));
                    tmp_op->child[1] = analyze(string[i + 1], Get_Double_Right(string, len, i) - i);
                    return tmp_op;
                    break;
                default:
                    break;
                }
            }
            break;
        }
    }

    for (int i = 0; i < len; ++i)
    {
        switch (string[i])
        {
        case '(':
            tmp_circle++;
            break;
        case ')':
            tmp_circle--;
            break;
        case '[':
            tmp_square++;
            break;
        case ']':
            tmp_square--;
            break;
        default:
            if (!(tmp_circle + tmp_square))
            {
                switch (string[i])
                {
                case '*': // A+B
                    op *tmp_op = new_op('*', 1);
                    tmp_op->child[0] = analyze(string[Get_Double_Left(string, len, i)], i - Get_Double_Left(string, len, i));
                    tmp_op->child[1] = analyze(string[i + 1], Get_Double_Right(string, len, i) - i);
                    return tmp_op;
                    break;
                case '/': // A-B
                    op *tmp_op = new_op('/', 1);
                    tmp_op->child[0] = analyze(string[Get_Double_Left(string, len, i)], i - Get_Double_Left(string, len, i));
                    tmp_op->child[1] = analyze(string[i + 1], Get_Double_Right(string, len, i) - i);
                    return tmp_op;
                    break;
                default:
                    break;
                }
            }
            break;
        }
    }

    // for (int i = 0, tmp = 0; i < len + 1; ++i)
    // {
    //     if (string[i] == '(') //累加左括号数量
    //     {
    //         tmp++;
    //     }
    //     else if (string[i] == ')') //累减右括号数量
    //     {
    //         tmp--;    //积累括号
    //         if (!tmp) //左右括号匹配
    //         {
    //             op *tmp_ch = analyze(string + 1, i - 1); //左表达式递归解析 // (>(a)+(b)<)+...
    //             char tmp_symbol = string[i + 1];
    //             op *tmp_op = new_op(string + i + 1, 1); //本层级运算符 // ((a)+(b))>+<...
    //             if (tmp_symbol == 's' || tmp_symbol == 'c' || tmp_symbol == 'g')
    //             {
    //                 tmp_op->child[0] = tmp_ch;
    //             }
    //             else
    //             {
    //                 tmp_op->child[0] = tmp_ch;
    //                 tmp_op->child[1] = analyze(string + i + 3, len - 1); //)+(>123<)
    //             }
    //             return tmp_op;
    //         };
    //     }
    // }
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
    char tmp[] = "(3.14)+((-1.414)*((1.427)+(0.333)))";
    // printf("Format_test:%d", Is_Format(tmp, strlen(tmp)));
    printf("Single_Left_test:%d", Get_Double_Right(tmp, strlen(tmp), 8));
    // for (int i = 0; i < 100; ++i)
    // {
    //     op *final = analyze(tmp, strlen(tmp) - 1); //be->ed
    //     op_print(final);
    //     printf("\n\nResult: %f Answer: %f", final->get_value(final), (3.14) + ((1.414) * ((1.427) + (0.333))));
    //     // printf("\nSize of Data: %d", sizeof(Data));
    //     op_clean(final);
    // }
    return 0;
}
