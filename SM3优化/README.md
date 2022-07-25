Project: do your best to optimize SM3 implementation (software)

该项目主要对SM3进行实现，并通过循环展开、优化代码的方式对SM3进行优化。

首先初步实现了SM3：

BinToHex（）将二进制字符串转换为十六进制字符串。

HexToBin（）将十六进制字符串转换为二进制字符串。

BinToDec（）将二进制字符串转换为十进制数。

DecToBin（）将十进制数转换为二进制字符串。

HexToDec（）将十六进制字符串转换为十进制数。

DecToHex（）将十进制数转换为十六进制字符串。

XOR（）字符串异或

AND（）字符串相与

OR（）字符串或

NOT（）字符串非

binXor（）、binAnd（）单个字符的或和与

ModAdd（）字符串模加运算

根据SM3原理实现：

padding（）数据填充

LeftShift（）循环左移位

实现P1、P0、T、FF、GG运算

extension（）为消息扩展

compress（）为消息压缩

iteration（）为迭代函数，对于杂凑过程迭代运算


此样例演示对消息“Steve"进行哈希运算结果

![image](https://user-images.githubusercontent.com/105588850/180755187-a30cf7b0-fb04-4569-8779-3d0a2ffb616e.png)
由于运算过程大多直接使用字符串进行运算故执行较慢，但可以初步实现SM3的功能。

进而在SM3优化中对于该代码进行优化。改变了运算变量的类型，减少字符串的使用以及对部分循环采用循环展开，来优化SM3的执行。

