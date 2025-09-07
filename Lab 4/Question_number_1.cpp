#include <iostream>
using namespace std;
void print(int data[], int size)
{
    cout << "Print array" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << data[i] << ", ";
    }
    cout << endl;
}
int main(int argc, char **argv)
{
    int arr1[] = {2, 3, 5, 7, 11};
    int arr2[10];
    print(arr1, 5);
    print(arr2, 10);
    std::copy(std::begin(arr1) + 1, std::end(arr1), arr2);
    print(arr2, 10);
    return 0;
}