#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    int arr[] = {1, 2, 3, 4, 5};
    int *ptr = arr;

    cout << *ptr << endl;     // (1)
    cout << *++ptr << endl;   // (2)
    cout << ++*ptr << endl;   // (3)
    cout << *ptr++ << endl;   // (4)
    cout << *ptr << endl;     // (5)

    return 0;
}
