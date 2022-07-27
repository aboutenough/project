Project: Implement the above ECMH scheme

该project主要实现了ECMH

该算法中利用SM3作为哈希函数，对于一个消息m，计算d=Hash（m），再将其映射到椭圆曲线上的点M=[d]G，即可
具有相关性质。

EC_hash为计算一个字符串的哈希

![image](https://user-images.githubusercontent.com/105588850/181162420-a8825a66-6e96-4c5c-8390-8217470096c5.png)

![image](https://user-images.githubusercontent.com/105588850/181162394-b4ef5b6a-65f7-4a08-abae-5f5a7f596855.png)

EC_Hashab为计算两个字符串的哈希

![image](https://user-images.githubusercontent.com/105588850/181162589-3a2ee185-c155-47e9-a138-72525857d808.png)

![image](https://user-images.githubusercontent.com/105588850/181162597-d3357d96-8366-43d3-b3f2-5e64eefc3c21.png)

EC_add为两个哈希值相加，用于验证是否满足同态

![image](https://user-images.githubusercontent.com/105588850/181162896-6e2cb914-763c-4731-942d-3dd2c84775c3.png)

![image](https://user-images.githubusercontent.com/105588850/181162972-1be87645-7e10-4b0d-8479-612e7b5cb5a8.png)

结果相同满足同态

ECMH函数计算一个字符串列表的哈希值

![image](https://user-images.githubusercontent.com/105588850/181163138-a851818b-0219-4942-baa8-8818ffa02b98.png)

![image](https://user-images.githubusercontent.com/105588850/181163157-afddece1-89eb-4be0-aed9-b345f59de653.png)

remove函数为计算移除一个字符串后的哈希值

removelist为计算移除一个字符串列表的哈希值

此处演示验证message列表中移除message1列表中的哈希值是否正确

![image](https://user-images.githubusercontent.com/105588850/181163569-309a5059-e7bc-41fa-907e-3244f615232d.png)


![image](https://user-images.githubusercontent.com/105588850/181163551-01e5e588-a2d2-4f5d-8b34-386c6bf6c366.png)
