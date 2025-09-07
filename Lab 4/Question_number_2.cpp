#include <iostream>
#include <string>
using namespace std;

void print(string data[], int size) {
    cout << "Print array" << endl;
    for (int i=0; i<size; i++) {
        cout << data[i] << ", ";
    }
    cout << endl;
}

int main(int argc, char** argv) {
    string arr1[] = {"Apple", "Banana", "Coconut", "Durian"};
    string *arr2 = new string[6];

    // 1) เติมโค้ด
    arr2[4] = "Eggplant";
    arr2[5] = arr1[0] + arr1[1];   // AppleBanana

    std::copy(std::begin(arr1), std::end(arr1), arr2);
    print(arr2, 6);

    // 2) คืนพื้นที่หน่วยความจำ
    delete[] arr2;

    return 0;
}
