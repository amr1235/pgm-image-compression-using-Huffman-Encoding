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
    node<valueType> * creatNode(valueType value,int frequancy);
};

template<class valueType>
huffman_tree <valueType>::huffman_tree(/* args */)
{
    
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


#endif