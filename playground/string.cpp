#include<iostream>
#include<fstream>

using namespace std;
int main(int argc, char** argv){
     ifstream file;
     file.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit);
     try{
           file.open("string.cpp");
           char buf[256];
           while (file.getline(buf,100)) 
		cout << buf << endl;
     }catch (const ifstream::failure& e) {
           cout << "Reading file error!" << endl;
           return -1;
     }
     file.close();
     return argc;
}	

