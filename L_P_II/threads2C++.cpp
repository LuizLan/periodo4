#include <iostream>
#include <thread>
#include <string>

using namespace std;

class pessoa {
    int id;
    string nome;

public:
    pessoa(int i, string n):id(i), nome(n){}
    //~pessoa(){counter--;}
    int get_id(){return id;}
    void set_id(int i){id = i;}
    string get_nome(){return nome;}
    void set_nome(string n){nome = n;}
    void print_info(string msg){
        cout << "id: " << id << " nome: " << nome << endl;
        cout << msg << endl;
    }
    //static void print_counter(){ cout << "counter: " << counter << endl; }
};

int main(){

    pessoa p(1010, "Joao");

    thread t(&pessoa::print_info, &p, "bom dia");

    t.join();

    return 0;
}