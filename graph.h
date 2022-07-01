#pragma once

#include <iostream>
#include "list.h"
#include "vector.h"


struct Edge {
    int destination;
    int weight;
    double chance;
    Edge() {}
    Edge(int d, int w, double c) {
        this->destination = d;
        this->weight = w;
        this->chance = c;
    }
    int getDestination() {
        return destination;
    }
};
struct Vertex {
    int id;
    list<Edge> edgeList;
    Vertex() {
        id = 0;
    }
    Vertex(int id) {
        this->id = id;
    }
    int getId() {
        return id;
    }
};
class Graph {
public:
    void print() {
        for (int i = 0; i != vertices.size(); i++) {
            Vertex* temp = &vertices[i];
            std::cout << "(" << temp->id << ") --> ";
            for (int j = 0; j != temp->edgeList.size(); j++) {
                std::cout << "(" << temp->edgeList[j].destination << ")";
            }
            std::cout << std::endl;
        }
    }
    void addVertex(Vertex v) {
        for (int i = 0; i != vertices.size(); i++) {
            if (vertices[i].getId() == v.getId()) return;
        }
        vertices.push_back(v);
    }
    void addEdges(int id1, int id2, int weight = 0, double chance = 0) {
        for (int i = 0; i != vertices.size(); i++) {
            if (vertices[i].getId() == id1) {
                Edge e(id2, weight, chance);
                vertices[i].edgeList.push_back(e);
            }
        }
    }

    void deleteEdge(int fromVertex, int toVertex) {
        for (int i = 0; i != vertices.size(); i++) {
            if (vertices[i].id == fromVertex) {
                for (int j = 0; j != vertices[i].edgeList.size(); j++) {
                    if (vertices[i].edgeList[j].destination == toVertex) {
                        vertices[i].edgeList.pop(j);
                        break;
                    }
                }
            }
            else if (vertices[i].id == toVertex) {
                for (int j = 0; j != vertices[i].edgeList.size(); j++) {
                    if (vertices[i].edgeList[j].destination == fromVertex) {
                        vertices[i].edgeList.pop(j);
                        break;
                    }
                }
            }
        }
    }
    void dfs(int start, int end) {
        path.push_back(start);
        Vertex* current = &vertices[start - 1];
        if (start == end) {
            allPath.push_back(path);
            path.pop_back();
            return;
        }
        else {
            for (int i = 0; i != current->edgeList.size(); i++) {
                dfs(current->edgeList[i].destination, end);
            }
        }
        path.pop_back();
    }
    list<list<int>> returnPath() const {
        return allPath;
    }
    void clearAllPath() {
        allPath.clear();
    }
    list<int> prev() const {
        return previous;
    }
    list<list<int>> bfs(int start, int end) {
        list<int> bfspath;
        list<list<int>> result;
        list<list<int>> queue;
        bfspath.push_back(start);
        queue.push_front(bfspath);
        while (!queue.isEmpty()) {
            bfspath = queue.head();
            queue.pop_front();
            int lastNode = bfspath[bfspath.size() - 1];
            if (lastNode == end) {
                result.push_back(bfspath);
            }
            else {
                Vertex* current = &vertices[lastNode - 1];
                list<Edge> neighbors = current->edgeList;
                for (int neighbor = 0; neighbor != neighbors.size(); neighbor++) {
                    list<int> t = bfspath;
                    t.push_back(neighbors[neighbor].destination);
                    queue.push_front(t);
                }
            }
        }
        return result;
    }

    int* dijkstra(const int src) {
        previous.clear();
        int allVertices = vertices.size();
        int* dist = new int[allVertices];
        int* prev = new int[allVertices];
        list<int> queue;
        for (int i = 0; i != allVertices; i++) {
            dist[i] = INT_MAX;
            prev[i] = -1;
            queue.push_back(i);
        }
        dist[src - 1] = 0;
        while (!queue.isEmpty()) {
            int u = queue.head();
            queue.pop_front();
            for (int i = 0; i != vertices[u].edgeList.size(); i++) {
                if ((dist[u] + vertices[u].edgeList[i].weight) < dist[vertices[u].edgeList[i].destination - 1]) {
                    dist[vertices[u].edgeList[i].destination - 1] = dist[u] + vertices[u].edgeList[i].weight;
                    prev[vertices[u].edgeList[i].destination - 1] = u;
                }
            } 
        }
        for (int i = 0; i != allVertices; i++) {
            previous.push_back(prev[i]+1);
        }
        return dist;
    }

    list<int> dijkstraPath(const int end) {
        list<int> result;
        int iterator = end;
        while (iterator != 0) {
            result.push_front(iterator);
            iterator = previous[iterator-1];
        }
        return result;
    }

    double chance(list<int>& shortest) {
        double result = 0;
        for (int i = 0; i != shortest.size(); i++) {
            if (i + 1 == shortest.size()) break;
            for (int j = 0; j != vertices[shortest[i]-1].edgeList.size(); j++) {
                if (vertices[shortest[i] - 1].edgeList[j].destination == shortest[i + 1]) {
                    double life = 100.0 - vertices[shortest[i] - 1].edgeList[j].chance;
                   // std::cout << life << std::endl;
                    result += life;
                }
            }
       }
        return result / (shortest.size() - 1);
    }
private:
    list<int> previous;
    list<int> path;
    list<list<int>> allPath;
    list<Vertex> vertices;
};