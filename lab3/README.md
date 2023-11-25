# SCXU Compiler Principles Lab 3

## Logs

0. 使用 GCC 进行编译

1. 改写 if 语句的语法
   - 原有语法：
     - if_stmt -> if exp then stmt_sequence end
     - if_stmt -> if exp then stmt_sequence else stmt_sequence end
   - 改写语法：
     - if_stmt -> if (exp) stmt_sequence
     - if_stmt -> if (exp) stmt_sequence else stmt_sequence
2. 增加 for 循环语句
   - for_stmt -> for indet := exp to exp do stmt_sequence enddo
   - for_stmt -> for indet := exp downto exp do stmt_sequence enddo
   - 在表达式树显示 to 和 downto 运算符
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
7. 增加位运算表达式
   - 支持运算符与 and
   - 支持运算符或 or
   - 支持运算符非 not
8. 增加位运算表达式赋值语句
10. 增加自动批量测试脚本
   - 使用方法：`python test.py [--parse|-p|--scan|-s] [--print|-p] [<filename>]`
11. 源文件约定：statement sequences 的最后一条 statement 不能带有分号，否则无法正常退出
