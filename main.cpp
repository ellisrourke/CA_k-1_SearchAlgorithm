#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cfloat>
#include <ctime>

class ksp {
public:
    ksp() {}
    void readData(const std::string & fileName) {
        std::cout << "Reading input data..." << std::endl;
        std::ifstream inFile;

        //Open inpit file and verify it opened correctly
        inFile.open(fileName);
        if (!inFile.is_open()) {
            std::cerr << "file error" << std::endl;
        }

        std::string inLine;
        inFile >> n >> m; //retrieve the number of nodes and edges from the file
        agecencyMatrix.resize(n);//resize the matrix to accommodate the number of nodes in the input file
        parent.resize(n);//resize the parent node array to accommodate the number of nodes in the input file
        for (int i = 0; i < n; ++i) {
            agecencyMatrix[i].resize(n); //resize each row in the matrix to accommodate the number of nodes in the input file
        }

        //a = edges first node, b = edges second node
        //w = edge weight

        //for each of the edges in the input file
        //retrieve the indexes and the weight and update the adjacency matrix accordingly
        int a = 0, b = 0;
        double w = 0.0;
        int count = 0;
        while (count < m) {
            std::getline(inFile, inLine);
            inFile >> a >> b >> w;
            agecencyMatrix[a][b] = w;
            count++;
        }

        //retrieve the source and destination nodes along with the k number of paths to find
        std::getline(inFile, inLine);
        inFile >> source >> dest >> k;
        std::cout << "finding paths from " << source << " to " << dest << " for k = " << k << std::endl << std::endl;
        x = dest;
    }

    //find the minimum value in the list of distances that has also not been
    //marked as visited in the visitedList  --(supporting function for Dijkstra implementation)--
    int minDist(std::vector < double > & dist, std::vector < bool > & visitedList) {
        int min = INT_MAX;
        int index = 0;

        for (int i = 0; i < n; i++) {
            if (visitedList[i] == false && dist[i] <= min) {
                min = dist[i];
                index = i;
            }
        }
        return index;
    }

    //run dijkstra for k iterations, removing a edge from the path each time to allow Dijkstra's algorithm to find a new path
    void runKdijkstra() {
        dijkstra(source, dest);//run initial pass of Dijkstra algorithm
        for (int i = 0; i < k - 1; i++) {
            int random = rand() % globalPath.size();
            double temp = agecencyMatrix[globalPath[random + 1]][globalPath[random]];
            agecencyMatrix[globalPath[random + 1]][globalPath[random]] = 0;
            globalPath.clear();
            dijkstra(source, dest);
            agecencyMatrix[globalPath[random + 1]][globalPath[random]] = temp;
        }

        std::cout << "Approximate k shortest paths: " << std::endl;
        for (int j = 0; j < results.size(); j++) {
            std::cout << std::fixed << results[j] << std::endl;
        }
    }

    //generic dijkstra's shortest path implementation
    //given a source and destination node, find the sh
    void dijkstra(int src, int destination) {
        std::vector < double > dist(n); //store distances to each node
        parent.clear(); //clear parents from previous dijkstra run
        std::vector < bool > visited(n, false); //initialise visited status for each node to false
        parent[src] = -1;
        for (int i = 0; i < n; i++) {
            dist[i] = INT_MAX; //initialise each distance to max int value
        }
        dist[src] = 0; //set distance of start node to 0
        for (int i = 0; i < n - 1; i++) {
            int nextNode = minDist(dist, visited); //find next closest node and set as visited
            visited[nextNode] = true;
            for (int j = 0; j < n; j++) { //update distances for next nodes
                //   node has not been visited + weight of edge not blank + the distance to the node is less than the previously recorded value for the node
                if (!visited[j] && agecencyMatrix[nextNode][j] != 0 && dist[nextNode] + agecencyMatrix[nextNode][j] < dist[j]) {
                    parent[j] = nextNode;
                    dist[j] = dist[nextNode] + agecencyMatrix[nextNode][j];
                }
            }
        }

        int j = dest;
        globalPath.push_back(destination);
        while (j != -1) {
            globalPath.emplace_back(parent[j]); //go backwards throught the links to calculate the path
            j = parent[j];
        }

        if (dist[destination] != INT_MAX) { //ensure a solution was found before adding to the list of solutions
            results.push_back(dist[destination]);
        } else {
            k += 1; //if solution not found, increase k to allow algorithm to run again
        }

    }

public:
    int n, m; //num nodes, num edges
    int source, dest; //source dest
    int x = 0;
    int k = 0; // kTimes
    int current = 0; //current k value
    std::vector < std::vector < double >> agecencyMatrix;

protected:
    std::vector < int > parent; //list of parents for each node
    std::vector < int > globalPath; //list recording the path found
    std::vector < double > results; //list of valid solutions found

};

int main(int argc, char * argv[]) {
    srand(time(0));
    ksp main;
    main.readData(argv[1]);
    main.runKdijkstra();

}