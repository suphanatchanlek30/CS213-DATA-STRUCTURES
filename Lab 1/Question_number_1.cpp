#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
    int *x, y;

    *x = 10;
    y = 10;

    cout << *x << ", " << y << endl;
    cout << x << ", " << &y << endl;
    
    return 0;
}