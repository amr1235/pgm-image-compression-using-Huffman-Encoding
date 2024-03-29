#include<iostream>
#include<fstream>
#include<string.h>
#include <vector>
using namespace std;

struct for_encoding {
 map <unsigned char, int > freq_table;
 vector<int> encoding_table;
}Freq;
void write_freq_table(string filename){

ifstream ifile;
 string data;
ifile.open(filename);
getline(ifile,data);
if (data == "P5")     P5_freq_table(filename);
else if (data == P2)  P2_freq_table(filename);
}
/****************************************************/


for_encoding P2_freq_table(string filename){
ifstream ifile;
string data; int m[2] ; int j=0;
ifile.open(filename );
getline(ifile,data);
getline(filename, data); 
unsigned char * temp = data;
for(int i=0 ; i<data.length(); i++){
  if(*temp = ' ')
    temp ++;
  else
  {
   m[j] = stoi(*temp);
   temp++; j++;
   }}
getline(ifile , data); m[3]= stoi(data);
//map <unsigned char , int> frequency_count;

while (!ifile.eof())
{
  getline(ifile , data);
  temp = data;
  for(int i=0 ; i< data.length() ; i++){
    if( *temp == ' ')  temp++;
      else
        {Freq.freq_table[*temp]++; temp++; Freq.encoding_table.push_back(*temp); }
      }  
}
for(Freq.freq_table :: iterator it = Freq.freq_table.begin(); it != Freq.freq_table.end(); it++)
  cout<<it->first<<"->"<<it->second<<endl;
  ifile.close();
  return Freq;}
/******************************************************************/


for_encoding P5_freq_table(string filename){
ifstream ifile;
string data; unsigned char x;
ifile.open(filename , ios::binary);
getline(ifile,data);
getline(ifile,data);
getline( ifile , data );
while (!ifile.eof()){
  x=ifile.get();
  Freq.freq_table[(unsigned char)x]++;
  Freq.encoding_table.push_back((unsigned char)x);
}
for(map<unsigned char , int>:: iterator it = Freq.freq_table.begin(); it != Freq.freq_table.end(); it++){
  cout<<(unsigned char) it->first<<"->"<<(unsigned char)it->second<<endl;}
  ifile.close();
  return Freq;
}
/***************************************************************/

int main()
{
  cout<< "please put the image in the same file with the source file"<<endl;
  string file_name;
  cin>> file_name;
  write_freq_table(file_name);
}
