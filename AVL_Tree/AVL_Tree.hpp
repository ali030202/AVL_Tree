#pragma once
#include<iostream>
#include<queue>
template <typename Type>
struct AVLTreeNode
{
    Type AVL_Date;                  // 关键字
    int AVL_hight;             // 高度
    AVLTreeNode* AVL_leftChild; // 左孩子
    AVLTreeNode* AVL_rightNode; // 右孩子
    constexpr AVLTreeNode(Type value, AVLTreeNode* left, AVLTreeNode* right)noexcept : AVL_Date(value), AVL_hight(0), AVL_leftChild(left), AVL_rightNode(right) {}
};
template <typename Type>
class AVLTree
{
public:
    constexpr AVLTree()noexcept : AVL_root(NULL) {}
    ~AVLTree() noexcept { destroy(AVL_root); }
public:
    void pre_order() { preorder(this->AVL_root); };//前序
    void in_order() { inorder(this->AVL_root); };//中序
    void last_order() { lastorder(this->AVL_root); }//后序
    void level_order() { levelorder(this->AVL_root); }//层次
    int hight() { Hight(this->AVL_root); };//求高度
    void exchange_child() { exchange(this->AVL_root); };
    void insert(Type Data) { this->AVL_root = Insert(this->AVL_root, Data); }//插入元素
private:
    AVLTreeNode<Type>*& LL_Rotation(AVLTreeNode<Type>*& node)
    {
        auto temp = node->AVL_leftChild;
        node->AVL_leftChild = temp->AVL_rightNode;
        temp->AVL_rightNode = node;
        temp->AVL_hight = ::std::max(Hight(temp->AVL_leftChild), Hight(temp->AVL_rightNode)) + 1;
        node->AVL_hight = ::std::max(Hight(node->AVL_leftChild), Hight(node->AVL_rightNode)) + 1;
        return temp;
    }
    AVLTreeNode<Type>*& RR_Rotation(AVLTreeNode<Type>*& node)
    {
        auto temp = node->AVL_rightNode;
        node->AVL_rightNode = temp->AVL_leftChild;
        temp->AVL_leftChild = node;
        temp->AVL_hight = ::std::max(Hight(temp->AVL_leftChild), Hight(temp->AVL_rightNode)) + 1;
        node->AVL_hight = ::std::max(Hight(node->AVL_leftChild), Hight(node->AVL_rightNode)) + 1;
        return temp;
    }
    AVLTreeNode<Type>*& RL_Rotation(AVLTreeNode<Type>*& node)
    {
        node->AVL_rightNode = this->LL_Rotation(node->AVL_rightNode);
        return this->RR_Rotation(node);
    }
    AVLTreeNode<Type>*& LR_Rotation(AVLTreeNode<Type>*& node)
    {
        node->AVL_leftChild = this->RR_Rotation(node->AVL_leftChild);
        return this->LL_Rotation(node);
    }
private:
    void preorder(AVLTreeNode<Type>* root)
    {
        if (root == nullptr)
        {
            return;
        }
        ::std::cout << root->AVL_Date<<" ";
        preorder(root->AVL_leftChild);
        preorder(root->AVL_rightNode);
    }
    void inorder(AVLTreeNode<Type>* root)
    {
        if (root == nullptr)
        {
            return;
        }
        inorder(root->AVL_leftChild);
        ::std::cout << root->AVL_Date<<" ";
        inorder(root->AVL_rightNode);
    }
    void lastorder(AVLTreeNode<Type>* root)
    {
        if (root == NULL)
        {
            return;
        }
        lastorder(root->AVL_leftChild);
        lastorder(root->AVL_rightNode);
        ::std::cout << root->AVL_Date << " ";
    }
    void levelorder(AVLTreeNode<Type>* root)
    {
        ::std::queue<AVLTreeNode<Type>*>Que;
        if (root != NULL)
        {
            Que.push(root);
        }
        while (!Que.empty())
        {
            AVLTreeNode<Type>* ptr = Que.front();
            ::std::cout << ptr->AVL_Date<<" ";
            if (ptr->AVL_leftChild!=NULL)
            {
                Que.push(ptr->AVL_leftChild);
            }
            if(ptr->AVL_rightNode != NULL)
            {
                Que.push(ptr->AVL_rightNode);
            }
            Que.pop();
        }
    }
    void exchange(AVLTreeNode<Type>* root)
    {
        if (root == NULL)
        {
            return;
        }
        else
        {
            auto temp = root->AVL_leftChild;
            root->AVL_leftChild = root->AVL_rightNode;
            root->AVL_rightNode = temp;
            exchange(root->AVL_leftChild);
            exchange(root->AVL_rightNode);
        }
    }
    int Hight(AVLTreeNode<Type>* root)
    {
        if (root == NULL)
        {
            return 0;
        }
        auto left_hight = Hight(root->AVL_leftChild);
        auto right_hight = Hight(root->AVL_rightNode);
        return ::std::max(left_hight, right_hight) + 1;
    }
    AVLTreeNode<Type>*& Insert(AVLTreeNode<Type>*& root, Type& Data)
    {
        if (root == NULL)
        {
            root = new AVLTreeNode<Type>(Data, NULL, NULL);
            root->AVL_hight = ::std::max(Hight(root->AVL_leftChild), Hight(root->AVL_rightNode)) + 1;
            return root;
        }
        else if (Data > root->AVL_Date)
        {
            root->AVL_rightNode = Insert(root->AVL_rightNode, Data);
            if (this->Hight(root->AVL_rightNode) - this->Hight(root->AVL_leftChild) == 2||this->Hight(root->AVL_rightNode) - this->Hight(root->AVL_leftChild)==-2)
            {
                //旋转
                if (Data > root->AVL_rightNode->AVL_Date)
                {
                    //RR
                    return this->RR_Rotation(root);
                }
                else
                {
                    //RL
                    return this->RL_Rotation(root);
                }

            }
        }
        else if (Data < root->AVL_Date)
        {
            root->AVL_leftChild = Insert(root->AVL_leftChild, Data);
            if (this->Hight(root->AVL_rightNode) - this->Hight(root->AVL_leftChild) == 2|| this->Hight(root->AVL_rightNode) - this->Hight(root->AVL_leftChild) == -2)
            {
                //旋转
                if (Data > root->AVL_leftChild->AVL_Date)
                {
                    //LR
                    return this->LR_Rotation(root);
                }
                if (Data < root->AVL_leftChild->AVL_Date)
                {
                    // LL
                    return this->LL_Rotation(root);
                }
            }
        }
        root->AVL_hight = ::std::max(Hight(root->AVL_leftChild), Hight(root->AVL_rightNode)) + 1;
        return root;
    }
    void destroy(AVLTreeNode<Type>* root)
    {
        if (root == nullptr)
        {
            return;
        }
        destroy(root->AVL_leftChild);
        destroy(root->AVL_rightNode);
        delete root;
    }
private:
    AVLTreeNode<Type>* AVL_root;
};
