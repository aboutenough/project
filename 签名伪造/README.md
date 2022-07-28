Project: forge a signature to pretend that you are Satoshi

该project实现ECDSA签名伪造。

在ECDSA.cpp中实现了按照ECDSA算法原理实现了ECDSA签名

在该签名中，利用SM3作为哈希函数，并按照标准文档选取椭圆曲线参数

以消息m="encryption standard"，

私钥d=0x68b5418eaaeeca62b41bf122e802b7919a8c7d385b62dea675a550d73824daa8

为例

![image](https://user-images.githubusercontent.com/105588850/181402222-02f48713-ed46-4462-82b2-7e1a0bcfc289.png)

![image](https://user-images.githubusercontent.com/105588850/181402221-10cc37b3-7284-4842-8ab1-e79cb55d465b.png)

在ECDSA签名伪造中，算法生成随机的u，v∈[1，n-1],计算R=[u]G+[v]P ,r1=Rx，通过r1来生成e1并构造s1来实现
不验证消息m的条件下，能够通过签名验证。

![image](https://user-images.githubusercontent.com/105588850/181402634-4e4b725c-c26c-4797-adcc-8df21bb9aa24.png)

![image](https://user-images.githubusercontent.com/105588850/181402653-e43324ed-2c4b-426a-8c98-a0f830739549.png)
