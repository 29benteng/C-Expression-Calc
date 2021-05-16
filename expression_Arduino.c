#include "stdio.h"
#include "stdlib.h"
// #include "windows.h"
#include "string.h"
typedef struct op
{
    char *content;
    // double value, grad;//先注释掉
    struct op *child[2];
} op;

// void split(char *tmp, char *string, unsigned char start, unsigned char end)
// {
//     for (unsigned char i = start; i < end; ++i)
//     {
//         tmp[i - start] = string[i];
//     }
// }

op *new_op(char *string, unsigned char start, unsigned char end)
{
    op *tmp_op = (struct op *)malloc(sizeof(struct op));
    tmp_op->content = (char *)malloc((end - start + 1) * sizeof(char));
    tmp_op->child[0] = NULL;
    tmp_op->child[1] = NULL;
    memcpy(tmp_op->content, string + start, end - start);
    tmp_op->content[end - start] = '\0'; // 手动加上终止符
    return tmp_op;
}
op *analyze(char *string, unsigned char start, unsigned char end)
{
    // char *tmp_char = (char *)malloc(255 * sizeof(char));//临时缓存区文本
    for (unsigned char i = start, tmp = 0; i < end + 1; ++i)
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
                op *tmp_ch = analyze(string, start + 1, i - 1); //左表达式递归解析
                char tmp_symbol = string[i + 1];
                op *tmp_op = new_op(string, i + 1, i + 2); //本层级运算符
                if (tmp_symbol == 's' || tmp_symbol == 'c' || tmp_symbol == 'g')
                {
                    tmp_op->child[0] = tmp_ch;
                }
                else
                {
                    tmp_op->child[0] = tmp_ch;
                    tmp_op->child[1] = analyze(string, i + 3, end - 1); //)+>(<123>)<)
                }
                return tmp_op;
            };
        }
    }
    return new_op(string, start, end + 1); //递归底层返回op //strtod(tmp_char, tmp_char)/*  */
}

void op_print(op *unit)
{
    Serial.print("op:");
    Serial.print((int)unit);
    Serial.print(" content:");
    Serial.println(unit->content);
    if (unit->child[0] != NULL)
    {
        op_print(unit->child[0]);
    }
    if (unit->child[1] != NULL)
    {
        op_print(unit->child[1]);
    }
}

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
    free(unit->content);
    free(unit);
}

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    char tmp[] = "(((1)+(2))+(23)+(3))+(((2)+(3)+((6)+(963))+(3))+((3)+(6)))";
    for (int i = 0; i < 5000; ++i)
    {
        op *final = analyze(tmp, 0, strlen(tmp) - 1);
        // Serial.println("Done!");
        //op_print(final);
        op_clean(final);
    }

    Serial.println("Done!");
    delay(1000);
}