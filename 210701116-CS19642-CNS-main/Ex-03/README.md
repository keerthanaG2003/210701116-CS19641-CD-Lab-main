# Aim:
To write a python program implementing the RSA algorithm.
# Algorithm:
### 1.Choose two large prime numbers (p and q)
### 2.Calculate n = p*q and z = (p-1)(q-1)
### 3.Choose a number e where 1 < e < z.
### 4.Calculate d = e-1mod(p-1)(q-1)
### 5.You can bundle private key pair as (n,d)
### 6.You can bundle public key pair as (n,e)
### 7.Encrypt using public key and decrypt using private key.
