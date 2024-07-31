#include "Task.hpp"

Task::Task(TaskFunction func) : taskFunc(func) {}

void Task::execute() 
{
    if (taskFunc) 
    {
        taskFunc();
    }
}