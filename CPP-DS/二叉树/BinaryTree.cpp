#include <iostream>
#include <queue>

//二叉链结构
template<class T>
struct BinaryTreeNode
{
    BinaryTreeNode(const T& data = T())
        :_data(data)
        ,_left(nullptr)
        ,_right(nullptr)
    {}
    T _data;
    BinaryTreeNode<T>* _left;
    BinaryTreeNode<T>* _right;
};

template<class T>
class BinaryTree
{
public:
    BinaryTree()
        :_head(nullptr)
        ,_size(0)
    {}
    BinaryTree(const std::string& preOrder)
    {
        int i = 0;
        _head = CreateByPreOrder(preOrder, i);
    }
    //前序遍历
    void PreOrder()
    {
        PreOrderCore(_head);
    }
    //中序遍历
    void InOrder()
    {
        InOrderCore(_head);
    }
    //后序遍历
    void PostOrder()
    {
        PostOrderCore(_head);
    }
    //层序遍历
    void LevelOrder()
    {
        std::queue<BinaryTreeNode<T>*> que;
        que.push(_head);
        while(!que.empty())
        {
            BinaryTreeNode<T>*temp = que.front();
            que.pop();
            if(temp == nullptr)
            {
                std::cout << "#";
            }
            else 
            {
                std::cout << (char)(temp->_data + 'A');
                que.push(temp->_left);
                que.push(temp->_right);
            }
        }
    }
    //判断是不是一棵完全二叉树
    //层序遍历二叉树，遍历到第一个nullptr结点，
    //就遍历整个队列，如果全为空则是完全二叉树
    //否则就不是
    bool IsComplateTree()
    {
        std::queue<BinaryTreeNode<T>*> que;
        que.push(_head);
        while(!que.empty())
        {
            BinaryTreeNode<T>* temp = que.front();
            que.pop();
            if(temp == nullptr)
            {
                break;
            }
            else
            {
                que.push(temp->_left);
                que.push(temp->_right);
            }
        }
        while(!que.empty())
        {

            BinaryTreeNode<T>* temp = que.front();
            que.pop();
            if(temp != nullptr)
            {
                return false;
            }
        }
        return true;
    }
private:
    void InOrderCore(BinaryTreeNode<T>* root)
    {
        if(root == nullptr)
        {
            std::cout << "#";
            return;
        }
        InOrderCore(root->_left);
        std::cout << (char)(root->_data + 'A');
        InOrderCore(root->_right);
    }
    void PreOrderCore(BinaryTreeNode<T>* root)
    {
        if(root == nullptr)
        {
            std::cout << "#";
            return;
        }
        std::cout << (char)('A' + root->_data);
        PreOrderCore(root->_left);
        PreOrderCore(root->_right);
    }
    void PostOrderCore(BinaryTreeNode<T>* root)
    {
        if(root == nullptr)
        {
            std::cout << "#";
            return;
        }
        PostOrderCore(root->_left);
        PostOrderCore(root->_right);
        std::cout << (char)('A' + root->_data);
    }
    BinaryTreeNode<T>* CreateByPreOrder(const std::string& preOrder, int& i)
    {
        if(preOrder[i] != '#')
        {
            BinaryTreeNode<T>* root = new BinaryTreeNode<T>(preOrder[i] - 'A');
            root->_left = CreateByPreOrder(preOrder, ++i);
            root->_right = CreateByPreOrder(preOrder, ++i);
            return root;
        }
        else 
        {
            return nullptr;
        }
    }
private:
    BinaryTreeNode<T>* _head;           //与链表一样存储一个头结点即可
    size_t _size;                   //节点个数
};


int main()
{
    BinaryTree<int> tree("ABD##E##CF##G##");
    tree.PreOrder();
    std::cout << std::endl;
    tree.InOrder();
    std::cout << std::endl;
    tree.PostOrder();
    std::cout << std::endl;
    tree.LevelOrder();
    std::cout << std::endl;
    std::cout << "Is Complate Tree: " << tree.IsComplateTree() << std::endl;;
}