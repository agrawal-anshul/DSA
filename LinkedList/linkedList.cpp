#include <iostream>
using namespace std;

class Node{
   public:
      int data;
      Node* next;
      Node(int value){
         data = value;
         next = NULL;
      }
};

class LinkedList{
   private:
      Node* head = NULL;
   
   public:
      LinkedList(){
        head = NULL;
      }

   // append
   void append(int value){
      // Create a new node
      Node* newNode = new Node(value);

      //Check if head==NULL
      if(head == NULL){
         head = newNode;
         return;
      }

      // Append
      Node* curr = head;
      while(curr->next != NULL){
         curr = curr->next;
      }
      curr->next = newNode;

   }

   // insertAt
   void insertAt(int value, int pos){
      Node* newNode = new Node(value);
      
       // Case: insert at head of non-empty list
      if(pos == 0){
         newNode->next = head;
         head = newNode;
         return;
      }
      
      // Traverse to the node before the desired position
      Node* curr = head;
      int counter = 0;

      while (curr != NULL && counter < pos - 1) {
         curr = curr->next;
         counter++;
      }

      // If we reached the end before reaching the position
      if (curr == NULL) {
         cout << "Cannot insert at position " << pos << " — out of bounds.\n";
         delete newNode; // cleanup
         return;
      }

      // Insert in between
      newNode->next = curr->next;
      curr->next = newNode;
   }

   // updateAt
   void updateAt(int value, int pos){
      if(head == NULL){
         cout << "Cannot update — list is empty.\n";
         return;
      }

      // Traverse to the position
      Node* curr = head;
      int counter = 0;
      while(curr != NULL && counter < pos){
         curr = curr->next;
         counter++;
      }

      // If we reached the end before reaching the position
      if (curr == NULL) {
         cout << "Cannot update at position " << pos << " — out of bounds.\n";
         return;
      }
      curr->data = value;

   }

   // deleteAt
   void deleteAt(int pos){
      if(head == NULL){
         cout<<"Cannot delete - empty list";
         return;
      }

      // Deleteion at pos = 0
      if(pos == 0){
         Node* toDelete = head;
         head = head->next;
         delete toDelete;
         return;
      }

      Node* curr = head;
      int counter = 0;
      while(curr!=NULL && counter < pos-1){
         curr = curr->next;
         counter++;
      }

      // If we reached the end before reaching the position
      if(curr == NULL || curr->next == NULL){
         cout << "Cannot delete at position " << pos << " — out of bounds.\n";
         return;
      }
      Node* toDelete = curr->next;
      curr->next = curr->next->next;
      delete toDelete;
   }
   
   // Display the list
   void display() {
      Node* temp = head;
      while (temp != NULL) {
          cout << temp->data << " -> ";
          temp = temp->next;
      }
      cout << "NULL\n";
  }
   void reverseList(){
      Node* prev = nullptr;
      Node* curr = head;
      Node* next = nullptr;
      while (curr != nullptr) {
         next = curr->next;   
         curr->next = prev;   
         prev = curr;
         curr = next;
     }
     head = prev;
   }
};

// Main function with user menu
int main() {
   LinkedList list;
   int choice, value, pos;

   do {
       cout << "\n--- Linked List Menu ---\n";
       cout << "1. Append\n2. Insert at Position\n3. Update at Position\n";
       cout << "4. Delete at Position\n5. Display\n6. Reverse LL\n0. Exit\n";
       cout << "Enter choice: ";
       cin >> choice;

       switch (choice) {
           case 1:
               cout << "Enter value to append: ";
               cin >> value;
               list.append(value);
               break;
           case 2:
               cout << "Enter position and value: ";
               cin >> pos >> value;
               list.insertAt(value, pos);
               break;
           case 3:
               cout << "Enter position and new value: ";
               cin >> pos >> value;
               list.updateAt(value, pos);
               break;
           case 4:
               cout << "Enter position to delete: ";
               cin >> pos;
               list.deleteAt(pos);
               break;
           case 5:
               list.display();
               break;
           case 6:
               list.reverseList();
               list.display();
               break;
           case 0:
               cout << "Exiting program...\n";
               break;
           default:
               cout << "Invalid choice. Try again.\n";
       }

   } while (choice != 0);

   return 0;
}