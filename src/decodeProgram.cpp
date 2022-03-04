#include <iostream>
#include "lib/priority_queue.hpp"
#include "lib/huffman.hpp"

int main(){
    std::string encFileName ;
    std::cout << " please enter the enc file name " << std::endl;
    std::cin >> encFileName;
    std::string freqFileName;
    std::cout << " please enter the freq file name " << std::endl;
    std::cin >> freqFileName ;
    huffman<unsigned char> huffMan;
    
    
    huffMan.creatPGMFile(encFileName,freqFileName);
    
}