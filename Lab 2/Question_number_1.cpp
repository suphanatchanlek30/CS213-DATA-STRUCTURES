#include <iostream>
using namespace std;
int *rectangleArea3(int *w, int &h)
{
    int *result = (int *)malloc(sizeof(int));
    *result = *w * h;
    free(result);
    return result;
}
int main(int argc, char **argv)
{
    int a = 7, b = 3;
    int *x = rectangleArea3(&a, b);
    cout << x << endl;
    cout << *x << endl;
    return 0;
}

// Output :
// 0x1991d2725c0
// 489104944