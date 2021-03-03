#ifndef GENERATESAMPLES_H
#define GENERATESAMPLES_H
#include <bits/stdc++.h>
using namespace std;

struct User{
    int X;
    int Y;
    int RequestSize;
    int energyRequiredForRequest;
};

struct Server{
    int X;
    int Y;
    int EnergyBudget;
    int computationalCapacityOfServer;
};

struct Scenario{
    vector<User> user;
};

struct Sample{
    vector<Server> server;
    int numberOfUsers;
    vector<Scenario> scenario;
};

void perTimeSlot(vector <Sample> sample,int locationLimit, int energyLimit, int requestSizeLimit);
vector<Sample> multipleSamples();
void printSample(vector <Sample> sample);


#endif // GENERATESAMPLES_H
