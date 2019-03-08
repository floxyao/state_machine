#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

template <typename T>
struct node{
    node();
    node(T value);

    T item;
    node* next;
    node* prev;
};

template <typename T>
node<T>::node(){
    //cout<<endl<<"NODE: DEFAULT CTOR"<<endl;
    next=NULL;
    prev=NULL;
}

template <typename T>
node<T>::node(T value){
    item=value;
    next=NULL;
    prev=NULL;
}




#endif // NODE_H
