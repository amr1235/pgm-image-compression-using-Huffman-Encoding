#ifndef __HuffmanTree__
#define __HuffmanTree__

template<class valueType>
class huffman_tree
{
private:
    struct node{
        valueType value;
        int frequancy;
        node* left;
        node* right;
    }; 
    node* root; 
public:
    huffman_tree(/* args */); 
    
};

template<class valueType>
huffman_tree <valueType>::huffman_tree(/* args */)
{
    
}




#endif