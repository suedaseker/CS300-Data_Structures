#ifndef TREE_H
#define TREE_H

#include <iostream>
using namespace std;

template <class Key, class Value> class AvlTree;

template <class Key, class Value>
class AvlNode{
    Key key;
    Value value;
    AvlNode* left;
    AvlNode* right;
    int height;
    AvlNode(Key k=Key(), Value v=Value(), AvlNode<Key, Value>* l=nullptr, AvlNode<Key, Value>* r=nullptr, int h=0 ): key(k), value(v), left(l), right(r), height(h){};

    friend class AvlTree<Key, Value>;
};

template <class Key, class Value>
class AvlTree
{
public:
    AvlTree();
    AvlTree(const AvlTree &rhs);
    ~AvlTree();
    
    const Value & findMin() const;
    const Value & findMax() const;
    const Value & find(const Key &x) const;
    
    bool isEmpty() const;
    void printTree() const;
    
    void makeEmpty();
    void insert(const Key &x, const Value &y);
    void remove(const Key &x);
    
    const AvlTree & operator=(const AvlTree & rhs);

private:
    AvlNode<Key, Value> *root;
    
    const Value & elementAt(AvlNode<Key, Value>* t) const;
    
    void insert(const Key &x, const Value &y, AvlNode<Key, Value>* &t) const;
    void remove(const Key &x, AvlNode<Key, Value>* &t) const;
    
    AvlNode<Key, Value>* findMin( AvlNode<Key, Value>* t) const;
    AvlNode<Key, Value>* findMax( AvlNode<Key, Value>* t) const;
    AvlNode<Key, Value>* find(const Key &x, AvlNode<Key, Value> *t) const;
    
    void makeEmpty(AvlNode<Key, Value>* &t) const;
    void printTree(AvlNode<Key, Value>* t) const;
    AvlNode<Key, Value>* clone(AvlNode<Key, Value>* t) const;
    
    int height(AvlNode<Key, Value>* t) const;
    int max(int lhs, int rhs) const;
    void rotateWithLeftChild(AvlNode<Key, Value>* &k2) const;
    void rotateWithRightChild(AvlNode<Key, Value>* &k1) const;
    void doubleWithLeftChild(AvlNode<Key, Value>* &k3) const;
    void doubleWithRightChild(AvlNode<Key, Value>* &k1) const;
};

//construct the tree
template <class Key, class Value>
AvlTree<Key, Value>::AvlTree() :root(NULL){}

//internal method to get element field in node t (private)
//return the element field or ITEM_NOT_FOUND if t is NULL
template <class Key, class Value>
const Value & AvlTree<Key, Value>::elementAt(AvlNode<Key, Value>* t) const
{
    return t == NULL ? NULL: t->value;
    //if t == NULL, return ITEM_NOT_FOUND, else return t->element
}

//find item x in the tree (public)
template <class Key, class Value>
const Value & AvlTree<Key, Value>::find(const Key &x) const
{
    return elementAt(find(x, root)); //these are private methods
}

//internal method to find an item in a subtree (private)
//x is item to search for, t is the node that roots the tree
//return node containing the matched item
template <class Key, class Value>
AvlNode<Key, Value>* AvlTree<Key, Value>::find(const Key &x, AvlNode<Key, Value>* t) const
{
    while (t != NULL)
        if (x < t->key)
            t = t->left;
        else if (t->key < x)
            t = t->right;
        else
            return t; //match
    
    return NULL; //no match
}

//find the smallest item in the tree (public)
//return smallest item or ITEM_NOT_FPUND if empty
template <class Key, class Value>
const Value & AvlTree<Key, Value>::findMin() const
{
    return elementAt(findMin(root)); //these are private methods
}

//internal method to find the smallest item in a subtree t (private)
//return node containing the smallest item
template <class Key, class Value>
AvlNode<Key, Value>* AvlTree<Key, Value>::findMin(AvlNode<Key, Value>* t) const
{
    if (t != NULL)
        while (t->left != NULL)
            t=t->left;
    return t;
}

//find the largest item in the tree (public)
//return largest item or ITEM_NOT_FPUND if empty
template <class Key, class Value>
const Value & AvlTree<Key, Value>::findMax() const
{
    return elementAt(findMax(root)); //these are private methods
}

//internal method to find the largest item in a subtree t (private)
//return node containing the largest item
template <class Key, class Value>
AvlNode<Key, Value>* AvlTree<Key, Value>::findMax(AvlNode<Key, Value>* t) const
{
    if (t != NULL)
        while (t->right != NULL)
            t=t->right;
    return t;
}

template <class Key, class Value>
int AvlTree<Key, Value>::height(AvlNode<Key, Value>* t) const
{
    if (t == NULL)
        return -1;
    return t->height;
}

//return maximum of lhs and rhs
template <class Key, class Value>
int AvlTree<Key, Value>::max(int lhs, int rhs) const
{
    if (lhs > rhs)
        return lhs;
    return rhs;
}


//internal method to insert into a subtree
//x is the item to insert, t is the node that roots the tree
//set the new root

/*
template <class Key, class Value>
void AvlTree<Key, Value>::insert(const Key &x, const Value &y, AvlNode<Key, Value>* &t) const
{
    if (t == NULL)
        t = new AvlNode<Key, Value>(x, y, NULL, NULL);
    else if (x < t->key)
    {
        insert(x, y, t->left); //x should be inserted to the left tree
        //check if the left tree is out of balance
        if (height(t->left)-height(t->right) == 2)
            if (x < t->left->key) //x was insterted to the left-left subtree
                rotateWithLeftChild(t);
            else                      //x was inserted to the left-right subtree
                doubleWithLeftChild(t);
    }
    else if (t->key < x)
    {
        insert(x, y, t->right); //otherwise x should be inserted to the right subtree
        //check if the right tree is out of balance
        if(height(t->right) - height(t->left) == 2)
            if (t->right->key < x) //x was insterted to the right-right subtree
                rotateWithRightChild(t);
            else                      //x was inserted to the right-left subtree
                doubleWithRightChild(t);
    }
    else
        ; //duplicate; do nothing
    
    //update the height of the node
    t->height = max(height(t->left), height(t->right)) + 1;
}*/

template <class Key, class Value>
void AvlTree<Key, Value>::insert(const Key &x, const Value &y, AvlNode<Key, Value>* &t) const{
    if (t==nullptr){
        t= new AvlNode<Key, Value>(x, y, NULL, NULL);
    }
    else if (x<t->key){
        // x should be inserted to left subtree;
        insert(x, y, t->left);
        // check if the left tree is out of balance (left subtree grew in height!!)
        if (height(t->left)-height(t->right)==2){
            if (x<t->left->key){
                rotateWithLeftChild(t);
            }
            else{
                doubleWithLeftChild(t);
            }
        }
    }
    else if (x>t->key){
        // x should be inserted to right subtree;
        insert(x, y, t->right);
        if (height(t->right)-height(t->left)==2){
            if (x>t->right->key){
                rotateWithRightChild(t);
            }
            else{
                doubleWithRightChild(t);
            }
        }
    }
    else
        ; // do nothing since dublication
    //updating the height of the node
    t->height=max(height(t->left),height(t->right))+1;
}

//insert x into the tree (public); duplicates are ignored
template <class Key, class Value>
void AvlTree<Key, Value>::insert(const Key &x, const Value &y)
{
    insert(x, y, root);
}

//remove x from the tree (public)
template <class Key, class Value>
void AvlTree<Key, Value>::remove(const Key &x){
    remove(x, root);
}

//remove x from the tree (private)
template <class Key, class Value>
void AvlTree<Key, Value>::remove(const Key &x, AvlNode<Key, Value>* &t) const
{
    if (t == NULL)
        return; //item not found, do nothing
    if (x < t->key)
        remove(x, t->left);
    else if (t->key < x)
        remove(x, t->right);
    else if (t-> right != NULL && t->left != NULL) { //item found, two children
        t->key = findMin(t->right)->key;
        remove(t->key, t->right);
    }
    else { //one or no children
        AvlNode<Key, Value>*  oldnode = t; //?
        if (t->left != NULL)
            t = t->left;
        else if (t->right != NULL)
            t = t->right;
        t = NULL;
        
        delete oldnode; //?
    }
}

/*
//rotate binary tree node with left child
//for AVL trees, this is a single rotation for case 1
//uodate heights, then set new root
template <class Key, class Value>
void AvlTree<Key, Value>::rotateWithLeftChild(AvlNode<Key, Value> *&k2) const
{
    AvlNode<Key, Value> *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}

//rotate binary tree node with right child
//for AVL trees, this is a single rotation for case 4
//uodate heights, then set new root
template <class Key, class Value>
void AvlTree<Key, Value>::rotateWithRightChild(AvlNode<Key, Value> *&k1) const
{
    AvlNode<Key, Value> *k2 = k1->right;
    k1->right = k2->right;
    k2->right = k1;
    k1->height = max(height(k1->right), height(k1->left)) + 1;
    k2->height = max(height(k2->right), k1->height) + 1;
    k1 = k2;
}

//double rotate binary tree
//first left child with its right child
//then node k3 with new left child
//for AVL trees, this is a double rotation for case 2
template <class Key, class Value>
void AvlTree<Key, Value>::doubleWithLeftChild(AvlNode<Key, Value> *&k3) const
{
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

//double rotate binary tree
//first right child with its left child
//then node k1 with new right child
//for AVL trees, this is a double rotation for case 3
template <class Key, class Value>
void AvlTree<Key, Value>::doubleWithRightChild(AvlNode<Key, Value> *&k1) const
{
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}
 */

template <class Key, class Value>
bool AvlTree<Key, Value>::isEmpty() const{
    return root==nullptr;
}

template <class Key, class Value>
void AvlTree<Key, Value>::makeEmpty(){
    makeEmpty(root);
}

template <class Key, class Value>
void AvlTree<Key, Value>::makeEmpty(AvlNode<Key, Value>* &t) const{
    if (t!=nullptr){
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t=nullptr;
}

template <class Key, class Value>
void AvlTree<Key, Value>::printTree() const{
    if (isEmpty()){
        cout<<"Empty tree"<<endl;
    }
    else{
        printTree(root);
    }
}

template <class Key, class Value>
void AvlTree<Key, Value>::printTree(AvlNode<Key, Value>* t) const{
    if (t!=nullptr){
        printTree(t->left);
        cout<<t->key<<" "<<t->value<< endl;;
        printTree(t->right);
    }
}

template <class Key, class Value>
AvlTree<Key, Value>::~AvlTree(){
    makeEmpty();
}

template <class Key, class Value>
AvlTree<Key, Value>::AvlTree(const AvlTree<Key, Value> & rhs): root(nullptr){
    *this=rhs;
}

template <class Key, class Value>
const AvlTree<Key, Value>& AvlTree<Key, Value>::operator=(const AvlTree<Key, Value>& rhs){
    if (this !=&rhs){
        makeEmpty();
        this->root=clone(rhs.root);
    }
    return *this;
}

template <class Key, class Value>
AvlNode<Key, Value>* AvlTree<Key, Value>::clone(AvlNode<Key, Value>* t) const{
    if (t==nullptr){
        return nullptr;
    }
    AvlNode<Key, Value>* tmp=new AvlNode<Key, Value>(t->key, t->value, clone(t->left), clone(t->right));
    return tmp;
}

template <class Key, class Value>
void AvlTree<Key, Value>::rotateWithLeftChild(AvlNode<Key, Value>* &k) const{
    AvlNode<Key, Value>* tmp = k->left;
    k->left=k->left->right;
    tmp->right=k;
    k->height=max(height(k->left), height(k->right))+1;
    tmp->height=max(height(tmp->left), height(k))+1;
    k=tmp;
}
template <class Key, class Value>
void AvlTree<Key, Value>::rotateWithRightChild(AvlNode<Key, Value>* &k) const{
    AvlNode<Key, Value>* tmp = k->right;
    k->right=k->right->left;
    tmp->left=k;
    k->height=max(height(k->left), height(k->right))+1;
    tmp->height=max(height(tmp->right),height(k))+1;
    k=tmp;
}
template <class Key, class Value>
void AvlTree<Key, Value>::doubleWithLeftChild(AvlNode<Key, Value>* &k) const{
    rotateWithRightChild(k->left);
    rotateWithLeftChild(k);
}
template <class Key, class Value>
void AvlTree<Key, Value>::doubleWithRightChild(AvlNode<Key, Value>* &k) const{
    rotateWithLeftChild(k->right);
    rotateWithRightChild(k);
}

#endif
