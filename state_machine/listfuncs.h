#ifndef LISTFUNCS_H
#define LISTFUNCS_H
#include <iostream>
#include <node.h>
using namespace std;

template <typename T>
node<T>* _search(node<T>* hPtr, const T &item);
template <typename T>
node<T>* _search(node<T>* hPtr, const T &item){
    while(hPtr){
        if(hPtr->item == item){
            //this allows the last node to be returned
            //if the item is not found

            //cout<<endl<<"hPtr item-> "<<hPtr->item<<endl;
            //cout<<endl<<"Item found, returning node"<<endl;
            return hPtr;
        }
        hPtr=hPtr->next;
    }

    cout<<endl<<"Item is not in the list, returning NULL"<<endl;
    return NULL;
}

template <typename T>
node<T>* _insertAfter(node<T>* afterMe, const T &item);
template <typename T>
node<T>* _insertAfter(node<T>* afterMe, const T &item){
    node<T>* temp = new node<T>(item);
    if(afterMe){
        //1. break the link and hold the next
        node<T>* hold=afterMe->next;

        //2. afterMe's next connect to new node
        afterMe->next=temp;

        //3. new node's previous connect to afterMe
        temp->prev=afterMe;

        //4. new node's next reconnect hold from #1
        temp->next=hold;

        return temp;
    }
    else{
        cout<<endl<<"(_insertAfter) returning NULL"<<endl;
        return NULL;
    }
}

template <typename T>
node<T>* _insertSorted(node<T>* &head, const T &item);
template <typename T>
node<T>* _insertSorted(node<T>* &head, const T &item){
    //cout<<endl<<"_insertSorted entered"<<endl;
    node<T>* after = _whereThisGoes(head, item);
    node<T>* temp = new node<T>(item);

    if(!after){
        //cout<<endl<<"_insertSorted return _insertHead"<<endl;
        //if whereThisGoes returned the head
        //cout<<endl<<"temp item is "<<temp->item<<endl;
        return _insertHead(temp, item);
    }
    else{
        //cout<<endl<<"_insertSorted else"<<endl;
        temp->prev = after;
        temp->next = after->next;
        after->next=temp;
//        cout<<endl<<"==================="<<endl;
//        cout<<"afterMe prev is "<<afterMe->prev->item;
//        cout<<endl<<"afterMe is "<<afterMe->item;
//        cout<<endl<<"afterMe next is "<<afterMe->next->item;
//        cout<<endl<<"==================="<<endl;

    }
    return temp;
}

template<typename T>
node<T>* _whereThisGoes(node<T>* head, const T &item);
template<typename T>
node<T>* _whereThisGoes(node<T>* head, const T &item){
    //cout<<endl<<"_wTG entered"<<endl;
    if(!head){
        //EMPTY LIST ATM
        //cout<<endl<<"replace head"<<endl;
        return NULL;
    }
    else{
        //cout<<endl<<"head is not null"<<endl;
        while(head){
            //NOT EMPTY LIST
            if(head->next){
                //cout<<endl<<"if(head->next)"<<endl;
                //head's next is not null = NOT AT THE END
                if(item < head->item){
                    //if item is less than head, replace head
                    return head->prev;
                }
                else{
                    if(item >= head->item && item < head->next->item){
                        //if the item is greater than head and less than
                        //the next elements item, return current position
                        return head;
                    }
                }
            }
            else{
                //cout<<endl<<"else"<<endl;
                //WE ARE AT THE END OF THE LIST
                if(item < head->item){
                    return head->prev;
                }
                else{
                    return head;
                }
                //return head;
                //head is at the end of the list
            }
            head=head->next;
            //traverse beeeeech
        }
    }
    //cout<<endl<<"_whereThisGoes: did not return"<<endl;
}

template <typename T>
node<T>* _insertHead(node<T>* &hPtr, const T &item);
template <typename T>
node<T>* _insertHead(node<T>* &hPtr, const T &item){
    //cout<<endl<<"entered insertHead"<<endl;
    //cout<<endl<<"hPtr item: "<<hPtr->item<<endl;

    //1. Create new node "temp"
    node<T>* temp = new node<T>(item);

    //2. Set temp's next to head pointer
    temp->next=hPtr;

    //3. If hPtr != NULL, set its previous to temp
    //the first hPtr will be NULL.
    //dont fuck with a NULL node
    if(hPtr){
        hPtr->prev=temp;
    }

    //4. Set temp's previous to NULL
    temp->prev=NULL;

    //5. Set the new head to temp
    hPtr=temp;

    return hPtr;
}

template <typename T>
void _clear(node<T>* &hPtr);
template <typename T>
void _clear(node<T>* &hPtr){
    node<T>* walker = hPtr;
    //cout<<endl<<"entered _clear"<<endl;
    if(hPtr){
        //cout<<endl<<"hPtr is not null"<<endl;
        //cout<<endl<<"hPtr->item is: "<<hPtr->item<<endl;
        while(walker){
            //cout<<endl<<"walker->item: "<<walker->item<<endl;
            walker=walker->next;
            //cout<<"walker->prev = "<<walker->prev->item;
            delete hPtr;
            hPtr=walker;
        }
    }
    else{
        cout<<endl<<"(_clear) hPtr is NULL"<<endl;
    }
    hPtr=NULL;
}

template <typename T>
node<T>* _copy(node<T>* copyMe);
template <typename T>
node<T>* _copy(node<T>* copyMe){
    node<T>* newList=new node<T>(copyMe->item);
    node<T>* hold=newList;
    if(copyMe){
        while(copyMe->next){
            copyMe=copyMe->next;
            newList->next=new node<T>(copyMe->item);
            newList->next->prev=newList;
            newList=newList->next;
        }
    }
    return hold;
}

//pre: takes a hPtr to the list and item to be removed
//post: returns the ("plucks") node to be deleted
template <typename T>
node<T>* _remove(node<T>* &hPtr, const T &item);
template <typename T>
node<T>* _remove(node<T>* &hPtr, const T &item){
    node<T>* walker = hPtr;
    while(walker){
        if(walker->item == item){
            cout<<endl<<"(_remove) found item"<<endl;
            return walker;
        }
        walker=walker->next;
    }
    cout<<endl<<"(_remove) item not found, returning NULL"<<endl;
    return NULL;
}


template <typename T>
void _print(node<T>* hPtr);
template <typename T>
void _print(node<T>* hPtr){
    if(!hPtr){
        cout<<endl<<"_print: head is NULL, exitting"<<endl;
        exit(0);
    }
    while(hPtr){
        cout << hPtr->item <<endl;
        hPtr=hPtr->next;
    }
}

//template <typename T>
//void _print_ptr(node<T>* hPtr);
//template <typename T>
//void _print_ptr(node<T>* hPtr){
//    if(!hPtr){
//        cout<<endl<<"_print: head is NULL, exitting"<<endl;
//        exit(0);
//    }
//    while(hPtr){
//        cout << *hPtr << " ";
//        hPtr++;
//    }
//}

template <typename T>
node<T>* _gethPtr(node<T>* hPtr);

template <typename T>
node<T>* _gethPtr(node<T>* hPtr){
    if(hPtr){
        return hPtr;
    }
    else{
        cout<<endl<<"(_peek) nothing to peek"<<endl;
    }
}


#endif // LISTFUNCS_H
