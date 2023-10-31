# NYCU_Introduction_to_Cryptography_Fall

## HW2
**DES Programming**

This part is to implement DES core function, which encrypts a 64-bit plaintext to a 64-bit ciphertext with 
a 64-bit key (with parity bits).
1. Input format: the input is an ordered pair of keys and plaintexts in ASCII characters, such as, ‘a’ 
= 01100001 (Bit) = 61 (Hex)
2. Output format: 16 hex characters, such as AE184796707E59FB.
3. You can use the following key-plaintext-ciphertext tuple as a test sample for correctness: 
“security”, “Hi Mary!” and “303B1E1CBA103695”.
4. Use C or C++ to write your code.
5. Submission to E3 with two files.
a. The source code file with name: des.cpp or des.c.
b. The output file “des-out.txt” that contains 5 lines of plaintexts (in ASCII) for the ordered pairs 
of key and ciphertext (one pair per line) from the file “DES-Key-Ciphertext.txt”.

**Use Crypto++ for AES**

This part is to use the crypto library “Crypto++” to encode messages in various encryption and padding 
modes. The purpose is to get familiar with AES function calls and parameter setting. Please find the 
related library and programming environment (e.g. Visual Studio) information on the Internet.

1. Encrypt the following 36-byte message (in ASCII, quotes are not included.) 

“AES is the US block cipher standard.”
by the key “keyis84932731830” (ASCII) and the following specifications.
Mode Initial Vector (IV) Output form Padding method
CFB
(block size = 4 bytes)
0000 0000 0000 0000 (ASCII) Hex no padding
CBC 0000 0000 0000 0000 (ASCII) Hex Zeros Padding
CBC 9999 9999 9999 9999 (ASCII) Hex PKCS#7
ECB - Hex PKCS#7

2. Test data: Plaintext = “Hello World!” (ASCII) and key=“1234567890ABCDEF” (ASCII) .

A. CFB, IV=0000 0000 0000 0000, block size=4 bytes → 36 db 74 5b 3b 6d a6 9a bf 5f eb 23
B. CBC, IV=0000 0000 0000 0000, Zeros Padding
→ 4c 85 5d 63 17 60 8f 8d d3 94 61 e5 bc c9 40 b8
C. ECB, PKCS padding → d5 23 32 6c 27 ee 0f 21 65 c7 69 6b 36 f2 68 8e

## HW3
**RSA encoding and decoding**
This programming problem is to practice RSA encoding and decoding using Crypto++. We only deal with one-block 
operation. You need to check whether the message length (in bits) is strictly shorter modulus n’s length.
I. Read in the key length in decimal, a public key (e, n) in Hex and a message in ASCII and do encryption as 
described in the following table. The first row is for testing and the rest is the problem. 
The ASCII message is treated as an integer, for example, “Hi” = “4869” (Hex) = 18537 (decimal). Since we 
are dealing with very long integer, use “Integer” class for integer operations.



| Key length (decimal) |                         Public key=(e, n) (Hex)                          | Message (ASCII)    | Ciphertext (Hex) |
|:--------------------:|:------------------------------------------------------------------------:| ------------------ | ----------------:|
|          64          |                          (11, c963f963d93559ff)                          | ElGamal            | 6672e7d4a8786631 |
|         128          |                  (11, 04823f9fe38141d93f1244be161b20f)                   | Hello World!       |                ? |
|         256          | (10001,9711ea5183d50d6a91114f1d7574cd52621b35499b4d3563ec95406a994099c9) | RSA is public key. |                ? |
          

II. Read in key length in decimal, e and n in Hex and a ciphertext in Hex. Try to find the correct private key d by 
searching thru possible keys as specified. Then, use the private to decrypt the ciphertext to a meaningful message.



| Key length (decimal) |        Public key=(e, n) (Hex)         | Ciphertext (Hex)                  |                 Private key (Hex) | Message (ASCII) |
|:--------------------:|:--------------------------------------:| --------------------------------- | ---------------------------------:|:---------------:|
|          64          |          11, c45350fa19fa8d93          | ElGamal                           |                  6672e7d4a8786631 |     secrecy     |
|         128          | 1d35, c4b361851de35f080d3ca7352cbf372d | a02d51d0e87efe1de fc19f3ee899c31d | 53a0a95b089cf23adb5cc73f07XXXXX ? |        ?        |

## HW4
**Mining**

Find a blockchain of hash values of leading zeros from 0 to 7 or 8

(b) If you exhaust all possible nonces (2^32) and cannot find a hash value of 8 leading zeros from the previous hash value of 7 leading zeros, you need to find another hash value of 7 leading zeros and search nonces  again.
