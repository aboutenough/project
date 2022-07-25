Project: implement the Rho method of reduced SM3

利用Rho method实现SM3哈希值高比特的碰撞

rho（）为Rho method实现。传入的参数c为碰撞的十六进制字符数量（即碰撞bit数大于等于4*c）
首先利用rand_str函数生成64长的ASCII码串，通过while循环构造p环，最大长度设置为100000即循环跳出条件
对生成的随机字符串进行哈希，并以高c个十六进制数作为索引构造哈希表。不断对上一个哈希值进行哈希以构造p环
检测在设定长度count下是否存在p碰撞。

在main函数中不断调用rho函数直到发生碰撞为止，注释的代码为打印成功的p环

由于该算法执行具有随机性，碰撞bit越高执行时间越长且每次执行结果不同，并未保存最初的执行截图，
故以36bit为样例。

![image](https://user-images.githubusercontent.com/105588850/180766623-da5b7b0c-63f8-4057-91d4-c63d627430a1.png)

该环的长度为5125，并且输出了碰撞消息。

执行结果 （注：以下m为ASCII码串，在哈希时无须转换）
34bit attack	rho lenth=43515

m1="FAAA7F208E8BEB622BC3D407764C8E74A49D4440A84D838D510FF17C69BCA62A"

m2="E283E5E9FFB09450E1BE8AF3C0556D2AD9C27472171B154D54435DE45F787272"

39 bit attack rho lenth=61371

m1="BFA90E01F10E684499EB6C7D41C94A986A96AE4F16CBE22ECDCF2DF2CF780B63"

m2="178BD25BAD8DC43AAEBEBF6D6C9DDAAA0320E8806B4E87E65A87CE0527E21F2B"


42 bit attack rho lenth=45185

m1="809F0AD92A7A86BEB55125FF47D4316B2A2AF935A45C772DE7EDCEEF866C9E00"

m2="D64A2F7855EFCE8575FD264364DA21CEE78BAFFFB8B3787FE99E4AE5A64BBC61"

该算法在可接受的时间内可达41bit碰撞.
