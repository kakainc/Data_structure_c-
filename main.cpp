#include <iostream>
#include "stack.h"
#include "queue.h"
#include "binarytree.h"
#include "binsearch.h"
#include "Adjamatrix_graph.h"
#include "Adjalist_graph.h"

using namespace std;

void test_stack();
void test_queue();
void test_tree();
void test_bstree();
void test_matrix_g();
void test_list_g();

int main() {
    std::cout << "Hello, World!" << std::endl;

    test_stack();
    test_queue();
    test_tree();
    test_bstree();
    test_matrix_g();
    test_list_g();

    return 0;
}

void test_stack() {
    Stack<int> my_s(10);
    for (int i = 0; i < 10; i++) {
        my_s.push(i * 10);

    }
    cout << my_s.size() << endl;
    while (not my_s.is_empty()) {
        int t = my_s.top();
        cout << t << endl;
        my_s.pop();
    }
    Stack_Link<int> my_sl;
    for (int i = 0; i < 10; i++) {
        my_sl.push(i * 10);

    }
    cout << my_sl.size() << endl;
    while (not my_sl.empty()) {
        int t = my_sl.top();
        cout << t << endl;
        my_sl.pop();
    }
}

void test_queue() {
    Queue<int> my_q;
    for (int i = 0; i < 12; i++) {
        my_q.push(i * 10);
    }
    cout << my_q.size() << endl;
    while (not my_q.is_empty()) {
        int t = my_q.top();
        cout << t << endl;
        my_q.pop();
    }
    Queue_list<int> my_ql(5);
    for (int i = 0; i < 12; i++) {
        my_ql.push(i * 10);
    }
    for (int i = 0; i < 5; i++) {
        my_ql.pop();
    }
    for (int i = 0; i < 5; i++) {
        my_ql.push(i * 5);
    }
    cout << my_ql.size_() << endl;
    cout << my_ql.back() << endl;
    while (not my_ql.is_empty()) {
        int t = my_ql.head();
        cout << t << endl;
        my_ql.pop();
    }
}

void test_tree() {
    BinaryTree<char> my_t;
    my_t.CreatBitree(my_t.root_());
    cout << "树的大小" << my_t.size() << endl;
    cout << "树的深度" << my_t.Treedepth(my_t.root_()) << endl;
    cout << "递归遍历" << endl;
    my_t.PreOrder(my_t.root_());
    cout << endl;
    my_t.InOrder(my_t.root_());
    cout << endl;
    my_t.PostOrder(my_t.root_());
    cout << endl;
    cout << "非递归遍历" << endl;
    my_t.preOrder(my_t.root_());
    my_t.inOrder(my_t.root_());
    my_t.postOrder(my_t.root_());
    my_t.levelOrder(my_t.root_());
    my_t.erase(my_t.root_());
    cout << "树的大小" << my_t.size() << endl;
}

void test_bstree(){
    int test[10] = {62, 34, 55, 28, 76, 48, 49, 84, 8, 10};
    Binsearch<int> my_st;
    for(int i : test){
        my_st.insert(i);
    }
    my_st.DeleteBST(my_st.root_(), 49);
    cout << "树的大小" << my_st.size() << endl;
    cout << "树的深度" << my_st.Treedepth(my_st.root_()) << endl;
    cout << "递归遍历" << endl;
    my_st.PreOrder(my_st.root_());
    cout << endl;
    my_st.InOrder(my_st.root_());
    cout << endl;
    my_st.PostOrder(my_st.root_());
    cout << endl;
    cout << "非递归遍历" << endl;
    my_st.preOrder(my_st.root_());
    my_st.inOrder(my_st.root_());
    my_st.postOrder(my_st.root_());
    my_st.levelOrder(my_st.root_());
    my_st.erase(my_st.root_());
    cout << "树的大小" << my_st.size() << endl;
}

void test_matrix_g(){
    Adjacencymatrix<char> my_mg(20);
    my_mg.creat_graph();
    my_mg.display_info();
    cout << "深度优先遍历" << endl;
    my_mg.DFS();
    cout << "广度优先遍历" << endl;
    my_mg.BFS();
}

void test_list_g(){
    Adgacencylist<char> my_lg(20);
    my_lg.creat_graph();
    my_lg.display_info();
    cout << "深度优先遍历" << endl;
    my_lg.DFS();
    cout << "广度优先遍历" << endl;
    my_lg.BFS();
}
