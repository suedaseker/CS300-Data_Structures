#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <vector>
using namespace std;

template <class Type>
class CStack {
private:
    vector<Type> stackArray;
    int topOfStack;

public:
    CStack();

    void push(Type coor);
    void pop();
    Type top();
    bool isEmpty();
    const static Type noItem;
};

template <class Type>
const Type CStack<Type>::noItem = INT_MAX;

template<class Type>
CStack<Type>::CStack()
{
    topOfStack = -1;
}

template<class Type>
void CStack<Type>::push(Type coor)
{
    stackArray.push_back(coor);
    topOfStack++;
}

template<class Type>
void CStack<Type>::pop()
{
    if (isEmpty())
        cout << "the stack is empty.\n";
    else{
        stackArray.pop_back();
        topOfStack--;
    }
}

template<class Type>
Type CStack<Type>::top()
{
    if (isEmpty())
    {
        cout << "the stack is empty.\n";
        return noItem;
    }
    //return
    //exception??
    else{
        Type coor;
        coor = stackArray[topOfStack];
        return coor;
    }
}

template<class Type>
bool CStack<Type>::isEmpty()
{
    return topOfStack == -1;
}

#endif
