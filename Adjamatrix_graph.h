//
// Created by 刘美玉 on 2020/4/8.
//

#ifndef DATA_STRUCTURE_ADJAMATRIX_GRAPH_H
#define DATA_STRUCTURE_ADJAMATRIX_GRAPH_H

#include <iostream>
#include <iomanip>
#include "graph.h"

using namespace std;


/************************邻接矩阵****************************/
template<typename v>
class Adjacencymatrix : public Graph {
private:
    v *vexlist;
    int **edge;
public:
    explicit Adjacencymatrix(int);

    virtual ~Adjacencymatrix();

    void creat_graph();

    bool insert_vex(v);

    int get_vexpos(v);

    bool insert_edge(v, v, int);

    void display_info();

    void DFS();

    void D_visit(int, vector<bool> &);

    void visit(int);

    void BFS();

};

template<typename v>
Adjacencymatrix<v>::Adjacencymatrix(int size) {
    max_vex = size;
    num_vex = 0;
    num_edge = 0;
    weight = false;
    direct = false;
    vexlist = new v[max_vex];
    edge = new int *[max_vex];
    for (int i = 0; i < max_vex; i++) {
        edge[i] = new int[max_vex];
    }
}

template<typename v>
Adjacencymatrix<v>::~Adjacencymatrix() {
    delete[]vexlist;
    for (int i = 0; i < max_vex; i++) {
        delete[]edge[i];
    }
    delete[]edge;
}

template<typename v>
void Adjacencymatrix<v>::creat_graph() {
    int m, n, w, d, wt;
    v vex, edg_t, edg_h;
    cout << "请输入顶点数和边数" << endl;
    cin >> m >> n;
    cout << "请依次输入顶点" << endl;
    for (int i = 0; i < m; i++) {
        cin >> vex;
        this->insert_vex(vex);
    }
    cout << "是否带有权重1/0" << endl;
    cin >> w;
    if (w == 1) {
        weight = true;
    }
    cout << "图是否有向1/0" << endl;
    cin >> d;
    if (d == 1) {
        direct = true;
    }
    if (weight) {
        for (int i = 0; i < max_vex; i++) {
            for (int j = 0; j < max_vex; j++) {
                edge[i][j] = (i == j) ? 0 : INT_MAX;
            }
        }
        cout << "请依次输入边(尾)， 边(头)， 权重：" << endl;
    } else {
        for (int i = 0; i < max_vex; i++) {
            for (int j = 0; j < max_vex; j++) {
                edge[i][j] = 0;
            }
        }
        cout << "请依次输入边(尾)， 边(头)：" << endl;
    }
    for (int i = 0; i < n; i++) {
        if (weight) {
            cin >> edg_t >> edg_h;
            cin >> wt;
        } else {
            cin >> edg_t >> edg_h;
            wt = 1;
        }
        this->insert_edge(edg_t, edg_h, wt);
    }
}

template<typename v>
bool Adjacencymatrix<v>::insert_vex(v vex) {
    int pos = this->get_vexpos(vex);
    if (pos != -1) {
        cout << "该顶点已存在，添加失败！" << endl;
        return false;
    }
    if (num_vex >= max_vex) {
        return false;
    }
    vexlist[num_vex++] = vex;
    return true;
}

template<typename v>
int Adjacencymatrix<v>::get_vexpos(v vex) {
    for (int i = 0; i < max_vex; i++) {
        if (vexlist[i] == vex) {
            return i;
        }
    }
    return -1;
}

template<typename v>
bool Adjacencymatrix<v>::insert_edge(v edg_t, v edg_h, int wt) {
    int pos_t = this->get_vexpos(edg_t);
    int pos_h = this->get_vexpos(edg_h);
    if (pos_t == -1 || pos_h == -1) {
        cout << "输入边的顶点不存在，添加失败！" << endl;
        return false;
    } else {
        if (edge[pos_t][pos_h] == 0 || edge[pos_t][pos_h] == INT_MAX) {
            if (not direct) {
                edge[pos_t][pos_h] = edge[pos_h][pos_t] = wt;
            } else {
                edge[pos_t][pos_h] = wt;
            }
            num_edge++;
            return true;
        } else {
            cout << "该边已存在，添加失败！" << endl;
            return false;
        }
    }
}

template<typename v>
void Adjacencymatrix<v>::display_info() {
    string s1, s2;
    s1 = direct ? "有向" : "无向";
    s2 = weight ? "有权" : "无权";
    cout << "该图为" << num_vex << "个顶点的" << s1 << s2 << "图，顶点分别是： ";
    for (int i = 0; i < num_vex; i++) {
        cout << vexlist[i];
    }
    cout << endl;
    cout << "邻接矩阵为：" << endl;
    for (int i = 0; i < num_vex; i++) {
        for (int j = 0; j < num_vex; j++) {
            if (edge[i][j] == INT_MAX) {
                cout << setw(5) << "∞";
            } else {
                cout << setw(5) << edge[i][j];
            }
        }
        cout << endl;
    }
}

template<typename v>
void Adjacencymatrix<v>::DFS() {
    vector<bool> visited(num_vex, false);
    for (int i = 0; i < num_vex; i++) {
        if (not visited[i]) {
            D_visit(i, visited);
        }
    }
    cout << endl;
}

template<typename v>
void Adjacencymatrix<v>::D_visit(int j, vector<bool> &visited) {
    visited[j] = true;
    visit(j);
    for (int i = 0; i < num_vex; i++) {
        if (edge[j][i] != 0 && edge[j][i] != INT_MAX && not visited[i]) {
            D_visit(i, visited);
        }
    }

}

template<typename v>
void Adjacencymatrix<v>::visit(int j) {
    cout << vexlist[j] << ' ';
}

template<typename v>
void Adjacencymatrix<v>::BFS() {
    vector<bool> visited(num_vex, false);
    queue<int> q;
    for (int i = 0; i < num_vex; i++) {
        if (not visited[i]) {
            q.push(i);
            visit(i);
            visited[i] = true;
            while (not q.empty()) {
                int tem = q.front();
                q.pop();
                for (int j = 0; j < num_vex; j++) {
                    if (edge[tem][j] != 0 && edge[tem][j] != INT_MAX && not visited[j]) {
                        q.push(j);
                        visit(j);
                        visited[j] = true;
                    }
                }
            }
        }
    }
    cout << endl;
}

#endif //DATA_STRUCTURE_ADJAMATRIX_GRAPH_H
