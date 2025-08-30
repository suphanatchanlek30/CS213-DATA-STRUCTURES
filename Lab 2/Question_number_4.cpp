#include <iostream>
using namespace std;
int *rectangleArea2(int *w, int &h)
{
    int *result = (int *)malloc(sizeof(int));
    *result = *w * h;
    return result;
}
int main(int argc, char **argv)
{
    int a = 7, b = 3;
    int *x, *y;
    x = rectangleArea2(&a, b);
    y = x;
    free(y);
    *x += 10;
    cout << x << endl;
    cout << *x << endl;
    return 0;
}