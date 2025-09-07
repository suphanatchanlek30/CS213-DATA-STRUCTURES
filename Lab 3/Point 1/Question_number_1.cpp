#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
int main(int argc, char **argv)
{
    string filename = "my_activities.txt";
    ifstream fin(filename.c_str(), ios::in);
    if (!fin)
    {
        cerr << "Error: open file for output failed!" << endl;
        abort(); // in <cstdlib> header
    }
    string s;
    while (!fin.eof())
    {
        fin >> s;
        cout << s << endl;
    }
    return 0;
}