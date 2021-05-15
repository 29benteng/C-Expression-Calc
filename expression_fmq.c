#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expression_fmq.h"

#define ERROR -100000
#define UNDEFINED -1

op A_, B_, C_, D_, E_, F_, X_, Y_, M_, e_, n_;

void variable_init()
{
    op_init(&A_);
    op_init(&B_);
    op_init(&C_);
    op_init(&D_);
    op_init(&E_);
    op_init(&F_);
    op_init(&X_);
    op_init(&Y_);
    op_init(&M_);
    op_init(&e_);
    op_init(&n_);
    e_.number = M_E;
    n_.number = M_PI;
    A_.get_value = calc_self;
    B_.get_value = calc_self;
    C_.get_value = calc_self;
    D_.get_value = calc_self;
    E_.get_value = calc_self;
    F_.get_value = calc_self;
    X_.get_value = calc_self;
    Y_.get_value = calc_self;
    M_.get_value = calc_self;
    e_.get_value = calc_self;
    n_.get_value = calc_self;
    A_.symple[0] = '#';
    A_.symple[1] = 'A';
    A_.symple[2] = '\0';
    B_.symple[0] = '#';
    B_.symple[1] = 'B';
    B_.symple[2] = '\0';
    C_.symple[0] = '#';
    C_.symple[1] = 'C';
    C_.symple[2] = '\0';
    D_.symple[0] = '#';
    D_.symple[1] = 'D';
    D_.symple[2] = '\0';
    E_.symple[0] = '#';
    E_.symple[1] = 'E';
    E_.symple[2] = '\0';
    F_.symple[0] = '#';
    F_.symple[1] = 'F';
    F_.symple[2] = '\0';
    X_.symple[0] = '#';
    X_.symple[1] = 'X';
    X_.symple[2] = '\0';
    Y_.symple[0] = '#';
    Y_.symple[1] = 'Y';
    Y_.symple[2] = '\0';
    M_.symple[0] = '#';
    M_.symple[1] = 'M';
    M_.symple[2] = '\0';
    e_.symple[0] = '#';
    e_.symple[1] = 'e';
    e_.symple[2] = '\0';
    n_.symple[0] = '#';
    n_.symple[1] = 'n';
    n_.symple[2] = '\0';
}

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
    int bit_circle = UNDEFINED, bit_square = UNDEFINED;
    for (int i = 0; i < len; ++i)
    {
        switch (string[i])
        {
        case '(':
            tmp_circle++;
            if (bit_circle == UNDEFINED)
                bit_circle = i;
            break;
        case ')':
            tmp_circle--;
            if (tmp_circle < 0) //)( 报错
                return 0;
            else if (tmp_circle == 0)
            {
                if (!Is_Format(string + bit_circle + 1, i - bit_circle - 1))
                    return 0;
                else
                    bit_circle = UNDEFINED;
            };
            break;
        case '[':
            tmp_square++;
            if (bit_square == UNDEFINED)
                bit_square = i;
            break;
        case ']':
            tmp_square--;
            if (tmp_square < 0)
                return 0;
            else if (tmp_square == 0)
            {
                if (!Is_Format(string + bit_square + 1, i - bit_square - 1))
                    return 0;
                else
                    bit_square = UNDEFINED;
            }
            break;
        default:
            break;
        }
    }
    return !(tmp_circle + tmp_square); //递归底层返回op //>123<
}

int Get_Double_Left(char *string, int len, int local) //获取二元运算符左边
{
    if (local <= 0 || local > len) // _+>123456+_<
        return ERROR;
    int tmp_bit = string[local - 1];
    if ((tmp_bit > 47 && tmp_bit < 58) || tmp_bit == 46) // 0123456789.
    {
        for (int i = local - 2; i > -1; --i)
        {
            if (!((string[i] > 47 && string[i] < 58) || string[i] == 46)) //! 0123456789.
                return i + 1;
        }
    }
    else if ((tmp_bit > 64 && tmp_bit < 71) || tmp_bit == 77 ||
             tmp_bit == 88 || tmp_bit == 89 || tmp_bit == 101 ||
             tmp_bit == 110)
        return local - 1; // ABCDEF MXY e n
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
                return i;
            }
        }
    }
    else
        return ERROR; //左边无操作符
    return 0;         //左边只有一位
}

int Get_Double_Right(char *string, int len, int local) //获取二元运算符右边
{
    if (local < -1 || local >= len - 1) // >_+123456<+_
        return ERROR;
    int tmp_bit = string[local + 1];
    if ((tmp_bit > 47 && tmp_bit < 58) || tmp_bit == 46) // 0123456789.
    {
        for (int i = local + 2; i < len; ++i)
        {
            if (!((string[i] > 47 && string[i] < 58) || string[i] == 46)) //! 0123456789.
            {
                return i - 1;
            }
        }
    }
    else if ((tmp_bit > 64 && tmp_bit < 71) || tmp_bit == 77 || tmp_bit == 88 || tmp_bit == 89 || tmp_bit == 101 || tmp_bit == 110)
        return local + 1;                      // ABCDEFMXY
    else if (tmp_bit == '(' || tmp_bit == '[') // ()[]
    {
        int tmp = 1;
        for (int i = local + 2; i < len; ++i)
        {
            // printf("%c", string[i]);
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
                return i;
        }
    }
    else
        return ERROR; //右边无单操作符
    return len - 1;   //右边只有一位
}

op *analyze(char *string, int len)
{
    for (int i = 0, tmp_brackets = 0; i < len; ++i) // +-
    {
        switch (string[i])
        {
        case '(':
            tmp_brackets++;
            break;
        case ')':
            tmp_brackets--;
            break;
        case '[':
            tmp_brackets++;
            break;
        case ']':
            tmp_brackets--;
            break;
        default:
            if (!(tmp_brackets + tmp_brackets))
            {
                switch (string[i])
                {
                case '+': // A+B
                {
                    op *tmp_op = new_op(string + i, 1);
                    tmp_op->child[0] = analyze(string, i);
                    tmp_op->child[1] = analyze(string + i + 1, len - i - 1);
                    return tmp_op;
                }
                case '-': // A-B
                {
                    if (Get_Double_Left(string, len, i) == ERROR) // -10
                    {
                        if (i == 0 && Get_Double_Right(string, len, i) == len - 1)
                        {
                            op *tmp_op = (struct op *)malloc(sizeof(struct op));
                            op_init(tmp_op);
                            tmp_op->symple[0] = '@';
                            tmp_op->symple[1] = '-';
                            tmp_op->symple[2] = '\0';
                            tmp_op->get_value = calc_neg;
                            tmp_op->child[0] = analyze(string + 1, len - 1);
                            return tmp_op;
                        }
                    }
                    else
                    {
                        op *tmp_op = new_op(string + i, 1);
                        tmp_op->child[0] = analyze(string, i);
                        tmp_op->child[1] = analyze(string + i + 1, len - i - 1);
                        return tmp_op;
                    }
                }
                default:
                    break;
                }
            }
            break;
        }
    }
    for (int i = 0, tmp_brackets = 0; i < len; ++i) // *
    {
        switch (string[i])
        {
        case '(':
            tmp_brackets++;
            break;
        case ')':
            tmp_brackets--;
            break;
        case '[':
            tmp_brackets++;
            break;
        case ']':
            tmp_brackets--;
            break;
        default:
            if (!(tmp_brackets + tmp_brackets))
            {
                switch (string[i])
                {
                case '*': // A+B
                {
                    op *tmp_op = new_op(string + i, 1);
                    tmp_op->child[0] = analyze(string, i);
                    tmp_op->child[1] = analyze(string + i + 1, len - i - 1);
                    return tmp_op;
                }
                default:
                    break;
                }
            }
            break;
        }
    }
    for (int i = 0, tmp_brackets = 0; i < len; ++i) // /
    {
        switch (string[i])
        {
        case '(':
            tmp_brackets++;
            break;
        case ')':
            tmp_brackets--;
            break;
        case '[':
            tmp_brackets++;
            break;
        case ']':
            tmp_brackets--;
            break;
        default:
            if (!(tmp_brackets + tmp_brackets))
            {
                switch (string[i])
                {
                case '/': // A/B
                {
                    op *tmp_op = new_op(string + i, 1);
                    tmp_op->child[0] = analyze(string, i);
                    tmp_op->child[1] = analyze(string + i + 1, len - i - 1);
                    return tmp_op;
                }
                default:
                    break;
                }
            }
            break;
        }
    }

    switch (string[0])
    {
    case '(':
        return analyze(string + 1, len - 2);
    case '[':
    {

        if (string[1] == '|' || string[1] == 'n' || string[1] == '!' || string[1] == 's' || string[1] == 's' || string[1] == 'c' || string[1] == 't' || string[1] == '%')
        {
            op *tmp_op = new_op(string + 1, 1);
            tmp_op->child[0] = analyze(string + 3, len - 4);
            return tmp_op;
        }
        else if (string[1] == '\\' || string[1] == '^' || string[1] == '`' || string[1] == '~')
        {
            op *tmp_op = new_op(string + 1, 1);
            for (int i = 3; i < len; ++i)
            {
                if (string[i] == ';')
                {
                    tmp_op->child[0] = analyze(string + 3, i - 2);
                    tmp_op->child[1] = analyze(string + i + 1, len - i - 2);
                    return tmp_op;
                }
            }
        }
        else if (string[1] == '_')
        {
            op *tmp_op = new_op(string + 1, 2);
            tmp_op->child[0] = analyze(string + 4, len - 5);
            return tmp_op;
        }
    }
    case 'A':
        return &A_;
    case 'B':
        return &B_;
    case 'C':
        return &C_;
    case 'D':
        return &D_;
    case 'E':
        return &E_;
    case 'F':
        return &F_;
    case 'X':
        return &X_;
    case 'Y':
        return &Y_;
    case 'M':
        return &M_;
    case 'e':
        return &e_;
    case 'n':
        return &n_;
    default:
        return new_num(string, len);
    }
    return new_num(string, len); //递归底层返回op //>123<
}

void op_print(op *unit)
{
    switch (unit->symple[0])
    {
    case '@':
    {
        printf("\nop:%p content:%s", unit, unit->symple + 1);
        break;
    }
    case '#':
    {
        printf("\nop:%p content:%c", unit, unit->symple[1]);
        break;
    }
    default:
    {
        printf("\nop:%p content:%f", unit, unit->number);
        break;
    }
    }
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
    if (unit->symple[0] != '#')
        free(unit);
}

int main()
{
    variable_init();
    A_.number=10;
    char tmp[] = "[^;A;300]*-110+-e"; //A=0
    // char tmp[] = "(128+9)*9+4";
    printf("Format_test:%d", Is_Format(tmp, strlen(tmp)));
    //printf("Single_Left_test:%d", Get_Double_Right(tmp, strlen(tmp), 8));
//    if (Is_Format(tmp, strlen(tmp)))
//    {
//        op *final = analyze(tmp, strlen(tmp)); //be->ed
//        // op_print(final);
//        //    double tmp_num = 1 + 5 - 8 * 7 / 9 * (88 * 7 - 9 * 8);
//        // printf("\n\nResult: %f Answer: %f", final->get_value(final), tmp_num);
//        printf("\n\nResult: %G ", final->get_value(final));
//        // printf("\nSize of Data: %d", sizeof(Data));
//        op_print(final);
//        op_clean(final);
//    }
     for (int i = 0; i < 1000000; ++i)
     {
         op *final = analyze(tmp, strlen(tmp) - 1); //be->ed
         op_print(final);
         printf("\n\nResult: %f Answer: %f", final->get_value(final), (3.14) + ((1.414) * ((1.427) + (0.333))));
         // printf("\nSize of Data: %d", sizeof(Data));
         op_clean(final);
     }
    return 0;
}
