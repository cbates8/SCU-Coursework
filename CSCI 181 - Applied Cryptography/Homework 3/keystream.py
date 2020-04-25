'''
CSCI 181 Homework 3
Author: Casey Bates
keystream.py - Generating keystreams to be used with the RC4 stream cipher
'''

''' Functions '''
def DecimalToBinary(number, n):
#Takes a decimal number and converts it to binary representation n bits long
    binary = []

    for i in range(0, n):
        binary.insert(0, int(number % 2)) #stores 0 or 1 in the most significant bit of the array
        number /= 2
    return binary;

def ConvertBitArraytoInt(k, n):
#Take an array of bits (binary) and converts it to an array of decimal integers
    integers = []

    #Filling the array with 0s
    for f in range(0, int(len(k)/n)):
        integers.append(0)

    #This nested for-loop effectively splits the key array into partitions of n bits. Then it converts those partitions from binary to decimal and stores the value into the integers array
    #e.g. k = [101] -> integers = [2^2 + 0 + 2^0] = [4 + 1] = [5]
    for i in range(0, int(len(k)/n)):
        for j in range(0, n):
            integers[i] += k[(i*n) + j] * pow(2, n-j-1)

    return integers

def InitS(n, key):
#Initializing and permuting the S array to be used in keystream generation
#Formula given in lecture notes
    S = []
    T = []
    j = 0

    #Filling S and T
    for i in range(0, pow(2, n)):
        S.append(i)
        T.append(key[i % len(key)])

    #Permutation of S based on the given key (stored in T)
    for i in range(0, pow(2, n)):
        j = (j + S[i] + T[i] )% pow(2, n)

        #Swapping S[i] and S[j]
        temp = S[i]
        S[i] = S[j]
        S[j] = temp

    return S


def KeystreamGen(n, l, key):
#Generating a RC4 keystream using a given keyword
#Formula given in lecture notes
    keystream = []
    K = ConvertBitArraytoInt(key, n)
    S = InitS(n, K)
    i = 0
    j = 0

    for count in range(0, l):
        i = (i + 1) % pow(2, n)
        j = (j + S[i]) % pow(2, n)

        #Swapping S[i] and S[j]
        temp = S[i]
        S[i] = S[j]
        S[j] = temp

        t = (S[i] + S[j]) % pow(2, n)
        keystream.extend(DecimalToBinary(S[t], n)) #Appending the binary array to the end of the keystream array

    return keystream



''' Main '''
#Testing fucntions with values from lecture notes:
#print(DecimalToBinary(100, 8))
#print(ConvertBitArraytoInt([1,0,0,0,0,0,1,1,1,0,0,1], 3))
#print(KeystreamGen(3, 4, [0,1,1,0,0,1,1,0,0,0,0,1,1,0,1]))

#Part B - Checking hw qestion 1:
#print(KeystreamGen(3, 7, [0,0,1,0,1,0,0,1,1,1,1,0]))

#Part C
print(KeystreamGen(8, 24, [1, 0, 1, 1, 1, 0, 0, 1 , 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1]))
