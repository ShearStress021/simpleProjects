#include <iostream>
#include <print>
#include <vector>
#include <map>

template<typename T>
class Graph{
	std::vector<std::vector<T>> adjMatrix{};

	public:
	explicit Graph(int n) {
		adjMatrix = std::vector<std::vector<T>>(n, std::vector<T>(n, 0));
	}


	void addEdge(int u, int v){
		adjMatrix[u][v] = 1;
		adjMatrix[v][u] = 2;
	}

	void printGraph(){
		int n = adjMatrix.size();

		for(size_t i{}; i < n; i++){
			for(size_t j{}; j < n; j++){
				std::print("{} ",adjMatrix[i][j]);
			}
			std::println();
		}
	}
};


template<typename T>
class Graph2{

	std::map<int,std::vector<T>> adjList{};

	public:
		void addEdge(int u, int v){
			adjList[u].push_back(v);
			adjList[v].push_back(u);
		}

		void printGraph(){
			for(auto& i: adjList){
				std::print("{}:", i.first);
				for(auto &j: i.second){
					std::print("{} ", j);
				}
				std::println();

			}

		}
};


unsigned int getString(const char *str){
	unsigned int n = 0;

	while(str[n] != '\0'){
		n++;
	}

	return n;
}

unsigned int stringlen(const char * str){
	unsigned int n;
	const char *p;

	for(p = str, n = 0; *p; p++, n++);
	return n;
}



int main(){

	// Matrix version
	Graph<int> graph{4};
	graph.addEdge(1,0);
	graph.addEdge(2,3);
	graph.addEdge(3,0);
	graph.addEdge(2,0);

	graph.printGraph();

	std::println();


	// adj List
	Graph2<int> gr{};
	gr.addEdge(1,0);
	gr.addEdge(2,3);
	gr.addEdge(3,0);
	gr.addEdge(2,0);

	gr.printGraph();


	std::println("Size {}", sizeof(unsigned int));


	std::println("string len {}", getString("kanja"));
//	std::println("string len {}", stringlen("kanja"));






}
