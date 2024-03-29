#include <iostream>
#include <time.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <random>

using namespace std; 

//Global variables
int N = pow(2,20); //Size of universe
const int k = 10; //Number of hash functions    
int n = 10000; //Number of entries
int c = 6; 
int s[k]; //Seeds for h1
int p; //prime for h2
long long a[k]; //as for h2
long long b[k]; //bs for h2
vector<int> addedValues; //Tracker for values added to bloom filter
int falsePositives; //Counter for false positives
mt19937 gen32; 


int h1(int x, int s, int m) //x is the value, s is the seed
{
    minstd_rand0 g1(x+s); 
    return g1(); 
    // srand(x + s); 
    // return rand() % m; 
}

int h2(int x, int s, int m) //x is the value, s is the seed
{
    int tempValue = (((a[s]*x)+b[s]) % p) % m; 
    if((((a[s]*x)+b[s]) % p) % m < 0)
    {
        tempValue *= -1; 
    }
    return tempValue; 
}

class bloomFilter1
{
    private: 
    

    public: 
    bloomFilter1(int n, int c); //n: number of items expected, c: factor for deciding table size, >1

    void add(int x); 
    bool contains(int x); 

    vector<int> hashTable; 
};

class bloomFilter2
{
    private: 
    vector<int> hashTable; 

    public: 
    bloomFilter2(int n, int c); //n: number of items expected, c: factor for deciding table size, >1

    void add(int x); 
    bool contains(int x); 
};

bloomFilter1::bloomFilter1(int n, int c)
{
    for(int i = 0; i < n*c; i++)
    {
        hashTable.push_back(0); 
    }
}

void bloomFilter1::add(int x)
{
    for(int i = 0; i < k; i++)
    {
        hashTable.at(h1(x, s[i], hashTable.size())) = 1;
    }
}

bool bloomFilter1::contains(int x)
{
    bool inFlag = true; 
    for(int i = 0; i < k; i++)
    {
        if(hashTable.at(h1(x, s[i], hashTable.size())) == 0)
        {
            inFlag = false; 
        }
    }
    return inFlag; 
}

bloomFilter2::bloomFilter2(int n, int c)
{
    for(int i = 0; i < n*c; i++)
    {
        hashTable.push_back(0); 
    }
}

void bloomFilter2::add(int x)
{
    for(int i = 0; i < k; i++)
    {
        hashTable.at(h2(x, i, hashTable.size())) = 1;
    }
}

bool bloomFilter2::contains(int x)
{
    bool inFlag = true; 
    for(int i = 0; i < k; i++)
    {
        if(hashTable.at(h2(x, i, hashTable.size())) != 1)
        {
            inFlag = false; 
        }
    }
    return inFlag; 
}

main()
{
    //Seed random number generator with current time for generating random values  
    
    gen32.discard(time(NULL)); 

    //h1 setup
    //Generate k seeds for k functions
    for(int i = 0; i < k; i++)
    {
        s[i] = gen32(); 
    }

    //h2 setup 
    //Pick a prime greater than N
    int primeSeed = gen32(); 
    while(pow(2,primeSeed) < N + 1)
    {
        primeSeed = gen32(); 
    }
    p = pow(2,primeSeed) - 1;

    //Generate a and b values
    for(int i = 0; i < k; i++)
    {
        int tempA = gen32();
        int tempB = gen32(); 
        a[i] = tempA % p; 
        b[i] = tempB % p; 
    }
    
    //Analyze False Positive Rates
    bloomFilter1 analysisFilter(n, c); //Switch between bloomFilter1 and bloomFilter2 to test different hash functions
    
    for(int i = 0; i < n; i++)
    {
        int newValue = gen32(); 
        analysisFilter.add(newValue); 
        addedValues.push_back(newValue); 
    }

    for(int i = 0; i < (5*n); i++)
    {
        int searchValue = gen32(); 

        if(analysisFilter.contains(searchValue))
        {
            bool valueAdded = false; 
            for(int i = 0; i < n; i++)
            {
                if(addedValues[i] == searchValue)
                {
                    valueAdded = true; 
                }
            }
            if(!valueAdded)
            {
                falsePositives++; 
            }
        }
    }

    cout << "False Positives: " << falsePositives << endl; 
    cout << "False Positive Rate: " << ((float)falsePositives / (float)(5*n)) << endl; 
    
    //Export hash table to csv
    // 
    //ofstream output; 
    // output.open("hash_table_" + to_string(time(NULL)) + ".csv"); 
    // for(int i = 0; i < analysisFilter.hashTable.size(); i++)
    // {
    //     output << analysisFilter.hashTable.at(i); 
    // }
    // output.close(); 
}