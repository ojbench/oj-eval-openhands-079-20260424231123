#include<iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

struct LinkedList {
    Node* head;
    
    LinkedList() : head(nullptr) {}
    
    void initialize() {
        int n;
        scanf("%d", &n);
        int *a = new int[n];
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);
        
        // Build linked list
        head = nullptr;
        Node* tail = nullptr;
        for(int i = 0; i < n; i++) {
            Node* newNode = new Node(a[i]);
            if(head == nullptr) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }
        
        delete[] a;
    }

    void insert(int i, int x) {
        Node* newNode = new Node(x);
        
        if(i == 0) {
            // Insert after position 0 (i.e., at the beginning)
            newNode->next = head;
            head = newNode;
            return;
        }
        
        Node* current = head;
        int count = 1;
        
        // Find the i-th node
        while(current != nullptr && count < i) {
            current = current->next;
            count++;
        }
        
        if(current != nullptr) {
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    void erase(int i) {
        if(head == nullptr) return;
        
        if(i == 1) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        
        Node* current = head;
        int count = 1;
        
        // Find the (i-1)-th node
        while(current != nullptr && current->next != nullptr && count < i-1) {
            current = current->next;
            count++;
        }
        
        if(current != nullptr && current->next != nullptr) {
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
        }
    }

    void swap() {
        if(head == nullptr || head->next == nullptr) return;
        
        Node* dummy = new Node(0);
        dummy->next = head;
        Node* prev = dummy;
        
        while(prev->next != nullptr && prev->next->next != nullptr) {
            Node* first = prev->next;
            Node* second = first->next;
            
            // Swap
            first->next = second->next;
            second->next = first;
            prev->next = second;
            
            // Move prev forward
            prev = first;
        }
        
        head = dummy->next;
        delete dummy;
    }

    void moveback(int i, int x) {
        if(head == nullptr || i <= 0) return;
        
        // Find the i-th node (end of first segment)
        Node* firstEnd = head;
        for(int count = 1; count < i; count++) {
            if(firstEnd->next == nullptr) return;
            firstEnd = firstEnd->next;
        }
        
        // Find the (i+x)-th node (where to insert)
        Node* insertPos = firstEnd;
        for(int count = 0; count < x && insertPos->next != nullptr; count++) {
            insertPos = insertPos->next;
        }
        
        // Store the original connections
        Node* secondStart = firstEnd->next;  // Start of second segment
        Node* insertNext = insertPos->next;  // What comes after insert position
        
        // Reconnect the segments
        firstEnd->next = insertNext;  // First segment connects to what was after insert position
        insertPos->next = head;       // Insert position connects to old head
        head = secondStart;           // New head is start of second segment
    }

    int query(int i) {
        Node* current = head;
        int count = 1;
        
        while(current != nullptr && count < i) {
            current = current->next;
            count++;
        }
        
        if(current != nullptr) {
            return current->data;
        }
        
        return 0; // Should not happen with valid input
    }

    void printAll() {
        Node* current = head;
        bool first = true;
        
        while(current != nullptr) {
            if(!first) printf(" ");
            printf("%d", current->data);
            current = current->next;
            first = false;
        }
        printf("\n");
    }

    void ClearMemory() {
        Node* current = head;
        while(current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
    }
};

int main() {
    LinkedList List;
    int m, op, i, x;
    List.initialize();
    scanf("%d", &m);
    while(m--) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d%d", &i, &x);
            List.insert(i, x);
        }
        else if(op == 2) {
            scanf("%d", &i);
            List.erase(i);
        }
        else if(op == 3) {
            List.swap();
        }
        else if(op == 4) {
            scanf("%d%d",&i, &x);
            List.moveback(i, x);
        }
        else if(op == 5) {
            scanf("%d", &i);
            printf("%d\n", List.query(i));
        }
        else if(op == 6) {
            List.printAll();
        }
    }
    List.ClearMemory();
    return 0;
}