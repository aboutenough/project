Project: implement sm2 2P sign with real network communication

该project实现两方共同签名

按照2P签名协议

首先A生成私钥的一个份额d1，计算P1=[d1逆]G，发送给B，B生成私钥的另一个份额d2,计算公钥P=[d2逆]P1-G

A计算一个Z并计算e，和Q1发送给B，B收到后计算r，s2，s3，A即可利用r,s2,s3来输出签名

在该项目中，利用python UDP通信来模拟两方共同签名，一方先准备建立连接，另一方接入，然后开始两方签名计算

相关私钥份额需要事先商议，代码中用随机数代替。

![image](https://user-images.githubusercontent.com/105588850/181160859-37ea84ff-06fd-4247-b611-4bd8cc168ee6.png)

![image](https://user-images.githubusercontent.com/105588850/181160908-a22ff992-7a4c-44b6-aae5-87e3beb162c7.png)
