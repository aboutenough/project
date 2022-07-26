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
