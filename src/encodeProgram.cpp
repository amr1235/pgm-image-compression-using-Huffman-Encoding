#include <iostream>
#include <string>
#include <map>
#include "lib/handlepgmfile.hpp"
#include "lib/priority_queue.hpp"
#include "lib/huffman.hpp"

int main(){

    //get file name
    std::cout<< "please put the image in the same file with the source file"<< std::endl<<"Enter file Name ";
    std::string file_name;
    std::cin>> file_name;

    // get data from the file
    for_encoding Data;

    std::ifstream ifile;
    std::string data;
    ifile.open(file_name , std::ios::binary);
    getline(ifile,data);

    if (data[1] == '5'){ 
        Data =  P5_freq_table(file_name);
    } else if (data[1] == '2'){
        Data =  P2_freq_table(file_name);
    }

    std::cout << Data.width << " " << Data.height << std::endl << Data.maxVal << std::endl ;

    //data 
    std::map<unsigned char,int> FreqTable = Data.freq_table ;
    std::vector<unsigned char> values     = Data.encoding_table ;
    
    //get file name whiout exetention
    for (size_t i = 0; i < 4; i++)
    {
        file_name.pop_back();
    }
    
    //creat min heap
    huffman<unsigned char> huffMan ; 
    min_heap<unsigned char> Qu ;

    //insert freq table to git the min heap 
    huffMan.insertFreqTableToMinHeap(FreqTable,Qu);

    //create encode file
    int W ,H , M;
    W = std::stoi(Data.width); 
    H = std::stoi(Data.height); 
    M = std::stoi(Data.maxVal); 
    huffMan.creatEncodedFile(file_name,values,Qu,W,H,M);
    

    //create freq File 
    huffMan.creatFrequancyFile(FreqTable,file_name);

    return 0;
}