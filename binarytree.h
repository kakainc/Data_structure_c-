//
// Created by 刘美玉 on 2020/3/31.
//

#ifndef DATA_STRUCTURE_BINARYTREE_H
#define DATA_STRUCTURE_BINARYTREE_H

#include <iostream>
#include <stack>
#include <queue>

using namespace std;

template<typename elem>
struct Bnode {
    elem data;
    Bnode *leftch, *rightch;
};

template<typename elem>
class BinaryTree {
protected:
    Bnode<elem> *root;
    int tree_size;
private:
    struct Pnode{    // 非递归后序遍历所用到的结点结构
        Bnode<elem>* pb;
        char tag;
    };
public:
    BinaryTree();
    ~BinaryTree();

    int size() { return this->tree_size; }
    Bnode<elem> *&root_() { return root; }      // *&

    void CreatBitree(Bnode<elem> *&node);    // *&前序遍历创建二叉树
    void erase(Bnode<elem> *node);
    int Treedepth(Bnode<elem> *node);

    void visit(Bnode<elem> *node) { cout << node->data << ' '; }
    void PreOrder(Bnode<elem> *node);
    void InOrder(Bnode<elem> *node);
    void PostOrder(Bnode<elem> *node);

    void preOrder(Bnode<elem> *node);
    void inOrder(Bnode<elem> *node);
    void postOrder(Bnode<elem> *node);
    void levelOrder(Bnode<elem> *node);
};

/***************树体结构********************/

template<typename elem>
BinaryTree<elem>::BinaryTree():tree_size(0) {
    root = NULL;
}

template<typename elem>
BinaryTree<elem>::~BinaryTree() {
    erase(root);
}

template<typename elem>
void BinaryTree<elem>::CreatBitree(Bnode<elem> *&node) {
    elem e;
    cin >> e;
    if (e == '.') {
        node = nullptr;
    } else {
        node = new Bnode<elem>;
        node->data = e;
        tree_size++;
        CreatBitree(node->leftch);
        CreatBitree(node->rightch);
    }
}

template<typename elem>
void BinaryTree<elem>::erase(Bnode<elem> *node) {
    if (node != nullptr) {
        erase(node->leftch);
        erase(node->rightch);
        delete node;
        tree_size--;
    }
}

template<typename elem>
int BinaryTree<elem>::Treedepth(Bnode<elem> *node) {
    int hleft, hright;
    if (node == nullptr) {
        return 0;
    } else {
        hleft = Treedepth(node->leftch);

        hright = Treedepth(node->rightch);
    }
    return hleft > hright ? ++hleft : ++hright;
}

/*****************递归遍历******************/
template<typename elem>
void BinaryTree<elem>::PreOrder(Bnode<elem> *node) {
    if (node) {
        visit(node);
        PreOrder(node->leftch);
        PreOrder(node->rightch);
    }
}

template<typename elem>
void BinaryTree<elem>::InOrder(Bnode<elem> *node) {
    if (node) {
        InOrder(node->leftch);
        visit(node);
        InOrder(node->rightch);
    }
}

template<typename elem>
void BinaryTree<elem>::PostOrder(Bnode<elem> *node) {
    if (node) {
        PostOrder(node->leftch);
        PostOrder(node->rightch);
        visit(node);
    }
}

/******************非递归遍历***********************/
template<typename elem>
void BinaryTree<elem>::preOrder(Bnode<elem> *node) {
    Bnode<elem> *q = node;
    stack<Bnode<elem> *> s;
    while (q || !s.empty()) {
        if (q) {
            s.push(q);
            visit(q);
            q = q->leftch;
        } else {
            q = s.top();
            s.pop();
            q = q->rightch;
        }
    }
    cout << endl;
}

template<typename elem>
void BinaryTree<elem>::inOrder(Bnode<elem> *node) {
    Bnode<elem> *q = node;
    stack<Bnode<elem> *> s;
    while (q || !s.empty()) {
        if (q) {
            s.push(q);
            q = q->leftch;
        } else {
            q = s.top();
            s.pop();
            visit(q);
            q = q->rightch;
        }
    }
    cout << endl;
}

template<typename elem>
void BinaryTree<elem>::postOrder(Bnode<elem> *node) {
    Bnode<elem> *q = node;
    Pnode *pn;       // pb, tag
    stack<Pnode *> s;
    while (q || !s.empty()) {
        while(q){
            pn = new Pnode;
            pn->pb = q;
            pn->tag = 'L';
            s.push(pn);
            q=q->leftch;
        }
        while(!s.empty() && (s.top())->tag == 'R'){
            visit((s.top())->pb);
            s.pop();
        }
        if(!s.empty()){
            pn = s.top();
            pn->tag = 'R';
            q = pn->pb;
            q = q->rightch;
        }
    }
    cout << endl;
}

template<typename elem>
void BinaryTree<elem>::levelOrder(Bnode<elem> *node) {
    Bnode<elem> *q = node;
    queue<Bnode<elem> *> l;
    l.push(q);
    while (!l.empty()) {
        q = l.front();
        visit(q);
        l.pop();
        if (q->leftch) {
            l.push(q->leftch);
        }
        if (q->rightch) {
            l.push(q->rightch);
        }
    }
    cout << endl;
}

#endif //DATA_STRUCTURE_BINARYTREE_H
