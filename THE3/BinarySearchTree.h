#ifndef _BinarySearchTree
#define _BinarySearchTree
#include<iostream>
#include<string>
using namespace std;

template <class Object>
class BinaryNode
{
    Object  element;
    BinaryNode  *left;
    BinaryNode  *right;

    BinaryNode( const Object & theElement, BinaryNode *lt, BinaryNode *rt )
            : element( theElement ), left( lt ), right( rt )
    { };

    template<class Comparable> friend class BinarySearchTree;
};

template <class Comparable>
class BinarySearchTree
{
public:
    explicit BinarySearchTree( const Comparable & notFound );
    BinarySearchTree( const BinarySearchTree & rhs );
    ~BinarySearchTree( );

    const Comparable & findMin( ) const;
    const Comparable & findMax( ) const;
    Comparable & find( const Comparable & x );
    //bool isEmpty( ) const;
    //void printTree( ) const;

    void makeEmpty( );
    void insert( const Comparable & x );
    void remove( const Comparable & x );

    //const BinarySearchTree & operator =( const BinarySearchTree & rhs );
    Comparable ITEM_NOT_FOUND;

private:
    BinaryNode<Comparable> *root;


    Comparable & elementAt( BinaryNode<Comparable> *t );

    void insert( const Comparable & x, BinaryNode<Comparable> * & t ) const;
    void remove( const Comparable & x, BinaryNode<Comparable> * & t ) const;
    BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *t ) const;
    BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *t ) const;
    BinaryNode<Comparable> * find( const Comparable & x, BinaryNode<Comparable> *t );
    void makeEmpty( BinaryNode<Comparable> * & t ) const;
    //void printTree( BinaryNode<Comparable> *t ) const;
    //BinaryNode<Comparable> * clone( BinaryNode<Comparable> *t ) const;

};

//#include"BinarySearchTree.cpp"

//CONSTRUCTOR
template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const Comparable & notFound )
        :ITEM_NOT_FOUND( notFound ), root( NULL )
{}

//DESTRUCTOR
template <class Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree( )
{
    makeEmpty();
}

//COPY CONSTRUCTOR
template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree( const BinarySearchTree<Comparable> & rhs )
        :root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
{
    *this = rhs;
}

/**
    * Internal method to get element field in node t.
    * Return the element field or ITEM_NOT_FOUND if t is NULL.
    */
template <class Comparable>
Comparable & BinarySearchTree<Comparable>::elementAt( BinaryNode<Comparable> *t )
{
    return t == NULL ? ITEM_NOT_FOUND : t->element;
}

/**
* Find item x in the tree.
* Return the matching item or ITEM_NOT_FOUND if not found.
*/
template <class Comparable>
Comparable & BinarySearchTree<Comparable>::find( const Comparable & x )
{
    return elementAt( find( x, root ) );
}

/**
* Internal method to find an item in a subtree.
* x is item to search for.
* t is the node that roots the tree.
* Return node containing the matched item.
*/
template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::find( const Comparable & x, BinaryNode<Comparable> * t )
{
    if ( t == NULL )
        return NULL;
    else if( x < t->element )
        return find( x, t->left );
    else if( t->element < x )
        return find( x, t->right );
    else
        return t;    // Match
}

/**
* Find the smallest item in the tree.
* Return smallest item or ITEM_NOT_FOUND if empty.
*/
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::findMin( ) const
{
    return elementAt( findMin( root ) );
}

/**
* Internal method to find the smallest item in a subtree t.
* Return node containing the smallest item.
*/
template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::findMin( BinaryNode<Comparable> *t ) const
{
    if( t == NULL )
        return NULL;
    if( t->left == NULL )
        return t;
    return findMin( t->left );
}

/**
* Find the greatest item in the tree.
* Return greatest item or ITEM_NOT_FOUND if empty.
*/
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax( ) const
{
    return elementAt( findMax( root ) );
}
/**
* Internal method to find the greatest item in a subtree t.
* Return node containing the greatest item.
*/
template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::findMax( BinaryNode<Comparable> *t ) const
{
    if( t == NULL )
        return NULL;
    if( t->right == NULL )
        return t;
    return findMax( t->left );
}

/**
* Insert x into the tree; duplicates are ignored.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::insert( const Comparable & x )
{
    insert( x, root );
}

/**
    * Internal method to insert into a subtree.
    * x is the item to insert.
    * t is the node that roots the tree.
    * Set the new root.
    */

template <class Comparable>
void BinarySearchTree<Comparable>::insert( const Comparable & x, BinaryNode<Comparable> * & t ) const
{
    if( t == NULL ) //  create a new node at the right place
        t = new BinaryNode<Comparable>( x, NULL, NULL );
    else if( x < t->element )
        insert( x, t->left );  // insert at the left or
    else if( t->element < x )
        insert( x, t->right );  // right subtree
    else
        ;  // Duplicate; do nothing
}

/**
* Remove x from the tree. Nothing is done if x is not found.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::remove( const Comparable & x )
{
    remove( x, root );
}

/**
    * Internal method to remove from a subtree.
    * x is the item to remove.
    * t is the node that roots the tree.
    * Set the new root.
    */
template <class Comparable>
void BinarySearchTree<Comparable>::remove( const Comparable & x, BinaryNode<Comparable> * & t ) const
{
    if( t == NULL )
        return;   // Item not found; do nothing
    if( x < t->element )
        remove( x, t->left );
    else if( t->element < x )
        remove( x, t->right );
}

/**
* Make the tree logically empty.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty( )
{
    makeEmpty( root );
}

/**
* Internal method to make subtree empty.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::
makeEmpty( BinaryNode<Comparable> * & t ) const
{
    if( t != NULL )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = NULL;
}



#endif
