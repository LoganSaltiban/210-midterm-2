#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

int timePeriodTracker = 0;

string randomName(ifstream& inputFile);

// Function Prototypes
void frontCustomerHelped(coffeeLine);
void newCustomerJoined(coffeeLine, nameList);
void backCustomerLeaving(coffeeLine);
void randomCustomerLeaving(coffeeLine);
void  VIPSkipLine(coffeeLine);
void newCustomerJoinedGarunteed(DoublyLinkedList& coffeeLine, vector<string> nameList);

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

    // Adding a get node name at position function to ensure that randomcustomerleaving works right
    string getNameAtNodePosition(int position)
    {
        if (!head)
        {
            cout << "List is empty" << endl; // test case if head is empty
            return;
        }

        Node* traversal = head; // set traversal ptr to head

        for (int i = 1; i < position; ++i)
        {
            if (!traversal) // check to see if the position is too far in list
            {
                cout << "Position is not valid" << endl;
                return;
            }

            // Set traversal to next node
            traversal = traversal->next;
        }
        // Finally return that name
        return traversal->name;
    }

    // Adding a Size Function so that i can properly add my randomCustomerLeaving function
    int getSizeOfList()
    {
        // Create temp traversal pointer and point to head
        Node* tempNode = head;
        int sizeOfList = 0; // store the number of times while loop travels

        // test case if list is empty
        if (!head)
        {
            return 0;
        }

        while (tempNode)
        {
            sizeOfList++; // increase sizeOfList
            tempNode = tempNode->next;
        }

        return sizeOfList; // return the correct size of list
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

void frontCustomerHelped(DoublyLinkedList& coffeeLine)
{
    int prob = rand() % 100 + 1; // create our random generator thanks for the tip ;)
    // check if probabability is 40%
    if (prob <= 40)
    {
        cout << coffeeLine->head->name << " is served." << endl; // announce served
        coffeeLine.pop_front(); // remove front node
    }
}

void newCustomerJoined(DoublyLinkedList& coffeeLine, vector<string> nameList)
{
    int prob = rand() % 100 + 1; // random number
    if (prob <= 60) // Check 60% chance of new customer joining
    {
        int index = rand() % nameList.size(); // create a random index to use for name
        string tempCustomer = nameList.at(index); // use temp customer to load pop_front()

        cout << tempCustomer << " has joined the line." << endl; // announce new customer joined

        // Now we add new customer to the end of the line
        coffeeLine.push_back(tempCustomer);
    }
}
// Just copied newCustomerJoined and took off the probability aspect
void newCustomerJoinedGarunteed(DoublyLinkedList& coffeeLine, vector<string> nameList)
{
        int index = rand() % nameList.size(); // create a random index to use for name
        string tempCustomer = nameList.at(index); // use temp customer to load pop_front()

        cout << tempCustomer << " has joined the line." << endl; // announce new customer joined

        // Now we add new customer to the end of the line
        coffeeLine.push_back(tempCustomer);
}

void backCustomerLeaving(DoublyLinkedList& coffeeLine)
{
    int prob = rand() % 100 + 1; // create our random number

    if (prob <= 20) // check 20% chance
    {
        cout << coffeeLine->tail->name << " has left the line." << endl; // tell user tail node left line
        coffeeLine.pop_back(); // delete tail node
    }
}

void randomCustomerLeaving(DoublyLinkedList& coffeeLine)
{
    int prob = rand() % 100 + 1; // create our random number

    // Check if probability is 10%
    if (prob <= 10)
    {
        int randomNodeIndex = rand() % coffeeLine.getSizeOfList + 1; // had to create a getSizeOfList function
        string customerLeft = coffeeLine.getNameAtNodePosition(randomNodeIndex);// Had to create a return name at position function

        // announce that the random left the line
        cout << customerLeft << " was a random customer that left the line." << endl;
        coffeeLine.delete_pos(randomNodeIndex); // delete the node/customer at that position
    }
}

void VIPSkipLine(DoublyLinkedList& coffeeLine, vector<string> nameList)
{
    int prob = rand() % 100 + 1; // create probability
    if (prob <= 10) // check 10%
    { 
        int randomNameIndex = rand() % nameList.size(); // create our random index to choose name in vector
        string customerName = nameList.at(randomNameIndex); // set customerName equal to new VIP's name

        cout << customerName << " (VIP) has joined the front of the line and has ordered" << endl;
        coffeeLine.push_front(customerName);
    }
}

void timePeriod(DoublyLinkedList& coffeeLine, vector<string> nameList)
{
    // Check if time period tracker is our first time period | if so, add 5 customers
    if (timePeriodTracker == 0)
    {
        for (int i = 0; i < 5; i++)
        {
            newCustomerJoinedGarunteed(coffeeLine, nameList);
        }
        // Finally increment timeperiodtracker so this doesnt happen again
        timePeriodTracker++;
    }
    // Call our functions
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

    DoublyLinkedList coffeeLine;

    // Start our instance with 5 customers in line.
    
    return 0;
}
