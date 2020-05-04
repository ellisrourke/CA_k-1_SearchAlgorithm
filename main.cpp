#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>

class ksp{
public:
    void readData(const std::string &fileName){
        std::ifstream inFile;
        inFile.open(fileName);

        if(!inFile.is_open()){ std::cerr << "file error" << std::endl; }

        std::string inLine;
        inFile >> n  >> m;
        agencyMatrix.resize(n);
        for (int i = 0; i < n; ++i){agencyMatrix[i].resize(n);}



        int a,b;
        double w;
        while(std::getline(inFile,inLine)) {
            inFile >> a >> b >> w;
            agencyMatrix[a][b] = w;
        }

        //outputMatrix();
    }
    void outputMatrix(){
        std::cout << "  ";
        for(int i=0;i<n;i++){std::cout << i << " ";}
        std::cout << std::endl;
        for (int i = 0; i < n; i++) {
            std::cout << i << '|';
            for (int j = 0; j < n; j++){
                std::cout<< agencyMatrix[i][j]<< " ";
            }
            std::cout<< std::endl;
        }
    }


    int minDist(std::vector<int> dist, std::vector<bool> visited){
        int min = INT_MAX;
        int index;

        for(int i=0;i<n;i++){
            if(visited[i] == false && dist[i]<=min){
                min = dist[i];
                index=i;
            }
        }
        return index;
    }

    void dijkstra(int src){
        std::vector<int>dist(n);
        std::vector<bool>visited(5,false);
        for(int i=0;i<n;i++){

            dist[i] = INT_MAX;
            //visited[i] = false; //done above
        }
        dist[src] = 0; //set distance of start node to 0

        for(int i =0; i<n;i++){ //find next closest node
            int nextNode = minDist(dist,visited);
            visited[nextNode] = true;
            std::cout << nextNode <<std::endl;
            for(int j=0;j<n;j++){ //update distances for next nodes
                if(!visited[i] && agencyMatrix[nextNode][i] && dist[nextNode]!=INT_MAX && dist[nextNode]+agencyMatrix[nextNode][i]<dist[i]) {
                    dist[i] = dist[nextNode] + agencyMatrix[nextNode][i];
                }
            }
        }

        for(int i =0;i<dist.size();i++){
            std::cout << dist[i] << std::endl;
        }



    }
protected:
    std::vector<std::vector<int>> agencyMatrix;
    std::vector<int> visited;
    int n,m;
};


int main(int argc, char *argv[]) {
    ksp main;
    main.readData(argv[1]);
    main.dijkstra(0);

 //N = number of veriticies
 //M = number of edges

 //s = start node
 //d = destination node
 //k = number of paths to find


}