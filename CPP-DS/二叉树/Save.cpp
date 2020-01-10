#include <iostream>

//template<class T>
//struct BinaryTreeNode
//{
//    T _data;
//    BinaryTreeNode<T>* _left;
//    BinartTreeNode<T>* _right;
//};
template<class T>
struct BinaryTreeNode
{
    T _data;
    BinaryTreeNode<T>* _left;
    BinartTreeNode<T>* _right;
    BinartTreeNode<T>* _parent;//多了一个指向父亲的指针
};