# Stacks-Queues-and-request-services

This project’s aim is to make you familiar with the logic behind queues and stacks (and a bit of
simply linked lists of linked lists, again) as well as recursions by practically using them in a real-case
scenario (you will probably encounter similar cases as a future programmer).

Namely, SU offers a certain number of services to its academic stuff and students (such as data
processing). The service requests are implemented as functions. You will keep the requests in a linked-
list base queue. The requests of the students and the academic stuff (instructors) are kept separately
and served in a First In First Out (FIFO) manner, thus we need two separate queues for both of them.
Each service (function) request contains a set of instructions (commands) described in the next section.
A certain service (function) can be a part of (called from) another function (e.g. print the output data
after processed from the supercomputer). Besides that, SU bills users for their total service usage. Price
of each service differs according to the commands it contains.

As it is common in modern day systems, for this reason we will need a single, commonly shared
memory stack to put on and serve in First In Last Out (FILO) manner those subsequent service (function)
calls. All of this is illustrated in Fig.1. Also, in order to process those consecutive function calls, you will be
asked to implement a recursive function that calls an instance of itself at any time a new function call is
issued. This will be more clarified in the ‘main menu & program guide’
section.

<img width="541" alt="Screenshot 2024-01-22 at 14 35 39" src="https://github.com/suleymanbrbr/Stacks-Queues-and-request-services/assets/111366311/76afe944-0d1a-4b41-abf3-d2eb418802c5">

For all of the input files, your job will be to construct a simply linked list of the commands. Eventually,
after reading all of your input files (in our case 3 input files), you should finish with a structure shown in
Fig.3.
<img width="429" alt="Screenshot 2024-01-22 at 14 35 58" src="https://github.com/suleymanbrbr/Stacks-Queues-and-request-services/assets/111366311/70ba453c-a23f-4ef6-9386-19d399d5b6f1">

If the requested service exists, then we are prompted for the name and ID of the student.
Subsequently, his/hers request is put in the instructors queue and a message is displayed and we are
sent back to the main menu.
<img width="437" alt="Screenshot 2024-01-22 at 14 36 32" src="https://github.com/suleymanbrbr/Stacks-Queues-and-request-services/assets/111366311/458baedd-d968-49dd-8ecb-78fc6a30bf12">
