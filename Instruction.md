# 解析方法
## 运算符
### 结构操作符：
+ `( ) [ ] ;`

### 零元操作符：
包括：`单常量、单变量`
+ 单常量 `e n eg:123`
+ 单变量 `A B C D E F X Y M`

### 一元操作符：
包括：`单元操作符`
+ 取绝对值 `[|;NUM]`
+ 自然对数 `[n;NUM]`
+ 阶乘 `[!;NUM]`
+ 三角函数 `[s;NUM] [c;NUM] [t;NUM]`
+ 反三角函数 `[_s;NUM] [_c;NUM] [_t;NUM]`
+ 百分比 `[%;NUM]`

### 二元操作符：
包括：`二元操作符`
+ 加、减、乘、除 `NUM+NUM NUM-NUM NUM*NUM NUM/NUM`
+ 分数 `[\;NUM_UP;NUM_DOWN]`
+ 幂运算 `[^;NUM_MAIN;NUM_UP]`
+ 开次方根(实现方式同上) ```[`;NUM_MAIN;NUM_UP]```
+ 取对数 `[~;NUM_MAIN;NUM_BASE]`
+ 双曲函数 (待定)

### 三元操作符：
包括：`三元操作符`
+ 求和 `[<;NUM_MAIN;NUM_BEG;NUM_END]`
+ 积分 `[{;NUM_MAIN;NUM_BEG;NUM_END]`
+ 微分 `[};NUM_MAIN;NUM_BEG;NUM_END]`


`eg:`

## 预处理
## 正式解析
`eg:((128+9)*8/[^,-3,2])+4`
1. 变量定义 
```
SHORT tmp_circle = 0, tmp_square = 0;//结构判断定义
```
2. 结构判断 
```
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
```
