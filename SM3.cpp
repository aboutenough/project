#include <iostream>
#include <string>
#include <cmath>
#include<windows.h>
using namespace std;
/*----SM3加密----*/

string BinToHex(string str) {
	string t = "";
	int temp = 0;
	while (str.size() % 4 != 0) 
	{
		str = "0" + str;
	}
	for (int i = 0; i < str.size(); i += 4) {
		temp = (str[i] - '0') * 8 + (str[i + 1] - '0') * 4 + (str[i + 2] - '0') * 2 + (str[i + 3] - '0') * 1;
		if (temp < 10) 
		{
			t += to_string(temp);
		}
		else 
		{
			t += 'A' + (temp - 10);
		}
	}
	return t;
}


string HexToBin(string str) 
{
	string t = "";
	string temp[16] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	for (int i = 0; i < str.size(); i++) 
	{
		if (str[i] >= 'A' && str[i] <= 'F') 
		{
			t += temp[str[i] - 'A' + 10];
		}
		else 
		{
			t += temp[str[i] - '0'];
		}
	}
	return t;
}

int BinToDec(string str) 
{
	int t = 0;
	for (int i = 0; i < str.size(); i++) 
	{
		t += (str[i] - '0') * pow(2, str.size() - i - 1);
	}
	return t;
}


string DecToBin(int str) {
	string t = "";
	while (str >= 1) 
	{
		t = to_string(str % 2) + t;
		str = str / 2;
	}
	return t;
}


int HexToDec(string str) 
{
	int t = 0;
	for (int i = 0; i < str.size(); i++) 
	{
		if (str[i] >= 'A' && str[i] <= 'F') 
		{
			t += (str[i] - 'A' + 10) * pow(16, str.size() - i - 1);
		}
		else 
		{
			t += (str[i] - '0') * pow(16, str.size() - i - 1);
		}
	}
	return t;
}


string DecToHex(int str) 
{
	string t = "";
	int temp = 0;
	while (str >= 1) {
		temp = str % 16;
		if (temp < 10 && temp >= 0) {
			t = to_string(temp) + t;
		}
		else {
			t += ('A' + (temp - 10));
		}
		str = str / 16;
	}
	return t;
}

string padding(string str)		//对数据进行填充 
{
	string res = "";
	for (int i = 0; i < str.size(); i++) 
	{
		res += DecToHex((int)str[i]);
	}
	cout << "输入字符串的ASCII码表示为：" << endl;
	for (int i = 0; i < res.size(); i++) {
		cout << res[i];
		if ((i + 1) % 8 == 0) {
			cout << "  ";
		}
		if ((i + 1) % 64 == 0 || (i + 1) == res.size()) {
			cout << endl;
		}
	}
	cout << endl;
	int res_length = res.size() * 4;
	res += "8";
	while (res.size() % 128 != 112) {
		res += "0";
	}
	string res_len = DecToHex(res_length);
	while (res_len.size() != 16) {
		res_len = "0" + res_len;
	}
	res += res_len;
	return res;
}

string LeftShift(string str, int len) 
{
	string res = HexToBin(str);
	res = res.substr(len) + res.substr(0, len);
	return BinToHex(res);
}

string XOR(string str1, string str2) {
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) 
	{
		if (res1[i] == res2[i]) 
		{
			res += "0";
		}
		else 
		{
			res += "1";
		}
	}
	return BinToHex(res);
}

string AND(string str1, string str2) 
{
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) 
	{
		if (res1[i] == '1' && res2[i] == '1') 
		{
			res += "1";
		}
		else {
			res += "0";
		}
	}
	return BinToHex(res);
}

string OR(string str1, string str2) 
{
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) 
	{
		if (res1[i] == '0' && res2[i] == '0') 
		{
			res += "0";
		}
		else 
		{
			res += "1";
		}
	}
	return BinToHex(res);
}

string NOT(string str) {
	string res1 = HexToBin(str);
	string res = "";
	for (int i = 0; i < res1.size(); i++) 
	{
		if (res1[i] == '0')
		{
			res += "1";
		}
		else 
		{
			res += "0";
		}
	}
	return BinToHex(res);
}

char binXor(char str1, char str2) {
	return str1 == str2 ? '0' : '1';
}

char binAnd(char str1, char str2) {
	return (str1 == '1' && str2 == '1') ? '1' : '0';
}

string ModAdd(string str1, string str2) 
{
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
	char temp = '0';
	string res = "";
	for (int i = res1.size() - 1; i >= 0; i--) 
	{
		res = binXor(binXor(res1[i], res2[i]), temp) + res;
		if (binAnd(res1[i], res2[i]) == '1') 
		{
			temp = '1';
		}
		else 
		{
			if (binXor(res1[i], res2[i]) == '1') 
			{
				temp = binAnd('1', temp);
			}
			else 
			{
				temp = '0';
			}
		}
	}
	return BinToHex(res);
}

string P1(string str) 
{
	return XOR(XOR(str, LeftShift(str, 15)), LeftShift(str, 23));
}

string P0(string str) 
{
	return XOR(XOR(str, LeftShift(str, 9)), LeftShift(str, 17));
}

string T(int j) 
{
	if (0 <= j && j <= 15) {
		return "79CC4519";
	}
	else {
		return "7A879D8A";
	}
}

string FF(string str1, string str2, string str3, int j) 
{
	if (0 <= j && j <= 15) 
	{
		return XOR(XOR(str1, str2), str3);
	}
	else 
	{
		return OR(OR(AND(str1, str2), AND(str1, str3)), AND(str2, str3));
	}
}

string GG(string str1, string str2, string str3, int j) 
{
	if (0 <= j && j <= 15) 
	{
		return XOR(XOR(str1, str2), str3);
	}
	else 
	{
		return OR(AND(str1, str2), AND(NOT(str1), str3));
	}
}
string extension(string str) 
{
	string res = str;
	for (int i = 16; i < 68; i++) 
	{
		res += XOR(XOR(P1(XOR(XOR(res.substr((i - 16) * 8, 8), res.substr((i - 9) * 8, 8)), LeftShift(res.substr((i - 3) * 8, 8), 15))), LeftShift(res.substr((i - 13) * 8, 8), 7)), res.substr((i - 6) * 8, 8));
	}
	for (int i = 0; i < 64; i++) 
	{
		res += XOR(res.substr(i * 8, 8), res.substr((i + 4) * 8, 8));
	}

	return res;
}

string compress(string str1, string str2)
{
	string IV = str2;
	string A = IV.substr(0, 8), B = IV.substr(8, 8), C = IV.substr(16, 8), D = IV.substr(24, 8), E = IV.substr(32, 8), F = IV.substr(40, 8), G = IV.substr(48, 8), H = IV.substr(56, 8);
	string SS1 = "", SS2 = "", TT1 = "", TT2 = "";
	for (int j = 0; j < 64; j++) {
		SS1 = LeftShift(ModAdd(ModAdd(LeftShift(A, 12), E), LeftShift(T(j), (j % 32))), 7);
		SS2 = XOR(SS1, LeftShift(A, 12));
		TT1 = ModAdd(ModAdd(ModAdd(FF(A, B, C, j), D), SS2), str1.substr((j + 68) * 8, 8));
		TT2 = ModAdd(ModAdd(ModAdd(GG(E, F, G, j), H), SS1), str1.substr(j * 8, 8));
		D = C;
		C = LeftShift(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = LeftShift(F, 19);
		F = E;
		E = P0(TT2);
	}
	string res = (A + B + C + D + E + F + G + H);
	cout << endl;
	return res;
}

string iteration(string str) 
{
	int num = str.size() / 128;
	string V = "7380166F4914B2B9172442D7DA8A0600A96F30BC163138AAE38DEE4DB0FB0E4E";
	string B = "", extensionB = "", compressB = "";
	for (int i = 0; i < num; i++)
	{
		B = str.substr(i * 128, 128);
		extensionB = extension(B);
		compressB = compress(extensionB, V);
		V = XOR(V, compressB);
	}
	return V;
}

int main() 
{

	string message;
	message = "steve";
	cout <<"输入: " + message << endl;
	cout << endl;
	LARGE_INTEGER BegainTime;
	LARGE_INTEGER EndTime;
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&BegainTime);
	string paddingValue = padding(message);
	cout << "填充后的消息为：" << endl;
	for (int i = 0; i < paddingValue.size() / 64; i++) {
		for (int j = 0; j < 8; j++) {
			cout << paddingValue.substr(i * 64 + j * 8, 8) << "  ";
		}
		cout << endl;
	}
	cout << endl;
	string result = iteration(paddingValue);
	cout << "杂凑值：" << endl;
	for (int i = 0; i < 8; i++) {
		cout << result.substr(i * 8, 8) << "  ";
	}
	cout << endl;
	QueryPerformanceCounter(&EndTime);
	cout << "运行时间（单位：s）：" << (double)(EndTime.QuadPart - BegainTime.QuadPart) / Frequency.QuadPart << endl;
}
