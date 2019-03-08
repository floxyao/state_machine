#ifndef LISTCLASS_H
#define LISTCLASS_H
#include <node.h>
#include <listfuncs.h>
//#include <mapclass.h>
#include <iostream>
using namespace std;

template <typename T>
class List
{
public:
    List();

    ~List<T>();
    List<T>(const List<T> &other);
    List<T> &operator=(List<T> &other);

    template <typename U>
    friend ostream &operator << (ostream &out, const List<U>& printMe);
    node<T>* InsertSorted(const T& item);
    node<T>* InsertHead(const T& item);
    void SortByValue(const T& item);
    T Peek();
    void Print()const;
    T operator* ();

private:
    node<T>* hPtr;

};

//================LIST CONSTRUCTORS==================
template <typename T>
List<T>::List(){
    //cout<<endl<<"List Default Ctor"<<endl;
    //hPtr=new node<T>;
    hPtr=NULL;
}
//================LIST CLASS FUNCTIONS===============
template <typename T>
T List<T>::operator *(){
    cout<<endl<<"entered * op"<<endl;
    if(!hPtr){
        return hPtr->item;
    }
    else{
        return T(); //default template
    }
}

template <typename T>
node<T>* List<T>::InsertSorted(const T &item){
    //cout<<endl<<"List InsertSorted entered"<<endl;
    node<T>* n = _insertSorted(hPtr, item);
    if(!n->prev){
        //cout<<endl<<"entered n->prev"<<endl;
        return InsertHead(item);
    }
    else{
        return n;
    }
}

template <typename T>
node<T>* List<T>::InsertHead(const T &item){
    return _insertHead(hPtr, item);
}

template <typename U>
ostream& operator << (ostream &out, const List<U>& printMe){
    printMe.Print();
    return out;
}

template <typename T>
void List<T>::Print()const{
    _print(hPtr);
}

template <typename T>
T List<T>::Peek(){
    return _gethPtr(hPtr)->item;
}




//================LIST BIG THREE=====================
template <typename T>
List<T>::~List(){
    //cout<<endl<<"LIST DESTRUCTOR"<<endl;
    if(hPtr){
        //cout<<endl<<"before _clear"<<endl;
        _clear(hPtr);
        //cout<<endl<<"after _clear"<<endl;
    }
    hPtr=NULL;
    //cout<<endl<<"hPtr set to NULL"<<endl;
    //cout<<endl<<"cursor set to NULL"<<endl;
    //tail=NULL;
}

template <typename T>
List<T>::List(const List<T> &other){
    //cout<<endl<<"LIST COPYCTOR"<<endl;
    hPtr=_copy(other.hPtr);
}

template <typename T>
List<T> &List<T>::operator = (List<T> &other){
    //cout<<endl<<"LIST =OP"<<endl;
    if(hPtr){
        //cout<<endl<<"(=) entered hPtr != NULL"<<endl;
        _clear(hPtr);
    }
    hPtr=NULL;
    //tail=NULL;
    if(other.hPtr){
        //cout<<endl<<"(=) entered other.hPtr != NULL"<<endl;
        hPtr=_copy(other.hPtr);
    }
}

#endif // LISTCLASS_H
