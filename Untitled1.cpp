#include "HashTable.h"
#include <iostream>
using namespace std;

HashTable::HashTable()
{
    for(int i = 0; i < tableSize;i++){
        hashTable[i] = NULL;
    }
}

HashTable::~HashTable()
{
    //dtor
}

int HashTable::hashSum(std::string x, int s)
{
    int sum = 0;
    for(unsigned int i = 0; i < x.size();i++){
        sum += x[i];
    }
    sum = sum % s;
    return sum;
}

void HashTable::insertMovie(string name, int year)
{
    int sum = hashSum(name,tableSize);
    HashElem * h = new HashElem(name, year,sum);
    if(hashTable[sum] == nullptr){
        hashTable[sum] = h;
    } else
    {
        HashElem * temp = hashTable[sum];
        while (temp -> next != nullptr){
            temp = temp -> next;
        }
        temp -> next = h;
        temp -> next -> previous = temp;
    }
}

void HashTable::deleteMovie(std::string name)
{
    int sum = hashSum(name, tableSize);
    if (hashTable[sum] == nullptr)
        cout << "not found" << endl;
    else
    {
        bool found = false;
        HashElem * q = hashTable[sum];
        while(q != nullptr){
            if (q->title == name)
            {
                found = true;
                if(q == hashTable[sum] && q-> next != nullptr){
                   q -> next -> previous = nullptr;
                   hashTable[sum] = q->next;
                   delete q;
                   break;
                   }
                else if(q == hashTable[sum] && q -> next == nullptr){
                    hashTable[sum] = nullptr;
                    delete q;
                    break;
                 }
                else if(q -> next == nullptr){
                    q -> previous -> next = nullptr;
                    delete q;
                    break;
                } else
                {
                    q -> previous -> next = q -> next;
                    q -> next -> previous = q -> previous;
                    delete q;
                    break;
                }
            } else
            q = q -> next;
        }
        if (found == false)
            cout << "not found" << endl;
    }
}

void HashTable::findMovie(string name)
{
    bool found = false;
    int sum = hashSum(name,tableSize);
    if(hashTable[sum] == nullptr){
        cout << "not found" << endl;
    } else
    {
        HashElem * t = hashTable[sum];
        if(t->title == name){
            cout << sum << ":" << t->title << ":" << t->year << endl;
        } else
        {
            while(t != nullptr){
                if (t->title == name){
                    cout << sum << ":" << t->title << ":" << t->year << endl;
                    found = true;
                    break;
                } else
                {
                    t = t -> next;
                }
            }
            if(found == false)
                cout <<"not found" << endl;
        }
    }

}

void HashTable::printTableContents()
{
    bool notNull = true;
    for(int i = 0; i < tableSize; i++){
        if(hashTable[i]!= nullptr)
        {
            notNull = false;
            break;
        }
    }
    if(notNull == true){
        cout << "empty" << endl;
    } else {
    HashElem * q ;
    for (int i = 0; i < tableSize;i++){
        q = hashTable[i];
        while (q != nullptr){
             cout << q->title << ":" << q->year << endl;
             q = q -> next;
        }
    }
    }
}
