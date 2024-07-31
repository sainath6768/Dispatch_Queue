#include <iostream>
#include "dispatchqueue.hpp"
#include "add.hpp"
#include "sub.hpp"
#include "div.hpp"
#include "mul.hpp"

using namespace std;


int main() 
{
    int number_1, number_2;

    cout << "Enter the number_1: ";
    cin >> number_1;
    cout << "Enter the number_2: ";
    cin >> number_2;

    Dispatcher dispatcher(4);  // Create 4 worker threads

    dispatcher.addTask(AddTwoNumbers, number_1, number_2);
    dispatcher.addTask(SubtractTwoNumbers, number_1, number_2);
    dispatcher.addTask(MultiplyTwoNumbers, number_1, number_2);
    dispatcher.addTask(DivideTwoNumbers, number_1, number_2);

    this_thread::sleep_for(chrono::seconds(1));

    return 0;
}