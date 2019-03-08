#ifndef PAIR_H
#define PAIR_H
#include <iostream>
using namespace std;

template <typename K, typename V>
struct Pair{
    Pair();
    Pair(K k, V v);
    K key;
    V value;

    template <typename KK, typename VV>
    friend bool operator < (const Pair<KK, VV>& left, const Pair<KK, VV>& right);
    template <typename KK, typename VV>
    friend bool operator >= (const Pair<KK, VV>& left, const Pair<KK, VV>& right);
    template <typename KK, typename VV>
    friend bool operator ==(const Pair<KK, VV>& left, const Pair<KK, VV>& right);
    template <typename KK, typename VV>
    friend ostream &operator << (ostream &out, const Pair<KK, VV> &printMe);

};
template <typename K, typename V>
Pair<K, V>::Pair(){
    //cout<<endl<<"default ctor"<<endl;
}

template <typename K, typename V>
Pair<K, V>::Pair(K k, V v){
    //cout<<endl<<"entered Pair 2nd ctor"<<endl;
    key = k;
    value = v;
}

template <typename KK, typename VV>
ostream& operator << (ostream& out, const Pair<KK, VV> &printMe){
    out << "Key: [" << printMe.key <<"] "
           " Value: [" << printMe.value << "]";
    return out;
}

template <typename KK, typename VV>
bool operator ==(const Pair<KK,VV>& left, const Pair<KK,VV>& right){
    if(left.key == right.key){
        return true;
    }
    return false;
}

template <typename KK, typename VV>
bool operator >= (const Pair<KK, VV>& left, const Pair<KK, VV>& right){
    if(left.key >= right.key){
        return true;
    }
    return false;
}

template <typename KK, typename VV>
bool operator < (const Pair<KK, VV>& left, const Pair<KK, VV>& right){
    if(left.key < right.key){
        return true;
    }
    return false;
}


#endif // PAIR_H
