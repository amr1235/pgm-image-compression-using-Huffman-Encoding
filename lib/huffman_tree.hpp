#ifndef __HuffmanTree__
#define __HuffmanTree__

template<class valueType>
struct node{
        valueType value;
        int frequancy;
        node* left;
        node* right;
    };

template<class valueType>   
class huffman_tree
{
private:
    node<valueType> * root;
public:
    huffman_tree(/* args */); 
    node<valueType> * creatNode(valueType value,int frequancy); // using this function to creat a node to insert it to the tree 
    void insert(node<valueType>* root,node<valueType>* leftChild,node<valueType> rightChild); // to insert you need the root and left and right child
};

template<class valueType>
huffman_tree <valueType>::huffman_tree(/* args */) // constructor of the class
{
    root = nullptr;
}

template<class valueType>
node<valueType> * huffman_tree<valueType>::creatNode(valueType value,int frequancy){
    node<valueType> n;
    n.value = value;
    n.frequancy = frequancy;
    n.left = nullptr;
    n.right = nullptr;
    return &n;
}

template<class valueType>
void huffman_tree<valueType>::insert(node<valueType>* sumNode,node<valueType>* leftChild,node<valueType> rightChild){
    root = sumNode;
    root->left = leftChild;
    root->right = rightChild;
}


#endif