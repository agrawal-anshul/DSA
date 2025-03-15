#include <iostream>
using namespace std;
int SumOfN(int n, int sum){
   if(n == 0){
      return sum;
   }
   return SumOfN(n-1,sum+n);
}

int main(){
   int n ;
   cin>>n;
   cout<<SumOfN(n,0);
   return 0;
}