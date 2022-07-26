*Project: verify the above pitfalls with proof-of-concept code

该project主要验证了SM2签名的几种缺陷

泄露k导致d泄露：

敌手可以直接使用受害者A签过的sig以及泄露的k求解d

![image](https://user-images.githubusercontent.com/105588850/180984933-3de6690e-5e5a-4bf1-94ee-26a36d36541b.png)

![image](https://user-images.githubusercontent.com/105588850/180985188-09f30684-3b86-477d-bbb9-ae188bf00dfb.png)

某个用户重复使用k时会导致其私钥d泄露：

敌手可以使用受害者A利用相同k签的sig1和sig2直接计算其私钥d

![image](https://user-images.githubusercontent.com/105588850/180985455-277f07b0-e3f1-4cf2-bf4c-015bff735fe5.png)

![image](https://user-images.githubusercontent.com/105588850/180985485-9e9301eb-58fb-4821-a6e0-76e87b9ea6b9.png)

不同用户重复使用相同k签名导致他们可以计算对方的私钥d

一方只需获取另一方的某个签名即可直接计算其私钥

![image](https://user-images.githubusercontent.com/105588850/180985986-26825802-e4c3-4117-b43d-0ef0cb3e9db2.png)

![image](https://user-images.githubusercontent.com/105588850/180985970-0f6dc8fb-5e49-49d9-9049-b87a85ef9628.png)

根据ECDSA原理实现ECDSA签名算法，并实现签名伪造

对于ECDSA签名，不验证消息m的情况下可以伪造签名

当敌手获得一个签名（r，s）时，在不验证消息m的情况下可以伪造（r1，s1）通过验证。

只需生成随机u，v∈[1，n-1]，计算R=[u]G＋[v]P，那么r1=Rx%n，s1=（r1*invert（v，n））%n

![image](https://user-images.githubusercontent.com/105588850/180988382-ba5dd58b-34c8-478d-aa50-91983a2da558.png)

![image](https://user-images.githubusercontent.com/105588850/180988409-f799108e-9414-43f6-9dc4-a5cbef529f92.png)




