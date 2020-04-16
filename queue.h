//
// Created by 刘美玉 on 2020/3/24.
//

#ifndef DATA_STRUCTURE_QUEUE_H
#define DATA_STRUCTURE_QUEUE_H

/**队列的链式存储结构**/

#include <iostream>

using namespace std;

template<typename element>
class Queue {
private:
    struct QNode {
        QNode *next;    // 指针域
        element data;    //数据域
        explicit QNode(const element &newdata, QNode *nextnode = nullptr) : data(newdata), next(nextnode) {};
    };

    QNode *front;   // 头指针
    QNode *rear;    // 尾指针
    int count;
public:
    Queue();

    ~Queue();

    void clear();

    bool is_empty() const;

    int size() const;

    void push(const element &e);

    void pop();

    element top() const;
};

/**-------------------------------------------------------*/
template<typename element>
Queue<element>::Queue():front(nullptr), rear(nullptr), count(0) {}

template<typename element>
Queue<element>::~Queue() {
    clear();
}

template<typename element>
bool Queue<element>::is_empty() const {
    return front == nullptr;
}

template<typename element>
int Queue<element>::size() const {
    return count;
}

template<typename element>
void Queue<element>::clear() {
    while (front) {
        QNode *newnode = front;
        front = front->next;
        delete (newnode);
    }
    count = 0;
}

template<typename element>
void Queue<element>::push(const element &e) {
    if (is_empty()) {
        front = rear = new QNode(e);
    } else {
        auto *newnode = new QNode(e);
        rear->next = newnode;
        rear = newnode;
    }
    count++;
}

template<typename element>
void Queue<element>::pop() {
    if (front == nullptr) {
        cerr << "Error, queue is empty!" << endl;
    } else {
        QNode *newnode = front;
        front = front->next;
        delete newnode;
    }
    count--;
}

template<typename element>
element Queue<element>::top() const {
    if(front == nullptr){
        cerr << "Error, queue is empty!" << endl;
    }else{
        return front->data;
    }

}

/**队列的顺序存储结构**/

template <typename elem>
class Queue_list{
private:
    elem *element;
    int capity;
    int size;
    int front;
    int rear;

public:
    explicit Queue_list(int);
    ~Queue_list();

    bool is_empty() const;
    bool is_full() const;

    int size_() const;
    void push(const elem &e);
    void pop();

    elem head() const;
    elem back() const;

};

/**-------------------------------------------------------*/

template<typename elem>
Queue_list<elem>::Queue_list(int max_size):front(0),rear(0) {
    element = new elem[max_size];
    capity = max_size;
    size = 0;
}

template<typename elem>
Queue_list<elem>::~Queue_list() {
    delete []element;
}

template<typename elem>
bool Queue_list<elem>::is_empty() const {
    return size==0;
}

template<typename elem>
bool Queue_list<elem>::is_full() const {
    return size==capity;
}

template<typename elem>
int Queue_list<elem>::size_() const {
    return size;
}

template<typename elem>
void Queue_list<elem>::push(const elem &e) {
    if(not is_full()){
        element[rear]=e;
        rear = (rear+1)%capity;
    }else{
        elem *new_element = new elem[2*capity];
        memcpy(new_element, element, sizeof(elem)*capity);
        delete []element;
        element = new_element;
        element[capity] = e;
        rear = capity+1;
        capity = 2*capity;
    }
    size++;
}

template<typename elem>
void Queue_list<elem>::pop() {
    if(is_empty()){
        cerr << "empty queue!" << endl;
    }
    element[front] = NULL;
    front = (front+1)%capity;
    size--;
}

template<typename elem>
elem Queue_list<elem>::head() const {
    if(is_empty()){
        cerr << "empty queue!" << endl;
    }
    return element[front];
}

template<typename elem>
elem Queue_list<elem>::back() const {
    if(is_empty()){
        cerr << "empty queue!" << endl;
    }
    return element[rear-1];
}

#endif //DATA_STRUCTURE_QUEUE_H
