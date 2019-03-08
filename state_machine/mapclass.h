#ifndef MAPCLASS_H
#define MAPCLASS_H
#include <listclass.h>
#include <token.h>
#include <pair.h>

template <typename K, typename V>
class Map{
public:
    Map();

    void Insert(K k, V v);
    void Insert(Token t);
    void Erase(K k, V v);
    V& operator[](K index);

    ~Map<K, V>();
    Map<K, V>(const Map<K, V> &other);
    Map<K, V> &operator=(Map<K, V> &other);

    int size();
    List<Pair<V, K> >* GetSortByValue();
    template <typename KK, typename VV>
    friend ostream& operator <<(ostream& out, const Map<KK, VV>& printMe);

private:
    node<Pair<K, V> >* head;
};

template <typename K, typename V>
Map<K, V>::Map(){
    head=NULL;
}

template <typename KK, typename VV>
ostream& operator <<(ostream& out, const Map<KK, VV>& printMe){
    _print(printMe.head);
    return out;
}

template <typename K, typename V>
List<Pair<V, K> >* Map<K,V>::GetSortByValue(){
    //cout<<endl<<"get sort by value"<<endl;
    List<Pair<V,K> >* list_ptr = new List<Pair<V,K> >;
    node<Pair<K,V> >* walker = head;
    //cout<<endl<<"walker item: "<<walker->item;
    for(int i=0; i<size(); i++){
        Pair<V, K> p(walker->item.value, walker->item.key);
        //cout<<endl<<"walker->item.val: "<<walker->item.value;
        //cout<<endl<<"walker->item.key "<<walker->item.key;
        //cout<<endl<<"making pair..."<<endl;
        //cout<<"printing pair: "<<p<<endl;
        list_ptr->InsertSorted(p);
        walker = walker->next;
    }
    return list_ptr;
}

template <typename K, typename V>
void Map<K, V>::Insert(Token t){
    //cout<<endl<<"inserting ["<<t<<"]"<<endl<<endl;
    Insert(t.token_string(), t.get_type());
}

template <typename K, typename V>
void Map<K, V>::Insert(K k, V v){
    Pair<K, V> p(k, v);
    //cout<<endl<<"pair: "<<p<<endl;
    node<Pair<K, V> >* nPtr = _whereThisGoes(head, p);
    if(!nPtr){
        _insertHead(head, p);
        //cout<<endl<<"headitem:"<<head->item;
        return;
    }
    else if(nPtr->item == p){
        //cout<<endl<<"Duplicate Entry: "<<p<<endl;
        nPtr->item.value++;
        return;
    }
    else{
        //cout<<endl<<"insert after"<<endl;
        _insertAfter(nPtr, p);
        return;
    }
}

template <typename K, typename V>
void Map<K, V>::Erase(K k, V v){
    Pair<K, V> p(k, v);
    _remove(head, p);
}

template <typename K, typename V>
int Map<K, V>::size(){
    node<Pair<K,V> >* walker = head;
    int count=0;
    while(walker){
        count++;
        walker=walker->next;
    }
    return count;
}

template <typename K, typename V>
Map<K, V>::~Map(){
    //cout<<endl<<"~Map()"<<endl;
    if(head){
        _clear(head);
    }
    head=NULL;
}

template <typename K, typename V>
Map<K, V>::Map(const Map<K,V>& other){
    cout<<endl<<"Map Copy Ctor"<<endl;
    head=_copy(other.head);
}

template <typename K, typename V>
Map<K, V> &Map<K,V>::operator = (Map<K,V>& other){
    cout<<endl<<"Map = Operator"<<endl;
    if(head){
        _clear(head);
    }
    head=NULL;
    if(other.head){
        head=_copy(other.head);
    }
}

template <typename K, typename V>
V& Map<K, V>::operator[](K index){
    int value = _search(head, index);
    return value;
}


#endif // MAPCLASS_H
