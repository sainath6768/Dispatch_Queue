##ifndef TASK_HPP
#define TASK_HPP

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>

using namespace std;

class Task 
{
public:
    using TaskFunction = function<void()>;  // Change to function

    Task(TaskFunction func = nullptr);
    void execute(); 

private:
    TaskFunction taskFunc;
};

class Dispatcher 
{
public:
    Dispatcher();
    ~Dispatcher();
    void addTask(Task::TaskFunction taskFunc); 

private:
    void ProcessTasks(); 

    queue<Task> tasks;
    mutex mtx;
    condition_variable cv;
    vector<thread> workers;
    bool stop;
};
#endif
