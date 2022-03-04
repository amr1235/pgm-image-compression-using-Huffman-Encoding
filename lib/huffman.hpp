#ifndef __HuffmanTree__
#define __HuffmanTree__
#include "priority_queue.hpp"
#include <map>
#include <bitset>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

template<class valueType>   
class huffman
{
private:
    void hufmaanEncoding(heapNode<valueType> * root,std::string str,std::map<valueType, std::string> &huffmanCode);
    void decode(heapNode<valueType> * root, int &index, std::string str);
    void buildHuffManTreeAndGetEncodedStringTable(min_heap<valueType>  &Qu, std::map<valueType,std::string> &encodedStringData);
public:
    void creatEncodedFile(std::string fileName,std::vector<valueType> &Data,min_heap<valueType> &Qu,int width,int height,int maxVal);
    void decodeFileAndReturnVectorOfPxls(std::string encfileName,std::string freqFilename,std::vector<valueType> &pxlsStream , int &width,int &height , int &maxVal);
    void creatFrequancyFile(std::map<valueType,int> &freqTable,std::string fileName);
    void insertFreqTableToMinHeap(std::map<valueType,int> &freqTable , min_heap<valueType> &Qu);
    void readFrequancyFileAndGetFreqTable(std::string fileName,std::map<unsigned char,int> &freqTable);
    void creatPGMFile(std::string encFileName,std::string freqFileName);
};



//build tree of huffman
template<class valueType>
void huffman<valueType>::buildHuffManTreeAndGetEncodedStringTable(min_heap<valueType>  &Qu, std::map<valueType,std::string> &encodedStringData){  // [{'a',2},{'b',5},{'c',12},{'d',20},{'e',30},{'f',40}]

    heapNode<valueType> * left , * right , * sumNode;
    while (Qu.size() != 1)
    {
        //first extract node from the min heap and make it the left child
        left = Qu.Extraction();
        // then extrach node from the heap and make it second Child 
        right = Qu.Extraction();
        //creat new node of sum last two nodes
        sumNode = (heapNode<valueType>*)malloc(sizeof(heapNode<valueType>)); 
        sumNode->frequancy = (left->frequancy + right->frequancy);
        sumNode->value = '$';
        sumNode->leftChild = left;
        sumNode->rightChild = right;
        //insert the new node to the heap 
        Qu.Insertion(sumNode);
    }
        
    heapNode<valueType> * k = Qu.Extraction();
    hufmaanEncoding(k,"",encodedStringData);
}


//traverse huffman tree
template<class valueType>
void huffman<valueType>::hufmaanEncoding(heapNode<valueType> * root,std::string str,std::map<valueType, std::string> &huffmanCode){

    // std::cout << root->leftChild->frequancy << std::endl;

    if(root->leftChild)
        hufmaanEncoding(root->leftChild, str  + "0" , huffmanCode);

    if(root->rightChild)
        hufmaanEncoding(root->rightChild, str + "1", huffmanCode);

    if ( !(root->leftChild) && !(root->rightChild)) {
		huffmanCode[root->value] = str;
	}

}



//create .enc file
template<class valueType>
void huffman<valueType>::creatEncodedFile(std::string fileName,std::vector<valueType> &Data,min_heap<valueType> &Qu,int width,int height,int maxVal){
    std::map<valueType,std::string> map ;

    buildHuffManTreeAndGetEncodedStringTable(Qu,map);
    
    std::string totalBits = "";
    for (size_t i = 0; i < Data.size(); i++)
    {
        valueType px = Data[i];
        std::string bits = map[px];
        totalBits += bits;
    }

    //now we have the encoded bits in string like this "1110110101010111001111000"
    std::ofstream output(fileName + ".enc", std::ios::out | std::ios::binary );
    if(!output){
        exit(1);
    }

    //write header info
    output << width << std::endl << height << std::endl << maxVal << std::endl;

    int n = 0;
    unsigned char value = 0;
    for(auto c : totalBits)
    {
        value |= static_cast<unsigned char>(c == '1') << n;
        if(++n == 8)
        {
            output.write(reinterpret_cast<const char*>(&value),sizeof(value));
            n = 0;
            value = 0;
        }
    }
    if(n != 0)
    {
        // one partial byte left
            output.write(reinterpret_cast<const char*>(&value),sizeof(value));
    }
    output.close();
    
}


//insert freq table to min heap
template<class valueType> 
void huffman<valueType>::insertFreqTableToMinHeap(std::map<valueType,int> &freqTable , min_heap<valueType> &Qu){
    typename std::map<valueType,int>::iterator it = freqTable.begin();
    while (it != freqTable.end())
    {
        heapNode<valueType> * node = (heapNode<valueType>*)malloc(sizeof(heapNode<valueType>));
        node->frequancy = it->second;
        node->value = it -> first;
        node->leftChild = nullptr;
        node->rightChild = nullptr;
        Qu.Insertion(node);
        it++;
    }
    
}

//return the vector of bytes from enc file
template<class valueType> 
void huffman<valueType>::decodeFileAndReturnVectorOfPxls(std::string encfileName,std::string freqFilename,std::vector<valueType> &pxlsStream , int &width,int &height , int &maxVal){

    //get frequancyTable 
    std::map<unsigned char,int> freqTable;
    readFrequancyFileAndGetFreqTable(freqFilename,freqTable);


    //put freqtable to min heap 
    min_heap<valueType> PQ ;
    insertFreqTableToMinHeap(freqTable,PQ);


    //build haffMan Tree
    heapNode<valueType> * left , * right , * sumNode;
    while (PQ.size() != 1)
    {
        //first extract node from the min heap and make it the left child
        left = PQ.Extraction();
        // then extrach node from the heap and make it second Child 
        right = PQ.Extraction();
        //creat new node of sum last two nodes
        sumNode = (heapNode<valueType>*)malloc(sizeof(heapNode<valueType>)); 
        sumNode->frequancy = (left->frequancy + right->frequancy);
        sumNode->value = '$';
        sumNode->leftChild = left;
        sumNode->rightChild = right;
        //insert the new node to the heap 
        PQ.Insertion(sumNode);
    }

    //now as soon as we do extraction we get root pointer
    heapNode<valueType> * root = PQ.Extraction();

    //read encfile  
    std::ifstream file(encfileName, std::ios::binary | std::ios::in);
    std::string totalbits ;

    //get width and height and size of the file
    std::string w , H , M;
    getline(file,w);
    getline(file,H);
    getline(file,M);

    width = std::stoi(w);
    height = std::stoi(H);
    maxVal = std::stoi(M);

    //get string of bits
    char c;
    while (file.get(c))
    {
        for (int i = 7; i >= 0; i--) {// or (int i = 0; i < 8; i++)  if you want reverse bit order in bytes
            int bit = ((c >> i) & 1);
            char b = std::to_string(bit)[0];
            totalbits.push_back(b);
        }
    }
    

    //now we have string of bits(totalBits) and root of haffmantree (root)
    heapNode<valueType> * curr = root;
    for (int i = 0; i < totalbits.size(); i++)
    {
        if(totalbits[i] == '0'){
            root = root->leftChild;
        }
        if(totalbits[i] == '1'){
            root = root->rightChild;
        }
        if(!root->leftChild && !root->rightChild){
            pxlsStream.push_back(root->value);
            //reset root
            root = curr;
        }
    }
    
}


template<class valueType>
void huffman<valueType>::creatPGMFile(std::string encFileName,std::string freqFileName){

    int width , height , maxVal ;
    std::vector<valueType> pxls;

    decodeFileAndReturnVectorOfPxls(encFileName,freqFileName,pxls,width,height,maxVal);

    //know we hav all information

    //getfile name whithout extention
    for (size_t i = 0; i < 4; i++)
    {
        encFileName.pop_back();
    }
    
    //create output fine
    std::ofstream PGM(encFileName + ".pgm",std::ios::binary);
    //write header info
    PGM << "P5" << std::endl << width << " " << height << std::endl << maxVal << std::endl;
    //write binary data 
    for (size_t i = 0; i < pxls.size(); i++)
    {
        PGM.write(reinterpret_cast<const char*>(&pxls[i]),1);
    }
    PGM.close();

}

template<class valueType>
void huffman<valueType>::readFrequancyFileAndGetFreqTable(std::string fileName,std::map<unsigned char,int> &freqTable){
    std::ifstream file(fileName);
    if(!file){
        exit(1);
    }
    std::string line;
    while (std::getline(file,line))
    {   
        auto to = line.find(' ');
        std::string value = line.substr(0,to);
        std::string freq = line.substr(to + 1);
        std::istringstream st(freq);
        int fr = 0;
        st >> fr;
        freqTable[value[0]] = fr;
    }
    
}

//create Frequancy File (.json)
template<class valueType>
void huffman<valueType>::creatFrequancyFile(std::map<valueType,int> &freqTable,std::string fileName){

    std::ofstream file;
    file.open(fileName+".txt");

    typename std::map<valueType,int>::iterator it = freqTable.begin();
    while (it != freqTable.end())
    {
        file << (unsigned) it->first << " " << it->second << " \n";
        it++;
    }
    
}



#endif