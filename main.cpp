#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <algorithm>

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

        int a=0,b=0;
        double w=0.0;
        int count =0;
        while(count<m){
            std::getline(inFile,inLine);
            inFile >> a >> b >> w;
            agencyMatrix[a][b] = w;
            count++;
        }
        std::getline(inFile,inLine);
        inFile >> source >> dest;
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
    int minDist(std::vector<double> &dist, std::vector<bool> &visitedList){
        int min = INT_MAX;
        int index;

        for(int i=0;i<n;i++){
            if(visitedList[i] == false && dist[i]<=min){
                min = dist[i];
                index=i;
            }
        }
        return index;
    }

    /*void getPath(std::vector<int> &parent, int &j)
    {
        // Base Case : If j is source
        if (parent[j] == - 1)
            return;
        edgeList.emplace_back(std::make_tuple(parent[j],j));
        getPath(parent, parent[j]);
        //std::cout << j << " ";
    }*/

    void kSolution(std::vector<int> &parent, int j){
        while(j!=-1){
            path.emplace_back(parent[j]);
            //std::cout << j;
            j = parent[j];
        }
        std::cout << dest << std::endl;
        for(int i=0;i<path.size()-1;i++){
            std::cout << path[i] << std::endl;
        }
        //dijkstra(source,1);
        }



    double dijkstra(int src,int count=0){
        std::vector<double> dist(n);
        std::vector<int> parent(n);
        std::vector<bool>visited(n,false);
        parent[0] = -1;
        for(int i=0;i<n;i++){
            dist[i] = INT_MAX;
        }
        dist[src] = 0; //set distance of start node to 0
        for(int i =0; i<n-1;i++){ //find next closest node
            int nextNode = minDist(dist,visited);
            visited[nextNode] = true;
            for(int j=0;j<n;j++){ //update distances for next nodes
                if (!visited[j] && agencyMatrix[nextNode][j]!=0 && dist[nextNode] + agencyMatrix[nextNode][j] < dist[j]){
                    parent[j] = nextNode;
                    dist[j] = dist[nextNode] + agencyMatrix[nextNode][j];
                }
            }
        }
        //if(called==0)
            //getPath(parent,dist[dest]
            std::cout << "distance = " << dist[dest] << std::endl;
            kSolution(parent,dest);
        //..if(k>1 && called==0) {
         //   ..kSoultion(dist,parent);
        //}
        //k -= 1;

    }

public:
    int n,m; //num nodes, num edges
    int source,dest;
    int k = 1; //source dest kTimes
protected:
    std::vector<std::vector<double>> agencyMatrix;
    std::vector<int> visited;
    std::vector<int> path;

};


int main(int argc, char *argv[]) {
    ksp main;
    main.readData(argv[1]);
    main.dijkstra(main.source);


 //N = number of veriticies
 //M = number of edges

 //s = start node
 //d = destination node
 //k = number of paths to find


}