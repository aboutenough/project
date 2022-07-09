#include<iostream>
#include<windows.h>
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
	for (int i = 16; i < 68; i += 4) {
		W[i] = ((P1(W[i - 16] ^ W[i - 9] ^ LeftShift(W[i - 3], 15))) ^ (LeftShift(W[i - 13], 7) ^ W[i - 6]));
		W[i + 1] = ((P1(W[i - 15] ^ W[i - 8] ^ LeftShift(W[i - 2], 15))) ^ (LeftShift(W[i - 12], 7) ^ W[i - 5]));
		W[i + 2] = ((P1(W[i - 14] ^ W[i - 7] ^ LeftShift(W[i - 1], 15))) ^ (LeftShift(W[i - 11], 7) ^ W[i - 4]));
		W[i + 3] = ((P1(W[i - 13] ^ W[i - 6] ^ LeftShift(W[i], 15))) ^ (LeftShift(W[i - 10], 7) ^ W[i - 3]));
	}
	for (int i = 0; i < 64; i += 8) {
		W_[i] = (W[i] ^ W[i + 4]);
		W_[i + 1] = (W[i + 1] ^ W[i + 5]);
		W_[i + 2] = (W[i + 2] ^ W[i + 6]);
		W_[i + 3] = (W[i + 3] ^ W[i + 7]);
		W_[i + 4] = (W[i + 4] ^ W[i + 8]);
		W_[i + 5] = (W[i + 5] ^ W[i + 9]);
		W_[i + 6] = (W[i + 6] ^ W[i + 10]);
		W_[i + 7] = (W[i + 7] ^ W[i + 11]);
	}
}


string update(string V, string Bi) {
	uint32_t temp[8], temp1[8];
	for (int i = 0; i < 8; i++) {
		temp[i] = str_to_uint(V.substr(8 * i, 8));
		temp1[i] = temp[i];
	}
	uint32_t SS1, SS2, TT1, TT2;
	for (int i = 0; i < 64; i++) {
		SS1 = LeftShift((LeftShift(temp[0], 12) + temp[4] + LeftShift(Ti(i), i % 32)), 7);
		SS2 = (SS1 ^ LeftShift(temp[0], 12));
		TT1 = FFi(temp[0], temp[1], temp[2], i) + temp[3] + SS2 + W_[i];
		TT2 = GGi(temp[4], temp[5], temp[6], i) + temp[7] + SS1 + W[i];
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

string compress(string *iv, string *b)
{
	Extend(*b);
	return update(*iv, *b);
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
		IV[i + 1] = compress(&IV[i], &B[i]);
	}
	string temp = IV[group_number];
	delete[]B;
	delete[]IV;
	return temp;
}

void ex_attack(string m,string H_m1, uint64_t len,string *t,string *t2)
{
	uint64_t num = (len + 1) % 512;
	padding(*t, num < 448 ? 448 - num : 960 - num, len);
	string m1(len/4, 'a');
	m = m1+*t + m;
	uint64_t size = (uint64_t)m.size() * (uint64_t)4;
	num = (size + 1) % 512;
	int k = padding(m, num < 448 ? 448 - num : 960 - num, size);
	uint64_t group_number = (size + 65 + k) / 512;
	string IV = H_m1;
	string B = m.substr(128, 128);
	*t2 = compress(&IV, &B);
	cout << "new Hash: " << *t2 << endl;
}

int main()
{
	string m1 = "this is a project";
	string m2 = "append";
	uint64_t len1 = (uint64_t)m1.size() * (uint64_t)4;;
	string H_m1 = "944B80739E6526675273A5E234F3013841A2093D250616810B68851FCD7845EA";
	string t,temp2;
	ex_attack(m2, H_m1,len1,&t,&temp2);
	t = m1 + t + m2;
	string temp1 = SM3(t);
	cout << "M1||M2 Hash :" << temp1 << endl;
	if (temp2.compare(temp1) == 0)
		cout << "success" << endl;
	return 0;
}