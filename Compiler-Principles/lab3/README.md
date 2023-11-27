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
   - 文法 term 修改为 term→power{( * | / | % ) power}，新增TokenType MOD代表%
   - 扩充乘方运算符 ^，优先级大于 *、/
   - 修改文法simple_exp→mod_term{( + | - |‘|’)mod_ term};
   - 新增文法mod_term→term{%  term};新增TokenType POW代表^
4. 扩充比较运算符号
   - 扩充大于 >
   - 扩充小于等于 <=
   - 扩充小于等于 >=
   - 扩充不等于 <>
   - 文法 op 修改为 op→< | = | > | <= | >= | <>
   - 新增TokenType LE：<= ，GE：>=，NE： <>， GT：>
5. 增加正则表达式
   - 支持运算符或 |
   - 支持运算符连接 &
   - 支持运算符闭包 #
   - 支持运算符可选 ?
   - 支持基本正则表达式 ident、num
   - 文法simple_exp修改为mod_term{( + | - | ‘|’ )mod_ term};
   - 文法mod_simple修改为mod_exp→term{%  term};
   - 文法 term 修改为 term→pow_factor{( * | / | &) pow_factor}
   - 文法 pow_factor 修改为 pow_factor→factor{( ^ | # | ? ) factor}
   - 新增TokenType REOR( | )，RECON( & )，RECLOSURE( # )，REOPTION( ),
6. 增加正则表达式赋值语句
   - id := 正则表达式
7. 增加位运算表达式
   - 支持运算符与 and
   - 支持运算符或 or
   - 支持运算符非 not
   - bitor_exp→bitand_exp { or  bitand_exp}
   - bitand_exp→bitnot_exp { and  bitnot_exp}
   - bitnot_exp→not newExpNode_exp | simple_exp}
8. 增加位运算表达式赋值语句
9. 增加自动批量测试脚本
   - 使用方法：`python test.py [--parse|-p|--scan|-s] [--print|-p] [<filename>]`
10. 源文件约定：statement sequences 的最后一条 statement 不能带有分号，否则无法正常退出

主要文法如下变化：

- statement -> if_stmt | repeat_stmt | assgin_stmt | read_stmt | write_stmt | write_stmt | for_stmt
- exp -> bitor_exp { (< | = | > | <= | >= | <>) bitor_exp }
- bitor_exp -> and_exp { or  bitand_exp }
- bitand_exp -> bitnot_exp { and  bitnot_exp}
- bitnot_exp -> (not)* simple_exp
- simple_exp -> mod_term { ( + | - | ‘|’ ) mod_ term };
- mod_term→term { %  term };
- term→pow_factor { (* | / | &) pow_factor }
- pow_factor→factor{ ( ^ | # | ? ) factor }
- factor→ID | NUM | (exp)
- if_stmt→if(exp) stmt-sequence [else stmt-sequence]
- for_stmt -> for ID = simple_exp ( to | downto ) exp1 do stmt_sequence enddo

