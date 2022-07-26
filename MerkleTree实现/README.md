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

在Merkle Tree优化中，以一种更简单的方式实现Merkle Tree

其中主要优化在MerkleTreeCreate（）中，树的创建用队列和栈来代替原来的递归。

该函数中，自下向上创建结点，利用数组（vector）来表示树。首先将所有结点入队列，将结点数按奇偶分开讨论，结点数的奇偶会导致某结点计算哈希值的方法不同（是否需要填充结点）。以最底层结点开始向上计算，如果最底层为偶数则直接两两计算，并将计算的新结点入队列，若为奇数，则将最后一个结点保留。计算过程中，将每一个结点入栈，并通过栈（保证顺序）在每一层的计算完成后插入到treelist数组中。计算完后，以新节点继续计算，以此向上完成树的实现。

ExistCheck（）实现存在性检验，在树创建的过程中对最初的结点构造哈希表，以记录每个结点的位置。存在性检验中输入要查找的字符串，通过查找哈希表找到相应的位置，通过指定路径计算根节点，判断是否存在。

Create_10w_leaf（）为创建10w个叶节点。

main（）函数中对于创建10w个叶节点进行测试
![image](https://user-images.githubusercontent.com/105588850/180905907-0fab0e38-30b8-485d-aad8-d46859ff334d.png)

存在性测试

![image](https://user-images.githubusercontent.com/105588850/180906511-99e6311c-f22f-4000-a449-ae26a9780879.png)

![image](https://user-images.githubusercontent.com/105588850/180906510-9ad989f2-d30f-4fc5-b790-12109c997a8d.png)

