#include<iostream>
#include<fstream>

using namespace std;
char* strs[] = {"main.ll", "reading file error"};
int main(int argc, char** argv){
     int base = argc;
     while (base != 1){
	if (base % 2 == 0)
	    base = base/2;
        else
	    base = 3*base + 1;
     }
     base--;
     ifstream file;
     file.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit);
     try{
           file.open(strs[base]);
           char buf[256];
           while (file.getline(buf,100)) 
		cout << buf << endl;
     }catch (const ifstream::failure& e) {
           cout << strs[base+1] << endl;
           return -1;
     }
     file.close();
     return argc;
}	

