#include<iostream>
#include<unistd.h>
#include<thread>
using namespace std;
void m2(long long a){
  long long result=0;
  for(long long i=0;i<=a;i++){
    result+=2*i;
  }
  cout<<"Multiplied "<<a<<" The result is: "<<result<<endl;
}
void m3(long long a){
  long long result=0;
  for(long long i=0;i<=a;i++){
    result+=3*i;
  }
  cout<<"Multiplied "<<a<<" The result is: "<<result<<"\n";
}
int main(){
  thread t1(m2,1999);
  thread t2(m3,1999);
  t1.join();
  t2.join();
  cout<<"Both calculations done"<<endl;
  return 0;

}