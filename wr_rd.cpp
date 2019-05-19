#include <mutex>
#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <random>
#include <ctime>
#include <conio.h>
#include <time.h>
#define TREADS_AMOUNT 10

bool interface;
bool wr_lock, rd_lock;
int zapis;
int wr_count, rd_count = 0;
using namespace std;

default_random_engine randomEngine(time(NULL)); 
int getDirection() {                                            
    uniform_int_distribution<int> randomNum(3, 18); 
    return randomNum(randomEngine);
}
 
void writer(int& x, mutex& mtx){
	while(1){
		this_thread::sleep_for(chrono::seconds(getDirection()));
		cout<< "Писатель "<<this_thread::get_id()<<" запросил доступ"<<endl;
		rd_lock = true; 
		if(wr_lock == false){
			wr_lock = true; 
			zhdem_chitalok:
			if(rd_count != 0){
				cout<< "Писатель "<<this_thread::get_id()<<" ждёт читателей============================================"<<rd_count<<rd_count<<rd_count<<rd_count<<rd_count<<rd_count<<rd_count<<rd_count<<endl;
				usleep(500000);
				goto zhdem_chitalok; 
			} else {
				cout<< "Писатель "<<this_thread::get_id()<<" начал писать++++++++++++++++++++++++++++++++++++++++++++++\n"<<endl;
				ofstream out;   
			    out.open("D:\\hello.txt"); 
				if (out.is_open()){
			        this_thread::sleep_for(chrono::seconds(3));
					zapis=getDirection(); 
			        out << zapis << endl;
					cout<< "Писатель "<<this_thread::get_id()<<" закончил писать------------------------------------------------------------------------\n"<<endl;
			    } else {
			    	cout<< "Писатель "<<this_thread::get_id()<<" не смог ничего записать\n"<<endl;
				}
			}
			wr_lock = false; rd_lock = false;
		} else {
			cout<< "Писатель "<<this_thread::get_id()<<" не получил доступ\n"<<endl;
		}
	}
}
void reader(int& x, mutex& mtx)
{
	while(1){
		this_thread::sleep_for(chrono::seconds(getDirection()));
		if(rd_lock == false){
			rd_count++;
			cout<< "Читатель "<<this_thread::get_id()<<" начал читать ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
			cout<< "Читатель "<<this_thread::get_id()<<" прочёл "<<zapis<<zapis<<zapis<<zapis<<zapis<<zapis<<zapis<<zapis<<zapis<<zapis<<zapis<<zapis<<zapis<<zapis<<zapis<<zapis<<zapis<<zapis<<zapis<<zapis<<zapis<<zapis<<zapis<<zapis<<endl;	
			this_thread::sleep_for(chrono::seconds(3));
			cout<< "Читатель "<<this_thread::get_id()<<" закончил читать  ###########################################"<<endl;
			rd_count--;
		} else {
			cout<< "Читатель "<<this_thread::get_id()<<" не получил доспуп\n"<<endl;		
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int x;
	mutex mtx;
	thread threads_wr[TREADS_AMOUNT],threads_rd[TREADS_AMOUNT];
	for(int i = 0; i < TREADS_AMOUNT; i++){
		threads_wr[i] = thread(writer, ref(x), ref(mtx));
		usleep(60000);
		threads_rd[i] = thread(reader, ref(x), ref(mtx));
	}
	threads_wr[TREADS_AMOUNT].join(); usleep(60000);
	threads_rd[TREADS_AMOUNT].join();
}
