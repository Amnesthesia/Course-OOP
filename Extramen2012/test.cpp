#include <iostream>

using namespace std;

class test1
{
    private:
        int  nr;

    public:
        void set(){ nr = 1;}
        void display(){ cout << nr; }
};

class test2 : public test1
{


};

int main(){

    test2* obj = new test2();
    obj->set();
    obj->display();
}
