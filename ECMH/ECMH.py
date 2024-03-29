from random import randint
import math
from gmpy2 import invert
import random
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


p=0x8542D69E4C044F18E8B92435BF6FF7DE457283915C45517D722EDB8B08F1DFC3    #256
a=0x787968B4FA32C3FD2417842E73BBFEFF2F3C848B6831D7E0EC65228B3937E498
b=0x63E4C6D3B23B0C849CF84241484BFE48F61D59A5B16BA06E6E12D1DA27C5249A
n=0x8542D69E4C044F18E8B92435BF6FF7DD297720630485628D5AE74EE7C32E79B7
Gx=0x421DEBD61B62EAB6746434EBC3CC315E32220B3BADD50BDC4C4E6C147FEDD43D
Gy=0x0680512BCBB42C07D47349D2153B70C4E5D7FDFCBFA36EA1A85841B9E46E09A2

def add(x1,y1,x2,y2):
    if x1==x2 and y1==p-y2:
        return False
    if x1!=x2:
        lamda=((y2-y1)*invert(x2-x1, p))%p
    else:
        lamda=(((3*x1*x1+a)%p)*invert(2*y1, p))%p
    x3=(lamda*lamda-x1-x2)%p
    y3=(lamda*(x1-x3)-y1)%p
    return x3,y3

def mul_add(x,y,k):
    k=bin(k)[2:]
    qx,qy=x,y
    for i in range(1,len(k)):
        qx,qy=add(qx, qy, qx, qy)
        if k[i]=='1':
            qx,qy=add(qx, qy, x, y)
    return qx,qy

def EC_Hash(m):     #一个字符串哈希
    m = hex(int(binascii.b2a_hex(m.encode()).decode(), 16)).upper()[2:]
    t=Hash(m)
    return mul_add(Gx,Gy,int(t,16))

def EC_add(m1,m2):      #两个哈希值相加
    return add(m1[0],m1[1],m2[0],m2[1])

def EC_Hashab(m1,m2):   #两个字符串哈希
    m1 = hex(int(binascii.b2a_hex(m1.encode()).decode(), 16)).upper()[2:]
    m2 = hex(int(binascii.b2a_hex(m2.encode()).decode(), 16)).upper()[2:]
    t1 = Hash(m1)
    t2 = Hash(m2)
    return mul_add(Gx,Gy,int(t1,16)+int(t2,16))

def ECMH(m):    #字符串列表哈希
    t=0
    for i in range(0,len(m)):
       t+= int(Hash(hex(int(binascii.b2a_hex(m[i].encode()).decode(), 16)).upper()[2:]),16)
    return mul_add(Gx, Gy, t)

def remove(m,hash):     #移除一个字符串
    m = hex(int(binascii.b2a_hex(m.encode()).decode(), 16)).upper()[2:]
    t=int(Hash(m),16)
    x,y=mul_add(Gx, Gy, t)
    return add(hash[0],hash[1],x,-y)

def removelist(m,hash):     #移除字符串列表
    t=0
    for i in range(0,len(m)):
       t+= int(Hash(hex(int(binascii.b2a_hex(m[i].encode()).decode(), 16)).upper()[2:]),16)
    x, y = mul_add(Gx, Gy, t)
    return add(hash[0],hash[1],x,-y)
m1="test1"
#print((hex(EC_Hash(m1)[0]),hex(EC_Hash(m1)[1])))
m2="test2"
# print((hex(EC_Hashab(m1,m2)[0]),hex(EC_Hashab(m1,m2)[1])))
# x=EC_Hash(m1)
# y=EC_Hash(m2)
# print((hex(EC_add(x,y)[0]),hex(EC_add(x,y)[1])))
m3="test3"
message=[]
message.append(m1)
message.append(m2)
message.append(m3)
# print((hex(ECMH(message)[0]),hex(ECMH(message)[1])))
message1=[]
message1.append(m2)
message1.append(m3)
print((hex(EC_Hash(m1)[0]),hex(EC_Hash(m1)[1])))
print((hex(removelist(message1,ECMH(message))[0]),hex(removelist(message1,ECMH(message))[1])))
