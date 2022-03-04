#ifndef handlePgmFile
#define handlePgmFile

#include<iostream>
#include<fstream>
#include <vector>
#include<map>

struct for_encoding {
 std::map <unsigned char, int > freq_table;
 std::vector<unsigned char> encoding_table;
 std::string width ;
 std::string height ;
 std::string maxVal ;
}Freq;
/****************************************************/


for_encoding P2_freq_table(std::string filename){
std::ifstream ifile;
std::string data; 
ifile.open( filename );
getline(ifile , data);
getline(ifile , data);
getline(ifile , data);
int a=0;
while (!ifile.eof())
{
  getline(ifile , data, ' ');
  a=stoi(data); 
  Freq.freq_table[ (unsigned char)a ]++ ; Freq.encoding_table.push_back( (unsigned char)a ); 
      
}
  ifile.close();
  return Freq;}

/******************************************************************/

for_encoding P5_freq_table(std::string filename){
std::ifstream ifile;
std::string data; unsigned char x;
ifile.open(filename , std::ios::binary);

getline(ifile,data);
getline(ifile,data);
int to = data.find(' ');
Freq.width = data.substr(0,to);
Freq.height = data.substr(to + 1);
getline(ifile,data);
Freq.maxVal = data;

while (!ifile.eof()){
  x=ifile.get();
  Freq.freq_table[(unsigned char)x]++;
  Freq.encoding_table.push_back((unsigned char)x);
}
  ifile.close();
  return Freq;
}

/***************************************************************/

#endif

