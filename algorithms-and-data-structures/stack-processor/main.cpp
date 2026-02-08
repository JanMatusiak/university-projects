#include <iostream>
using namespace std;

struct Node {
    char e;
    Node* next;
    explicit Node(char c) : e(c), next(nullptr) {}
} ;

struct List {
    Node* head;
    explicit List() : head(nullptr) {}
} ;

Node* readList() {
    Node* head = nullptr;
    Node* tail = nullptr;
    int ch;
    while((ch = getchar()) != '\n' && ch != EOF) {
        Node* node = new Node((char)ch);
        if (!head) {
            head = node;
            tail = node;
        }
        else {
            tail->next = node;
            tail = node;
        }
    }
    return head;
}

void freeNodes(Node* node){
    if(!node) return;
    Node* next = node->next;
    delete node;
    node = next;
    freeNodes(node);
}

void freeList(List* list){
    if(!list) return;
    freeNodes(list->head);
    delete list;
}

Node* copyNodes(Node* node){
    if(!node) return nullptr;
    Node* copiedNode = new Node(node->e);
    copiedNode->next = copyNodes(node->next);
    return copiedNode;
}

List* copyList(List* list){
    if(!list) return nullptr;
    List* copiedList = new List();
    copiedList->head = copyNodes(list->head);
    return copiedList;
}

Node* lastNode(Node* node){
    if(!node || !node->next) return node;
    return lastNode(node->next);
}

int convert(Node* node){
    if(!node || node->e == '-') return 0;
    return (node->e - '0') + 10 * convert(node->next);
}

int convertToInt(List* list){
    if(!list || !list->head) return 0;
    int integer = convert(list->head);
    if(lastNode(list->head)->e == '-'){
        integer = -integer;
    }
    return integer;
}

void prepend(List* list, char instruction){
    Node* node = new Node(instruction);
    node->next = list->head;
    list->head = node;
}

void removeLastNode(Node*& node){
    if(node == nullptr) return;
    if(node->next == nullptr){
        delete node;
        node = nullptr;
    }
    else removeLastNode(node->next);
}

void append(Node* node, char ch){
    Node* last = lastNode(node);
    last->next = new Node(ch);
}

Node* convertToListRec(int number){
    if(number == 0) return 0;
    Node* node = new Node((number % 10) + '0');
    node->next = convertToListRec(number/10);
    return node;
}

List* convertToList(int number){
    List* list = new List();
    if(number == 0){
        list->head = new Node('0');
    }
    else {
        list->head = convertToListRec(number);
    }
    return list;
}

void appendList(Node*& source, Node*& destination){
    if(destination == nullptr){
        destination = source;
    }
    else if(destination->next == nullptr){
        destination->next = source;
    }
    else{
        appendList(source, destination->next);
    }
}

Node* absolute(Node* head){
    if(!head) return nullptr;
    if(!head->next){
        if(head->e == '-'){
            return nullptr;
        }
        else{
            return new Node(head->e);
        }
    }
    Node* newNode = new Node(head->e);
    newNode->next = absolute(head->next);
    return newNode;
}

Node* reverseList(Node* head){
    if(!head || !head->next) return head;
    Node* rest = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    return rest;
}

Node* trimZeros(Node* head){
    if(!head) return nullptr;
    if(head->e == '0' && head->next){
        Node* temp = head->next;
        delete head;
        return trimZeros(temp);
    }
    return head;
}

Node* standardize(List* list){
    if(!list || !list->head) return new Node('0');
    char sign = lastNode(list->head)->e;
    bool negative = (list && sign == '-');

    Node* abs = absolute(list->head);
    Node* reversed = reverseList(abs);
    Node* final = trimZeros(reversed);

    if(!final) return new Node('0');
    if(!final->next && final->e == '0') negative = false;
    if(negative){
        Node* sign = new Node('-');
        sign->next = final;
        final = sign;
    }
    return final;
}

bool isNegative(List* list) {
    if (!list || !list->head)
        return false;
    return (lastNode(list->head)->e == '-');
}

int listLength(Node* head){
    if(!head) return 0;
    return 1 + listLength(head->next);
}

int compareStandardized(Node* head_A, Node* head_B){
    if(!head_A && !head_B) return 0;
    if(!head_A) return -1;
    if(!head_B) return 1;
    if(head_A->e == head_B->e) return compareStandardized(head_A->next, head_B->next);
    return head_A->e > head_B->e ? 1 : -1;
}

int compareLists(List* list_A, List* list_B){ // returns -1 if list_A < list_B, 0 if == and 1 if >
    Node* standard_A = standardize(list_A);
    Node* standard_B = standardize(list_B);

    bool neg_A = standard_A && standard_A->e == '-';
    bool neg_B = standard_B && standard_B->e == '-';

    if(neg_A != neg_B){
        int result = neg_A ? -1 : 1;
        freeNodes(standard_A);
        freeNodes(standard_B);
        return result;
    }

    int length_A = neg_A ? listLength(standard_A->next) : listLength(standard_A);
    int length_B = neg_B ? listLength(standard_B->next) : listLength(standard_B);

    int result = 0;

    if(length_A != length_B){
        if(neg_A) result = length_A > length_B ? -1 : 1;
        else result = length_A > length_B ? 1 : -1;
    }
    else{
        result = compareStandardized(neg_A ? standard_A->next : standard_A, neg_B ? standard_B->next : standard_B);
        if(neg_A && neg_B) result = -result;
    }

    freeNodes(standard_A);
    freeNodes(standard_B);
    return result;
}

Node* addRec(Node* a, Node* b, int carry){
    if(!a && !b && carry == 0) return nullptr;
    int int_a = a ? a->e - '0' : 0;
    int int_b = b ? b->e - '0' : 0;
    int sum = int_a + int_b + carry;
    int digit = sum % 10;
    int newCarry = sum / 10;
    Node* newNode = new Node(digit + '0');
    newNode->next = addRec(a ? a->next : nullptr, b ? b->next : nullptr, newCarry);
    return newNode;
}

List* addLists(List* list_A, List* list_B){
    List* result = new List();
    result->head = addRec(list_A ? list_A->head : nullptr, list_B ? list_B->head : nullptr, 0);
    return result;
}

Node* substractRec(Node* a, Node* b, int borrow){
    if(!a && !b && borrow == 0) return nullptr;
    int int_a = a ? a->e - '0' : 0;
    int int_b = b ? b->e - '0' : 0;
    int difference = int_a - int_b - borrow;
    int newBorrow = 0;
    if(difference < 0){
        difference += 10;
        newBorrow = 1;
    }
    Node* newNode = new Node(difference + '0');
    newNode->next = substractRec(a ? a->next : nullptr, b ? b->next : nullptr, newBorrow);
    return newNode;
}       

List* substractLists(List* list_A, List* list_B){
    List* result = new List();
    Node* node = substractRec(list_A ? list_A->head : nullptr, list_B ? list_B->head : nullptr, 0);
    Node* reversed = reverseList(node);
    Node* final = trimZeros(reversed);
    result->head = reverseList(final);
    return result;
}

List* addition(List* list_A, List* list_B){
    bool neg_A = isNegative(list_A);
    bool neg_B = isNegative(list_B);
    
    List* absolute_A = new List();
    List* absolute_B = new List();
    List* result = nullptr;

    absolute_A->head = absolute(list_A->head);
    absolute_B->head = absolute(list_B->head);

    if(neg_A == neg_B){
        result = addLists(absolute_A, absolute_B);
        if(neg_A){
            if(result->head->e != '0' || result->head->next != nullptr){
                append(result->head, '-');
            }
        }
    }
    else {
        int compared = compareLists(absolute_A, absolute_B);
        if(compared == 0){
            result = new List();
            result->head = new Node('0');
        }
        else if(compared == 1){
            result = substractLists(absolute_A, absolute_B);
            if(neg_A){
                if(result->head->e != '0' || result->head->next != nullptr){
                    append(result->head, '-');
                }
            }
        }
        else if(compared == -1){
            result = substractLists(absolute_B, absolute_A);
            if(neg_B){
                if(result->head->e != '0' || result->head->next != nullptr){
                    append(result->head, '-');
                }
            }
        }
    }
    freeList(absolute_A);
    freeList(absolute_B);

    return result;
}

struct StackNode {
    List* data;
    StackNode* next;
    explicit StackNode(List* list): data(list), next(nullptr) {}
} ;

List* getListAt(StackNode* node, int index){
    if(!node) return nullptr;
    if(index == 0) return node->data;
    return getListAt(node->next, index - 1);
}

class Stack {
private:
    StackNode* top;

    void printNodes(Node* node) {
    if(!node) return;
    cout << node->e;
    printNodes(node->next);
    }

    void printStack(StackNode* node, int index){
    if(!node) return;
    printStack(node->next, index + 1);
    cout << index << ": ";
    if(node->data && node->data->head){
        printNodes(node->data->head);
    }
    cout << '\n';
    }

public:
    Stack(): top(nullptr) {}

    void push(List* list){
        StackNode* newNode = new StackNode(list);
        newNode->next = top;
        top = newNode;
    }

    List* pop(){
        if(!top) return nullptr;
        StackNode* temp = top;
        top = top->next;
        List* list = temp->data;
        delete temp;
        return list;
    }

    List* peek(){
        if(!top) return nullptr;
        List* list = top->data;
        return list;
    }

    List* getStackListAt(int index){
        return getListAt(top, index);
    }

    void print(){
        printStack(top, 0);
    }

    void freeStackNodes(StackNode* node){
        if(!node) return;
        freeList(node->data);
        freeStackNodes(node->next);
        delete node;
    }

    ~Stack(){
        freeStackNodes(top);
    }
} ;

void execute(Stack &stack, Node** programArray, Node* input, int instructionPointer, int numberOfInstructions){
    while(instructionPointer < numberOfInstructions){
        Node* instructionNode = programArray[instructionPointer];
        if(!instructionNode) break;
        char instruction = instructionNode->e;
        switch(instruction){
            case '\'' : {
                stack.push(new List);
                break;
            }
            case ',' : {
                List* list = stack.pop();
                freeList(list);
                break;
            }
            case ':' : {
                List* list = stack.peek();
                List* copiedList = copyList(list); 
                stack.push(copiedList);
                break;
            }
            case ';' : {
                List* first = stack.pop();
                List* second = stack.pop();
                if(first || second){
                    stack.push(first);
                    stack.push(second);
                }
                break;
            }
            case '@' : {
                List* top = stack.pop();
                int index = convertToInt(top);
                freeList(top);
                List* list = stack.getStackListAt(index);
                List* copiedList = copyList(list);
                stack.push(copiedList);
                break;
            }
            case '&' : {
                stack.print();
                break;
            }
            case '.' : {
                if(input){
                    char ch = input->e;
                    List* top = stack.peek();
                    if(top){
                        prepend(top, ch);
                    }
                    input = input->next;
                }
                break;
            }
            case '>' : {
                List* list = stack.pop();
                if(list && list->head){
                    cout << list->head->e;
                }
                freeList(list);
                break;
            }
            case '-': {
                List* top = stack.peek();
                if(top == nullptr) break;
                if(top->head != nullptr){
                    char last = lastNode(top->head)->e;
                    if(last == '-'){
                        removeLastNode(top->head);
                    }
                    else{
                        append(top->head, '-');
                    }
                } else {
                    top->head = new Node('-');
                }
                break;
            }
            case '^': {
                List* list = stack.peek();
                if(list && list->head){
                    if(lastNode(list->head)->e == '-'){
                        removeLastNode(list->head);
                    }
                }
                break;
            }
            case '[': {
                List* list = stack.pop();
                char ch = list->head->e;
                freeList(list);
                int ascii = (int)ch;
                List* newList = convertToList(ascii);
                stack.push(newList);
                break;
            }
            case ']': {
                List* list = stack.pop();
                int number = convertToInt(list);
                freeList(list);
                char ascii = (char)number;
                List* newList = new List();
                newList->head = new Node(ascii);
                stack.push(newList);
                break;
            }
            case '$': {
                List* top = stack.peek();
                if(!top || !top->head) break;
                Node* temp = top->head;
                char t = temp->e;
                top->head = temp->next;
                delete temp;
                List* newList = new List();
                newList->head = new Node(t);
                stack.push(newList);
                break;
            }
            case '#': {
                List* list_A = stack.pop();
                List* list_B = stack.peek();
                if(list_A){
                    appendList(list_A->head, list_B->head);
                }
                break;
            }
            case '<': {
                List* list_A = stack.pop();
                List* list_B = stack.pop();
                int result = compareLists(list_B, list_A);
                freeList(list_A);
                freeList(list_B);
                List* list = new List();
                if(result < 0){
                    list->head = new Node('1');
                }
                else {
                    list->head = new Node('0');
                }
                stack.push(list);
                break;
            }
            case '=': {
                List* list_A = stack.pop();
                List* list_B = stack.pop();
                int result = compareLists(list_A, list_B);
                freeList(list_A);
                freeList(list_B);
                List* list = new List();
                if(result == 0){
                    list->head = new Node('1');
                }
                else {
                    list->head = new Node('0');
                }
                stack.push(list);
                break;
            }
            case '!' : {
                List* list = stack.pop();
                if(list->head == nullptr || (list->head->e == '0' && list->head->next == nullptr)){
                    list->head = new Node('1');
                }
                else {
                    list->head = new Node('0');
                }
                stack.push(list);
                break;
            }
            case '~' : {
                List* list = convertToList(instructionPointer);
                stack.push(list);
                break;
            }
            case '?' : {
                List* top_t = stack.pop();
                List* top_w = stack.pop();
                int target = convertToInt(top_t);
                freeList(top_t);
                if(top_w != nullptr && top_w->head != nullptr){
                    if(top_w->head->next != nullptr || top_w->head->e != '0'){
                        instructionPointer = target - 1;
                    }
                }
                freeList(top_w);
                break;
            }
            case '+' : {
                List* list_a = stack.pop();
                List* list_b = stack.pop();
                List* list_c = addition(list_a, list_b);
                stack.push(list_c);
                freeList(list_a);
                freeList(list_b);
                break;
            }
            default : {
                List* top = stack.peek();
                if(top){
                    prepend(top, instruction);
                }
            }
        }
        instructionPointer++;
    }
}

int countNodes(Node* head){
    if(!head) return 0;
    return 1 + countNodes(head->next);
}

void fillProgramArray(Node** programArray, Node* program, int index, int numberOfInstructions) {
    if(index >= numberOfInstructions) return;
    programArray[index] = program;
    fillProgramArray(programArray, program->next, index + 1, numberOfInstructions);
}

int main(){
    Node* program = readList();
    Node* input = readList();

    int numberOfInstructions = countNodes(program);
    Node** programArray = new Node*[numberOfInstructions];
    fillProgramArray(programArray, program, 0, numberOfInstructions);

    Stack stack;

    execute(stack, programArray, input, 0, numberOfInstructions);

    delete[] programArray;
    return 0;
}