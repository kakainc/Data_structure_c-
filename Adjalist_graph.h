//
// Created by 刘美玉 on 2020/4/8.
//

#ifndef DATA_STRUCTURE_ADJALIST_GRAPH_H
#define DATA_STRUCTURE_ADJALIST_GRAPH_H

#include <iostream>
#include "graph.h"

using namespace std;

/************************邻接表*****************************/
template<typename v>
class Adgacencylist : public Graph {
private:
    struct Enode {
        int idx;
        int wt;
        Enode *next_node;

        Enode(int num, int ww) {
            idx = num;
            wt = ww;
        }
    };

    struct Vnode {
        int out;
        v vex;
        Enode *firstenode;
    };
    Vnode *vexlist;
public:
    explicit Adgacencylist(int);

    virtual ~Adgacencylist();

    void creat_graph();

    bool insertvex(v);

    int getvexpos(v);

    bool insertedge(v, v, int);

    void display_info();

    void DFS();

    void D_visit(int, vector<bool> &);

    void visit(int);

    void BFS();

};

template<typename v>
Adgacencylist<v>::Adgacencylist(int size) {
    max_vex = size;
    num_vex = 0;
    num_edge = 0;
    weight = false;
    direct = false;
    vexlist = new Vnode[size];
    if (vexlist == NULL) {
        cerr << "内存分配失败！" << endl;
        exit(1);
    }
    for (int i = 0; i < max_vex; i++) {
        vexlist[i].out = 0;
        vexlist[i].firstenode = NULL;
    }
}

template<typename v>
Adgacencylist<v>::~Adgacencylist() {
    for (int i = 0; i < num_vex; i++) {
        Enode *e = vexlist[i].firstenode;
        while (e->next_node) {
            vexlist[i].firstenode = e->next_node;
            delete e;
            e = vexlist[i].firstenode;
        }
    }
    delete[]vexlist;
}

template<typename v>
void Adgacencylist<v>::creat_graph() {
    int m, n, w, d, wt;
    v vex, edg_t, edg_h;
    cout << "请依次输入顶点数和边数" << endl;
    cin >> m >> n;
    if (m > max_vex) {
        cerr << "顶点数超出申请数，创建失败！" << endl;
        exit(1);
    }
    cout << "请依次输入顶点" << endl;
    for (int i = 0; i < m; i++) {
        cin >> vex;
        insertvex(vex);
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
        cout << "请依次输入边(尾)， 边(头)， 权重：" << endl;
    } else {
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
        insertedge(edg_t, edg_h, wt);
    }
}

template<typename v>
bool Adgacencylist<v>::insertvex(v vi) {
    int pos_v = getvexpos(vi);
    if (pos_v != -1) {
        cout << "顶点已存在，添加失败" << endl;
        return false;
    }
    vexlist[num_vex].vex = vi;
    num_vex++;
    return true;
}

template<typename v>
int Adgacencylist<v>::getvexpos(v vi) {
    for (int i = 0; i < max_vex; i++) {
        if (vexlist[i].vex == vi) {
            return i;
        }
    }
    return -1;
}

template<typename v>
bool Adgacencylist<v>::insertedge(v vt, v vh, int wt) {
    int pos_t = getvexpos(vt);
    int pos_h = getvexpos(vh);
    if (pos_t == -1 || pos_h == -1) {
        cout << "输入边的顶点不存在，添加失败！" << endl;
        return false;
    } else {
        Enode *p = vexlist[pos_t].firstenode;
        while (p && p->idx != pos_h) {
            p = p->next_node;
        }
        if (p) {
            cout << "该边已存在，插入失败！" << endl;
            return false;
        }
        if (direct) {
            auto *e1 = new Enode(pos_h, wt);
            e1->next_node = vexlist[pos_t].firstenode;
            vexlist[pos_t].firstenode = e1;
            vexlist[pos_t].out++;
        } else {
            auto *e1 = new Enode(pos_h, wt);
            e1->next_node = vexlist[pos_t].firstenode;
            vexlist[pos_t].firstenode = e1;
            vexlist[pos_t].out++;

            auto *e2 = new Enode(pos_t, wt);
            e2->next_node = vexlist[pos_h].firstenode;
            vexlist[pos_h].firstenode = e2;
            vexlist[pos_h].out++;
        }
        num_edge++;
        return true;
    }
}

template<typename v>
void Adgacencylist<v>::display_info() {
    string s1, s2;
    s1 = direct ? "有向" : "无向";
    s2 = weight ? "有权" : "无权";
    cout << "该图为" << num_vex << "个顶点的" << s1 << s2 << "图，顶点分别是：";
    for (int i = 0; i < num_vex; i++) {
        cout << vexlist[i].vex << ' ';
    }
    cout << endl;
    cout << "邻接表为：" << endl;
    for (int i = 0; i < num_vex; i++) {
        if (direct) {
            cout << "下标为" << i << "的顶点" << vexlist[i].vex << "的出度为" << vexlist[i].out << " -> ";
        } else {
            cout << "下标为" << i << "的顶点" << vexlist[i].vex << "的度为" << vexlist[i].out << " -> ";
        }
        Enode *tem = vexlist[i].firstenode;
        while (tem) {
            cout << '(' << vexlist[tem->idx].vex << ',' << tem->wt << ')';
            tem = tem->next_node;
            if (tem) {
                cout << "->";
            }
        }
        cout << endl;
    }
}

template<typename v>
void Adgacencylist<v>::DFS() {
    vector<bool> visited(num_vex, false);
    for (int i = 0; i < num_vex; i++) {
        if (not visited[i]) {
            D_visit(i, visited);
        }
    }
    cout << endl;
}

template<typename v>
void Adgacencylist<v>::D_visit(int i, vector<bool> &visited) {
    visit(i);
    visited[i] = true;
    Enode *p = vexlist[i].firstenode;
    while (p) {
        if (not visited[p->idx]) {
            D_visit(p->idx, visited);
        }
        p = p->next_node;
    }
}

template<typename v>
void Adgacencylist<v>::visit(int i) {
    cout << vexlist[i].vex << ' ';
}

template<typename v>
void Adgacencylist<v>::BFS() {
    vector<bool> visited(num_vex, false);
    queue<int> vq;
    for (int i = 0; i < num_vex; i++) {
        if (not visited[i]) {
            vq.push(i);
            visit(i);
            visited[i] = true;
            while (not vq.empty()) {
                int tem = vq.front();
                vq.pop();
                Enode *p = vexlist[tem].firstenode;
                for (int j = 0; j < vexlist[tem].out; j++) {
                    if (not visited[p->idx]) {
                        vq.push(p->idx);
                        visit(p->idx);
                        visited[p->idx] = true;
                    }
                    p = p->next_node;
                }
            }
        }
    }
    cout << endl;
}


#endif //DATA_STRUCTURE_ADJALIST_GRAPH_H
