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

