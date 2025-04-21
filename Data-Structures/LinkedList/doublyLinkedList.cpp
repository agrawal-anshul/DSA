#include <iostream>
using namespace std;

// Node definition for doubly linked list
class DoublyNode {
public:
    int data;
    DoublyNode* next;
    DoublyNode* prev;

    DoublyNode(int value) {
        data = value;
        next = nullptr;
        prev = nullptr;
    }
};

// Class for Doubly Linked List operations
class DoublyLinkedList {
private:
    DoublyNode* head = nullptr;

public:
    // Add a new node at the end
    void append(int value) {
        DoublyNode* newNode = new DoublyNode(value);
        if (head == nullptr) {
            head = newNode;
            return;
        }

        DoublyNode* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }

        curr->next = newNode;
        newNode->prev = curr;
    }

    // Insert node at given position
    void insertAt(int value, int pos) {
        DoublyNode* newNode = new DoublyNode(value);

        if (pos == 0) {
            newNode->next = head;
            if (head != nullptr) head->prev = newNode;
            head = newNode;
            return;
        }

        DoublyNode* curr = head;
        int counter = 0;
        while (curr != nullptr && counter < pos - 1) {
            curr = curr->next;
            counter++;
        }

        if (curr == nullptr) {
            cout << "Position " << pos << " is out of bounds.\n";
            delete newNode;
            return;
        }

        newNode->next = curr->next;
        if (curr->next != nullptr) curr->next->prev = newNode;
        newNode->prev = curr;
        curr->next = newNode;
    }

    // Update value at a given position
    void updateAt(int value, int pos) {
        DoublyNode* curr = head;
        int counter = 0;
        while (curr != nullptr && counter < pos) {
            curr = curr->next;
            counter++;
        }

        if (curr == nullptr) {
            cout << "Cannot update at position " << pos << " — out of bounds.\n";
            return;
        }

        curr->data = value;
    }

    // Delete node at given position
    void deleteAt(int pos) {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        // Deleting the first node
        if (pos == 0) {
            DoublyNode* toDelete = head;
            head = head->next;
            if (head != nullptr) head->prev = nullptr;
            delete toDelete;
            return;
        }

        // Traverse to the position
        DoublyNode* curr = head;
        int counter = 0;
        while (curr != nullptr && counter < pos) {
            curr = curr->next;
            counter++;
        }

        if (curr == nullptr) {
            cout << "Position " << pos << " is out of bounds.\n";
            return;
        }

        // Re-link previous and next nodes
        if (curr->prev != nullptr) curr->prev->next = curr->next;
        if (curr->next != nullptr) curr->next->prev = curr->prev;

        delete curr;
    }

    // Display list from head to tail
    void displayForward() {
        DoublyNode* curr = head;
        while (curr != nullptr) {
            cout << curr->data << " <-> ";
            curr = curr->next;
        }
        cout << "NULL\n";
    }

    // Display list from tail to head
    void displayBackward() {
        DoublyNode* curr = head;
        if (curr == nullptr) {
            cout << "NULL\n";
            return;
        }

        // Go to the last node
        while (curr->next != nullptr) {
            curr = curr->next;
        }

        // Traverse backward
        while (curr != nullptr) {
            cout << curr->data << " <-> ";
            curr = curr->prev;
        }
        cout << "NULL\n";
    }
};

int main() {
   DoublyLinkedList list;
   int choice, value, position;

   do {
       cout << "\n--- Doubly Linked List Menu ---\n";
       cout << "1. Append\n";
       cout << "2. Insert at Position\n";
       cout << "3. Update at Position\n";
       cout << "4. Delete at Position\n";
       cout << "5. Display Forward\n";
       cout << "6. Display Backward\n";
       cout << "0. Exit\n";
       cout << "Enter your choice: ";
       cin >> choice;

       switch (choice) {
           case 1:
               cout << "Enter value to append: ";
               cin >> value;
               list.append(value);
               break;
           case 2:
               cout << "Enter position and value: ";
               cin >> position >> value;
               list.insertAt(value, position);
               break;
           case 3:
               cout << "Enter position and new value: ";
               cin >> position >> value;
               list.updateAt(value, position);
               break;
           case 4:
               cout << "Enter position to delete: ";
               cin >> position;
               list.deleteAt(position);
               break;
           case 5:
               cout << "List (forward): ";
               list.displayForward();
               break;
           case 6:
               cout << "List (backward): ";
               list.displayBackward();
               break;
           case 0:
               cout << "Exiting...\n";
               break;
           default:
               cout << "Invalid choice. Try again.\n";
       }
   } while (choice != 0);

   return 0;
}