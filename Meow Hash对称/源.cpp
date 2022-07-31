#include "meow_hash_x64_aesni.h"
#include<iostream>
using namespace std;
string index = "0123456789abcdef";

string uint_to_str(uint8_t* num, string s = "") {
    for (int i = 0; i < 16; i++) {
        s += index[(num[i]) / 16];
        s += index[(num[i]) % 16];
    }
    return  s;
}

string str_Hash(meow_u128 Hash)
{
    uint8_t out[16];
    *(uint32_t*)&out = (uint32_t)MeowU32From(Hash, 0);
    *(uint32_t*)&out[4] = (uint32_t)MeowU32From(Hash, 1);
    *(uint32_t*)&out[8] = (uint32_t)MeowU32From(Hash, 2);
    *(uint32_t*)&out[12] = (uint32_t)MeowU32From(Hash, 3);
    /*for (int i = 0; i < 16; i++)
        printf("%02X", out[i]);*/
    return uint_to_str(out);
}



static void dump_buf(uint8_t* buf, uint32_t len)
{
    int i;
    printf("buf:");

    for (i = 0; i < len; i++) {
        printf("%s%02X%s", i % 16 == 0 ? "\r\n\t" : " ",
            buf[i],
            i == len - 1 ? "\r\n" : "");
    }
}




static void print_num(uint64_t buf)
{
    int len = 1;
    int i;
    printf("buf:");

    for (i = 0; i < len; i++) {
        printf("%s%02X%s", i % 16 == 0 ? "\r\n\t" : " ",
            buf,
            i == len - 1 ? "\r\n" : "");
    }
}


int main() {
    uint64_t symmetrize32[16] = {
    3224358602161482154llu, 1814594138510994814llu, 13954951486077169833llu, 12219675304746119337llu,
    32, 0, 0, 0,
    15245537510594700387llu, 11375056618140292268llu, 15015954861103735561llu, 7161769469951828835llu,
    0, 0, 0, 0
    };
    uint64_t message[4] = { 1,1, 1, 1 };
    meow_u128 h = MeowHash(symmetrize32, 32, message);
    cout << str_Hash(h) << endl;
}