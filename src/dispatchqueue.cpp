#include "dispatchqueue.hpp"

Task::Task(TaskFunction func,int num1,int num2) : taskFunc(func), number_1(num1) , number_2(num2) {}

void Task::execute() 
{
    if (taskFunc) 
    {
        int result = taskFunc(number_1, number_2);
        cout << "Result: " << result << "(Thread ID : " <<  this_thread::get_id() << ")" << endl;
    }
}

Dispatcher::Dispatcher(size_t num_threads) : stop(false) 
{
    //worker = thread(&Dispatcher::ProcessTasks, this);

    for (size_t i = 0; i < num_threads; ++i) 
    {
        workers.emplace_back(&Dispatcher::ProcessTasks, this);
    }
}
Dispatcher::~Dispatcher() 
{
    {
        unique_lock<mutex> lock(mtx);
        stop = true;
    }
    cv.notify_all();  // Notify the worker thread to stop
    //worker.join();
    for (auto& worker : workers) 
    {
        if (worker.joinable()) 
        {
            worker.join();
        }
    }
}

void Dispatcher::addTask(Task::TaskFunction taskFunc,int number_1,int number_2) 
{
    // workers.push_back(thread([taskFunc]() {
    //     Task(taskFunc).execute();
    // }));
    {
        unique_lock<mutex> lock(mtx);
        tasks.emplace(taskFunc, number_1, number_2);
    }
    cv.notify_one();
}


void Dispatcher::ProcessTasks() 
{
    while (true) 
    {
        Task task;
        {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this] { return !tasks.empty() || stop; }); // Wait for tasks or stop signal
            if (stop && tasks.empty()) 
            {
                return;
            }
            task = tasks.front();
            tasks.pop();
        }
        task.execute();  // Call the execute method
    }
}
