#include <iostream>
#include <fstream>       // for ifstream
#include <cctype>
#include <string>
#include <vector>
#include <sstream>      // std::stringstream

using namespace std;

// This commands struct is a basic building block for creating a singly linked list of commands. Each node (instance of the Commands struct) holds a command and a pointer to the next command in the list.
struct Commands {
    string command; // command name like print stack, call function and define
    Commands * down;

    Commands (string command, Commands * down)
      : command(command), down (down)
    {};
};

// This ServicesHead struct allows you to create a linked list of services, where each service has a name and a pointer to a list of associated commands.
struct ServicesHead {
    string name; // name of the functions
    ServicesHead * next;
    Commands * command; // it connects functions with commands
    
    ServicesHead (string function_name, ServicesHead * next)
      : name(function_name), next (next)
    {};
};

// This QueueInformation struct allows you to create a linked list of QueueInformation objects, where each object represents an item in a queue. The items have associated information such as ID, price, name, and the name of the function or service they are related to.
struct QueueInformation {
    
    int id, price; // users id and process prices
    string name; // user name
    string function_name;
    QueueInformation * next;
    
    QueueInformation(int num, string name, string function, int pricee)
      : id(num), name(name), function_name(function), price(pricee)
    {};
};

// This Stake struct allows you to create instances that represent a specific stake or function, with associated information about the commands or definitions related to that function. It's a simple container for storing and managing data related to functions or stakes in a program or system.
struct Stack {
    string function_name, defined; // defined refers to commands
    Stack * next;
    
    Stack(string name, string define)
      : function_name(name), defined(define)
    {};
};

// The DynUserQueue class provides a dynamic queue implementation using a linked list of QueueInformation nodes. It includes methods for enqueueing, dequeueing, and checking (isEmpty) the status of elements in the queue. The class also includes functionality to create a deep copy of the queue using the copy constructor and the createClone method.
class DynUserQueue {
    
    private:
        // These follow the rear and front of the queue.
        QueueInformation* front;
        QueueInformation* rear;
        
        QueueInformation get_helper(){ // A private method that returns a copy of the front of the queue.
            return * front;
        }
        
    public:
        DynUserQueue()
        {
            front = NULL;
            rear = NULL;
        }
    
        DynUserQueue(const DynUserQueue & copy){
                front = copy.createClone();
                rear = copy.createClone();
            }
        
        QueueInformation * createClone() const { // A private method that creates and returns a deep copy of the stack. It traverses the existing linked list and creates new nodes to
            if (front == NULL)  //if list is empty
                return NULL;
            
            QueueInformation * frontClone = new QueueInformation (front->id, front->name, front->function_name, front->price);
            QueueInformation * ptr = front->next;
            QueueInformation * ptrClone = frontClone;
            while (ptr != nullptr){
                ptrClone->next = new QueueInformation (ptr->id, ptr->name, ptr->function_name, ptr->price);
                ptr = ptr->next;
                ptrClone = ptrClone->next;
            }
            return frontClone;
        }
    
        QueueInformation get_data(){
            return get_helper();
        }
        
        void enqueue(string user_name, string user_func, int id, int price) // adding new request the queue
        {
            if (isEmpty())   //if the queue is empty
            {    //make it the first element
                front = new QueueInformation(id, user_name, user_func, price);
                rear = front;
            }
            else  //if the queue is not empty
            {    //add it after rear
                rear->next = new QueueInformation(id, user_name, user_func, price);
                rear = rear->next;
            }

        }
        
        void dequeue() // removing processed request from queue
        {
            QueueInformation *temp;
            if (!isEmpty())
            {
                //return front's value, advance front and delete old front
                temp = front;
                front = front->next;
                delete temp;
            }
        }
        
        bool isEmpty() const // checks that there is command in stack or not
        {
            if (front == NULL)
                return true;
            else
                return false;
        }
        
        void clear() // clears the queue
        {
            while(!isEmpty())
                dequeue(); //delete all elements
        }
};
    
// The DynUserStack class provides a dynamic stack implementation using a linked list of Stack nodes. It includes methods for push, pop, and checking (isEmpty) the status of elements in the stack. The class also includes functionality to create a deep copy of the stack using the copy constructor and the createClone method.
class DynUserStack{
    
    private:
        Stack* top;
    
        Stack get_helper_stack(){ // A private method that returns a copy of the top of the stack.
            return * top;
        }
        
    public:
        DynUserStack()
        {
            top = NULL;
        }
    
        DynUserStack(const DynUserStack & copy){
            top = copy.createClone();
        }
        
    Stack * createClone() const { // A private method that creates and returns a deep copy of the stack. It traverses the existing linked list and creates new nodes to form a copy.
        if (top == NULL)  //if list is empty
            return NULL;
        
            Stack * topClone = new Stack (top->function_name, top->defined);
            Stack * ptr = top->next;
            Stack * ptrClone = topClone;
            while (ptr != nullptr){
                ptrClone->next = new Stack (ptr->function_name, ptr->defined);
                ptr = ptr->next;
                ptrClone = ptrClone->next;
            }
        return topClone;
        }
    
        Stack get_stack(){
            return get_helper_stack();
        }
    
        void push(string command, string function) // adding new commands to stack
            {
                Stack *newCommand;
                
                // Allocate a new node & store Num
                newCommand = new Stack(function, command);
                // If there are no nodes in the list
                // make newNode the first node
                if (isEmpty())
                {
                    top = newCommand;
                    newCommand->next = NULL;
                }
                else    // Otherwise, insert NewNode before top
                {
                    newCommand->next = top;
                    top = newCommand;
                }
            }
            
        void pop() // removing command from stack
            {
                Stack *temp;
                
                if (isEmpty())
                {
                    cout << "The stack is empty.\n";
                }
                else    // pop value off top of stack
                {
                    temp = top->next;
                    delete top;
                    top = temp;
                }
            }

        bool isEmpty(void) // checks that there is command in stack or not
            {
                bool status;
                
                if (top == NULL)
                    status = true;
                else
                    status = false;
                
                return status;
            }
};

int counter = 0; // This global variable counts the number of instructer process

// The process function is designed to execute a sequence of commands associated with a specific function, updating the tempqueue and share_stack as it goes. It uses a combination of iteration and recursion to execute commands and maintain a stack of function calls.
void processWorkload(string function_name, string user_name, int user_id, int &user_price, DynUserQueue &tempqueue, ServicesHead * service_head, DynUserStack share_stack){
    
    ServicesHead * ptr = service_head;
    while (ptr){  // While loop is aimed to find the searched function
        
        if (ptr->name == function_name)
            break;
        if (ptr)
            ptr = ptr->next;
    }
    if (ptr){
        
        Commands * command = ptr->command;
        while (command){ // While loop is aimed to process commands orderly
            
            if (command->command.find("print") != string::npos){ // if statement is aimed to prints the content of the program stack
                
                user_price +=  2; // updates the users commands price
                cout << "Executing "<< command->command <<" command from " << function_name.substr(0,function_name.length()-1) << "\nPRINTING THE STACK TRACE:\n";
                
                if (share_stack.isEmpty())
                    cout << "The stack is empty\n";
                
                else {
                    DynUserStack temp(share_stack);
                    DynUserStack print;

                    while (!temp.isEmpty()){ // While loop passes information to another stack
                        Stack stack_data = temp.get_stack();
                        string stack_command = stack_data.defined;
                        string stack_function = stack_data.function_name;
                        print.push(stack_command, stack_function);
                        temp.pop();
                    }
        
                    while (!print.isEmpty()){ // while loop prints to information
                        Stack print_data = print.get_stack();
                        cout << print_data.function_name << " " << print_data.defined << endl;
                        print.pop();
                    }
                }
            }
            else if ((command->command).substr(0,6) == "define"){ // if statement is aimed to push the variable to the program stack
                
                share_stack.push(command->command, function_name);
                user_price +=  1; // updates the users commands price
            }
            else if ((command->command).substr(0,4) == "call"){ // if statement is aimed to process with the execution of the newly called one.
                
                string f_name = command->command.substr(5,command->command.size()-6) + ":"; // new function
                cout << "Calling" << command->command.substr(4,command->command.length()-5) << " from " << function_name.substr(0,function_name.length()-1) << endl;
                user_price +=  5; // updates the users commands price
                bool flag = false;
                ServicesHead * control_function = service_head;
                
                while (control_function){ // while loop is intended to control that Is the new function in our linklist (service_head), if there is, flag is true
                    
                    if (control_function->name == f_name){
                        flag = true;
                        break;
                    }
                    else if (control_function)
                        control_function = control_function->next;
                }
                if (flag == true) // if new function is in our linklist, it process that recursively
                    processWorkload(f_name, user_name, user_id, user_price, tempqueue, service_head, share_stack);
            }
            command = command->down;
        }
        if (command == nullptr){ // When functions commands are processed, it return the message
            cout << function_name.substr(0,function_name.length()-1) << " is finished. Clearing the stack from it's data..." << endl;
            while (!share_stack.isEmpty()) // it clears the share_stack which includes processed commands
                share_stack.pop();
        }
    }
}

// This processWorkload function appears to be part of a system for managing and processing service requests from instructors and students. It controls the flow of requests, ensures that only 10 instructor requests are processed before processing a student request, and delegates the actual command execution to the process function.
void processWorkload(string function_name, string user_name, int user_id, int user_price, DynUserQueue &studentsQueue, DynUserQueue &instructorsQueue, ServicesHead * service_head, DynUserStack share_stack, DynUserQueue &temporary)
{
    // This if statement is used when counter is equal to 10, if the number of instructor process reaches 10 this if statement applies the student process
    if (counter == 10 && !studentsQueue.isEmpty()){
        
        QueueInformation data = studentsQueue.get_data(); // it forms the necessary information of the requested student
        user_price = data.price;
        user_id = data.id;
        user_name = data.name;
        function_name = data.function_name;

        counter = 0; //  After student process, instructor process is available
        if (!studentsQueue.isEmpty())
        {
            function_name = function_name + ":";
            cout << "10 instructors are served. Taking 1 student from the queue..." << endl;
            cout << "Processing " << user_name << "'s request (with ID " << user_id << ") of service (function):\n" << function_name.substr(0,function_name.length()-1) << endl;
            cout << "-------------------------------------------------------" << endl;

            processWorkload(function_name, user_name, user_id, user_price, studentsQueue, service_head, share_stack); // According to user information, this function process
            DynUserQueue price;
            
            while (!temporary.isEmpty()){ // While loop is aimed to update the process price of the users, it updates temporary of queue by transferring information one queue to another queue
                string temp_name, temp_function;
                int temp_id, temp_price;
                QueueInformation temp_data = temporary.get_data();
                temp_price = temp_data.price;
                temp_id = temp_data.id;
                temp_name = temp_data.name;
                temp_function = temp_data.function_name;
                
                if (temp_name == user_name && temp_id == user_id)
                    price.enqueue(user_name, function_name, user_id, user_price + temp_price);
                else
                    price.enqueue(temp_name, temp_function, temp_id, temp_price); // add request to price stacke
                
                temporary.dequeue();
            }
            temporary = price;
            studentsQueue.dequeue(); // removes processed user from queue
            cout << "GOING BACK TO MAIN MENU" << endl;
        }
    }
    // This else statement is used when counter is not equal to 10, if the number of instructor process does not reach 10 this else statement applies the student and instructor process
    else {
        
        if (!instructorsQueue.isEmpty())
        {
            QueueInformation data = instructorsQueue.get_data(); // it forms the necessary information of the requested student
            user_price = data.price;
            user_id = data.id;
            user_name = data.name;
            function_name = data.function_name;
            function_name = function_name + ":";
            
            cout << "Processing instructors queue..." << endl;
            cout << "Processing prof." << user_name << "'s request (with ID " << user_id << ") of service (function):\n" << function_name.substr(0,function_name.length()-1) << endl;
            cout << "-------------------------------------------------------" << endl;
            
            processWorkload(function_name, user_name, user_id, user_price, instructorsQueue, service_head, share_stack); // According to user information, this function process
            DynUserQueue price;
            
            while (!temporary.isEmpty()){ // While loop is aimed to update the process price of the users, it updates temporary of queue by transferring information one queue to another queue
                string temp_name, temp_function;
                int temp_id, temp_price;
                QueueInformation temp_data = temporary.get_data();
                temp_price = temp_data.price;
                temp_id = temp_data.id;
                temp_name = temp_data.name;
                temp_function = temp_data.function_name;
                
                if (temp_name == user_name && temp_id == user_id)
                    price.enqueue(user_name, function_name, user_id, user_price + temp_price); // add request to price stacke
                else
                    price.enqueue(temp_name, temp_function, temp_id, temp_price);
                
                temporary.dequeue();
            }
            temporary = price;
            counter++; // if the instructor processed, update counter
            instructorsQueue.dequeue(); // removes processed user from queue
            cout << "GOING BACK TO MAIN MENU" << endl;
        }
        else if (!studentsQueue.isEmpty())
        {
            QueueInformation data = studentsQueue.get_data(); // it forms the necessary information of the requested student
            user_price = data.price;
            user_id = data.id;
            user_name = data.name;
            function_name = data.function_name;
            function_name = function_name + ":";
            
            cout << "Instructors queue is empty. Proceeding with students queue..." << endl;
            cout << "Processing " << user_name << "'s request (with ID " << user_id << ") of service (function):\n" << function_name.substr(0,function_name.length()-1) << endl;
            cout << "-------------------------------------------------------" << endl;
            
            processWorkload(function_name, user_name, user_id, user_price, studentsQueue, service_head, share_stack); // According to user information, this function process
            DynUserQueue price;

            while (!temporary.isEmpty()){ // While loop is aimed to update the process price of the users, it updates temporary of queue by transferring information one queue to another queue
                string temp_name, temp_function;
                int temp_id, temp_price;
                QueueInformation temp_data = temporary.get_data();
                temp_price = temp_data.price;
                temp_id = temp_data.id;
                temp_name = temp_data.name;
                temp_function = temp_data.function_name;
                
                if (temp_name == user_name && temp_id == user_id)
                    price.enqueue(user_name, function_name, user_id, user_price + temp_price); // add request to price stacke
                else
                    price.enqueue(temp_name, temp_function, temp_id, temp_price);
                
                temporary.dequeue();
            }
            temporary = price;
            studentsQueue.dequeue(); // removes processed user from queue
            cout << "GOING BACK TO MAIN MENU" << endl;
        }
        else
            cout << "Both instructor's and student's queue is empty.\nNo request is processed." << endl << "GOING BACK TO MAIN MENU" << endl;
    }
}

// The purpose of this read_files function is to allow the user to define and read service definitions from files, and it creates a data structure that organizes these services with their associated commands. The created linked list of services can be used by other parts of the program to execute the specified commands when requested.
bool read_files (ServicesHead * &service_head){
    
    bool control = false; // it is used to control when there is a problem or not
    ServicesHead * temp;
    Commands * head = nullptr, * ptr = nullptr;
    string answer = "", filename = "", line, service_name, commands;
    cout << "If you want to open a service (function) defining file,\nthen press (Y/y) for 'yes', otherwise press any single key" << endl;
    cin >> answer;
    
    if (answer == "Y" || answer == "y"){
        cout << "Enter the input file name: ";
        cin >> filename;
        ifstream input(filename);
        
        if (input.fail()){ // when file is not opened, it terminates the program
            cout << "Could not open the file " << filename << endl;
            control = true;
        }
        else {
            getline(input, service_name);
            service_head = new ServicesHead(service_name.substr(0,service_name.size()-1), nullptr); // first function of linklist
            temp = service_head;
            getline(input, commands);
           
            if (commands[commands.length()-1]=='\r')
                commands = commands.substr(0,commands.size()-1);
            head = new Commands(commands, nullptr); // first command of first function
            ptr = head;
            service_head->command = ptr; // connects function with command
            
            while(getline(input, commands)){ // while loop is intended to adding commands to linklist
                if (commands[commands.length()-1]=='\r')
                    commands = commands.substr(0,commands.size()-1);
                ptr->down = new Commands(commands, nullptr);
                ptr = ptr->down;
            }
            bool flag = false;
            
            do {
                cout << "Do you want to open another service defining file?\nPress (Y/y) for 'yes', otherwise press anykey" << endl;
                cin >> answer;
                if (answer == "Y" || answer == "y"){
                    
                    cout << "Enter the input file name: ";
                    cin >> filename;
                    ifstream other_input(filename);
                    if (other_input.fail()){ // when file is not opened, it terminates the program
                        cout << "Could not open the file " << filename << endl;
                        control = true;
                        break;
                    }
                    Commands * f_head = nullptr, * temporary = nullptr;
                    getline(other_input, service_name);
                    temp->next = new ServicesHead(service_name.substr(0,service_name.size()-1), nullptr); // other function of linklist
                    getline(other_input, commands);
                    if (commands[commands.length()-1]=='\r')
                        commands = commands.substr(0,commands.size()-1);
                    f_head = new Commands(commands, nullptr); // first command of other function
                    temporary = f_head;
                    temp->next->command = temporary; // connects function with command
                    
                    while(getline(other_input, commands)){ // while loop is intended to adding commands to linklist
                        if (commands[commands.length()-1]=='\r')
                            commands = commands.substr(0,commands.size()-1);
                        temporary->down = new Commands(commands, nullptr);
                        temporary = temporary->down;
                    }
                    temp = temp->next;
                }
                else
                    flag = true;
            } while (flag == false);
            
            if (control == false){
                cout << "------------------------------------------------------------------\nPRINTING AVAILABLE SERVICES (FUNCTIONS) TO BE CHOSEN FROM THE USERS\n------------------------------------------------------------------\n\n";
                
                ServicesHead * read1 = service_head;
                while (read1){ // While loop is intended to prints functions and their commands orderly
                    
                    Commands * read2 = read1->command;
                    cout << "\n" << read1->name << "\n";
                    while (read2->down){
                        cout << read2->command << ", ";
                        read2 = read2->down;
                    }
                    read2->command = read2->command.substr(0,read2->command.size()-1);
                    cout << read2->command << ".\n";
                    read1 = read1->next;
                }
            }
        }
    }
    return control;
}

// The control_user function appears to check whether a given combination of name and id (user) exists in a dynamic queue (temporary) of user information.
bool control_user(string name, int id, DynUserQueue temporary){
    
    bool flag = false;
    while (!temporary.isEmpty()){
        QueueInformation temp_data = temporary.get_data();
        if (temp_data.name == name && temp_data.id == id){
            flag = true;
            break;
        }
        else
            temporary.dequeue();
    }
    return flag;
}

// The addInstructorWorkload function allows an instructor to request a service by specifying the function name, instructor's name, and instructor ID. The request is then added to the queue for instructors' service requests for later processing. If the requested service does not exist, an error message is displayed, and no request is added to the queue.
void addInstructorWorkload(ServicesHead * service_head,  DynUserQueue &instructorsQueue, DynUserQueue &temporary){
    
    string function_name, instructor_name;
    int instructor_id, price = 0;
    bool flag = false;
    cout << "Add a service (function) that the instructor wants to use:" << endl;
    cin >> function_name;
    while (service_head){ // control that Does the requested function exist or not in data structure
        if (service_head->name.substr(0,service_head->name.size()-1) == function_name){
            flag = true;
            break;
        }
        service_head = service_head->next;
    }
    if (flag == false)
        cout << "The requested service (function) does not exist.\nGOING BACK TO MAIN MENU\n";
    else{
        cout << "Give instructor's name: ";
        cin >> instructor_name;
        cout << "Give instructor's ID (an int): ";
        cin >> instructor_id;
        cout << "Prof. " << instructor_name << "'s service request of " << function_name << endl << "has been put in the instructor's queue.\nWaiting to be served...\n";
        bool control = control_user(instructor_name, instructor_id, temporary);
        if (control == false)
            temporary.enqueue(instructor_name, function_name, instructor_id, price); // Adding new request to queue to control the order of requests
        instructorsQueue.enqueue(instructor_name, function_name, instructor_id, price); // Adding new request to queue
    }
}

// The addStudentWorkload function allows a student to request a service by specifying the function name, student's name, and student ID. The request is then added to the queue for students' service requests for later processing. If the requested service does not exist, an error message is displayed, and no request is added to the queue.
void addStudentWorkload(ServicesHead * service_head,  DynUserQueue &studentsQueue, DynUserQueue &temporary){
                        
    string function_name, student_name;
    int student_id, price = 0;
    bool flag = false;
    cout << "Add a service (function) that the student wants to use:" << endl;
    cin >> function_name;
    while (service_head){ // control that Does the requested function exist or not in data structure
        if (service_head->name.substr(0,service_head->name.size()-1) == function_name){
            flag = true;
            break;
        }
        service_head = service_head->next;
    }
    if (flag == false)
        cout << "The requested service (function) does not exist.\nGOING BACK TO MAIN MENU\n";
    else{
        cout << "Give student's name: ";
        cin >> student_name;
        cout << "Give student's ID (an int): ";
        cin >> student_id;
        cout << student_name << "'s service request of " << function_name << " has been put in the student's queue.\nWaiting to be served...\n";

        if (control_user(student_name, student_id, temporary) == false)
            temporary.enqueue(student_name, function_name, student_id, price); // Adding new request to queue to control the order of requests
        studentsQueue.enqueue(student_name, function_name, student_id, price); // Adding new request to queue
    }
}

// The displayUsers function is intended to display the names, IDs, and prices of users stored in a queue of QueueInformation objects. If the queue is empty, it indicates that no payments are defined, and if the queue is not empty, it displays the user information and dequeues the users one by one.
void displayUsers(DynUserQueue temporary){
    
    if (temporary.isEmpty())
        cout << "No payments defined." << endl;
    while (!temporary.isEmpty()){
        cout << "Name: " << temporary.get_data().name << " ID: " << temporary.get_data().id << " " << temporary.get_data().price << " TRY" << endl;
        temporary.dequeue();
    }
}

//  This delete_linked_list function is designed to delete a linked list of nodes, where each node has an associated linked list of commands. It does so by traversing the linked list and deleting nodes and their associated command lists.
void delete_linked_list(ServicesHead * service_head){
    
    ServicesHead * ptr;
    while (service_head) {
        Commands * temp, * temporary;
        temp = service_head->command;
        while (temp) {
            temporary = temp->down;
            delete temp;
            temp = temporary;
        }
        ptr = service_head->next;
        delete service_head;
        service_head = ptr;
    }
}

int main()
{
    ServicesHead * service_head = nullptr;
    DynUserQueue studentsQueue; // The studentsQueue have students requests
    DynUserQueue instructorsQueue; // The instructorsQueue have instructor requests
    DynUserQueue temporary; // The queue temporary includes the information of the users like names, IDs, prices, it is used to control the order of requests
    DynUserStack commands; // The stake commands is share stack which includes the commands (print stack, call function, define) of functions
    
    if (read_files (service_head) == false){
      
        while (true){
            cout << endl;
            cout<<"**********************************************************************"<<endl
            <<"**************** 0 - EXIT PROGRAM                        *************"<<endl
            <<"**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST   *************"<<endl
            <<"**************** 2 - ADD A STUDENT SERVICE REQUEST       *************"<<endl
            <<"**************** 3 - SERVE (PROCESS) A REQUEST           *************"<<endl
            <<"**************** 4 - DISPLAY USER PAYMENTS               *************"<<endl
            <<"**********************************************************************"<<endl;
            cout << endl;
            int option;
            cout << "Pick an option from above (int number from 0 to 3): ";
            cin>>option;
            string name = "", f_name = "";
            int id = 0, price = 0;
            switch (option)
            {
                case 0:
                    cout<<"PROGRAM EXITING ... "<<endl;
                    exit(0);
                case 1:
                    addInstructorWorkload(service_head, instructorsQueue, temporary);
                    break;
                case 2:
                    addStudentWorkload(service_head, studentsQueue, temporary);
                    break;
                case 3:
                    processWorkload(name, f_name, id, price, studentsQueue, instructorsQueue, service_head, commands, temporary);
                    break;
                case 4:
                    displayUsers(temporary);
                    break;
                default:
                    cout<<"INVALID OPTION!!! Try again"<<endl;
            }
        }
    }
    temporary.clear(); // not give up memory leak
    delete_linked_list(service_head); // not give up memory leak
    return 0;
}
// SULEYMAN BERBER
