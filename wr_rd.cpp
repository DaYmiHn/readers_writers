#include <mutex>
#include <thread>
#include <iostream>
#include <mutex>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using namespace std;
string chitateli [4];
void writer(int& x, mutex& mtx)
{
	while(1){
		mtx.lock();
		x = rand() % 999 +100;
		ofstream out;   
	    out.open("D:\\hello.txt"); 
		if (out.is_open()){
	        out << x << endl;
	        cout<< "Писатель написал:\t"<<x<<"\t"<<this_thread::get_id()<<endl;
	    }
		mtx.unlock();
		usleep(400000);
	}
}
void reader(int& x, mutex& mtx)
{
	while(1){
		mtx.lock();
		string line;
	    ifstream in("D:\\hello.txt"); 
		if (in.is_open()){
			getline(in, line);	
		    for(int i=0; i < 4;i++){
		    	chitateli[i] = line;
		    	cout <<"Читатель "<<i+1 <<" прочёл:\t" <<chitateli[i] <<"\t"<<this_thread::get_id()<< endl;
		    	if (i == 3) cout<< "\n";
			}
			in.close(); 
			mtx.unlock();
			usleep(500000);
		}		
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int x;
	mutex mtx;
	thread th_wr(writer, ref(x), ref(mtx));
	thread th_rd(reader, ref(x), ref(mtx));
	
	th_wr.join();
	th_rd.join();
}

