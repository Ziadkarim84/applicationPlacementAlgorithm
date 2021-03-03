#include<bits/stdc++.h>
#include "G-Map.h"
#include "generateSamples.h"

using namespace std;



//redeclaration (will be removed later)
const int totalNumberOfServers=3;
const int totalNumberOfUsers=2;
int sigma = 1; //coefficient constant
bool X[20][10];

void printX(){

    cout << endl << "Printing X" << endl;
    for(int i=0 ; i<totalNumberOfUsers ; i++){
        for(int j=0 ; j<totalNumberOfServers ; j++){
            cout << X[i][j] << " ";
        }
        cout << endl;
    }

}
int randomNumberGenerator(){
    return rand()%1000 + 1;
}

int formula1(int wk, User user){
    int phi;
    phi = wk /(sigma * user.energyRequiredForRequest);
    return phi;
}

int formula2(Server server,User user){
    int utilizedEnergy;
    utilizedEnergy = sigma * user.energyRequiredForRequest/server.computationalCapacityOfServer;
    return utilizedEnergy;
}

int argMax(int phi[]){
    int absPhi;
    int maxPhi=-1;
    for(int i=0 ; i<totalNumberOfUsers ; i++){
        absPhi = abs(phi[i]);
        maxPhi = absPhi > maxPhi ? absPhi : maxPhi;
    }
    return maxPhi;
}

void GMAP(vector <int> W_K,Sample sample){
    vector <User> user;
    vector<Server> server;
    user = sample.scenario[0].user;
    server = sample.server;
    while(user.size()){
            int phi[10];
            int J[10];
        for(int i = 0 ; i < totalNumberOfUsers ; i++){
            J[i] = -1; //what is J
            phi[i] = 0; //what is phi
            cout << "i: " << i << endl;
           for(int j = 0 ; j < totalNumberOfServers ; j++){
                //formula1 and formula2 replacement is needed
                cout << "j: " << j << endl;
                if( formula1(W_K[j],user[i]) > phi[i] && formula2(server[j],user[i]) < server[j].EnergyBudget){
                    J[i] = j;
                    phi[i] = formula1(W_K[j],user[i]);
                }

           }

        }

        int iCap = argMax(phi);
        int j = J[iCap];

        if(J[iCap] != -1){
            X[iCap][j]  = 1;
            server[j].EnergyBudget -= formula2(server[iCap], user[iCap]);
            if(server[j].EnergyBudget<=0){
                server.erase(server.begin()+j);
            }

        }
        user.erase(user.begin()+iCap);
    }


    printX();
}

