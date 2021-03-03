#include "generateSamples.h"

int totalNumberOfServers = 3;
int totalNumberOfUsers = 2;
int numberOfScenario = 1;
int totalNumberOfSamples = 1;
int totalNumberOfScenarios= 1;



void printSample(vector <Sample> sample){

    for(int s = 0 ; s<totalNumberOfSamples ; s++){
        vector<Server> server;
        vector<Scenario> scenario;
        server = sample[s].server;
        scenario = sample[s].scenario;

        cout << endl <<  "**************************************" << endl;

        cout << "SampleNo " << s << endl;

        cout << "Number of Servers : " << server.size() << endl;
        int numberOfUsers = sample[s].numberOfUsers;
        cout << "Number of Users : " << numberOfUsers << endl << endl;


        for(int i=0 ;  i< totalNumberOfServers ; i++){
            cout << "sever " << i << ": " << endl;
            cout << "    location : " <<  server[i].X << "," << server[i].Y << endl;
            cout << "    energyBudget :" << server[i].EnergyBudget << endl;
        }

        for(int i=0 ; i< numberOfScenario ; i++){
            vector<User> user;
            user = scenario[i].user;
            cout << "Scenario " << i << endl;
            for(int j=0 ; j< numberOfUsers ; j++){
                cout << "    User " << j << ": " << endl;
                cout << "      location : " <<  user[j].X << "," << user[j].Y << endl;
                cout << "      requestSize :" << user[j].RequestSize << endl;
            }
        }
    }
}


int randomNumber(int n){
    return (rand()%n)+1;
}


vector<Server> generateServers(int locationLimit, int energyLimit){
    //int numberOfServers = randomNumber(totalNumberOfServers);

    vector<Server> setOfServers;

    for(int i = 0; i<totalNumberOfServers; i++){
        Server newServer;
        newServer.X = randomNumber(locationLimit);
        newServer.Y = randomNumber(locationLimit);
        newServer.EnergyBudget = randomNumber(energyLimit);
        newServer.computationalCapacityOfServer = 1; //check Later
        setOfServers.push_back(newServer);
    }

    return setOfServers;
}


int generateNumberOfUsers(){
    //return randomNumber(totalNumberOfUsers);
    return totalNumberOfUsers;
}

Scenario generateScenario(int numberOfUsers,int locationLimit, int requestSizeLimit ){

    Scenario newScenario;

    for(int i=0; i<numberOfUsers; i++){
        User newUser;
        newUser.X = randomNumber(locationLimit);
        newUser.Y = randomNumber(locationLimit);
        newUser.RequestSize = randomNumber(requestSizeLimit);
        newUser.energyRequiredForRequest = 1; //check again
        newScenario.user.push_back(newUser);
    }
    return newScenario;
}

vector<Scenario> generateScenarios(int numberOfUsers, int numberOfScenario,int locationLimit, int requestSizeLimit){

    vector<Scenario> setOfScenarios;
    Scenario newScenario = generateScenario(numberOfUsers,locationLimit, requestSizeLimit);
    for(int i=0 ; i< numberOfScenario ; i++){
        setOfScenarios.push_back(newScenario);
    }

    return setOfScenarios;
}

Sample generateSample(int locationLimit,int energyLimit, int requestSizeLimit){

    Sample newSample;
    newSample.server = generateServers(locationLimit,energyLimit);
    newSample.numberOfUsers = generateNumberOfUsers();
    newSample.scenario = generateScenarios(newSample.numberOfUsers, numberOfScenario,locationLimit,requestSizeLimit);

    return newSample;
}


vector<Sample> multipleSamples(){
    int locationLimit = 10;
    int energyLimit = 10;
    int requestSizeLimit = 10;
    int H = totalNumberOfSamples;
    int L = totalNumberOfScenarios;
    numberOfScenario = L;
    vector<Sample> sample;
    for(int i= 0; i<H;i++){
        sample.push_back(generateSample(locationLimit,energyLimit,requestSizeLimit));
    }
    perTimeSlot(sample,locationLimit,energyLimit,requestSizeLimit);
    return sample;

}


//These function is for per timeslot

vector<User> randomizeUserlocation(vector<User> user, int locationLimit){

    for(int i=0;i<user.size(); i++) {
        user[i].X = randomNumber(locationLimit);
        user[i].Y = randomNumber(locationLimit);
    }
    return user;
}

Sample randomizeUserlocationPerSample(Sample sample, int locationLimit){
    for(int i=0; i<sample.scenario.size();i++){
        sample.scenario[i].user = randomizeUserlocation(sample.scenario[i].user, locationLimit);
    }
    return sample;
}

//These is a example function
void perTimeSlot(vector <Sample> sample, int locationLimit, int energyLimit, int requestSizeLimit){
    //T is total number of time slots
    int T = 60;

    //These two nested loops will randomize the user location per time slot.
    for(int i= 0;i <T; i++){
        for(int j=0; j< sample.size();j++){
            randomizeUserlocationPerSample(sample[j],locationLimit);
        }
    }
}





