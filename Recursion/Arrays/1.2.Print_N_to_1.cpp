#include <iostream>
using namespace std;
void printn(int n){
   if (n<1){
      return;
   }
   cout<<n<<" ";
   printn(n-1);
}

int main(){
   int n ;
   cin>>n;
   printn(n);
}