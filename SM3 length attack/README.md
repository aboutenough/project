Project: implement length extension attack for SM3, SHA256, etc.

该项目为对SM3的长度扩展攻击

ex_attack（）函数为长度扩展，传入的参数m为需要添加的消息，H_m1为原消息的杂凑值，len为原消息长度，
t返回填充字符，t2返回哈希值，
t2为扩展后的哈希值。在该函数中，先填充len个任意字符，再将其转换为ASCII码，并计算长度，对其进行padding
填充完后，再尾部追加需要填充消息的ASCII码，对整个消息进行SM3过程，但是直接从添加的分组开始，并且初始iv
设置为原消息的哈希值，计算填充后的哈希值。

在main（）中，原消息为m1=“this is a project”

计算其哈希值为H_m1="1C70E1E0C59B8F4A216032DF732FE5FA9709EE4BBB9005A85175291AD94FA972"

需要填充的消息m=“append”

调用ex_attack函数开始扩展攻击。

最后验证扩展攻击返回的哈希值是否与消息级联产生的哈希值相同。在级联时以分组为单位，需要对前一个消息分组先进行填充。
![image](https://user-images.githubusercontent.com/105588850/180902485-b3917d61-3cd7-472b-ba51-ec63b9097deb.png)
