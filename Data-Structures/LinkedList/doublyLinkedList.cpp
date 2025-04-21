#include <iostream>
using namespace std;

// Node definition for doubly linked list
class Node {
public:
    int data;
    Node* next;
    Node* prev;

    Node(int value) {
        data = value;
        next = nullptr;
        prev = nullptr;
    }
};

// Class for Doubly Linked List operations
class DoublyLinkedList {
private:
    Node* head = nullptr;

public:
    // Add a new node at the end
    void pushBack(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = newNode;
        newNode->prev = current;
    }

    // Insert node at given position
    void insertAtPosition(int value, int pos) {
        Node* newNode = new Node(value);

        if (pos == 0) {
            newNode->next = head;
            if (head != nullptr) head->prev = newNode;
            head = newNode;
            return;
        }

        Node* current = head;
        int counter = 0;
        while (current != nullptr && counter < pos - 1) {
            current = current->next;
            counter++;
        }

        if (current == nullptr) {
            cout << "Position " << pos << " is out of bounds.\n";
            delete newNode;
            return;
        }

        newNode->next = current->next;
        if (current->next != nullptr) current->next->prev = newNode;
        newNode->prev = current;
        current->next = newNode;
    }

    // Update value at a given position
    void updateAtPosition(int value, int pos) {
        Node* current = head;
        int counter = 0;
        while (current != nullptr && counter < pos) {
            current = current->next;
            counter++;
        }

        if (current == nullptr) {
            cout << "Cannot update at position " << pos << " — out of bounds.\n";
            return;
        }

        current->data = value;
    }

    // Delete node at given position
    void deleteAtPosition(int pos) {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        // Deleting the first node
        if (pos == 0) {
            Node* nodeToDelete = head;
            head = head->next;
            if (head != nullptr) head->prev = nullptr;
            delete nodeToDelete;
            return;
        }

        // Traverse to the position
        Node* current = head;
        int counter = 0;
        while (current != nullptr && counter < pos) {
            current = current->next;
            counter++;
        }

        if (current == nullptr) {
            cout << "Position " << pos << " is out of bounds.\n";
            return;
        }

        // Re-link previous and next nodes
        if (current->prev != nullptr) current->prev->next = current->next;
        if (current->next != nullptr) current->next->prev = current->prev;

        delete current;
    }

    // Display list from head to tail
    void printForward() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " <-> ";
            current = current->next;
        }
        cout << "NULL\n";
    }

    // Display list from tail to head
    void printBackward() {
        Node* current = head;
        if (current == nullptr) {
            cout << "NULL\n";
            return;
        }

        // Go to the last node
        while (current->next != nullptr) {
            current = current->next;
        }

        // Traverse backward
        while (current != nullptr) {
            cout << current->data << " <-> ";
            current = current->prev;
        }
        cout << "NULL\n";
    }
};

int main() {
   DoublyLinkedList list;
   int choice, value, position;

   do {
       cout << "\n--- Doubly Linked List Menu ---\n";
       cout << "1. Push Back\n";
       cout << "2. Insert at Position\n";
       cout << "3. Update at Position\n";
       cout << "4. Delete at Position\n";
       cout << "5. Print Forward\n";
       cout << "6. Print Backward\n";
       cout << "0. Exit\n";
       cout << "Enter your choice: ";
       cin >> choice;

       switch (choice) {
           case 1:
               cout << "Enter value to push back: ";
               cin >> value;
               list.pushBack(value);
               break;
           case 2:
               cout << "Enter position and value: ";
               cin >> position >> value;
               list.insertAtPosition(value, position);
               break;
           case 3:
               cout << "Enter position and new value: ";
               cin >> position >> value;
               list.updateAtPosition(value, position);
               break;
           case 4:
               cout << "Enter position to delete: ";
               cin >> position;
               list.deleteAtPosition(position);
               break;
           case 5:
               cout << "List (forward): ";
               list.printForward();
               break;
           case 6:
               cout << "List (backward): ";
               list.printBackward();
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