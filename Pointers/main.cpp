#include <iostream>
using namespace std;

int main(){
   int a = 10;
   int *p;
   p = &a;
   cout << "The value of a is " << a << endl;
   cout << "The address of a is " << &a << endl;
   cout << "The value of a is " << *p << endl;
   cout<<"The address of a is " << p << endl;
   cout<<"The address of p is " << &p << endl;
   cout<<"The address of p+1 is " << p+1 << endl;

   *p = 100;
   cout << "The value of a is " << a << endl;
   cout << "The value of a is " << *p << endl<<endl<<endl;
 


   // Arrays and pointers
   // NOTE:
   // A refers to &A
   // *A refers to A[0]

   int A[5] = {2,53,41,50,69};
   for(int i=0;i<5;i++){
      cout<<"Address = "<< &A[i]<<endl;
      cout<<"Address = "<< A+i<<endl;  
      cout<<"Value = "<< A[i]<<endl;
      cout<<"Value = "<< *(A+i)<<endl;
   }
   
   int* ptr = A;
   cout<<"ptr: "<<ptr<<endl;
   cout<<"*ptr: "<<*ptr<<endl;
   cout<<"*++ptr: "<<*++ptr<<endl;
   cout<<"*ptr+1: "<<*ptr+1<<endl;
   cout<<"*(ptr+1): "<<*(ptr+1);
   
   return 0;

}