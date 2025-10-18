#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;
const int TIME_PERIOD = 20;
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
const int MAX = 100;
const int MIN = 1;
vector<string> NAMES;
class DoublyLinkedList {
private:
struct Node {
int data;
Node* prev;
Node* next;
Node(int val, Node* p = nullptr, Node* n = nullptr) {
data = val;
prev = p;
next = n;
}
};
Node* head;
Node* tail;
public:
DoublyLinkedList() { head = nullptr; tail = nullptr; }

void insert_after(int value, int position) {
if (position < 0) {
cout << "Position must be >= 0." << endl;
return;
}
Node* newNode = new Node(value);
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
void delete_val(int value) {
if (!head) return;
Node* temp = head;
while (temp && temp->data != value)
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
void push_back(int v) {
Node* newNode = new Node(v);
if (!tail)
head = tail = newNode;
else {
tail->next = newNode;
newNode->prev = tail;
tail = newNode;
}
}
void push_front(int v) {
Node* newNode = new Node(v);
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

void store_opens(){
    cout << "Store opens: \n";
    for (int i = 0; i < 5; i++) {
        int value = rand() % (MAX - MIN +1) + MIN;
        push_back(value);
        cout << NAMES[value] << " joins the line. \n";
    }
}

void customerHelped(){ //40%
    int prob = rand() % 100 + 1;
    if (prob <=40){
    if (head){
        cout << NAMES[head->data] << " is served \n";
        pop_front();
    }
}
}

void joinsLine() { //60% 
    int prob = rand() % 100 + 1;
    int value = rand() % (MAX - MIN +1) + MIN;
    if (prob <=60){
        push_back(value);
        cout << NAMES[value] << " joins the line \n";
    }
    }

void lastLeavesBfServed(){ //20 %
    int prob = rand() % 100 + 1;
    if (prob <=20){
        if (tail){
            cout << NAMES[tail->data] << " (at the rear) left the line \n";
            pop_back();
        }
    }
} 
void anyLeavesBfServed(){ //10%
    int prob = rand() % 100 + 1;
    if (prob <= 10){
        //pick random position within list and delete_pos
        Node * temp = head; 
        int value = rand() % (MAX - MIN +1) + MIN;
        cout << "value: " << value << "\n";
        if (!head){
            cout << "null" << endl;
            return;
        }
        for (int i = 0; i < value; i++) {
            temp = temp->next;
            cout << NAMES[temp->data] << " left the line \n";
            delete_pos(i+1);
        }
        }

    }

void VIPjoin(){ //10%
     int prob = rand() % 100 + 1;
     if (prob <= 10){
        int value = rand() % (MAX - MIN + 1) + MIN;
        push_front(value);
        cout << NAMES[value] << " (VIP) joins the front of the line \n";
     }
}

void printList(){
    Node * temp = head;
    cout << " ---- Resulting line ---- \n";
    while (temp){
        cout << NAMES[temp->data] << "\n"; 
        temp = temp->next;
    }
}


};

int main() {
    // load the names with getline into a vector
    ifstream fin("names.txt");
    string n;
    while (fin && getline(fin, n)) {
        NAMES.push_back(n);
    }
    DoublyLinkedList storeLine;
    // start with store Opens fn
    storeLine.store_opens();

    // for loop until 20 min and call probability functions 
    for (int min = 2; min <= TIME_PERIOD; min++){
        cout << "Time step: " << min << "\n";
        storeLine.customerHelped();
        storeLine.joinsLine();
        storeLine.printList();
        storeLine.lastLeavesBfServed();
        storeLine.anyLeavesBfServed();
        storeLine.VIPjoin();
        storeLine.printList();
    }

return 0;
}