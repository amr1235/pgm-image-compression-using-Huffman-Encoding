#include<iostream>
#include<fstream>
#include<string.h>
#include <vector>
using namespace std;


void write_freq_table(string filename){

ifstream ifile;
 string data;
ifile.open(filename);
getline(ifile,data);
if (data == "P5")     P5_freq_table(filename);
else if (data == P2)  P2_freq_table(filename);
}
/****************************************************/


void P2_freq_table(string filename){
ifstream ifile;
string data; int m[2] ; int j=0;

ifile.open(filename );
getline(ifile,data);
getline(filename, data); 
unsigned char * temp = data;
for(int i=0 ; i<data.length(); i++){
if(*temp = " ")
temp ++;
else
{
  m[j] = stoi(*temp);
  temp++; j++;
}}
getline(ifile , data); m[3]= stoi(data);
map<unsigned char , int> frequency_count;
vector<unsigned char> key_values;
 while (!ifile.eof())
    {
      getline(ifile , data);
      temp = data;
      for(int i=0 ; i< data.length() ; i++){
        if( *temp == ' ')  temp++;
        else
         {frequency_count[*temp]++; temp++; key_values.push_back(*temp); }
      }  
      }
      for(map<unsigned char,int>:: iterator it = frequency_count.begin(); it != frequency_count.end(); it++)
        cout<<it->first<<"->"<<it->second<<endl;
      ifile.close();}
/******************************************************************/


void P5_freq_table(string filename){
ifstream ifile;
string data; int num_of_colors=0 ; int m[4];
ifile.open(filename , ifstream::binary);
getline(ifile,data);
getline( ifile , data );
char * temp = data;
for(int i=0 ; i<data.length(); i++){
if(*temp = " ")
temp ++;
else
{
  m[j] = stoi(*temp);
  temp++; j++;
}}
num_of_colors = m[0] * m[1];
char x=0;
map<int , int> frequency_count;
  for (int i=0; i<num_of_colors ; i++){
    ifile.get(&x,sizeof(char));
    frequency_count[x]++;
    key_values.push_back(x);

}
 for(map<int,int>:: iterator it = frequency_count.begin(); it != frequency_count.end(); it++){
  cout<<it->first<<" "<<it->second<<endl;}
ifile.close();}
/***************************************************************/

int main()
{
  cout<< "please put the image in the same file with the source file"<<endl;
  string file_name;
  cin>> file_name;
  write_freq_table(file_name);
}
