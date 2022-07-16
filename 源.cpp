#include<iostream>
#include<windows.h>
#include<sstream>
#include<vector>
#include<queue>
#include<stack>
#include<map>
using namespace std;

string index = "0123456789ABCDEF";
uint32_t* W = new uint32_t[64];

string str_to_hex(const string& str)
{
	string result = "";
	string tmp;
	stringstream ss;
	for (int i = 0; i < str.size(); i++)
	{
		ss << hex << int(str[i]) << endl;
		ss >> tmp;
		result += tmp;
	}
	return result;
}
uint32_t H[8]
{
	0x6a09e667,0xbb67ae85,
	0x3c6ef372,0xa54ff53a,
	0x510e527f,0x9b05688c,
	0x1f83d9ab,0x5be0cd19
};

uint32_t K[64]
{
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

int hex_to_int(char p) {
	return p < 58 ? p - 48 : p - 55;
}

uint32_t str_to_uint(string s) {
	uint32_t temp = 0;
	for (auto i : s)
		temp = ((temp << 4) | hex_to_int(i));
	return temp;
}

string uint_to_str(uint32_t num, int k = 8, string s = "") {
	for (int i = 0; i < k; i++, num /= 16)
		s += index[num % 16];
	return  string(s.rbegin(), s.rend());
}

int padding(string& s, int n, uint64_t size) {
	s.push_back('8');
	for (int i = 0; i < n / 4; i++)
		s.push_back('0');
	s += uint_to_str(size, 16);
	return n;
}

uint32_t Ch(uint32_t x, uint32_t y, uint32_t z) {
	return (x & y) ^ ((~x) & z);
}

uint32_t M(uint32_t x, uint32_t y, uint32_t z) {
	return (x & y) ^ (x & z) ^ (y & z);
}

uint32_t RightShift(uint32_t num, int left) {
	return (num >> left) | (num << (32 - left));
}

uint32_t F1(uint32_t x)
{
	return RightShift(x, 2) ^ RightShift(x, 13) ^ RightShift(x, 22);
}

uint32_t F2(uint32_t x)
{
	return RightShift(x, 6) ^ RightShift(x, 11) ^ RightShift(x, 25);
}

uint32_t F3(uint32_t x)
{
	return RightShift(x, 7) ^ RightShift(x, 18) ^ (x >> 3);
}

uint32_t F4(uint32_t x)
{
	return RightShift(x, 17) ^ RightShift(x, 19) ^ (x >> 10);
}

void compress(uint32_t* temp)
{
	uint32_t T1, T2;
	for (int j = 0; j < 64; j++)
	{
		T1 = temp[7] + F2(temp[4]) + Ch(temp[4], temp[5], temp[6]) + K[j] + W[j];
		T2 = F1(temp[0]) + M(temp[0], temp[1], temp[2]);
		temp[7] = temp[6];
		temp[6] = temp[5];
		temp[5] = temp[4];
		temp[4] = temp[3] + T1;
		temp[3] = temp[2];
		temp[2] = temp[1];
		temp[1] = temp[0];
		temp[0] = T1 + T2;
	}
}

void extend(string m)
{
	for (int i = 0; i < 16; i++)
	{
		W[i] = str_to_uint(m.substr(i * 8, 8));
	}
	for (int i = 16; i < 64; i++)
	{
		W[i] = F4(W[i - 2]) + W[i - 7] + F3(W[i - 15]) + W[i - 16];
	}
}

string Hash(string m)	//SHA_256
{
	m = str_to_hex(m);
	uint64_t size = (uint64_t)m.size() * (uint64_t)4;
	uint64_t num = (size + 1) % 512;
	int k = padding(m, num < 448 ? 448 - num : 960 - num, size);
	extend(m);
	uint64_t group_number = (size + 65 + k) / 512;
	uint32_t temp[8];
	uint32_t temp1[8];
	for (int i = 0; i < 8; i++)
	{
		temp[i] = H[i];
		temp1[i] = H[i];
	}
	uint32_t t;
	for (int i = 0; i < group_number; i++)
	{
		compress(temp);
		for (int i = 0; i < 8; i++)
		{
			t = temp[i];
			temp[i] = t + temp1[i];
			temp1[i] = temp[i];
		}
	}
string result = "";
for (int i = 0; i < 8; i++)
	result += uint_to_str(temp[i]);
return result;
}

typedef struct MerkleNode {
	struct MerkleNode* lChild;
	struct MerkleNode* rChild;
	struct MerkleNode* parent;
	struct MerkleNode* brother;
	string data;
	MerkleNode() :data(""), lChild(nullptr), rChild(nullptr), parent(nullptr), brother(nullptr) {}
	MerkleNode(string m) :data(m), lChild(nullptr), rChild(nullptr), parent(nullptr), brother(nullptr) {}
};

class MerkleTree {
private:
	vector<MerkleNode*>treelist;
	map<string, MerkleNode*>leaf;
	string hashHead;
	int leafnum;
public:
	void MerkleTreeCreate(int num, string* str) {
		leafnum = num;
		queue< MerkleNode*> templist;
		stack< MerkleNode*>templist2;
		string m;
		if (num % 2 == 0) {
			for (int i = 0; i < num; i++)
			{
				m = Hash(str[i]);
				MerkleNode* temp = new MerkleNode(m);
				leaf[m] = temp;
				templist.push(temp);
			}
		}
		else
		{
			for (int i = 0; i < num - 1; i++)
			{
				m = Hash(str[i]);
				MerkleNode* temp = new MerkleNode(m);
				templist.push(temp);
				leaf[m] = temp;
			}
			m = Hash(str[num - 1]);
			MerkleNode* temp = new(MerkleNode)(Hash(str[num - 1] + str[num - 1]));
			leaf[m] = temp;
			templist.push(temp);
		}
		int level = 0;
		while (templist.size() != 1)
		{
			int t = (templist.size() % 2 == 0) ? templist.size() : templist.size() - 1;
			MerkleNode* t1, * t2;
			for (int i = 0; i < t; i += 2)
			{
				t1 = templist.front();
				templist2.push(t1);
				templist.pop();
				t2 = templist.front();
				templist2.push(t2);
				templist.pop();
				t1->brother = t2;
				t2->brother = t1;
				MerkleNode* t3 = new MerkleNode(Hash(t1->data + t2->data));
				t3->lChild = t1;
				t3->rChild = t2;
				t1->parent = t3;
				t2->parent = t3;
				templist.push(t3);
			}
			if (t % 2 == 0)
			{
				templist.push(templist.front());
				templist.pop();
			}
			while (templist2.size() != 0)
			{
				treelist.insert(treelist.begin(), templist2.top());
				templist2.pop();
			}
			level++;
		}
		treelist.insert(treelist.begin(), templist.front());
		treelist[0]->lChild = treelist[1];
		treelist[0]->rChild = treelist[2];
		hashHead = treelist[0]->data;
	}
	bool ExistCheck(string m)
	{
		string t;
		MerkleNode* node = leaf[Hash(m)];
		if (node == NULL)
			return 0;
		while (node->brother != NULL)
		{
			node = node->parent;
			t = Hash(node->lChild->data + node->rChild->data);
		}
		if(t.compare(hashHead)==0)
			return true;
		return false;
	}

	void printTree() //层序遍历
	{
		cout << "层序遍历" << endl;
		int n = treelist.size();
		for (int i = 0; i < n; i++)
		{
			cout << "data: " << treelist[i]->data << endl;
		}
	}

	string rand_str(const int len)
	{
		string str;
		char c;
		int idx;
		for (idx = 0; idx < len; idx++)
		{
			c = index[rand() % 16];
			str.push_back(c);
		}
		return str;
	}

	void Create_10w_leaf()
	{
		string* sList = new string[100000];
		for (int i = 0; i < 100000; i++)
		{
			sList[i] = rand_str(16);
		}
		cout << "begin" << endl;
		MerkleTreeCreate(100000, sList);
		cout << "success" << endl;
	}

};



int main()
{
	LARGE_INTEGER BegainTime;
	LARGE_INTEGER EndTime;
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&BegainTime);
	MerkleTree tree;
	tree.Create_10w_leaf();
	QueryPerformanceCounter(&EndTime);
	cout << "运行时间（单位：s）：" << (double)(EndTime.QuadPart - BegainTime.QuadPart) / Frequency.QuadPart << endl;
	return 0;
}
