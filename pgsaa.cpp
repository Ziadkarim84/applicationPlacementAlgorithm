#include "pgsaa.h"

int numberOfSamples = 1;
int id;
const int numberOfTimeSlots = 3;
const int totalNumberOfServers = 3;
int userAssignmentGraph[numberOfTimeSlots+1][totalNumberOfServers][totalNumberOfServers]; // (total time slot +1)* (total Number of servers) *total Number of servers . Change this number as necessary.
int relocationCost[totalNumberOfServers][totalNumberOfServers]; //Double check this value.There needs to be logic behind it.




void initializeUserAssignmentGraphWithDummyBigValue(){
  for(int i= 0; i< numberOfTimeSlots; i++){
    for(int j=0; j< totalNumberOfServers; j++){
      for(int k=0; k< totalNumberOfServers; k++){
         userAssignmentGraph[i][j][k] = 999999999;
      }

    }
  }
}

//implement euclidian distance (implemented)
int euclidianDist(int X1, int Y1, int X2, int Y2){
    int dist = (X1-X2)*(X1-X2) + (Y1-Y2)*(Y1-Y2);
    dist = sqrt(dist);

  return dist;
}


int manhattanDist(int X1, int Y1, int X2, int Y2){

  int Xdist = X1-X2 < 0 ? X2-X1 : X1-X2;
  int Ydist = Y1-Y2 < 0 ? Y2-Y1 : Y1-Y2;
  int dist = Xdist + Ydist;
  return dist;
}

//incomplete (completed)
int magicCost(int userToServerDistance, int userRequestSize, int relocationCost){
  int cost = relocationCost - (userRequestSize/userToServerDistance) ;
  return cost;
}

void setRelocationCost(vector<Server> server,User user) {
  for(int i = 0 ; i < totalNumberOfServers ; i++){
    for(int j = 0 ; j < totalNumberOfServers ; j++){
      relocationCost[i][j] = euclidianDist(user.X, user.Y, server[j].X, server[j].Y);
  }
}
}


void createUserAssignmentGraph(vector<Server> server, User user, int numberOfTimeSlots ){
    initializeUserAssignmentGraphWithDummyBigValue();
    setRelocationCost(server,user);
    for(int t= 1; t<numberOfTimeSlots; t++){
      for(int i=0; i< totalNumberOfServers ; i++) {
        for( int j=0; j< totalNumberOfServers ; j++){

          int userToServerDistance = euclidianDist(server[j].X, server[j].Y, user.X, user.Y);
          // it represents the connection cost between node (t,i) to (t-1,j)
          userAssignmentGraph[t][i][j] = magicCost( userToServerDistance, user.RequestSize ,relocationCost[i][j]);
        }
      }
    }

    //Assign the vlaue of the last time slot According to Figure 3 to zero.

     for(int i = 0 ; i < totalNumberOfServers ; i++){
        userAssignmentGraph[numberOfTimeSlots][0][i] = 0;
     }
}

//Need to modify input parameter, implement funciton body
int averageCostForAllScenarioForAServer(){

  return 0 ;
}


//change function parameters, implement body
//void GMAP();

int  G[50][50];
map<pair<int,int>, int> mp; //stores the id for the graph. You can get id from (t,i) where t reperesents time, and i represents node.
map< int, pair<int,int> > rmp;// Stores the reverse of rmp. You can get (t,i) from id;

void printUserAssignmentGraph(int totalNumberOfUsers, int numberOfScenario)
{
    for(int i = 0 ; i<numberOfTimeSlots ; i++){
        for(int j = 0 ; j<totalNumberOfServers ; j++){
            for(int k =0 ; k<totalNumberOfServers ; k++){
                cout << i << " " << j << " " << k << " : " << userAssignmentGraph[i][j][k] << endl;
            }

        }
    }

}
void printGeneratedGraph(){
    for(int i = 1 ; i< id+1  ; i++){
        for(int j=1 ; j < id+1 ; j++){
            if(G[i][j] == 999999999) cout << "-1 ";
            else cout << G[i][j] << " ";

        }
        cout << endl;
    }
}
int generateGraphforDijakstra(){

  //initialize with big value.
  for(int i=0; i < 50; i++){
      for(int j = 0 ; j < 50; j++) {
        G[i][j] = 999999999;
      }
   }

  // Set id for the vertexes to make it a planar graph.
  // We got rid of time by this way.
  id = 1;
  for(int i = 0 ; i< numberOfTimeSlots; i++){
    for (int j = 0 ; j< totalNumberOfServers ; j++ ) {
        mp[make_pair(i,j)] = id;
        rmp[id++] = make_pair(i,j);
    }
  }

  mp[make_pair(numberOfTimeSlots,0)] = id;
  rmp[id] = make_pair(numberOfTimeSlots,0);


  // Make the new G graph.
  for(int t= 1; t<=numberOfTimeSlots; t++){
      for(int i=0; i< totalNumberOfServers ; i++) {
        for( int j=0; j< totalNumberOfServers ; j++){

          int u = mp[make_pair(t,i)];
          int v = mp[make_pair(t-1,j)];
          int cost = userAssignmentGraph[t][i][j];
          G[u][v] = cost;
        }
      }
    }
    return id;
}

void firstIteration(vector <int> W_K,Sample sample){
    GMAP(W_K , sample);
}

void secondIteration(vector <int> Z_K){

}


//Pass Parameter as needed(passed)
void pgsaa(vector<Sample> sample,bool iteration){


    /**********duplicate variables declared , need to handle it later**************/
    int totalNumberOfUsers = 2;
    int numberOfScenario = 1;

  vector<Scenario> scenario;
  vector<User> user;
  vector <int> W_K;

    cout << "Total number of users: " << totalNumberOfUsers << endl;
  for(int k=0 ; k < numberOfSamples; k++) {
     for (int i = 0 ;i < totalNumberOfUsers; i++){
        vector <int> shortestPathsToServer[50];
        int D;
        for(int l = 0; l < numberOfScenario; l++){

            scenario = sample[k].scenario;
            user = scenario[l].user;
            createUserAssignmentGraph(sample[k].server, user[i], numberOfTimeSlots);

            D = generateGraphforDijakstra() ;

            cout << "User Assignment Graph " << endl;
            printUserAssignmentGraph(totalNumberOfUsers,numberOfScenario);
            cout << "Generated Graph " << endl;
            printGeneratedGraph();
            vector<int> dijkstraDistance = dijkstra(G, D);


            for(int s=1; s<D ; s++){
                 shortestPathsToServer[s].push_back(dijkstraDistance[s]);
            }

        }


        for(int m = 1; m<=totalNumberOfServers; m++){
            //Average Cost for all scenario for a particualar server
           // avergaecost = averageCostForAllScenarioForAServer();
             int sum = 0;
           for(int j=0 ; j<shortestPathsToServer[m].size() ; j++){
                sum += shortestPathsToServer[m][j];
           }
           int avg = sum/numberOfScenario;
           W_K.push_back(avg);

     }

     //Probably Need to calculate W_K(line 13) here.
     if(iteration){
        firstIteration(W_K, sample[k]);
     }
     else{
        vector<int>Z_K;
        secondIteration(Z_K);
     }
  }
  if(iteration){
   // generateLargeSample();
  }
  else{
    //zStar = objectiveValue
  }
  }
  cout << "done" << endl;
}

