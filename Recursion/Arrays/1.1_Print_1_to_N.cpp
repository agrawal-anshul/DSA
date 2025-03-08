#include <iostream>
using namespace std;
void printn(int n){
   if (n<1){
      return;
   }
   printn(n-1);
   cout<<n<<" ";
}

int main(){
   int n ;
   cin>>n;
   printn(n);
}