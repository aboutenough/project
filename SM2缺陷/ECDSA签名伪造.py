from random import randint
import math
from gmpy2 import invert
import random
import binascii



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
    return qx%p,qy%p




p=0x8542D69E4C044F18E8B92435BF6FF7DE457283915C45517D722EDB8B08F1DFC3    #256
a=0x787968B4FA32C3FD2417842E73BBFEFF2F3C848B6831D7E0EC65228B3937E498
b=0x63E4C6D3B23B0C849CF84241484BFE48F61D59A5B16BA06E6E12D1DA27C5249A
n=0x8542D69E4C044F18E8B92435BF6FF7DD297720630485628D5AE74EE7C32E79B7
Gx=0x421DEBD61B62EAB6746434EBC3CC315E32220B3BADD50BDC4C4E6C147FEDD43D
Gy=0x0680512BCBB42C07D47349D2153B70C4E5D7FDFCBFA36EA1A85841B9E46E09A2
P=(0x7e2c7fd68d3f5af1544f075ba4c29dd3e4cb7d1f96a880354875d9e7b6f24cec,
   0x8058596a79762023a4dace0a107ae0b35ca448ebf2dd32cbf7a0fea3084d5233)


def Verify(r,s,e):
    if int(r,16) not in range(1,n-1):
        return False
    if int(s,16) not in range(1,n-1):
        return False
    s=int(s,16)
    r=int(r,16)
    e = int(e, 16)
    w=invert(s,n)
    u1=(e*w)%n
    u2=(r*w)%n
    x1,y1=mul_add(Gx,Gy,u1)
    x2,y2=mul_add(P[0],P[1],u2)
    X=add(x1,y1,x2,y2)
    if(X[0]%n==r):
        return True
    return False


def sig_forge(r,s):
    u=randint(1,n)
    v=randint(1,n)
    x,y=mul_add(Gx,Gy,u)
    x1,y1=mul_add(P[0],P[1],v)
    R=add(x,y,x1,y1)
    r1=R[0]%n
    e1=(r1*u*invert(v,n))%n
    print(hex(e1))
    s1=(r1*invert(v,n))%n
    return hex(r1),hex(s1),hex(e1)

r=0x6a8a98bdf35dc8bc03a3b0c8e909bb6f191972f77d5fc646ad5d8d4128ae025
s=0x4193be4246138851670ef1e04aa4c372094ca477dc7a73fa95dd9d110867278

r1,s1,e1=sig_forge(r,s)
print(Verify(r1,s1,e1))

