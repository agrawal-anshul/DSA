#include <iostream>
using namespace std;

// Node definition for circular linked list
class CircularNode {
public:
    int data;
    CircularNode* next;

    CircularNode(int value) {
        data = value;
        next = nullptr;
    }
};

// Circular linked list class
class CircularLinkedList {
private:
    CircularNode* head = nullptr;

public:
    void append(int value) {
        CircularNode* newNode = new CircularNode(value);
        if (head == nullptr) {
            head = newNode;
            newNode->next = head;
            return;
        }

        CircularNode* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = head;
    }

    void insertAt(int value, int pos) {
        CircularNode* newNode = new CircularNode(value);
        if (pos == 0) {
            if (head == nullptr) {
                head = newNode;
                newNode->next = head;
                return;
            }
            CircularNode* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
            head = newNode;
            return;
        }

        CircularNode* curr = head;
        int count = 0;
        while (curr->next != head && count < pos - 1) {
            curr = curr->next;
            count++;
        }

        if (count != pos - 1) {
            cout << "Position " << pos << " is out of bounds.\n";
            delete newNode;
            return;
        }

        newNode->next = curr->next;
        curr->next = newNode;
    }

    void updateAt(int value, int pos) {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        CircularNode* curr = head;
        int count = 0;
        do {
            if (count == pos) {
                curr->data = value;
                return;
            }
            curr = curr->next;
            count++;
        } while (curr != head);

        cout << "Position " << pos << " is out of bounds.\n";
    }

    void deleteAt(int pos) {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        if (pos == 0) {
            CircularNode* temp = head;
            if (head->next == head) {
                delete head;
                head = nullptr;
                return;
            }
            CircularNode* last = head;
            while (last->next != head) {
                last = last->next;
            }
            head = head->next;
            last->next = head;
            delete temp;
            return;
        }

        CircularNode* curr = head;
        int count = 0;
        while (curr->next != head && count < pos - 1) {
            curr = curr->next;
            count++;
        }

        if (curr->next == head || count != pos - 1) {
            cout << "Position " << pos << " is out of bounds.\n";
            return;
        }

        CircularNode* temp = curr->next;
        curr->next = temp->next;
        delete temp;
    }

    void display() {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        CircularNode* curr = head;
        do {
            cout << curr->data << " -> ";
            curr = curr->next;
        } while (curr != head);
        cout << "(back to head)\n";
    }
};

int main() {
    CircularLinkedList clist;
    int choice, value, position;

    do {
        cout << "\n--- Circular Linked List Menu ---\n";
        cout << "1. Append\n";
        cout << "2. Insert at Position\n";
        cout << "3. Update at Position\n";
        cout << "4. Delete at Position\n";
        cout << "5. Display\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to append: ";
                cin >> value;
                clist.append(value);
                break;
            case 2:
                cout << "Enter position and value: ";
                cin >> position >> value;
                clist.insertAt(value, position);
                break;
            case 3:
                cout << "Enter position and new value: ";
                cin >> position >> value;
                clist.updateAt(value, position);
                break;
            case 4:
                cout << "Enter position to delete: ";
                cin >> position;
                clist.deleteAt(position);
                break;
            case 5:
                cout << "List: ";
                clist.display();
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