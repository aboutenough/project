Project: impl sm2 with RFC6979

该project主要实现了SM2的各种功能

SM2加解密实现：

首先SM2需要用到SM3作为哈希函数，所以先用python实现SM3。

以标准文档中椭圆曲线标准参数为例，参数长度为256bit

add（）函数为椭圆曲线上的点加

mul_add（）为椭圆曲线上的点乘

之后根据SM2的原理实现加解密功能，其中须生成随机参数时，将该参数设置为标准文档中的值（若需要随机生成，只需修改注释）

该样例为对m="encryption standard"加解密

![image](https://user-images.githubusercontent.com/105588850/180980937-eeef797f-9ac5-45fd-9b75-22350fdec361.png)

![image](https://user-images.githubusercontent.com/105588850/180980967-e3523b2b-1f6e-40ce-a442-0cd7beeceb74.png)


SM2密钥交换实现：

哈希函数以及椭圆曲线上运算与SM2加解密相同。

假定：

IDa="ALICE123@YAHOO.COM"

IDb="BILL456@YAHOO.COM"

开始执行密钥交换协议

Alice随机生成一个ra计算[ra]G发送给bill，bill随机生成一个rb计算[rb]G发送给Alice

对于BILL，可以使用Alice的ID以及公钥计算Za，同样可以计算自己的Zb，之后利用Alice发送的Ra按照密钥交换
协议可以计算一个密钥。

对于Alice，同样可以计算Za和Zb，并利用Bill的Rb按照密钥交换协议计算一个密钥。

二者计算的密钥相同，从而达到密钥交换。

![image](https://user-images.githubusercontent.com/105588850/180982453-30fe9458-401a-4cf7-88ad-97b753644abc.png)

![image](https://user-images.githubusercontent.com/105588850/180982477-892506e0-a6bf-4aed-9718-b7e4a7c098c8.png)


SM2签名：

按照标准文档参数作为测试，在签名过程中生成的随机值用定值代替（使用随机值时只需修改注释）

按照签名和验签原理实现SM2签名和验签，签名需要消息m和Za，签名验证是需要签名、Za、消息和公钥

以IDa="ALICE123@YAHOO.COM"，对于消息m="message digest"进行测试

![image](https://user-images.githubusercontent.com/105588850/180983548-aa525321-4da7-478f-b9db-6d05f62b2075.png)

![image](https://user-images.githubusercontent.com/105588850/180983633-915217ad-4b6e-442a-b6a6-ad5954337506.png)






