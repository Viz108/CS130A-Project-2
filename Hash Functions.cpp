#include <iostream>
#include <time.h>
#include <math.h>
#include <fstream>
#include <set>

using namespace std; 

//Global variables
int N = 2000000; //Size of universe
int m = 1000; //Size of table
int k = 100; //Number of hash functions    
int a = 500; //Number of inputs to test


int h1(int x, int s) //x is the value, s is the seed
{
    srand(x + s); 
    return rand() % m; 
}

int h2(int x, int p) //x is the value, p is the prime
{
    //NOTE: long long is used here to avoid overflow and wraparound in return calculation
    long long a = (((rand() % 10)*(pow(10,7)))+((rand() % 10)*(pow(10,6)))+((rand() % 10)*(pow(10,5)))+((rand() % 10)*(pow(10,4)))+((rand() % 10)*(pow(10,3)))+((rand() % 10)*(pow(10,2)))+((rand() % 10)*(pow(10,1)))+((rand() % 10)*(pow(10,0)))); 
    long long b = (((rand() % 10)*(pow(10,7)))+((rand() % 10)*(pow(10,6)))+((rand() % 10)*(pow(10,5)))+((rand() % 10)*(pow(10,4)))+((rand() % 10)*(pow(10,3)))+((rand() % 10)*(pow(10,2)))+((rand() % 10)*(pow(10,1)))+((rand() % 10)*(pow(10,0)))); 
    a = a % p; 
    b = b % p; 
    return (((a*x)+b) % p) % m; 
}



main()
{
    //Seed srand with current time for generating random values 
    srand(time(NULL)); 

    //Generate random inputs for testing
    //NOTE: due to limitations of rand(), max value will be around 32000 from just rand()
    int inputs[a]; 

    cout << "Select input data set (1 - fully random, 2 - first 500, 3 - odd only)" << endl; 
    int dataGenType; 
    cin >> dataGenType; 

    if(dataGenType == 1)
    {
        for(int i = 0; i < a; i++)
        {
            int newInput = (((rand() % 10)*(pow(10,7)))+((rand() % 10)*(pow(10,6)))+((rand() % 10)*(pow(10,5)))+((rand() % 10)*(pow(10,4)))+((rand() % 10)*(pow(10,3)))+((rand() % 10)*(pow(10,2)))+((rand() % 10)*(pow(10,1)))+((rand() % 10)*(pow(10,0)))); //Need to generate each digit randomly since rand caps at 32000
            newInput = newInput % N; 
            inputs[i] = newInput; 
        }
    }
    else if(dataGenType == 2)
    {
        for(int i = 0; i < a; i++)
        {
            inputs[i] = i; 
        }
    }
    else if(dataGenType == 3)
    {
        for(int i = 0; i < a; i++)
        {
            int newInput = (((rand() % 10)*(pow(10,7)))+((rand() % 10)*(pow(10,6)))+((rand() % 10)*(pow(10,5)))+((rand() % 10)*(pow(10,4)))+((rand() % 10)*(pow(10,3)))+((rand() % 10)*(pow(10,2)))+((rand() % 10)*(pow(10,1)))+((rand() % 10)*(pow(10,0)))); //Need to generate each digit randomly since rand caps at 32000
            newInput = newInput % N; 
            newInput = (2*newInput)+1; 
            inputs[i] = newInput; 
        }
    }

    

    //h1 setup
    //Generate k seeds for k functions
    int s[k]; //Seeds for h1
    for(int i = 0; i < k; i++)
    {
        s[i] = rand(); 
    }

    //h2 setup 
    //Pick a prime greater than N
    int primeSeed = rand(); 
    while(pow(2,primeSeed) < N + 1)
    {
        primeSeed = rand(); 
    }
    int p = pow(2,primeSeed) - 1;

    //Testing
    int testingFunction; 

    //Setup output
    ofstream output; 

    output.open("data" + to_string(time(NULL)) + ".csv"); 
    output << "input,"; 

    //Pick hash function to test

    cout << "Select hash function (1 or 2): " << endl; 
    cin >> testingFunction; 

    if(testingFunction == 1)
    {
        for(int i = 0; i < k; i++)
        {
            output << "h1_" << i << ","; 
        }
        output << endl; 

        //Generate k hash functions and hash the current value, output resulting indexes
        for(int i = 0; i < a; i++)
        {
            output << inputs[i] << ","; 

            int currHashes[k];
            for(int j = 0; j < k; j++)
            {
                currHashes[j] = h1(inputs[i], s[j]); 
            }

            for(int j = 0; j < k; j++)
            {
                output << currHashes[j] << ","; 
            }
            output << endl; 
        }
    }
    else if(testingFunction == 2)
    {
        for(int i = 0; i < k; i++)
        {
            output << "h2_" << i << ","; 
        }
        output << endl; 

        //Generate k hash functions and hash the current value, output resulting indexes
        for(int i = 0; i < a; i++)
        {
            output << inputs[i] << ","; 

            int currHashes[k];
            for(int j = 0; j < k; j++)
            {
                currHashes[j] = h2(inputs[i], p); 
            }

            for(int j = 0; j < k; j++)
            {
                output << currHashes[j] << ","; 
            }
            output << endl; 
        }
    }
    else
    {
        cout << "Invalid input" << endl; 
    }

}