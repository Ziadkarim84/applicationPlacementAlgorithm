#include <bits/stdc++.h>
#include "shortestPath.h"
#include "generateSamples.h"
#include "pgsaa.h"

using namespace std;
int noOfScenario;
int noOfUser;
int noOfServer;
int timeSlots;

int main()
{

    vector<Sample> sample = multipleSamples();
    //printSample(sample);
    pgsaa(sample,1); //for first iteration
    pgsaa(sample,0); // for second iteration
    return 0;
}
