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

    /*void kSolution() {


        while(sol == INT_MAX){
            a = parent[x];
            b = parent[a];
            x = a;
            temp = agencyMatrix[b][a];
            agencyMatrix[b][a]  = 0;
            sol = dijkstra(source);
            agencyMatrix[b][a] = temp;
        }

        std::cout << "---" << std::endl;
        std::cout << b << " " << a << " ";
        std::cout << agencyMatrix[b][a] << std::endl;
        std::cout << b << " " << a << " ";
        std::cout << agencyMatrix[b][a] << std::endl;
        std::cout << "---" << std::endl;


        parent.clear();
        }
*/

    static void swap(double* x, double* y)
    {
        double temp = *x;
        *x = *y;
        *y = temp;
    }
    static int partition(std::vector<double> scores, int low, int high){
        int pivot = scores[high];
        int index = (low - 1);

        for(int i=low;i<=high;i++){
            if(scores[i] <= pivot){
                i++;
                swap(&scores[index],&scores[i]);
            }
        }
        swap(&scores[index+1],&scores[high]);
        return(index+1);
    }
    static void quickSort(std::vector<double> &scores, int low, int high){
        if(low<high){
            int pIndex = partition(scores,low,high);
            quickSort(scores,low,pIndex-1);
            quickSort(scores,pIndex+1,high);
        }
    }

    void runKdijkstra(){
        std::cout << " START " << std::endl;
        dijkstra(source,dest);
        for(int i=0;i<k-1;i++){
            int random = rand() % globalPath.size();
            //std::cout << random << " " << random+1 << std::endl;
            //std::cout << initialPath[i] << initialPath[i+1] << std::endl;
            //std::cout << agencyMatrix[initialPath[random+1]][initialPath[random]] << " " << std::endl;
            double temp = agencyMatrix[globalPath[random+1]][globalPath[random]];
            agencyMatrix[globalPath[random+1]][globalPath[random]] = 0;
            globalPath.clear();
            dijkstra(source,dest);
            agencyMatrix[globalPath[random+1]][globalPath[random]] = temp;
        }

        //quickSort(results,0,results.size());
        for(int j=0;j<results.size();j++){
            std::cout << "k=" << j+1 << " "<< std::fixed << results[j] << std::endl;
        }
    }

    void dijkstra(int src,int destination){
        std::vector<double> dist(n);
        parent.clear();
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

        //std::cout << "distance = " << std::fixed << dist[destination] << std::endl;
        int j = dest;
        //std::vector<int> path;
        globalPath.push_back(destination);
        while(j!=-1){
            globalPath.emplace_back(parent[j]);
            //std::cout << j << std::endl;
            j = parent[j];
        }
        /*for(int i=0;i<path.size();i++){
            std::cout << path[i] <<  " " << std::endl;
        }*/
        results.push_back(dist[destination]);
        //return path;
    }

public:
    int n,m; //num nodes, num edges
    int source,dest;//source dest
    int x;
    int k = 10; // kTimes
    int current = 0; //current k value
    std::vector<std::vector<double>> agencyMatrix;

protected:
    std::vector<int> parent;
    std::vector<int> globalPath;
    std::vector<double> results;

};


int main(int argc, char *argv[]) {
    srand(time(0));

    ksp main;
    main.readData(argv[1]);
    main.runKdijkstra();

    //std::vector<int> initialPath = main.dijkstra(3,2);







    //N = number of veriticies
 //M = number of edges

 //s = start node
 //d = destination node
 //k = number of paths to find


}