// 6709616897
// Suphanat Chanlek

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cctype>
#include <cstdlib>
using namespace std;

// Represents one student's record (BST key = id)
struct StudentRecord {
    long long id;
    char program;  // 'N' = normal, 'S' = special
    string email;
    char status;   // 'A' = active, 'W' = withdraw
};

// Basic BST node for StudentRecord
struct BSTNode {
    StudentRecord rec;
    BSTNode *left, *right;
    BSTNode(const StudentRecord& r): rec(r), left(NULL), right(NULL) {}
};

// Trim leading/trailing spaces from a string
static inline void trimWhitespace(string &x){
    size_t i=0, n=x.size();
    while(i<n && isspace((unsigned char)x[i])) ++i;
    if(i==n){ x.clear(); return; }
    size_t j=n-1;
    while(j>i && isspace((unsigned char)x[j])) --j;
    x = x.substr(i, j-i+1);
}

// Keep only digits
static inline string extractDigits(const string& s){
    string t; t.reserve(s.size());
    for(size_t i=0;i<s.size();++i){
        unsigned char c = (unsigned char)s[i];
        if(c>='0' && c<='9') t.push_back((char)c);
    }
    return t;
}

// Insert a record into BST; update record if duplicate id is found.
// Returns true when a new node is created, false when an existing node is updated.
bool bstInsertOrUpdate(BSTNode*& root, const StudentRecord& rec){
    if(!root){ root=new BSTNode(rec); return true; }
    if(rec.id < root->rec.id)  return bstInsertOrUpdate(root->left, rec);
    if(rec.id > root->rec.id)  return bstInsertOrUpdate(root->right, rec);
    root->rec = rec; // update
    return false;
}

// Find node by student id; returns pointer or NULL if not found
BSTNode* bstFindById(BSTNode* root, long long key){
    while(root){
        if(key < root->rec.id) root = root->left;
        else if(key > root->rec.id) root = root->right;
        else return root;
    }
    return NULL;
}

// Get leftmost (minimum id) node
BSTNode* bstMinNode(BSTNode* root){
    if(!root) return NULL;
    while(root->left) root=root->left;
    return root;
}

// Get rightmost (maximum id) node
BSTNode* bstMaxNode(BSTNode* root){
    if(!root) return NULL;
    while(root->right) root=root->right;
    return root;
}

// Post-order free of all nodes
void bstDestroyTree(BSTNode* root){
    if(!root) return;
    bstDestroyTree(root->left);
    bstDestroyTree(root->right);
    delete root;
}

// Print table header for list output
void printTableHeader(const string& title){
    cout << title << "\n\n";
    cout << left
         << setw(12) << "ID" << "  "
         << setw(8)  << "PROGRAM" << "  "
         << setw(30) << "EMAIL" << "  "
         << "STATUS" << "\n";
}

// In-order traversal printing only a specific program ('N' or 'S')
void printInorderByProgram(BSTNode* root, char program, int& counter){
    if(!root) return;
    printInorderByProgram(root->left, program, counter);
    if(toupper((unsigned char)root->rec.program)==toupper((unsigned char)program)){
        cout << right << setw(12) << root->rec.id << "  "
             << left  << setw(8)  << string(1, root->rec.program) << "  "
             << left  << setw(33) << root->rec.email << "  "
             << left  << root->rec.status << "\n";
        ++counter;
    }
    printInorderByProgram(root->right, program, counter);
}

// Count how many students are Active (A) and Withdrawn (W)
void countActiveWithdrawn(BSTNode* root, int& activeCount, int& withdrawnCount){
    if(!root) return;
    countActiveWithdrawn(root->left, activeCount, withdrawnCount);
    if(root->rec.status=='A') ++activeCount;
    else if(root->rec.status=='W') ++withdrawnCount;
    countActiveWithdrawn(root->right, activeCount, withdrawnCount);
}

// Read classlist file and build BST of StudentRecord
bool loadClasslistIntoBST(const string& path, BSTNode*& root){
    ifstream fin(path.c_str(), ios::binary);
    if(!fin.is_open()){
        cerr << "Cannot open file: " << path << "\n";
        return false;
    }

    string idStr, prg, email, st;
    int inserted = 0;

    while (fin >> idStr >> prg >> email >> st) {
        idStr = extractDigits(idStr);
        if (idStr.empty()) continue;

        StudentRecord rec;
        rec.id      = atoll(idStr.c_str());
        rec.program = (char)toupper((unsigned char)prg[0]);
        rec.email   = email;
        rec.status  = (char)toupper((unsigned char)st[0]);

        if (bstInsertOrUpdate(root, rec)) ++inserted;
    }
    return inserted > 0;
}

// main
int main(){
    const string filename = "classlist60.txt";

    BSTNode* root = NULL;
    if(!loadClasslistIntoBST(filename, root)) return 0;

    // Print Normal program list
    int normalCount=0;
    printTableHeader("List of normal program students in CS213 class:");
    printInorderByProgram(root, 'N', normalCount);
    cout << "\nTotal registered normal program students: " << normalCount << "\n\n";

    // Print Special program list
    int specialCount=0;
    printTableHeader("List of special program students in CS213 class:");
    printInorderByProgram(root, 'S', specialCount);
    cout << "\nTotal registered special program students: " << specialCount << "\n\n";

    // Summary of A/W
    int activeCount=0, withdrawnCount=0;
    countActiveWithdrawn(root, activeCount, withdrawnCount);
    cout << "Number of Active students : " << activeCount << "\n";
    cout << "Number of withdrawal students : " << withdrawnCount << "\n\n";

    // Min/Max IDs
    BSTNode* minNode = bstMinNode(root);
    BSTNode* maxNode = bstMaxNode(root);
    if(minNode && maxNode){
        cout << "The first ID of this classlist is  " << minNode->rec.id << "\n";
        cout << "The last ID of this classlist is   " << maxNode->rec.id << "\n\n";
    }

    cout << "======================================================================\n\n";

    // Search loop for contacting email by student ID
    while(true){
        cout << "Search email for student ID : ";
        cout.flush();

        string query;
        if(!getline(cin, query)) break;
        trimWhitespace(query);
        if(query.empty()) break;

        string idStr = extractDigits(query);
        if(idStr.empty()){
            cout << "Contact email : invalid student ID\n\n";
            continue;
        }

        long long key = atoll(idStr.c_str());
        BSTNode* found = bstFindById(root, key);
        if(found) cout << "Contact email : " << found->rec.email << "\n\n";
        else      cout << "Contact email : not found\n\n";
    }

    bstDestroyTree(root);
    return 0;
}

