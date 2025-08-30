#include <iostream>
using namespace std;
int *rectangleArea4(int *w, int &h)
{
    int result;
    result = *w * h;
    return &result;
}
int main(int argc, char **argv)
{
    int a = 7, b = 3;
    int *x = rectangleArea4(&a, b);
    *x *= 2;
    cout << x << endl;
    cout << *x << endl;
    return 0;
}
