//
// Created by 刘美玉 on 2020/4/7.
//

#ifndef DATA_STRUCTURE_GRAPH_H
#define DATA_STRUCTURE_GRAPH_H


class Graph {
protected:
    int max_vex;
    int num_vex;
    int num_edge;
    bool weight;
    bool direct;
public:
    Graph();
    ~Graph();

    int get_numvex();
    int get_numedge();
};

Graph::Graph() {
    max_vex = 0;
    num_vex = 0;
    num_edge = 0;
    weight = false;
    direct = false;
}

int Graph::get_numvex() {
    return num_vex;
}

int Graph::get_numedge() {
    return num_edge;
}

Graph::~Graph() = default;


#endif //DATA_STRUCTURE_GRAPH_H
