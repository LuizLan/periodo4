#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <condition_variable>

using namespace std;

#define BUFFER_SIZE 8
#define QTD_PRODUCER 10

class monitor_buffer{
    private:
        int buffer[BUFFER_SIZE];
        int count;
        int in;
        int out;
        mutex mtx;
        condition_variable not_full;
        condition_variable not_empty;
    public:
        monitor_buffer(){
            count = 0;
            in = 0;
            out = 0;
        }
        void insert(int item){
            unique_lock<mutex> lock(mtx);
            while(count == BUFFER_SIZE){
                not_full.wait(lock);
            }
            buffer[in] = item;
            in = (in + 1) % BUFFER_SIZE;
            count++;
            not_empty.notify_one();
        }
        int retrieve(){
            unique_lock<mutex> lock(mtx);
            while(count == 0){
                not_empty.wait(lock);
            }
            int item = buffer[out];
            out = (out + 1) % BUFFER_SIZE;
            count--;
            not_full.notify_one();
            return item;
        }
};

monitor_buffer buffer;

void producer(){
    for (int i = 0; i < QTD_PRODUCER; i++){
        int item = rand() % 100;
        buffer.insert(item);
        cout << "Producer " << this_thread::get_id() << " inserted " << item << endl;
        sleep(1);
    }
    
}

void consumer(){
    for (int i = 0; i < QTD_PRODUCER; i++){
        int item = buffer.retrieve();
        cout << "Consumer " << this_thread::get_id() << " retrieved " << item << endl;
        sleep(1);
    }
}

int main(){

    srand(time(NULL));

    thread prod(producer);
    thread cons(consumer);

    prod.join();
    cons.join();
    
    return 0;
}