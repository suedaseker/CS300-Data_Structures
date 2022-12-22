#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Stack.h"
using namespace std;

template <class Type>
struct snode{
    Type x;
    Type y;
    snode(Type x=0, Type y=0):x(x), y(y){};
};

template <>
const snode<int> CStack<snode<int>>::noItem = snode<int>(INT_MAX, INT_MAX);

bool fileFail(string filename)
{
    ifstream input;

    input.open(filename.c_str());

    if (input.fail())
    {
        return false;
    }
    input.close();
    return true;
}

CStack<snode<int>> getData(string filename)
{
    ifstream input;
    //string filename = "input.txt";
    input.open(filename.c_str());

    int x, y;
    snode<int> coor;
    CStack<snode<int>> destination;
    while (input >> x >> y)
    {
        coor.x = x;
        coor.y = y;
        destination.push(coor);
    }
    input.close();

    return destination;
}

void printStack(CStack<int> mystack)
{
    while (!mystack.isEmpty())
    {
        snode<int> num = mystack.top();
        cout << num.x << num.y << endl;
        mystack.pop();
    }
}

void reverseStack(CStack<snode<int>> &destination)
{
    CStack<snode<int>> temp;
    //int num;
    while (!destination.isEmpty())
    {
        snode<int> coor;
        coor.x = destination.top().x;
        coor.y = destination.top().y;
        destination.pop();
        temp.push(coor);
    }
    destination = temp;
}

bool isVisited(int x, int y, CStack<snode<int>> road)
{
    while(!road.isEmpty())
    {
        snode<int> cor = road.top();
        road.pop();
        
        if(x == cor.x & y == cor.y)
            return true;
    }
    return false;
}


void movingTo(int i, int j, CStack<snode<int>> &road)
{
    snode<int> coor;
    if (road.isEmpty())
    {
        road.push(coor);
    }
    
    cout << "Moving to " << "(" << i << "," << j << ")\n";
    
    int x = road.top().x;
    int y = road.top().y;
    
    if (x < i){
        for (x++; x != i; x++)
        {
            coor.x = x;
            coor.y = y;
            road.push(coor);
            cout << "(" << road.top().x << "," << road.top().y << ")\n";
        }
    }
    else{
        for (x--; x != i; x--)
        {
            coor.x = x;
            coor.y = y;
            road.push(coor);
            cout << "(" << road.top().x << "," << road.top().y << ")\n";
        }
    }
    if (y < j){
        for (;y != j; y++)
        {
            coor.x = x;
            coor.y = y;
            road.push(coor);
            cout << "(" << road.top().x << "," << road.top().y << ")\n";
        }
    }
    else{
        for (;y != j; y--)
        {
            coor.x = x;
            coor.y = y;
            road.push(coor);
            cout << "(" << road.top().x << "," << road.top().y << ")\n";
        }
    }
    cout << "Arrived to " << "(" << i << "," << j << ")\n";
    coor.x = x;
    coor.y = y;
    road.push(coor);
}

void timeTravel(int i, int j, CStack<snode<int>> &road)
{
    cout << "Time travel back to " << "(" << i << "," << j << ")\n";
    while(!road.isEmpty() && (road.top().x != i || road.top().y != j))
    {
        road.pop();
    }
}

void backHome(CStack<snode<int>> &road)
{
    cout << "Back to (0,0)\n";
    road.pop();
    while (!road.isEmpty() && (road.top().x != 0 || road.top().y != 0))
    {
        cout << road.top().x << "," << road.top().y << "\n";
        road.pop();
    }
    cout << "Home sweet home\n";
}

int main()
{
    CStack<snode<int>> destination;
    CStack<snode<int>> road;
    string filename;
    cout << "Enter the input file name\n";
    cin >> filename;
    //string filename = "input.txt";
    if (!fileFail(filename))
        cout << "Cannot open the file" << endl;
    else
        destination = getData(filename);
    reverseStack(destination);

    while (!destination.isEmpty())
    {
        snode<int> cor = destination.top();
        destination.pop();
        
        if (isVisited(cor.x, cor.y, road))
            timeTravel(cor.x, cor.y, road);
        else
            movingTo(cor.x, cor.y, road);
    }
    backHome(road);
    
    return 0;
}
