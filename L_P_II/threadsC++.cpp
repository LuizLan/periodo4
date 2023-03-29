#include <iostream>
#include <thread>

using namespace std;

void foo(int loop_limit, string msg)
{
    for (int i = 0; i < loop_limit; i++)
    {
        cout << "[t] "<< msg << " - " << i << " \n";
    }
}

int main()
{
    thread t(foo, 500, "bom dia");
    t.join();

    return 0;
}