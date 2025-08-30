#include <iostream>
using namespace std;
int *rectangleArea(int w, int h)
{
    int *result = (int *)malloc(sizeof(int));
    *result = w * h;
    w++;
    h++;
    return result;
}
int main(int argc, char **argv)
{
    int a = 7, b = 3;
    int *x = rectangleArea(a, b);
    cout << x << " " << *x << endl;
    cout << a << " " << b << endl;
    return 0;
}

// Output : 
// 0x24adbec25c0 21
// 7 3