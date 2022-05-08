#include <iostream>
#include "Queue.hpp"
int main()
{
        MyQueue<int> q(5);

        int name = 24;

        q.push(name, 3);

        int name2 = 55;
        q.push(name2, 4); //push(const MyString&)

        q.push(66, 0);//push(MyString&&)

        std::cout << q.peek() << std::endl;
        q.pop();

        std::cout << q.peek() << std::endl;
        q.pop();

        std::cout << q.peek() << std::endl;
        q.pop();
}