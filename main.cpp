#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

string randomName(ifstream& inputFile);

// Function Prototypes
void frontCustomerHelped(coffeeLine);
void newCustomerJoined(coffeeLine, nameList);
void backCustomerLeaving(coffeeLine);
void randomCustomerLeaving(coffeeLine);
void  VIPSkipLine(coffeeLine);

class DoublyLinkedList {
private:
    struct Node {
        string name;
        Node* prev;
        Node* next;
        Node(string inputName, Node* p = nullptr, Node* n = nullptr) {
            name = inputName; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(string inputName, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(inputName);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string inputName) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->name != inputName)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(string inputName) {
        Node* newNode = new Node(inputName);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(string inputName) {
        Node* newNode = new Node(inputName);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->name << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->name << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

void timePeriod(DoublyLinkedList& coffeeLine, vector<string> nameList)
{
    frontCustomerHelped(coffeeLine);
    newCustomerJoined(coffeeLine, nameList);
    backCustomerLeaving(coffeeLine);
    randomCustomerLeaving(coffeeLine);
    VIPSkipLine(coffeeLine);
}

int main() {
    // Create our random seed using time
    srand(time(0));
    
    ifstream nameList("names.txt"); // create our nameList to read from

    // Check input file 
    if (!nameList.is_open())
    {
        cout << "Error accessing the name list.";
        return 0;
    }
    
    // Create a vector to store all our names then close file
    vector<string> nameListVector;
    string traversalName;

    while (getline(nameList, traversalName))
    {
        nameListVector.push_back(traversalName);
    }

    nameList.close() // close file stream
    
    return 0;
}
