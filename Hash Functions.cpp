#include <iostream>
#include <time.h>
#include <math.h>
#include <fstream> 
#include <set> 

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
    srand(time(NULL));
    //generate data
    int k = 100; //Number of values
    int m = 200; //Size of hash table
    int data[k]; 
    // for(int i = 0; i < k; i++)
    // {
    //     data[i] = rand(); 
    // }
    //in order
    // for(int i = 0; i < k; i++)
    // {
    //     data[i] = i; 
    // }
    //only odd
    for(int i = 0; i < k; i++)
    {
        data[i] = (2*rand())+1; 
    }

    //hash function 1

    //initialize s values
    int seeds[k]; 
    for(int i = 0; i < k; i++)
    {
        seeds[i] = rand(); 
    }

    //hash values
    int h1Results[k]; 
    for(int i = 0; i < k; i++)
    {
        h1Results[i] = h1(seeds[i], data[i], m); 
    }


    //hash function 2

    //Choose prime
    int p = pow(2, rand()) - 1; 

    //hash values
    int h2Results[k]; 
    for(int i = 0; i < k; i++)
    {
        h2Results[i] = h2(p, data[i], m);
    }

    //Print results 
    // cout << "Results: " << endl; 
    // cout << "Input    h1    h2" << endl; 
    // for(int i = 0; i < k; i++)
    // {
    //     cout << data[i] << "    " << h1Results[i] << "    " << h2Results[i] << endl; 
    // }

    //Save to csv
    ofstream output; 

    output.open("data" + to_string(time(NULL)) + ".csv"); 
    output << "data, h1, h2" << endl; 
    for(int i = 0; i < k; i++)
    {
        output << data[i] << "," << h1Results[i] << "," << h2Results[i] << endl; 
    }
    output.close();

    //Check number of collisions
    int h1Collisions = 0; 
    int h2Collisions = 0; 
    set<int> alreadyVisitedh1;
    set<int> alreadyVisitedh2; 
    for(int i = 0; i < k; i++)
    {
        for(int j = i+1; j < k; j++)
        {
            if(alreadyVisitedh1.find(h1Results[i]) == alreadyVisitedh1.end())
            {
                if(h1Results[i] == h1Results[j])
                {
                    h1Collisions++; 
                }
            }
            if(alreadyVisitedh2.find(h2Results[i]) == alreadyVisitedh2.end())
            {
                if(h2Results[i] == h2Results[j])
                {
                    h2Collisions++; 
                }
            }
        }
        alreadyVisitedh1.emplace(h1Results[i]); 
        alreadyVisitedh2.emplace(h2Results[i]); 
    } 

    cout << "h1 Collisions: " << h1Collisions << endl; 
    cout << "h2 Collisions: " << h2Collisions << endl; 

}