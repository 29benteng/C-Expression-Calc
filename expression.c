#include "stdio.h"
#include "stdlib.h"
// #include "windows.h"
// #include "string.h"
typedef struct op
{
    char *content;
    // double value, grad;//先注释掉
    struct op **child;
} op;

void split(char *tmp, char *string, unsigned char start, unsigned char end)
{
    for (unsigned char i = start; i < end; ++i)
    {
        tmp[i - start] = string[i];
    }
}

op *new_op(char *string, unsigned char start, unsigned char end)
{
    op *tmp_op = (struct op *)malloc(sizeof(struct op));
    tmp_op->content = (char *)malloc((end - start) * sizeof(char));
    tmp_op->child = NULL;
    split(tmp_op->content, string, start, end);
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
                    tmp_op->child = (op *)malloc(sizeof(op *));
                    tmp_op->child[0] = tmp_ch;
                }
                else
                {
                    tmp_op->child = (op *)malloc(2 * sizeof(op *));
                    tmp_op->child[0] = tmp_ch;
                    tmp_op->child[1] = analyze(string, i + 3, end); //)+(123)
                }
                return tmp_op;
            };
        }
    }
    return new_op(string, start, end + 1); //递归底层返回op //strtod(tmp_char, tmp_char)/*  */
}

int main()
{
    char tmp[] = "(1)+((2)*((3)+(9)))";
    op *final = analyze(tmp, 0, sizeof(tmp) / sizeof(char));
    printf("%p", final);
    return 0;
}
