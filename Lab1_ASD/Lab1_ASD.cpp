#include <iostream>
#include <ctime>

using namespace std;

string specialities[] = {
    "Computer Science", "Software Engineering", "Cybersecurity", "Mathematics",
    "System Analysis", "Data Science", "Artificial Intelligence", "Information Technology",
    "Robotics", "Cloud Computing"
};

struct Diploma {
    string specialty;
    int year;
    float usefulness;

    Diploma() {
        specialty = specialities[rand() % 10];
        year = rand() % 76 + 1950;
        usefulness = rand() % 1001 / 10.0f;
    }

    Diploma(string specialty, int year, float usefulness)
        : specialty(specialty), year(year), usefulness(usefulness) {
    }

    void Print() const {
        cout << "Specialty: " << specialty << "\nYear: " << year
            << "\nUsefulness: " << usefulness << "\n";
    }
};

struct DynamicArray {
    Diploma* diplomas;
    int capacity;
    int current_size;
    int frontIndex;

    DynamicArray() : capacity(2), current_size(0), frontIndex(0) {
        diplomas = new Diploma[capacity];
    }

    void resize() {
        int newCapacity = capacity * 2;
        Diploma* newData = new Diploma[newCapacity];
        for (int i = 0; i < current_size; i++) {
            newData[i] = diplomas[(frontIndex + i) % capacity];
        }
        delete[] diplomas;
        diplomas = newData;
        capacity = newCapacity;
        frontIndex = 0;
    }

    void push_back(Diploma value) {
        if (current_size == capacity) resize();
        diplomas[(frontIndex + current_size) % capacity] = value;
        current_size++;
    }

    void push_front(Diploma value) {
        if (current_size == capacity) resize();
        frontIndex = (frontIndex - 1 + capacity) % capacity;
        diplomas[frontIndex] = value;
        current_size++;
    }

    void pop_front() {
        if (current_size == 0) return;
        frontIndex = (frontIndex + 1) % capacity;
        current_size--;
    }

    void pop_back() {
        if (current_size == 0) return;
        current_size--;
    }

    Diploma get(int index) {
        if (index < 0 || index >= current_size) {
            cout << "Error. Index out of range :(" << endl;
            return Diploma();
        }
        return diplomas[(frontIndex + index) % capacity];
    }

    int size() { return current_size; }

    ~DynamicArray() { delete[] diplomas; }
};

struct Node {
    Diploma value;
    Node* next;
    Node* prior;
    Node(Diploma value) : value(value), next(nullptr), prior(nullptr) {}
};

struct LinkedList {
    Node* head;
    Node* tail;
    int size;
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    void push_back(Diploma value) {
        Node* newNode = new Node(value);
        if (!tail) head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prior = tail;
            tail = newNode;
        }
        size++;
    }

    void push_front(Diploma value) {
        Node* newNode = new Node(value);
        if (!head) head = tail = newNode;
        else {
            newNode->next = head;
            head->prior = newNode;
            head = newNode;
        }
        size++;
    }

    void pop_front() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        if (head) head->prior = nullptr;
        else tail = nullptr;
        delete temp;
        size--;
    }

    void pop_back() {
        if (!tail) return;
        Node* temp = tail;
        tail = tail->prior;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        size--;
    }
    void insert(Diploma value, int index) {
        if (index < 0 || index > size) {
            cout << "Error. Index out of range :(" << endl;
            return;
        }

        Node* newNode = new Node(value);

        if (index == 0) { 
            push_front(value);
        }
        else if (index == size) {  
            push_back(value);
        }
        else {
            Node* current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }

            newNode->next = current;
            newNode->prior = current->prior;
            if (current->prior) {
                current->prior->next = newNode;
            }
            current->prior = newNode;

            size++;
        }

    }
    void remove(int index) {
        if (index < 0 || index >= size) {
            cout << "Error. Index out of range :(" << endl;
            return;
        }

        if (index == 0) {
            pop_front();
        }
        else if (index == size - 1) {  
            pop_back();
        }
        else {
            Node* current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }

            current->prior->next = current->next;
            if (current->next) {
                current->next->prior = current->prior;
            }

            delete current;
            size--;
        }

    }
    Diploma get(int index) {
        if (index < 0 || index >= size) {
            cout << "Error. Index out of range :(" << endl;
            return Diploma();
        }

        Node* node = (index < size / 2) ? head : tail;
        int steps = (index < size / 2) ? index : size - 1 - index;

        for (int i = 0; i < steps; i++) {
            node = (index < size / 2) ? node->next : node->prior;
        }

        return node->value;
    }

    int sizeList() {
        return size;
    }

    void clear() {
        while (head) {
            pop_front();
        }
    }
    ~LinkedList() {
        clear();
    }
};

void reverse(LinkedList& list) {
    Node* prior = nullptr;
    Node* next = list.head;
    list.tail = list.head;

    while (next) {
        Node* tmp = next->next;
        next->next = prior;
        next->prior = tmp;
        prior = next;
        next = tmp;
    }

    list.head = prior;
}
int hasCycle(Node* head) {
    if (head == nullptr) return 0;  

    Node* slow = head;
    Node* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;         
        fast = fast->next->next;    

        if (slow == fast) {
            return 1;  
        }
    }

    return 0; 
}

int main() {
    srand(time(0));
    LinkedList list;
    double sumaList = 0;
    clock_t ListStartTime = clock();
  
    for (int i = 0; i < 50000; i++) {
        list.push_back(Diploma());
    }
    clock_t ListEndTime = clock();
    double ListSeconds = double(ListEndTime - ListStartTime) / CLOCKS_PER_SEC;
    cout << "List push_back(50000): " << ListSeconds << "sec" << " Size = " << list.sizeList() << endl;
    sumaList += ListSeconds;
    ListStartTime = clock();
    for (int i = 0; i < 10000; i++) {
        list.push_front(Diploma());
    }
    ListEndTime = clock();
    ListSeconds = double(ListEndTime - ListStartTime) / CLOCKS_PER_SEC;
    cout << "List push_front(10000): " << ListSeconds << "sec" << " Size = " << list.sizeList() << endl;
    sumaList += ListSeconds;

    ListStartTime = clock();
    for (int i = 0; i < 20000; i++) {
        list.get(rand() % list.sizeList()).Print();
    }
    ListEndTime = clock();
    ListSeconds = double(ListEndTime - ListStartTime) / CLOCKS_PER_SEC;
    cout << "List get(20000): " << ListSeconds << "sec" << " Size = " << list.sizeList() << endl;
    sumaList += ListSeconds;

    ListStartTime = clock();
    for (int i = 0; i < 5000; i++) {
        list.pop_front();
    }
    ListEndTime = clock();
    ListSeconds = double(ListEndTime - ListStartTime) / CLOCKS_PER_SEC;
    cout << "List pop_front(5000): " << ListSeconds << "sec" << " Size = " << list.sizeList() << endl;
    sumaList += ListSeconds;

    ListStartTime = clock();
    for (int i = 0; i < 5000; i++) {
        list.pop_back();
    }
    ListEndTime = clock();
    ListSeconds = double(ListEndTime - ListStartTime) / CLOCKS_PER_SEC;
    cout << "List pop_back(5000): " << ListSeconds << "sec" << " Size = " << list.sizeList() << endl;
    sumaList += ListSeconds;
    cout << "List Time: " << sumaList << " sec" << endl;

    //--------------------------------------------------------
    cout << "--------------------------------------------------------" << endl;
    DynamicArray array;
    double sumaArray = 0;
    clock_t ArrayStartTime = clock();
    for (int i = 0; i < 50000; i++) {
        array.push_back(Diploma());
    }
    clock_t ArrayEndTime = clock();
    double ArraySeconds = double(ArrayEndTime - ArrayStartTime) / CLOCKS_PER_SEC;

    cout << "Array push_back(50000): " << ArraySeconds << "sec"<<" Size = "<<array.size() << endl;
    sumaArray += ArraySeconds;
    ArrayStartTime = clock();
    for (int i = 0; i < 10000; i++) {
        array.push_front(Diploma());
    }
    ArrayEndTime = clock();
    ArraySeconds = double(ArrayEndTime - ArrayStartTime) / CLOCKS_PER_SEC;
    cout << "Array push_front push_back(10000): " << ArraySeconds << "sec" << " Size = " << array.size() << endl;
    sumaArray += ArraySeconds;

    ArrayStartTime = clock();
    for (int i = 0; i < 20000; i++) {
        array.get(rand() % array.size()).Print();
    }
    ArrayEndTime = clock();
    ArraySeconds = double(ArrayEndTime - ArrayStartTime) / CLOCKS_PER_SEC;
    cout << "Array push_front get(20000): " << ArraySeconds << "sec" << " Size = " << array.size() << endl;
    sumaArray += ArraySeconds;
    ArrayStartTime = clock();
    for (int i = 0; i < 5000; i++) {
        array.pop_front();
    }
    ArrayEndTime = clock();
    ArraySeconds = double(ArrayEndTime - ArrayStartTime) / CLOCKS_PER_SEC;
    cout << "Array pop_front get(5000): " << ArraySeconds << "sec" << " Size = " << array.size() << endl;
    sumaArray += ArraySeconds;
    ArrayStartTime = clock();
    for (int i = 0; i < 5000; i++) {
        array.pop_back();
    }
    ArrayEndTime = clock();
    ArraySeconds = double(ArrayEndTime - ArrayStartTime) / CLOCKS_PER_SEC;
    cout << "Array pop_back get(5000): " << ArraySeconds << "sec" << " Size = " << array.size() << endl;
    sumaArray += ArraySeconds;

   
    cout << "ArraySeconds Time: " << sumaArray << " sec" << endl;

    return 0;
}
