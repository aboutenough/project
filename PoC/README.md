Project: PoC impl of the scheme, or do implement analysis by Google

该project模拟实现PoC，利用python UDP来模拟client与server之间的通信

client计算k，v发送给服务器，服务器根据k来查找符合要求的集合，并将该集合与h^ab一并发送给client。client在集合中查找，看自己的用户名及密钥是否泄漏。

该演示构建一个实例，以两个小名单库为例

![image](https://user-images.githubusercontent.com/105588850/182011822-73dd85e9-e339-40b3-ae99-4f2f9051ecd0.png)

![image](https://user-images.githubusercontent.com/105588850/182011842-98f35963-6ff4-4fae-b759-242467ffd0ec.png)

服务器先进行本地预计算。

而client为

![image](https://user-images.githubusercontent.com/105588850/182011852-3c98ff87-b450-4736-a130-f1858dc96145.png)

执行结果

![image](https://user-images.githubusercontent.com/105588850/182011858-6b714b38-eb81-440b-b8e9-b8bd7f5b9c9f.png)

![image](https://user-images.githubusercontent.com/105588850/182011862-baad1a1f-bf6c-425c-8aaa-0690c3169a84.png)
