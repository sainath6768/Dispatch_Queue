#ifndef DISPATCH_QUEUE_HPP
#define DISPATCH_QUEUE_HPP

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>
#include <vector>

using namespace std;

class Task 
{
public:
    using TaskFunction = function<int(int ,int )>;  

    Task(TaskFunction func = nullptr,int num_1=0,int num_2=0);
    void execute(); 

private:
    TaskFunction taskFunc;
    int number_1, number_2;
};

class Dispatcher 
{
public:
    Dispatcher(size_t num_threads);
    ~Dispatcher();
    void addTask(Task::TaskFunction taskFunc,int number_1,int number_2); 

private:
    void ProcessTasks(); 

    queue<Task> tasks;
    mutex mtx;
    condition_variable cv;
    //thread worker;
    vector<thread> workers;
    bool stop=false;
};
#endif
