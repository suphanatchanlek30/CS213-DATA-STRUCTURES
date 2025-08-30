#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
    int *x, y;
    y = 10;
    x = &y; // ให้ x ชี้ไปที่ y

    *x = 10;

    cout << *x << ", " << y << endl;
    cout << x << ", " << &y << endl;
    
    return 0;
}