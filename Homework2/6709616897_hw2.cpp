// 6709616897
// Suphanat Chanlek

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <limits>
#include <cctype>
#include <cstdlib>
#include <cstdio>
using namespace std;

struct Student {
    long long id;   // student ID (BST key)
    char program;   // 'N' = normal, 'S' = special
    string email;   // student email
    char status;    // 'A' = active, 'W' = withdraw
};

struct Node {
    Student s;
    Node* left;
    Node* right;
    Node(const Student& st) : s(st), left(NULL), right(NULL) {}
};

// ---------- helpers ----------
static inline void trim(string &s) {
    // remove leading/trailing spaces
    size_t n = s.size();
    size_t i = 0;
    while (i < n && isspace((unsigned char)s[i])) i++;
    if (i == n) { s.clear(); return; }
    size_t j = n - 1;
    while (j > i && isspace((unsigned char)s[j])) j--;
    s = s.substr(i, j - i + 1);
}

static inline bool isDigits(const string& t) {
    if (t.empty()) return false;
    for (size_t i = 0; i < t.size(); ++i) {
        if (!isdigit((unsigned char)t[i])) return false;
    }
    return true;
}

// ---------- BST ops ----------
bool bstInsert(Node*& root, const Student& st) {
    if (!root) { root = new Node(st); return true; }
    if (st.id < root->s.id) return bstInsert(root->left, st);
    if (st.id > root->s.id) return bstInsert(root->right, st);
    // duplicate ID: update existing node (or skip)
    root->s = st;
    return false;
}

Node* bstFind(Node* root, long long id) {
    while (root) {
        if (id < root->s.id) root = root->left;
        else if (id > root->s.id) root = root->right;
        else return root;
    }
    return NULL;
}

void bstDestroy(Node* root) {
    if (!root) return;
    bstDestroy(root->left);
    bstDestroy(root->right);
    delete root;
}

Node* bstMin(Node* root) {
    if (!root) return NULL;
    while (root->left) root = root->left;
    return root;
}

Node* bstMax(Node* root) {
    if (!root) return NULL;
    while (root->right) root = root->right;
    return root;
}

// ---------- printing / counters ----------
void printTableHeader(const string& title) {
    cout << title << "\n";
    cout << " ID          PROGRAM   EMAIL                          STATUS\n";
}

void inorderPrintByProgram(Node* root, char program, int& counter) {
    if (!root) return;
    inorderPrintByProgram(root->left, program, counter);
    if (toupper((unsigned char)root->s.program) == toupper((unsigned char)program)) {
        // align columns: ID(12) PROGRAM(8) EMAIL(30) STATUS(6)
        cout << ' ' << setw(12) << root->s.id << "  "
             << left << setw(8) << string(1, (char)toupper((unsigned char)root->s.program)) << " "
             << left << setw(30) << root->s.email << " "
             << left << setw(6)  << string(1, (char)toupper((unsigned char)root->s.status))
             << right << "\n";
        counter++;
    }
    inorderPrintByProgram(root->right, program, counter);
}

void countStatusAW(Node* root, int& cntA, int& cntW) {
    if (!root) return;
    countStatusAW(root->left, cntA, cntW);
    if (toupper((unsigned char)root->s.status) == 'A') cntA++;
    else if (toupper((unsigned char)root->s.status) == 'W') cntW++;
    countStatusAW(root->right, cntA, cntW);
}

// ---------- load file ----------
bool loadFromFile(const string& path, Node*& root, int& totalRows) {
    ifstream fin(path.c_str());
    if (!fin.is_open()) {
        cerr << "File not found: '" << path << "'\n";
        return false;
    }

    string line;
    totalRows = 0;
    int inserted = 0;

    while (getline(fin, line)) {
        trim(line);
        if (line.empty()) continue;

        // robust: split by whitespace (tabs/spaces)
        stringstream ss(line);
        string idStr, programStr, emailStr, statusStr;

        if (!(ss >> idStr >> programStr >> emailStr >> statusStr)) {
            // likely header/bad line => skip
            continue;
        }
        if (!isDigits(idStr)) {
            // header like "ID PROGRAM ..." => skip
            continue;
        }
        if (programStr.empty() || statusStr.empty()) continue;

        Student st;
        st.id = atoll(idStr.c_str());         // C++98-friendly
        st.program = (char)toupper((unsigned char)programStr[0]); // 'N' or 'S'
        st.email = emailStr;
        st.status  = (char)toupper((unsigned char)statusStr[0]);  // 'A' or 'W'

        if (bstInsert(root, st)) inserted++;
        totalRows++;
    }

    if (inserted == 0) {
        cerr << "No valid data rows parsed.\n";
    }
    return inserted > 0;
}

// ---------- main ----------
int main() {
    // Keep default sync/tie for Dev-C++98
    const string filename = "classlist60.txt";

    Node* root = NULL;
    int totalRows = 0;
    if (!loadFromFile(filename, root, totalRows)) {
        return 0; // abort if failed to load
    }

    // 1) normal program list
    int countN = 0;
    printTableHeader("List of normal program students in CS213 class:");
    inorderPrintByProgram(root, 'N', countN);
    cout << "Total registered normal program students: " << countN << "\n\n";

    // 2) special program list
    int countS = 0;
    printTableHeader("List of special program students in CS213 class:");
    inorderPrintByProgram(root, 'S', countS);
    cout << "Total registered special program students: " << countS << "\n\n";

    // 3) count A/W
    int cntA = 0, cntW = 0;
    countStatusAW(root, cntA, cntW);
    cout << "Number of Active students : " << cntA << "\n";
    cout << "Number of withdrawal students : " << cntW << "\n\n";

    // 4) min/max IDs
    Node* mn = bstMin(root);
    Node* mx = bstMax(root);
    if (mn && mx) {
        cout << "The first ID of this classlist is " << mn->s.id << "\n";
        cout << "The last ID of this classlist is " << mx->s.id << "\n\n";
    }

    cout << "======================================================================\n\n";

    // 5) search loop until empty Enter
    while (true) {
        // Show prompt and FLUSH so the cursor is ready to type immediately
        cout << "Search email for student ID : ";
        cout.flush();            // or: fflush(stdout);

        string line;
        if (!getline(cin, line)) break; // EOF => exit
        trim(line);
        if (line.empty()) break;        // empty => stop

        if (!isDigits(line)) {
            cout << "Contact email : invalid student ID\n\n";
            continue;
        }

        long long qid = atoll(line.c_str());
        Node* node = bstFind(root, qid);
        if (node) cout << "Contact email : " << node->s.email << "\n\n";
        else      cout << "Contact email : not found\n\n";
    }

    bstDestroy(root);
    return 0;
}

