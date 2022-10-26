# Large-integer-arithmetic
背景信息：
信息加密中的密钥及加密算法涉及到大整数，如：[0, 21024]，一般程序设计语言提供的基本数据类型无法满足要求。 

实现：
利用双向链表来实现大整数的加、减、乘运算。
输出格式：每 4 位十进制数为一组，各组间以空格隔开。如： 
26 的输出：26 
123456 的输出: 12 3456 
-987654321 输出为：-9 8765 4321 
使用：
提示输入第一个数（减法运算中为被减数），回车结束->提示输入第二个数，回车结束->结果输出。
注意：
本源代码利用VS2019实现。
