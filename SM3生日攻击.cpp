#include<iostream>
#include<string>
#include<windows.h>
#include <map>
#include <ctime>
#include <thread>
using namespace std;

string iv = "7380166F4914B2B9172442D7DA8A0600A96F30BC163138AAE38DEE4DB0FB0E4E";
uint32_t T[2] = { 0x79cc4519, 0x7a879d8a };
string index = "0123456789ABCDEF";
uint32_t* W = new uint32_t[68];
uint32_t* W_ = new uint32_t[64];

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

uint32_t LeftShift(uint32_t num, int left) {
	return (num << left) | (num >> (32 - left));
}

uint32_t Ti(int x) {
	return x > 15 ? T[1] : T[0];
}

uint32_t FFi(uint32_t x, uint32_t y, uint32_t z, int n) {
	return n > 15 ? ((x & y) | (y & z) | (x & z)) : (x ^ y ^ z);
}

uint32_t GGi(uint32_t x, uint32_t y, uint32_t z, int n) {
	return n > 15 ? ((x & y) | ((~x) & z)) : (x ^ y ^ z);
}

uint32_t P0(uint32_t x) {
	return (x ^ LeftShift(x, 9) ^ LeftShift(x, 17));
}

uint32_t P1(uint32_t x) {
	return (x ^ LeftShift(x, 15) ^ LeftShift(x, 23));
}

int padding(string& s, int n, uint64_t size) {
	s.push_back('8');
	for (int i = 0; i < n / 4; i++)
		s.push_back('0');
	s += uint_to_str(size, 16);
	return n;
}

void Extend(string B) {
	for (int i = 0; i < 16; i++)
		W[i] = str_to_uint(B.substr(8 * i, 8));
	for (int i = 16; i < 68; i++)
		W[i] = (P1(W[i - 16] ^ W[i - 9] ^ LeftShift(W[i - 3], 15)) ^ LeftShift(W[i - 13], 7) ^ W[i - 6]);
	for (int i = 0; i < 64; i++)
		W_[i] = (W[i] ^ W[i + 4]);
}


string compress(string V, string Bi) {
	uint32_t temp[8], temp1[8];
	for (int i = 0; i < 8; i++) {
		temp[i] = str_to_uint(V.substr(8 * i, 8));
		temp1[i] = temp[i];
	}
	for (int i = 0; i < 64; i++) {
		uint32_t SS1 = LeftShift((LeftShift(temp[0], 12) + temp[4] + LeftShift(Ti(i), i % 32)), 7);
		uint32_t SS2 = (SS1 ^ LeftShift(temp[0], 12));
		uint32_t TT1 = FFi(temp[0], temp[1], temp[2], i) + temp[3] + SS2 + W_[i];
		uint32_t TT2 = GGi(temp[4], temp[5], temp[6], i) + temp[7] + SS1 + W[i];
		temp[3] = temp[2];
		temp[2] = (LeftShift(temp[1], 9));
		temp[1] = temp[0];
		temp[0] = TT1;
		temp[7] = temp[6];
		temp[6] = LeftShift(temp[5], 19);
		temp[5] = temp[4];
		temp[4] = P0(TT2);
	}
	string result = "";
	for (int i = 0; i < 8; i++)
		result += uint_to_str(temp1[i] ^ temp[i]);
	return result;
}

string SM3(string m) {
	uint64_t size = (uint64_t)m.size() * (uint64_t)4;
	uint64_t num = (size + 1) % 512;
	int k = padding(m, num < 448 ? 448 - num : 960 - num, size);
	uint64_t group_number = (size + 65 + k) / 512;
	string* B = new string[group_number];
	string* IV = new string[group_number + 1];
	IV[0] = iv;
	for (int i = 0; i < group_number; i++) {
		B[i] = m.substr(128 * i, 128);
		Extend(B[i]);
		IV[i + 1] = compress(IV[i], B[i]);
	}
	return IV[group_number];
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



int birthdayattack(int m)
{
	srand((int)time(0));
	map<string, string> list1;
	map<string, string> list2;
	cout << "begin" << endl;
	string temp1;
	string temp2;
	string temp3;
	string temp4;
	int count = 0;
	while (count < 1000) {
		temp1 = rand_str((rand() % 256) + 16);
		temp3 = SM3(temp1).substr(0, m);
		if (list1[temp3] != "" && temp1 != list1[temp3]) {
			cout << temp1 << endl;
			cout << SM3(temp1) << endl;
			cout << list1[temp3] << endl;
			cout << SM3(list1[temp3]) << endl;
			return 1;
		}
		list1[temp3] = temp1;
		temp2 = rand_str((rand() % 256)+16);
		temp4 = SM3(temp2).substr(0, m);
		if (list2[temp4] != "" && temp2 != list2[temp4]) {
			cout << temp2 << endl;
			cout << SM3(temp2) << endl;
			cout << list2[temp4] << endl;
			cout << SM3(list2[temp4]) << endl;
			return 1;
		}
		list2[temp4] = temp2;
		count++;
	}
	map<string, string>::iterator iter;
	iter = list1.begin();
	while (iter != list1.end()) {
		if (list2.find(iter->first) != list2.end()) {
			cout <<  iter->second << endl;
			cout <<  list2[iter->first] << endl;
			return 1;
		}
		iter++;
	}
	return 0;
}

int main()
{
	while (!birthdayattack(8));
	return 0;
}

//24bit
// message:
//EAF8F197CF6D277910D6B02AB86F80C1A367DFD53661F815F5449D80AA3CA16E45675C0536990B55F5986E2D4A7058C3359102B1289CE992884A9B792FC50E8A
//8BA81C7CDB0FBE41986BB2E5AAE7FC7F01C2A6761ECF3AB838955A175960D9D86E9EF072CBB309A5F4A5D770B5713C092B8452DA7873A3BE4313C0885681AE8C

//29bit
// message:
//F7313BCC391ADE20649B3E29C7DCE61A153992790572432FD36B1F1BBD4CAE9F66729E42B7ADE0DCB9C0C85DCCE5C116848697ADC6453BCEAF25D2757E2EE715
//1F9B1C4F50BA94CF452DA5913F1BCA15C0E29FD4CF512596474CA15AC8EB9E72B58BA67404FCDD2AD1F166736BD3DCD065FFCBB7B7E344E35BB58C73B07C0DA7


//31bit
//message
//1EC16C92B263F795913242A8C397906EB55178BD266FA2B
//C3AF9F007FDF74289C2D19A

//32bit
//message
//00E5989CF3E4EC07B4CE86BA5FD29E3D28B29E1E9346197E8C991171F00ABFA2313C50ADD6F6B2939963BB8A77E3710AD40963D1249B3FDF53C5DA6B4EE66CDC58824101169E29DA4317089DFC7BF7A2655E61C62377070CF0F
//2DA8BCC50A038F9C48545522CF3C2E339AAF21EC18C5E57FEC0A1963DE0DBD9208A5F6F9C9374EDCC5F172CFC2B3729EFD308446A3C2122A69B3E7CF25C4F6D0E2DA738B1F0CD8F141C7E2DA5DCA91DF5FFB2B1EB56009CAF4A6F988F33DFB14DB193479ED732E0CDCC695426E838B05C0DE05344FBFCD407FA15EAF4