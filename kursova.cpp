#include <iostream>
#include <locale>
#include <fstream>
#include <string>
#include <ctime>
#include "list.h"
#include "binaryTree.h"
#include "vector.h"
#include "graph.h"
#include "windows.h"

int main()
{
    Graph g;
    std::ifstream fileGraph, fileButton,fileDelete;
    std::string path = "graph.txt";
    fileGraph.open(path);
    int amount;
    fileGraph >> amount;
    for (int i = 1; i <= amount; i++) {
        Vertex v(i);
        g.addVertex(v);
    }
    while (!fileGraph.eof()) {
        int fromVertex, toVertex, weight, chance;
        fileGraph >> fromVertex;
        fileGraph >> toVertex;
        fileGraph >> weight;
        fileGraph >> chance;
        g.addEdges(fromVertex, toVertex, weight, chance);
    }
    fileGraph.close();
    path = "button.txt";
    fileButton.open(path);
    list<list<int>> buttons;
    binaryTree end;
    while (!fileButton.eof()) {
        int current;
        fileButton >> current;
        if (current == 0) {
            buttons.push_back(end.convertToList());
            continue;
        }
        end.insert(current);
    }
    fileButton.close();
    srand(time(NULL));
    list<int> selectedEnd = buttons[rand() % buttons.size()];
    std::cout << "Graph: " << std::endl;
    g.print();
    std::cout << "Opened vertexes: ";
    for (int i = 0; i != selectedEnd.size(); i++) {
        std::cout << selectedEnd[i] << ' ';
    }
    std::cout << std::endl;

    for (int end = 0; end != selectedEnd.size(); end++) {
        g.dfs(1, selectedEnd[end]);
        std::cout << "DFS to " << selectedEnd[end] << std::endl;
        list<list<int>> pathh = g.returnPath();
        for (int i = 0; i != pathh.size(); i++) {
            for (int j = 0; j != pathh[i].size(); j++) {
                std::cout << " -> " << "(" << pathh[i][j] << ")";
            }
            std::cout << std::endl;
        }
        g.clearAllPath();
    }

    for (int end = 0; end != selectedEnd.size(); end++) {
        std::cout << "BFS to " << selectedEnd[end] << std::endl;
        list<list<int>> resultt = g.bfs(1, selectedEnd[end]);
        for (int i = 0; i != resultt.size(); i++) {
            for (int j = 0; j != resultt[i].size(); j++) {
                std::cout << " -> " << "(" << resultt[i][j] << ")";
            }
            std::cout << std::endl;
        }
    }

    std::cout << "Dijkstra:" << std::endl;
    int* dijkstra = g.dijkstra(1);
    list<int> resultik = g.prev();
    for (int i = 0; i != amount; i++) {
        for (int j = 0; j != selectedEnd.size(); j++) {
            if (selectedEnd[j] == i + 1) {
                std::cout << "from " << 1 << " to " << i + 1 << " - " << dijkstra[i] << std::endl;
            }
        }
        
    }

    for (int end = 0; end != selectedEnd.size(); end++) {
        std::cout << "Shortest path to " << selectedEnd[end] << std::endl;
        list<int> shortest = g.dijkstraPath(selectedEnd[end]);
        for (int i = 0; i != shortest.size(); i++) {
            std::cout << shortest[i] << ' ';
        }
        std::cout << std::endl;
        std::cout << "Chance: " << g.chance(shortest) << std::endl;
    }
    path = "delete.txt";
    list<list<int>> toDelete;
    list<int> vertexes;
    fileDelete.open(path);
    while (!fileDelete.eof()) {
        int current;
        fileDelete >> current;
        if (current == 0) {
            toDelete.push_back(vertexes);
            vertexes.clear();
            continue;
        }
        vertexes.push_back(current);
    }
    fileDelete.close();
    for (int i = 0; i != toDelete.size(); i++) {
        std::cout << "Deleted edges: " << toDelete[i][0] << " --> " << toDelete[i][1]<<std::endl;
        g.deleteEdge(toDelete[i][0], toDelete[i][1]);
    }
    std::cout << "Graph: " << std::endl;
    g.print();
    std::cout << "Opened vertexes: ";
    for (int i = 0; i != selectedEnd.size(); i++) {
        std::cout << selectedEnd[i] << ' ';
    }
    std::cout << std::endl;

    for (int end = 0; end != selectedEnd.size(); end++) {
        g.dfs(1, selectedEnd[end]);
        std::cout << "DFS to " << selectedEnd[end] << std::endl;
        list<list<int>> pathh = g.returnPath();
        for (int i = 0; i != pathh.size(); i++) {
            for (int j = 0; j != pathh[i].size(); j++) {
                std::cout << pathh[i][j]<<' ';
            }
            std::cout << std::endl;
        }
        g.clearAllPath();
    }

    for (int end = 0; end != selectedEnd.size(); end++) {
        std::cout << "BFS to " << selectedEnd[end] << std::endl;
        list<list<int>> resultt = g.bfs(1, selectedEnd[end]);
        for (int i = 0; i != resultt.size(); i++) {
            for (int j = 0; j != resultt[i].size(); j++) {
                std::cout << resultt[i][j] << ' ';
            }
            std::cout << std::endl;
        }
    }

    std::cout << "Dijkstra:" << std::endl;
    dijkstra = g.dijkstra(1);
    resultik = g.prev();
    for (int i = 0; i != amount; i++) {
        for (int j = 0; j != selectedEnd.size(); j++) {
            if (selectedEnd[j] == i + 1) {
                std::cout << "from " << 1 << " to " << i + 1 << " - " << dijkstra[i] << std::endl;
            }
        }
    }

    for (int end = 0; end != selectedEnd.size(); end++) {
        std::cout << "Shortest path to " << selectedEnd[end] << std::endl;
        list<int> shortest = g.dijkstraPath(selectedEnd[end]);
        if (shortest.head() != 1) {
            std::cout << "No path."<<std::endl;
            continue;
        }
        for (int i = 0; i != shortest.size(); i++) {
            std::cout << shortest[i] << ' ';
        }
        std::cout << std::endl;
        std::cout << "Chance: " << g.chance(shortest) << std::endl;
    }
}
