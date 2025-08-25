//============================================================================
// ProjectTwo.cpp
// CS 300 Project Two - Advising Assistance Program
// Author: Rene Guzman
// Implements: load file -> BST, menu, print sorted course list, print course
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//-------------- Course model -------------------------------------------------
struct Course {
    string number;               // e.g., CSCI200
    string title;                // e.g., Data Structures
    vector<string> prerequisites; // e.g., { "CSCI101", "MATH201" }
};

// Uppercase helper so inputs like "csci400" work
static string toUpperCopy(string s) {
    transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return static_cast<char>(toupper(c)); });
    return s;
}

// Trim helper (left+right)
static string trim(string s) {
    auto notspace = [](unsigned char c) { return !isspace(c); };
    s.erase(s.begin(), find_if(s.begin(), s.end(), notspace));
    s.erase(find_if(s.rbegin(), s.rend(), notspace).base(), s.end());
    return s;
}

//-------------- BST for Course keyed by course.number ------------------------
struct Node {
    Course course;
    Node* left = nullptr;
    Node* right = nullptr;

    explicit Node(const Course& c) : course(c) {}
};

class CourseBST {
public:
    ~CourseBST() { destroy(root); }

    void insert(const Course& c) {
        if (!root) { root = new Node(c); return; }
        insertRec(root, c);
    }

    const Course* search(const string& number) const {
        Node* cur = root;
        while (cur) {
            if (number == cur->course.number) return &cur->course;
            cur = (number < cur->course.number) ? cur->left : cur->right;
        }
        return nullptr;
    }

    // In-order traversal printing "CSCI100, Introduction to Computer Science"
    void printInOrder() const {
        inOrder(root);
    }

    void clear() { destroy(root); root = nullptr; }

private:
    Node* root = nullptr;

    static void insertRec(Node* node, const Course& c) {
        if (c.number < node->course.number) {
            if (!node->left) node->left = new Node(c);
            else insertRec(node->left, c);
        }
        else {
            if (!node->right) node->right = new Node(c);
            else insertRec(node->right, c);
        }
    }

    static void inOrder(Node* node) {
        if (!node) return;
        inOrder(node->left);
        cout << node->course.number << ", " << node->course.title << '\n';
        inOrder(node->right);
    }

    static void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
};

//-------------- CSV Loading ---------------------------------------------------
/*
Expected line formats (prereqs optional, 0..N of them):
CSCI100,Introduction to Computer Science
CSCI300,Introduction to Algorithms,CSCI200,MATH201
*/
static bool loadCoursesFromCSV(const string& path, CourseBST& bst, size_t& countOut) {
    ifstream in(path);
    if (!in.is_open()) {
        cerr << "Error: could not open file '" << path << "'.\n";
        return false;
    }

    bst.clear();
    countOut = 0;

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;

        // Parse by commas
        vector<string> tokens;
        string token;
        stringstream ss(line);
        while (getline(ss, token, ',')) tokens.push_back(trim(token));
        if (tokens.size() < 2) {
            cerr << "Warning: skipping malformed line: " << line << '\n';
            continue;
        }

        Course c;
        c.number = toUpperCopy(tokens[0]);
        c.title = tokens[1];

        for (size_t i = 2; i < tokens.size(); ++i) {
            if (!tokens[i].empty())
                c.prerequisites.push_back(toUpperCopy(tokens[i]));
        }

        bst.insert(c);
        ++countOut;
    }

    return true;
}

//-------------- Printing helpers ---------------------------------------------
static void printCourse(const Course& c) {
    cout << c.number << ", " << c.title << '\n';
    cout << "Prerequisites: ";
    if (c.prerequisites.empty()) {
        cout << "None";
    }
    else {
        for (size_t i = 0; i < c.prerequisites.size(); ++i) {
            if (i) cout << ", ";
            cout << c.prerequisites[i];
        }
    }
    cout << "\n";
}

//-------------- Main / Menu ---------------------------------------------------
int main() {
    CourseBST bst;
    bool dataLoaded = false;
    size_t loadedCount = 0;

    cout << "Welcome to the course planner.\n\n";

    while (true) {
        cout << "  1. Load Data Structure.\n";
        cout << "  2. Print Course List.\n";
        cout << "  3. Print Course.\n";
        cout << "  9. Exit\n\n";
        cout << "What would you like to do? ";

        string choiceStr;
        if (!getline(cin, choiceStr)) break;
        int choice = 0;
        try { choice = stoi(choiceStr); }
        catch (...) { choice = 0; }
        cout << endl;

        if (choice == 1) {
            cout << "Enter the name of the data file (or full path): ";
            string path;
            getline(cin, path);
            path = trim(path);

            if (loadCoursesFromCSV(path, bst, loadedCount)) {
                dataLoaded = true;
                cout << "Loaded " << loadedCount << " courses.\n\n";
            }
            else {
                dataLoaded = false;
                cout << "Failed to load courses. Please check the file and try again.\n\n";
            }
        }
        else if (choice == 2) {
            if (!dataLoaded) {
                cout << "Please load the data structure first (option 1).\n\n";
                continue;
            }
            cout << "Here is a sample schedule:\n";
            bst.printInOrder();
            cout << '\n';
        }
        else if (choice == 3) {
            if (!dataLoaded) {
                cout << "Please load the data structure first (option 1).\n\n";
                continue;
            }
            cout << "What course do you want to know about? ";
            string key;
            getline(cin, key);
            key = toUpperCopy(trim(key));
            cout << endl;

            const Course* found = bst.search(key);
            if (found) {
                printCourse(*found);
            }
            else {
                cout << "Course " << key << " not found.\n";
            }
            cout << '\n';
        }
        else if (choice == 9) {
            cout << "Thank you for using the course planner!\n";
            break;
        }
        else {
            cout << choice << " is not a valid option.\n\n";
        }
    }

    return 0;
}
