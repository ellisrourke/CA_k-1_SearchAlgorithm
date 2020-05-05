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
        //outputMatrix();
        dijkstra(source);
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

    static void printPath(std::vector<int> &parent, int &j)
    {

        // Base Case : If j is source
        if (parent[j] == - 1)
            return;
        printPath(parent, parent[j]);

        std::cout << j;
    }

    int printSolution(std::vector<double> &dist, std::vector<int> &parent)
    {
        int src = source;
        printf("Vertex\t Distance\tPath\n");
        for (int i = dest; i <= dest; i++)
        {
            if(dist[i] == INT_MAX or dist[i] <0){
                std::cout << src << " -> "  << i << "\t " << "null\t\t";

            } else {
                std::cout << src << " -> "  << i <<  "\t " << dist[i] << "\t\t";
            }
            //printf("\n%d -> %d \t\t %d\t\t%d ",src, i, dist[i], src);
            //printPath(parent, i);
            std::cout << std::endl;

        }
    }

    void dijkstra(int src){
        std::vector<double>dist(n);
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
            //std::cout << nextNode <<std::endl;
            for(int j=0;j<n;j++){ //update distances for next nodes

                if (!visited[j] && agencyMatrix[nextNode][j]!=0 && dist[nextNode] + agencyMatrix[nextNode][j] < dist[j]){
                    parent[j] = nextNode;
                    dist[j] = dist[nextNode] + agencyMatrix[nextNode][j];
                }
            }
        }
        printSolution(dist,parent);


    }
protected:
    std::vector<std::vector<double>> agencyMatrix;
    std::vector<int> visited;
    int n,m; //num nodes, num edges
    int source,dest; //source dest
};


int main(int argc, char *argv[]) {
    ksp main;
    main.readData(argv[1]);


 //N = number of veriticies
 //M = number of edges

 //s = start node
 //d = destination node
 //k = number of paths to find


}