import socket
import sys
from random import randint
import math
from gmpy2 import invert
import json
import random
import binascii
import math
import time
import binascii
iv = "7380166F4914B2B9172442D7DA8A0600A96F30BC163138AAE38DEE4DB0FB0E4E"
T = (0x79cc4519, 0x7a879d8a)
index = "0123456789ABCDEF"
W = []
W_ = []

def LeftShift(num, left):
    return (((num << left)&((1<<32)-1)) | (num >> (32 - left)))


def Ti(x):
    return (T[1]) if x > 15 else (T[0])


def FFi(x, y, z, n):
    return ((x & y) | (y & z) | (x & z)) if n > 15 else (x ^ y ^ z)


def GGi(x, y, z, n):
    return ((x & y) | ((~x) & z)) if n > 15 else (x ^ y ^ z)


def P0(x):
    return (x ^ LeftShift(x, 9) ^ LeftShift(x, 17))


def P1(x):
    return (x ^ LeftShift(x, 15) ^ LeftShift(x, 23))


def padding(n, size,s):
    s=list(s)
    s.append('8')
    for i in range(0, n // 4):
        s.append("0")
    s=''.join(s)
    s+=hex(size)[2:].zfill(16).upper()
    return n,s





def Extend(B):
    for i in range(0, 16):
        W.append(int(B[(8 * i):(8 * i) + 8],16)%((1<<32)))

    for i in range(16, 68):
        W.append(int(hex((P1(W[i - 16] ^ W[i - 9] ^ LeftShift(W[i - 3], 15))) ^ (LeftShift(W[i - 13], 7) ^ W[i - 6])),16)%((1<<32)))

    for i in range(0, 64):
        W_.append(int(hex(W[i] ^ W[i + 4]),16)%((1<<32)))

index=['0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F']
def uint_to_str(num,k = 8) :
    s=""
    for i in range(0,k):
        s+=index[num % 16]
        num//=16
    return  s[::-1]

def update(V, Bi):
    temp = []
    temp1 = []
    for i in range(0, 8):
        t="0x"+V[8 * i: (8 * i) + 8]
        temp.append(int(t,16))
        temp1.append(temp[i])
    for i in range(0, 64):
        SS1 = LeftShift((LeftShift(temp[0], 12) + temp[4] + LeftShift(Ti(i), i % 32))%(1<<32), 7)
        SS2 = (SS1 ^ LeftShift(temp[0], 12))
        t=(FFi(temp[0], temp[1], temp[2], i)+temp[3])%((1<<32))
        TT1 = (FFi(temp[0], temp[1], temp[2], i) + temp[3] + SS2 + W_[i])%(1<<32)
        TT2 = (GGi(temp[4], temp[5], temp[6], i) + temp[7] + SS1 + W[i])%(1<<32)
        temp[3] = temp[2]
        temp[2] = (LeftShift(temp[1], 9))
        temp[1] = temp[0]
        temp[0] = TT1
        temp[7] = temp[6]
        temp[6] = LeftShift(temp[5], 19)
        temp[5] = temp[4]
        temp[4] = P0(TT2)
    result = ""
    for i in range(0, 8):
        result += uint_to_str(temp1[i] ^ temp[i])
    return result.upper()


def Hash(m):
    m = '0' * ((4 - (len(bin(int(m.encode().hex(), 16))[2:]) % 4)) % 4) + bin(int(m.encode().hex(), 16))[2:]
    size = len(m) * 4
    num = (size + 1) % 512
    t = 448 - num if num < 448 else 960 - num
    k ,m= padding(t,size,m)
    t=len(m)
    group_number = (size + 65 + k) // 512
    B = []
    IV = []
    IV.append(iv)
    for i in range(0, group_number):
        B.append(m[128 * i:128 * i + 128])
        Extend(B[i])
        IV.append(update(IV[i], B[i]))
        W.clear()
        W_.clear()
    temp = IV[group_number]
    return temp

def mod(x,n,m): #模幂运算
    if(n==0):
        return 1
    res=mod((x*x)%m,n//2,m)
    if(n%2==1):
        res=(res*x)%m
    return res

n=0xBDB6F4FE3E8B1D9E0DA8C0D46F4C318CEFE4AFE3B6B8551F
d=0xBDB6F4FE3E8B1D9E0DA8C0D40FC962195DFAE76F56564677

host = '127.0.0.1'
port=1234
address=(host,port)
s_client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

u="Steve"   #user name
p="1234567"     #password

sk=1234567

try:
    s_client.connect(address)
    print("Successfully connected")
except Exception:
    print('Not found or not open')
    sys.exit()
else:
    h = Hash(u + p)
    k = h[:4]  # 两个字节
    v = hex(mod(int(h, 16), sk, n))[2:]

    s_client.sendto(k.encode(), address)
    s_client.sendto(v.encode(), address)

    H_ab, address = s_client.recvfrom(1024)
    H_ab = int(H_ab.decode(), 16)

    S, address = s_client.recvfrom(1024)
    S = S.decode('utf-8')
    S = json.loads(S)

    H_b = hex(mod(H_ab, invert(sk, n-1), n)).upper()[2:]
    flag=0
    for item in S:
        if H_b==item[1]:
            print("unsafe")
            flag=1
            break
    if flag==0:
        print("safe")
    s_client.close()



