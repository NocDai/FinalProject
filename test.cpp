#include <iostream>
using namespace std;

class A{
    public:
        A();
        int get_a(){return a;}
    private:
        int a;
};
A::A(){
    a=0;
}

template<class T, class U>
bool operator==(T& a, U& b){
    if (a.get_a()==b.get_a()) return true;
    else return false;
}

class B :public A{
    public:
        B():A(){}
};

class C :public A{
    public:
        C():A(){}
};

int main(void){
    B b;
    C c;
//    b = c;// error operator overload is needed.

    if(b==c) cout<<"="<<endl;
    else cout<<"!="<<endl;
}