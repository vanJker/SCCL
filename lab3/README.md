# SCXU Compiler Principles Lab 3

## dev

0. 使用 GCC 进行编译

1. 改写 if 语句的语法
   - 原有语法：
     - if_stmt -> if exp then stmt-sequence end
     - if_stmt -> if exp then stmt-sequence else stmt-sequence end
   - 改写语法：
     - if_stmt -> if (exp) stmt-sequence
     - if_stmt -> if (exp) stmt-sequence else stmt-sequence
