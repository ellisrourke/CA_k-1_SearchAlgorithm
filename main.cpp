#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <algorithm>
#include <float.h>
#include <ctime>

class ksp{
public:
    ksp(){}
    void readData(const std::string &fileName){
        std::ifstream inFile;
        inFile.open(fileName);

        if(!inFile.is_open()){ std::cerr << "file error" << std::endl; }

        std::string inLine;
        inFile >> n  >> m;
        agencyMatrix.resize(n);
        parent.resize(n);
        for (int i = 0; i < n; ++i){agencyMatrix[i].resize(n);}
        //std::cout << agencyMatrix[0][1];
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
        x = dest;
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
        int index=0;

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

    void kSolution() {
        //while(j!=-1){
        //path.emplace_back(parent[j]);
        //std::cout << j << std::endl;
        //    j = parent[j];
        //}
        double sol = INT_MAX;
        int a=0;
        int b=0;
        int temp=0;
        int minIndex = 0;
        double minValue = INT_MAX; 
        /*while(sol == INT_MAX){
            a = parent[x];
            b = parent[a];
            x = a;
            temp = agencyMatrix[b][a];
            agencyMatrix[b][a]  = 0;
            sol = dijkstra(source);
            agencyMatrix[b][a] = temp;
        }
*/
        std::cout << "---" << std::endl;
        std::cout << b << " " << a << " ";
        std::cout << agencyMatrix[b][a] << std::endl;
        std::cout << b << " " << a << " ";
        std::cout << agencyMatrix[b][a] << std::endl;
        std::cout << "---" << std::endl;


        parent.clear();
        }

    double dijkstra(int src){
        std::vector<double> dist(n);
        //std::cout << dist[dest] << "dM " << std::endl;
        //parent.clear();
        std::vector<bool>visited(n,false);
        parent[src] = -1;
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

        std::cout << "distance = " << std::fixed << dist[dest] << std::endl;

        return dist[dest];



    }

public:
    int n,m; //num nodes, num edges
    int source,dest;//source dest
    int x;
    int k = 5; // kTimes
    int current = 0; //current k value
protected:
    std::vector<std::vector<double>> agencyMatrix;
    std::vector<int> parent;

};


int main(int argc, char *argv[]) {
    srand(time(0));

    ksp main;
    main.readData(argv[1]);
    main.dijkstra(main.source);
    main.kSolution();
    main.dijkstra(main.source);







    //N = number of veriticies
 //M = number of edges

 //s = start node
 //d = destination node
 //k = number of paths to find


}