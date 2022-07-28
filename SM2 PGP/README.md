Project: Implement a PGP scheme with SM2

该project实现SM2 PGP

首先通过SM2密钥交换协议两方获取一个相同密钥（密钥协商），双方完成密钥协商后，用该密钥作为对称加密
私钥来加密消息m，该项目中选取DES对称加密算法，加密完消息后，另一方用自己的公钥对协商的私钥进行加密，
加密算法为SM2。

解密时，先用私钥进行SM2解密求解协商的密钥，再使用该密钥对消息进行解密。

密钥协商：

![image](https://user-images.githubusercontent.com/105588850/181408231-d4bb2b63-c088-48ee-9c04-3ab234c2bd03.png)

此过程后两方具有相同密钥。


对消息m进行加密

![image](https://user-images.githubusercontent.com/105588850/181408474-1a565ffc-2848-44ca-ba47-387eb0724f0c.png)

![image](https://user-images.githubusercontent.com/105588850/181409147-3216d8d1-411b-4b5c-9b97-271abbf29220.png)

用公钥对协商密钥进行加密

![image](https://user-images.githubusercontent.com/105588850/181408503-39c031c6-67c5-4c0e-8041-c57718eab651.png)

利用公钥解密私钥

![image](https://user-images.githubusercontent.com/105588850/181409131-90c74b3e-93b5-4774-9de8-59aed333504b.png)

![image](https://user-images.githubusercontent.com/105588850/181409215-613bc5e5-6a3e-4f59-95c6-3cc71e7d138e.png)


利用私钥解密消息

![image](https://user-images.githubusercontent.com/105588850/181409132-027f2488-54d8-44fd-8cde-79b89d69ce8b.png)

![image](https://user-images.githubusercontent.com/105588850/181409243-6bb24781-00f7-4b1c-b9d9-75cc1e0a90f6.png)

