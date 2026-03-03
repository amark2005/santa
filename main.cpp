//reindeer go on vacation
// come back on by one, 9th reindeer wakes santa
// santa takes all the 9 reindeer to deliver gifts
// repeat
#include <chrono>
#include<random>
#include <iostream>
#include <ostream>
#include<thread>
#include <vector>
#include<cstdlib>
#include<mutex>
#include<semaphore>
constexpr int REINDERR_COUNT=9;
constexpr int ELF_COUNT=10;
int elfwaiting=0;
int reindeer_avail=0;
std::mutex mux;
std::counting_semaphore<9> santa_wake(0);
std::counting_semaphore<9> reindeer_wake(0);
std::counting_semaphore<3> elf_bouncer(3);  
std::counting_semaphore<9> elf_signal(0);  
std::counting_semaphore<9> elf_problem(0);  
std::counting_semaphore<9> elf_done(0);

void randisleep(int minS,int maxS){
  std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(minS,maxS);
  std::this_thread::sleep_for(std::chrono::seconds(dist6(rng)));
}
void santaThread(){
  std::cout<<"santa is sleeping"<<std::endl;
  while(true){
    santa_wake.acquire();
    std::cout<<"[santa] All reindeers here!!!! Time to deliver gifts!!!"<<std::endl;
    for(int i=0;i<REINDERR_COUNT;i++)reindeer_wake.release();
    randisleep(0,1);
    std::cout<<"Toys are Delivered!!! Ho HO HOOOOO!!"<<std::endl;
    std::lock_guard<std::mutex> lock(mux);
    reindeer_avail=0;
  }

  //TODO: wake up when 9 deer arrive
}
void reindeerThread(int id){
  randisleep(1,3);
  {std::lock_guard<std::mutex> lock(mux);
  reindeer_avail++;
  std::cout<<"Reindeer "<<id<<" Has arrived. "<<reindeer_avail<<"Available now\n"<<std::endl;
  if(reindeer_avail==REINDERR_COUNT){
    std::cout<<"All the Reindeers have arrived...\n Waking up santa!!! "<<std::endl;
    santa_wake.release();
  }}
  reindeer_wake.acquire();
  std::cout<<"[Reindeer "<<id<<"] Delivering Toysssss!!!!"<<std::endl;
}


int main(){
  std::thread santa(santaThread);
  std::vector<std::thread> reindeer;
  for(int i=1;i<=REINDERR_COUNT;i++){
    reindeer.emplace_back(reindeerThread,i);
  }
  for(auto& r: reindeer) r.join();
  santa.detach();
  std::cout<<"All the reindeers came"<<std::endl;

}
//TODO:have to create trigger for santa and reindeer
