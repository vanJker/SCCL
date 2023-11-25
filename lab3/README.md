# SCXU Compiler Principles Lab 3

## Logs

0. 使用 GCC 进行编译

1. 改写 if 语句的语法
   - 原有语法：
     - if_stmt -> if exp then stmt-sequence end
     - if_stmt -> if exp then stmt-sequence else stmt-sequence end
   - 改写语法：
     - if_stmt -> if (exp) stmt-sequence
     - if_stmt -> if (exp) stmt-sequence else stmt-sequence
2. 增加 for 循环语句
3. 扩充算术表达式的运算符号
   - 扩充加法赋值运算符号 +=
   - 扩充求余运算符 %，优先级大于 +、-，小于 *、/
   - 扩充乘方运算符 ^，优先级大于 *、/
4. 扩充比较运算符号
   - 扩充大于 >
   - 扩充小于等于 <=
   - 扩充小于等于 >=
   - 扩充不等于 <>
5. 增加正则表达式
   - 支持运算符或 |
   - 支持运算符连接 &
   - 支持运算符闭包 #
   - 支持运算符可选 ?
   - 支持基本正则表达式 ident、num
6. 增加正则表达式赋值语句
   - id := 正则表达式
