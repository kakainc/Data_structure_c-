//
// Created by 刘美玉 on 2020/3/24.
//

#ifndef DATA_STRUCTURE_STACK_H
#define DATA_STRUCTURE_STACK_H

#include <iostream>

using namespace std;

/**栈的顺序存储结构**/

template<typename element>  // T
class Stack {
private:
    element *elem;   // 数组
    int top_e;   // 栈顶
    int max_size; // 最大容量
public:
    explicit Stack(int size);  // 不允许隐式转换

    ~ Stack();

    void push(const element &x);

    element pop();

    element top() const;

    int size() const;

    bool is_empty() const;

    void clear();
};

/**-------------------------------------------------------*/
template<typename element>
Stack<element>::Stack(int size):top_e(-1), max_size(size) {
    elem = new element[size];
}

template<typename element>
Stack<element>::~Stack() {
    clear();
    delete[] elem;
}

template<typename element>
void Stack<element>::push(const element &x) {
    if (top_e == max_size - 1) {
        cerr << "Error, stack is full!" << endl;
        return;
    }
    elem[++top_e] = x;
}

template<typename element>
element Stack<element>::pop() {
    if (top_e == -1) {
        cerr << "Error, stack is empty!" << endl;
    } else {
        return elem[top_e--];
    }
}

template<typename element>
element Stack<element>::top() const {
    if (is_empty()) {
        cerr << "Error, stack is empty!" << endl;
    } else {
        return elem[top_e];
    }
}

template<typename element>
int Stack<element>::size() const {
    return top_e + 1;
}

template<typename element>
bool Stack<element>::is_empty() const {
    return top_e == -1;
}

template<typename element>
void Stack<element>::clear() {
    while (top_e != -1) {
        elem[top_e].~element();
    }
}

/**栈的链式存储结构**/

template <typename elem>
class Stack_Link{
private:
    struct s_node{
        elem e;
        s_node *next_node;
    };
    s_node *top_e;
    int cont;
public:
    Stack_Link();
    ~Stack_Link();

    void push(const elem&);
    void pop();
    elem top();
    int size();
    bool empty();
    void clear();
};

/**-------------------------------------------------------*/

template<typename elem>
Stack_Link<elem>::Stack_Link() {
    top_e = NULL;
    cont = 0;
}

template<typename elem>
Stack_Link<elem>::~Stack_Link() {
    clear();
}

template<typename elem>
void Stack_Link<elem>::push(const elem &pe) {
    auto n_node = new s_node;
    n_node->e = pe;
    n_node->next_node = top_e;
    top_e = n_node;
    cont++;
}

template<typename elem>
void Stack_Link<elem>::pop() {
    if(empty()){
        cerr << "Error, stack is empty!" << endl;
    }
    auto tem = top_e;
    top_e = top_e->next_node;
    delete tem;
    cont--;
}

template<typename elem>
elem Stack_Link<elem>::top() {
    if(empty()){
        cerr << "Error, stack is empty!" << endl;
    }
    return top_e->e;
}

template<typename elem>
int Stack_Link<elem>::size() {
    return cont;
}

template<typename elem>
bool Stack_Link<elem>::empty() {
    return cont==0;
}

template<typename elem>
void Stack_Link<elem>::clear() {
    while(top_e){
        auto tem = top_e;
        top_e = top_e->next_node;
        delete tem;
    }
    cont = 0;
}

#endif //DATA_STRUCTURE_STACK_H
