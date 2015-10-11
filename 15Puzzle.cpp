#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <cstdlib>

using namespace std;

const string SOLUTION = "010203040506070809101112131415SS";

struct Node{
	string state;
	string path;
};

bool goalTest(Node a){
	return (a.state.compare(SOLUTION)==0);
}

string swapNew(string state, unsigned int a, unsigned int b){
	string newState(state);
	string temp = newState.substr(a,2);
	newState[a] = newState[b];
	newState[a+1] = newState[b+1];
	newState[b] = temp[0];
	newState[b+1] = temp[1];
	return newState;
}

void generateSuccessors(Node curNode, vector<Node>& possible_paths){
	int loc = curNode.state.find("SS");
	// cout << "SS: " << loc << endl;
	if(loc > 7){ //can move up?e
		Node newNode;
		newNode.state = swapNew(curNode.state, loc, loc-8);
		newNode.path = curNode.path;
		newNode.path += 'u';
		possible_paths.push_back(newNode);
	}
	if (loc < 24){ //can move down?
		Node newNode;
		newNode.state = swapNew(curNode.state, loc, loc+8);
		newNode.path = curNode.path;
		newNode.path += 'd';
		possible_paths.push_back(newNode);
	}
	if (loc%8 < 6){ //can move right?
		Node newNode;
		newNode.state = swapNew(curNode.state, loc, loc+2);
		newNode.path = curNode.path;
		newNode.path += 'r';
		possible_paths.push_back(newNode);		
	}
	if (loc%8 > 1){ //can move left?
		Node newNode;
		newNode.state = swapNew(curNode.state, loc, loc-2);
		newNode.path = curNode.path;
		newNode.path += 'l';
		possible_paths.push_back(newNode);		
	}
}

Node bfs(Node startNode){
	queue<Node> frontier; //list for next nodes to expand
	frontier.push(startNode);
	map<string,int> expanded; //keeps track of nodes visited
	int numExpanded = 0;
	int maxFrontier = 0;
	while(!frontier.empty()){
		Node curNode = frontier.front();
		frontier.pop();
		numExpanded += 1;
		expanded[curNode.state] = 1;
		vector<Node> nextNodes;
		generateSuccessors(curNode,nextNodes);
		for(unsigned int i = 0; i < nextNodes.size(); i++){
			if (goalTest(nextNodes[i])){
				cout << "Expanded: " << numExpanded << " nodes" << endl;
				cout << "Max Frontier: " << maxFrontier << " nodes" << endl;
				cout << nextNodes[i].state << endl;
				return nextNodes[i];
			}
			if (expanded.find(nextNodes[i].state) != expanded.end()){
				continue;
			}
			frontier.push(nextNodes[i]);
			if(frontier.size() > maxFrontier){
				maxFrontier = frontier.size();
			}
		}
	}
}

Node dfs(Node startNode, int maxDepth = 80){
	stack<Node> frontier;
	frontier.push(startNode);
	map<string,int> expanded;
	int numExpanded = 0;
	int maxFrontier = 0;
	while(!frontier.empty()){
		Node curNode = frontier.top();
		frontier.pop();
		expanded[curNode.state] = curNode.path.length();
		numExpanded += 1;
		vector<Node> nextNodes;
		//cout << curNode.path << endl;
		generateSuccessors(curNode,nextNodes);
		for(unsigned int i = 0; i < nextNodes.size(); i++){
			if(nextNodes[i].path.length() > maxDepth){
				continue;
			}
			if (goalTest(nextNodes[i])){
				cout << "Expanded: " << numExpanded << " nodes" << endl;
				cout << "Max Frontier: " << maxFrontier << " nodes" << endl;
				return nextNodes[i];
			}
			if (expanded.find(nextNodes[i].state) != expanded.end() 
					&& expanded[nextNodes[i].state] < nextNodes[i].path.length()){
				continue;
			}
			frontier.push(nextNodes[i]);
			if(frontier.size() > maxFrontier){
				maxFrontier = frontier.size();
			}
		}
	}
	return startNode;
}

Node ittdfs(Node startNode){
	for(unsigned int i = 1; i < 80; i++){
		//cout << "current iteration: " << i << endl;
		Node solved = dfs(startNode, i);
		if(goalTest(solved)){
			//cout << "max depth: " << i << endl;
			return solved;
		}
	}
	return startNode;
}

int main(int argc, char* argv[]){
	Node startNode;
	startNode.state = "";
	if(argc < 3){
		cout << "Please enter the state of the puzzle using 2 digits for each position" 
			<< " and SS for the empty space" << endl;
		cout << "Example Usage: " << argv[0] << "010203040506070809101112131415SS" << endl;
		return 1;
	}
	int method = atoi(argv[1]);
	startNode.state = argv[2];
	if(startNode.state.length() != 32){
		cout << "Please enter the state of the puzzle using 2 digits for each position" 
			<< " and SS for the empty space" << endl;
		cout << "Example Usage: " << argv[0] << "010203040506070809101112131415SS" << endl;
		return 1;	
	}
	// vector<Node> test;
	// generateSuccessors(startNode,test);
	// for (int i = 0; i < test.size(); i++){
	// 	cout << test[i].state << " " << test[i].path << endl;
	int depth;
	Node solved;
	switch(method){
		case 1: //bfs
			cout << "BFS USED" << endl;
			solved = bfs(startNode);
			break;
		case 2: //dfs
			cout << "DFS USED" << endl;
			solved = dfs(startNode);
			break;
		case 3: //limited dfs
			cout << "depth limited DFS USED" << endl;
			if(argc < 4){
				cout << "Need a third parameter for maximum depth" << endl;
				return 1;
			}
			depth = atoi(argv[3]);
			solved = dfs(startNode,depth);
			break;
		case 4:
			cout << "ITTERATIVE DFS USED" << endl;
			solved = ittdfs(startNode); 
			break;
	}

	if (!goalTest(solved)){
		cout << "No solution found" << endl;
		return 1;
	}

	cout << "path to solution: " << solved.path << endl;
	return 0;
}