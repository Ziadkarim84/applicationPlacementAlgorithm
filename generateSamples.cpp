#include "generateSamples.h"


int locationLimit = 10;
int energyLimit = 10;
int totalNumberOfServers = 3;
int totalNumberOfUsers = 2;
int requestSizeLimit = 10;
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


vector<Server> generateServers(){
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

Scenario generateScenario(int numberOfUsers){

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

vector<Scenario> generateScenarios(int numberOfUsers, int numberOfScenario){

    vector<Scenario> setOfScenarios;
    Scenario newScenario = generateScenario(numberOfUsers);
    for(int i=0 ; i< numberOfScenario ; i++){
        setOfScenarios.push_back(newScenario);
    }

    return setOfScenarios;
}

Sample generateSample(){

    Sample newSample;
    newSample.server = generateServers();
    newSample.numberOfUsers = generateNumberOfUsers();
    newSample.scenario = generateScenarios(newSample.numberOfUsers, numberOfScenario);

    return newSample;
}


vector<Sample> multipleSamples(){
    int H = totalNumberOfSamples;
    int L = totalNumberOfScenarios;
    numberOfScenario = L;
    vector<Sample> sample;
    for(int i= 0; i<H;i++){
        sample.push_back(generateSample());

    }
    return sample;

}


//These function is for per timeslot

vector<User> randomizeUserlocation(vector<User> user){

    for(int i=0;i<user.size(); i++) {
        user[i].X = randomNumber(locationLimit);
        user[i].Y = randomNumber(locationLimit);
    }
    return user;
}

Sample randomizeUserlocationPerSample(Sample sample){
    for(int i=0; i<sample.scenario.size();i++){
        sample.scenario[i].user = randomizeUserlocation(sample.scenario[i].user);
    }
    return sample;
}

//These is a example function
void perTimeSlot(){
    //T is total number of time slots
    int T = 60;

    //This should be same as the populated graph input function mutipleSamples()
    vector<Sample> sample;

    //These two nested loops will randomize the user location per time slot.
    for(int i= 0;i <T; i++){
        for(int j=0; j< sample.size();j++){
            randomizeUserlocationPerSample(sample[j]);
        }
    }
}





