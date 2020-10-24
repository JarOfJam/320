#include <iostream>
#include <vector>
#include <queue>
#include <map>

enum color_t{BLACK = -1, GRAY = 0, WHITE = 1};

class Graph {
	private:
		std::map<int, std::vector<int>> vertices;
		std::vector<color_t> color;
		std::vector<int> distance;
		std::vector<int> parent;
		int numElems = 0;
		const bool directed;
		std::map<int, std::vector<int>> transpose;
		int numCycles;
		vector<vector<int>> cycles;
		vector<vector<int>> subGraphs;
	public:
		Graph(bool);
		bool addVertex(int);
		bool addEdge(int, int);
		void print();
		void printBfs(int);
		bool isDirected();
		void DFS(int);
		vector<int> getTranspose();
		bool isCyclic();
		bool isDAG();
};

Graph::Graph(bool a) {
	directed = a;
}

bool Graph::addVertex(int v) {
	bool dupcheck = false;
  	for(auto iterat = vertices.begin(); iterat != vertices.end(); iterat++) {
    		if(iterat->first == v) {
			dupcheck = true;
		}
  	}
  	if(dupcheck) {
    		std::cout << "Duplicate" << std::endl;
		return false;
  	}
  	else {
    		vertices[v] = std::vector<int>();
    		std::cout << "Added " << v << std::endl;
		numElems++;
		return true;
  	}
}

bool Graph::addEdge(int from, int to) {
  	bool edcheck = false;
  	for(auto iterat = vertices.begin(); iterat != vertices.end(); iterat++) {
    		if(iterat->first == from) {
      			for(auto iterat2 = iterat->second.begin(); iterat2 != iterat->second.end(); iterat2++) {
    				if(*iterat2 == to) {
					edcheck = true;
				}
      			}
    		}
  	}
  	if(!directed);
		for(auto iterat = vertices.begin(); iterat != vertices.end(); iterat++) {
    			if(iterat->first == to) {
      				for(auto iterat2 = iterat->second.begin(); iterat2 != iterat->second.end(); iterat2++) {
    					if(*iterat2 == from) {
						edcheck = true;
					}
      				}
    			}
  		}
	}
  	if(edcheck) {
    		std::cout<<"Preexisting" << std::endl;
    		return false;
  	}
  	else {
  		vertices[from].push_back(to);
    		vertices[to].push_back(from);
    		std::cout << "Edge from " << from << " to " << to << std::endl;
		return true;
  	}
}

void Graph::print() {
	std::cout<<"Adjacency List:" << std::endl;
  	for(auto iterat = vertices.begin(); iterat != vertices.end(); iterat++) {
    		std::cout << "For " << iterat->first << ":";
    		for(auto iterat2 = iterat->second.begin(); iterat2 != iterat->second.end(); iterat2++) {
      			std::cout << " " << *iterat2;
    		}
    		std::cout << std::endl;
  	}
}

void Graph::printBfs(int start) {
	std::map<int, std::vector<int>>::iterator iterat = vertices.find(start);
	if(iterat != vertices.end()) {
		color = std::vector<color_t>(numElems + 1, WHITE);
		distance = std::vector<int>(numElems + 1, -1);
		parent = std::vector<int>(numElems + 1, -1);
		std::queue<int> neighbors = std::queue<int>();
		color[start] = GRAY;
		distance[start] = 0;
		neighbors.push(start);
		while(!neighbors.empty()) {
			int u = neighbors.front();
			neighbors.pop();
			std::cout << "Dequeue: " << u << "    Distance: " << distance[u] << std::endl;
			for(int v : vertices[u]) {
				std::cout << v << std::endl;
				if(color[v] == WHITE) {
					color[v] = GRAY;
					distance[v] = distance[u] + 1;
					parent[v] = u;
					neighbors.push(v);
				}
			}
			color[u] = BLACK;
		}
		for(int i = 0; i < distance.size(); i++) {
			if(distance[i] != -1) {
				std::cout <<  "Distance to " << i << " is " << distance[i] << std::endl;
			}
		}
	}
	else {
		std::cout << "Not found" << std::endl;
	}
	std::cout << std::endl;
}

bool Graph::isDirected() {
	if(directed) {
		std::cout << "Graph is directed" << std::endl;
	}
	else {
		std::cout << "Graph is undirected" << std::endl;
	}
	return directed;
}

void DFS(int start) {
	if(vertices.find(start) != vertices.end()) {
		std::stack<int> s;
		vertices[start]->color = WHITE;
		vertices[start]->parent = NULL;
		vertices[start]->discovertime = vertices[start]->finishtime = 0;
	}
}

bool Graph::isDirected() {
	return directed;
}

bool Graph::isCyclic() {
	return numCycles > 0;
}

bool Graph::isDAG() {
	return directed && numCycles == 0;
}

int main() {
	Graph a;
  	int v;
  	int e;
  	std::cout << "Enter num of vertices: ";
  	std::cin >> v;
  	while(v < 0) {
    		std::cout << "Invalid, enter num of vertices: ";
    		std::cin >> v;
  	}
  	int vertex;
  	for(int i = 1; i <= v; i++) {
    		std::cout << "Enter vertice value: ";
    		std::cin >> vertex;
    		if(!a.addVertex(vertex)) {
			i--;
		}
  	}
  	std::cout << "Enter num of edges: ";
  	std::cin >> e;
  	while(e < 0 && e > (v/2)) {
    		std::cout << "Invalid, enter num of edges: ";
    		std::cin >> e;
  	}
  	int V1;
  	int V2;
  	for(int i = 1; i <= e; i++) {
    		std::cout << "Enter vertices to connect: ";
    		std::cin >> V1;
    		std::cin >> V2;
    		if(!a.addEdge(V1,V2)) {
			i--;
		}
  	}
	int i;
	std::cout << std::endl << "Enter num to BFS: ";
	std::cin >> i;
	a.printBfs(i);
  	a.print();
  	return 0;
}
