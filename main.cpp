#include <iostream>
class B;
class A
{
public:
    int a = 1;
    int af() { return a; }
    //virtual operator B() = 0;
};

class B : public A
{
public:
    int b = 2;
    //operator B() override 
    //{
    //    printf("call B() in B\n");
    //    return B();
    //}
};

int main(int, char**) {
    A a;
    B b;
    A* a1 = &b;
    A& a2 = b;
    
    
    printf("%d\n", a2.af());
    printf("a2:%p\n", &a2);

    printf("%d\n", a1->af());
    printf("A1:%p\n", a1);

    //printf("A:%p\n", &a);
    printf("B:%p\n", &b);
}
