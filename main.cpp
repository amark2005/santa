#include<iostream>
#include <ostream>
#include<semaphore>
#include<chrono>
#include<cstdlib>
#include <thread>
std::counting_semaphore<3> sem(3);
int stall_count=10;
void occo(int id){
  sem.acquire();
  int sec=(rand()%5)+1;
  std::cout<<"Person "<<id<<" enter the stall\n"<<std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(sec));
  std::cout<<"Person "<<id<<" is done peeing...\n"<<std::endl;
  sem.release();
}

int main(){
  std::cout<<"Number of Stalls: "<<stall_count<<std::endl;
  std::thread t1(occo, 1);
  std::thread t2(occo, 2);
  std::thread t3(occo, 3);
  std::thread t4(occo, 4);
  std::thread t5(occo, 5);
  t1.join(); t2.join(); t3.join(); t4.join(); t5.join();
  return 0;
}