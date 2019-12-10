#ifndef FINALHASHCLASS_HPP
#define FINALHASHCLASS_HPP
#include <cmath>
#include <string>
//Hash table class for data structures final project
using namespace std;

struct node
{
    int key;
    struct node* next;
};
struct Node{
    int key;
    Node* left ;
    Node* right;
};
class HashTable
{
  static const int tableSize=10009;  // No. of buckets (linked lists)
    int cuckooTablesize=10009;
    node* *tableLL;// Pointer to an array containing buckets
    node* *tableLL2;
    Node* *tableBST;//Pointer to an array of BST's
    Node* *tableBST2;
    int tableLP[tableSize];
    int tableLP2[tableSize];
    int *tableCuckooOne=new int[cuckooTablesize];//dynamically allocated arrays for cuckoo
    int *tableCuckooTwo=new int[cuckooTablesize];
    node* createNodeLL(int key, node* next);
public:
    HashTable();  // Constructor/
    unsigned int hashFunctionOne(int key);// hash function x%tablesize
    unsigned int hashFunctionTwo(int key);//hash function floor(x/tableSize)
    unsigned int hashFunctionOneCUCKO(int key);
    unsigned int hashFunctionTwoCUCKO(int key);
    void resetAnyTable(int index);//resets the tables
    void changeTablesize();//changes cuckoo table size
    int getTableSize();//returns cuckoo table size
    void resetTable();//reset the cuckoo tables
    int searchItemCuckoo(int key);//searches the cuckoo tables
    bool insertHelper(int holder,int key);//helps insert into cuckoo
    bool insertItemCuckoo(int key);
    void printItemCuckoo();
    void deleteItemCuckoo(int key);
    bool insertItemLP2(int key);
    void printTableLP2();
    bool searchItemLP2(int key);
    void deleteItemLP2(int key);
    void deleteItemLP(int key);
    bool insertItemLP(int key);
    void printTableLP();
    bool searchItemLP(int key);
    bool insertItemBST2(int key);
    void printTableBST2();
    bool searchItemBST2(int key);
    Node* deleteItemBST2(int key);
    Node* deleteItemBST(int key);
    bool insertItemBST(int key);
    void printTableBST();
    bool searchItemBST(int key);
    bool insertItemLL2(int key);
    void printTableLL2();
    node* searchItemLL2(int key);
    int getBucketsLL();
    int getBucketsLL2();
    void deleteItemLL(int key);
    void deleteItemLL2(int key);
    bool insertItemLL(int key);
    void printTableLL();
    node* searchItemLL(int key);
};

#endif
