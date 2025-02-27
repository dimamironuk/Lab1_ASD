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


    DynamicArray() : capacity(10), current_size(0) {
        diplomas = new Diploma[capacity];
    }
    void resize() {
        int new_capacity = capacity * 2;
        Diploma* new_data = new Diploma[new_capacity];

        for (int i = 0; i < current_size; i++) {
            new_data[i] = diplomas[i];
        }

        delete[] diplomas;
        diplomas = new_data;
        capacity = new_capacity;
    }

    void push_back(Diploma diploma) {
        if (current_size >= capacity) {
            resize();
        }
        diplomas[current_size++] = diploma;
    }

    Diploma pop_back() {
        if (current_size == 0) {
            cout << "Error. array is empty" << endl;
            return Diploma();
        }
        return diplomas[--current_size];
    }

    void push_front( Diploma diploma) {
        if (current_size >= capacity) {
            resize();
        }
        for (int i = current_size; i > 0; i--) {
            diplomas[i] = diplomas[i - 1];
        }
        diplomas[0] = diploma;
        current_size++;
    }

    Diploma pop_front() {
        if (current_size == 0) {
            cout << "Error. array is empty" << endl;
            return Diploma();
        }
        Diploma removed = diplomas[0];
        for (int i = 0; i < current_size - 1; i++) {
            diplomas[i] = diplomas[i + 1];
        }
        current_size--;
        return removed;
    }

    Diploma get(int index) {
        if (index < 0 || index >= current_size) {
            cout << "Error. index out of range" << endl;
            return Diploma();
        }
        return diplomas[index];
    }

    int size()  {
        return current_size;
    }

    void print()  {
        if (current_size == 0) {
            cout << "Empty\n";
            return;
        }
        for (int i = 0; i < current_size; i++) {
            cout << "#" << i << endl;
            diplomas[i].Print();
            cout << "-----------------------\n";
        }
    }

    void clear() {
        delete[] diplomas;
        capacity = 10;
        current_size = 0;
        diplomas = new Diploma[capacity];
    }

    ~DynamicArray() {
        delete[] diplomas;
    }
};

struct Node {
    Diploma value;

    Node* next;
    Node* prior;

    Node(Diploma value, Node* next, Node* prior)
    {
        this->value = value;
        this->next = next;
        this->prior = prior;
    }
};

struct LinkedList {
    int size;
    Node* head;
    Node* tail;

    LinkedList() : size(0), head(nullptr), tail(nullptr) {}

    void push_front(Diploma value) {
        Node* newNode = new Node(value, head, nullptr);
        if (head) head->prior = newNode;
        head = newNode;
        if (!tail) tail = newNode;
        size++;
    }

    void push_back(Diploma value) {
        Node* newNode = new Node(value, nullptr, tail);
        if (tail) tail->next = newNode;
        tail = newNode;
        if (!head) head = newNode;
        size++;
    }

    void print() {
        Node* value = head;
        while (value) {
            value->value.Print();
            value = value->next;
        }
    }

    Diploma get(int n) {
        if (n < 0 || n >= size) {
            cout << "Error: Index out of range" << endl;
            return Diploma("None", 0, 0);
        }
        Node* value = (size / 2 > n) ? head : tail;
        for (int i = 0; i < n; i++) {
            value = (size / 2 > n) ? value->next : value->prior;
        }
        return value->value;
    }

    void pop_front() {
        if (!head) return;
        Node* removeValue = head;
        head = head->next;
        if (head) head->prior = nullptr;
        else tail = nullptr;
        delete removeValue;
        size--;
    }

    void pop_back() {
        if (!tail) return;
        Node* removeValue = tail;
        tail = tail->prior;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete removeValue;
        size--;
    }

    void clear() {
        while (head) {
            pop_front();
        }
    }
    int sizeList() {
        return size;
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


int main() {
    srand(time(0));
    DynamicArray array;
    LinkedList list;
    clock_t ListStartTime = clock();
  
    for (int i = 0; i < 50000; i++) {
        list.push_back(Diploma());
    }

    for (int i = 0; i < 10000; i++) {
        list.push_front(Diploma());
    }

    for (int i = 0; i < 20000; i++) {
        list.get(rand() % list.sizeList()).Print();
    }

    for (int i = 0; i < 5000; i++) {
        list.pop_front();
    }

    for (int i = 0; i < 5000; i++) {
        list.pop_back();
    }

    clock_t ListEndTime = clock();

    clock_t ArrayStartTime = clock();
    for (int i = 0; i < 50000; i++) {
        array.push_back(Diploma());
    }

    for (int i = 0; i < 10000; i++) {
        array.push_front(Diploma());
    }

    for (int i = 0; i < 20000; i++) {
        array.get(rand() % array.size()).Print();
    }

    for (int i = 0; i < 5000; i++) {
        array.pop_front();
    }

    for (int i = 0; i < 5000; i++) {
        array.pop_back();
    }
    clock_t ArrayEndTime = clock();

    double ListSeconds = double(ListEndTime - ListStartTime) / CLOCKS_PER_SEC;
    double ArraySeconds = double(ArrayEndTime - ArrayStartTime) / CLOCKS_PER_SEC;
    cout << "List Time: " << ListSeconds << " sec" << endl;
    cout << "ArraySeconds Time: " << ArraySeconds << " sec" << endl;

    return 0;
}
