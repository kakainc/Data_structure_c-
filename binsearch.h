//
// Created by 刘美玉 on 2020/4/3.
//

#ifndef DATA_STRUCTURE_BINSEARCH_H
#define DATA_STRUCTURE_BINSEARCH_H

#include <iostream>
#include "binarytree.h"

using namespace std;

/**********************二叉搜索树*******************************/
template<typename elem>
class Binsearch : public BinaryTree<elem> {
private:
    void Delete(Bnode<elem> *&node);

public:
    bool DeleteBST(Bnode<elem> *&fir_node, elem key);   // 找到并删除结点
    Bnode<elem> *search(Bnode<elem> *node, elem key, Bnode<elem> *f);

    bool insert(elem e);
};

/******************************************/

template<typename elem>
void Binsearch<elem>::Delete(Bnode<elem> *&node) {
    Bnode<elem> *t = node;
    Bnode<elem> *m;
    if (node->leftch == NULL) {
        node = node->rightch;
        delete t;
    } else if (node->rightch == NULL) {
        node = node->leftch;
        delete t;
    } else {
        m = node->leftch;
        while (m->rightch) {
            t = m;
            m = m->rightch;
        }
        node->data = m->data;
        if (t == node) {
            t->leftch = m->leftch;
        } else {
            t->rightch = m->leftch;
        }
        delete m;
    }
    this->tree_size--;
}

template<typename elem>
bool Binsearch<elem>::DeleteBST(Bnode<elem> *&fir_node, elem key) {
    if (fir_node == NULL) {
        return false;
    } else {
        if (key == fir_node->data) {
            Delete(fir_node);
            return true;
        } else if (key < fir_node->data) {
            return DeleteBST(fir_node->leftch, key);
        } else {
            return DeleteBST(fir_node->rightch, key);
        }
    }
}

template<typename elem>
Bnode<elem> *Binsearch<elem>::search(Bnode<elem> *node, elem key, Bnode<elem> *f) {
    if (not node) {
        return f;
    } else if (key == node->data) {
        return node;
    } else if (key < node->data) {
        return search(node->leftch, key, node);
    } else if (key > node->data) {
        return search(node->rightch, key, node);
    }
}

template<typename elem>
bool Binsearch<elem>::insert(elem e) {
    auto *s = new Bnode<elem>;
    s->data = e;
    s->leftch = s->rightch = NULL;
    Bnode<elem> *p = search(this->root, e, NULL);
    if (not p) {
        this->root = s;
    } else {
        if (p->data == e) {
            return false;
        } else if (p->data > e) {
            p->leftch = s;
        } else {
            p->rightch = s;
        }
    }
    this->tree_size++;
    return true;
}

#endif //DATA_STRUCTURE_BINSEARCH_H
