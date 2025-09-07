#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

int main(int argc, char **argv) {
    string filename = "my_activities.txt";
    ofstream fout(filename.c_str(), ios::out);

    if (!fout) {
        cerr << "Error: open file for output failed!" << endl;
        abort(); // จาก <cstdlib>
    }

    cout << "กรุณากรอกกิจกรรมของนักศึกษา 3 อย่าง (พิมพ์ทีละบรรทัด):" << endl;

    string activity;
    for (int i = 1; i <= 3; i++) {
        cout << "กิจกรรมที่ " << i << ": ";
        getline(cin, activity);
        fout << activity << endl;
    }

    fout.close();
    cout << "บันทึกกิจกรรมลงไฟล์ '" << filename << "' เรียบร้อยแล้ว" << endl;
    return 0;
}
