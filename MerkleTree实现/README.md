Project: Impl Merkle Tree following RFC6962

该project实现了Merkle Tree

在MerkleTree.cpp中，利用class类实现Merkle Tree

LastNode（）返回最后一个结点指针

CreateNode（）创建一个空结点

CreatTree（）利用递归方式将一个字符串数组构建Merkle Tree

EmptyNode（）自下往上查找一个空结点

DeleteTree（）释放该树

printTree（）为层序遍历，按层打印树结点的值

该样例为创建一个10个节点的树，并按层序打印。

![image](https://user-images.githubusercontent.com/105588850/180903953-27d66e15-3cb6-4bea-a838-99e1562e4d15.png)

该代码在创建结点较少的树时可以较快速的实现，但由于采用递归创建树时过程较为繁琐，创建10w结点需要大量时间
因此对Merkle Tree的实现进行了优化

在Merkle Tree优化中
