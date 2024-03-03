#include <iostream>
#include <math.h>

using namespace std; 

int h1(int s, int x, int m)
{
    //s is the randomly generated seed
    //x is the key to be hashed

    srand(s + x); 
    return rand() % (m); 
}

int h2(int p, int x, int m)
{
    //p is the random prime
    //x is the key to be hashed

    int a = rand() % (p-1) + 1; 
    int b = rand() % (p-1) + 1; 
    return ((a*x + b) % p) % m; 
}

main()
{
//Bloom Filter

    int numElements = 10;
    int tableSize = 200;
    int numHashes = (tableSize/numElements)*(0.693147); 

    int hashTable1[tableSize];
    int hashTable2[tableSize]; 
    for(int i = 0; i < tableSize; i++)
    {
        hashTable1[i] = 0; 
        hashTable2[i] = 0;
    }

    int inputs[numElements]; 
    for(int i = 0; i < numElements; i++)
    {
        inputs[i] = rand(); 
    }

    //h1 setup
    int h1Seeds[numHashes]; 
    for(int i = 0; i < numHashes; i++)
    {
        h1Seeds[i] = rand();
    }

    //h2 setup
    int prime = pow(2, rand()) - 1;

    //hashing and inserting
    for(int i = 0; i < numElements; i++)
    {
        for(int j = 0; j < numHashes; j++)
        {
            hashTable1[h1(h1Seeds[j], inputs[i], tableSize)] = 1; 
            hashTable2[h2(prime, inputs[i], tableSize)] = 1; 
        }
    }

    for(int i = 0; i < tableSize; i++)
    {
        cout << hashTable1[i]; 
    }
}

