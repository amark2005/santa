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
std::mutex mux;
std::counting_semaphore<9> santa_wake(0);
std::counting_semaphore<9> reindeer_wake(0);

void randisleep(int minS,int maxS){
  std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(minS,maxS);
  std::this_thread::sleep_for(std::chrono::seconds(dist6(rng)));
}
void santaThread(){
  std::cout<<"santa is sleeping"<<std::endl;
  //TODO: wake up when 9 deer arrive
}
void reindeerThread(int id){
  randisleep(2,10);
  std::cout<<"Reindeer Number "<<id<<" Has arrived"<<std::endl;
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
