// class implementation for a hash tables in final data structures project
//all of the functions are self explanatory or have been covered before in the class
//except for cuckoo hashing which has comments
#include<iostream>
#include "Finalhashclass.hpp"
using namespace std;

node* HashTable::createNodeLL(int key, node* next)
{
    node* nw = new node;
    nw->key = key;
    nw->next = next;
    return nw;
}
HashTable::HashTable()
{
    tableLL = new node*[tableSize];
    tableLL2=new node*[tableSize];
    for(int i=0;i<tableSize;i++)
    {
        tableLL[i] = nullptr;
    }
    for(int i=0;i<tableSize;i++)
    {
      tableLL2[i]=nullptr;
    }
    tableBST = new Node*[tableSize];
    for(int i=0;i<tableSize;i++)
    {
        tableBST[i] = nullptr;
    }
    tableBST2 = new Node*[tableSize];
    for(int i=0;i<tableSize;i++)
    {
      tableBST2[i] = nullptr;
    }
    for(int i=0;i<tableSize;i++)
    {
        tableLP2[i] = -1;
    }
    for(int i=0;i<tableSize;i++)
    {
        tableLP[i] = -1;
    }
    for(int i=0;i<tableSize;i++)
    {
      tableCuckooOne[i]=-1;
      tableCuckooTwo[i]=-1;
    }

}

void HashTable::resetAnyTable(int tableNum)
{
  switch (tableNum)
  {
    case 1:
            for(int i=0;i<tableSize;i++)
            {
                tableLL[i] = nullptr;
            }

            break;
    case 2:
            for(int i=0;i<tableSize;i++)
            {
              tableLL2[i]=nullptr;
            }
            break;
    case 3:
            for(int i=0;i<tableSize;i++)
            {
                tableBST[i] = nullptr;
            }
            break;
    case 4:
            for(int i=0;i<tableSize;i++)
            {
              tableBST2[i] = nullptr;
            }
            break;
    case 5:
            for(int i=0;i<tableSize;i++)
            {
                tableLP[i] = -1;
            }
            break;
    case 6:
            for(int i=0;i<tableSize;i++)
            {
                tableLP2[i] = -1;
            }
            break;


  }
}


//functions to calculate hash function
unsigned int HashTable::hashFunctionOne(int key)
{
    return (key % tableSize);
}
unsigned int HashTable::hashFunctionTwo(int key)
{
  return (floor(key/tableSize));
}
unsigned int HashTable::hashFunctionOneCUCKO(int key)
{
    return (key % cuckooTablesize);
}
unsigned int HashTable::hashFunctionTwoCUCKO(int key)
{
  return (floor(key/cuckooTablesize));
}
int HashTable::getTableSize()
{
  return cuckooTablesize;
}
void HashTable::changeTablesize()
{
  cuckooTablesize=cuckooTablesize+2;
}
void HashTable::resetTable()
{
  for(int i=0;i<cuckooTablesize;i++)
  {
    tableCuckooOne[i]=-1;
    tableCuckooTwo[i]=-1;
  }
  //cout<<"wejwoiheoijewoip"<<endl;
}
int HashTable::searchItemCuckoo(int key)
{
  int index=hashFunctionOneCUCKO(key);//get indices
  int index2=hashFunctionTwoCUCKO(key);
  if(tableCuckooOne[index]==key&&index<cuckooTablesize)//check first hash table location
  {
    return 1;//return 1, which means the value is in the first hash table
  }
  if(tableCuckooTwo[index2]==key&&index2<cuckooTablesize)//check second hash table
  {
    return 2;//return 2 for the second table
  }

  return -1;

}
bool HashTable::insertHelper(int holder,int key)//takes in the value that was previously in the key's first location
{
  if(holder==-1)//if it is -1 that means that there is not value
  {
    return true;
  }
  if (holder==key)//this means there would be a cycle
  {

    return false;//return false to tell the driver that there is a cycle
  }
  int holder2;
  int index2=hashFunctionTwoCUCKO(holder);
  int index=hashFunctionOneCUCKO(holder);
  if(tableCuckooTwo[index2]==-1)//checks second table
  {
    tableCuckooTwo[index2]=holder;//if empty then put the value there
    return true;
  }
  else
  {
    holder2=tableCuckooOne[index];//grab the value that is being replaced
    tableCuckooOne[index]=holder;
    return insertHelper(holder2,key);//call recursive function

  }


}
bool HashTable::insertItemCuckoo(int key)
{
  int index=hashFunctionOneCUCKO(key);//get the indices
  int index2=hashFunctionTwoCUCKO(key);
  int holder,holder2;
  if(tableCuckooOne[index]==-1)//these check if the tables have empty spots at the indices
  {
    tableCuckooOne[index]=key;
    return true;
  }
  else if(tableCuckooTwo[index2]==-1)
  {
    tableCuckooTwo[index2]=key;
    return true;

  }
  else//if not then replace the first then call the recursive helper
  {
    holder=tableCuckooOne[index];
    tableCuckooOne[index]=key;
    return insertHelper(holder,key);

    //use recursion
    //if you run in to your original key you have a cycle
    //if you run into a cycle then make whole new hash table

    }
    return true;
  }





void HashTable::printItemCuckoo()//prints the tables
{
  cout<<"****TABLE ONE****"<<endl;

  for(int i=0;i<cuckooTablesize;i++)
  {
    cout << i <<"|| ";
    cout <<tableCuckooOne[i];

    cout<<endl;
  }

    cout<<"****TABLE TWO****"<<endl;
    for(int i=0;i<cuckooTablesize;i++)
    {
      cout << i <<"|| ";
      cout <<tableCuckooTwo[i];

      cout<<endl;
    }

}
void HashTable::deleteItemCuckoo(int key)//just goes to the index of each to see if they can be deleted
{
  int index=hashFunctionOneCUCKO(key);
  int index2=hashFunctionTwoCUCKO(key);
  int check=searchItemCuckoo(key);
  if(check==1)
  {
    tableCuckooOne[index]=-1;

  }
  if(check==2)
  {
    tableCuckooTwo[index2]=-1;
  }


}
bool HashTable::insertItemLP2(int key)
{
  int index = hashFunctionTwo(key);

    for(int i=index;i<tableSize;i++)
    {
      if(tableLP2[i]==-1)
      {
        tableLP2[i]=key;
        return true;
      }
      if(i==tableSize-1)
      {
        for(int j=0;j<index;j++)
        {
          if(tableLP2[j]==-1)
          {
            tableLP2[j]=key;
            return true;
          }
        }
      }
    }
    return false;
}
void HashTable::printTableLP2()
{
  for(int i=0;i<tableSize;i++)
  {
    cout << i <<"|| ";
    cout <<tableLP2[i];

    cout<<endl;
  }


}
bool HashTable::searchItemLP2(int key)
{
  int index = hashFunctionTwo(key);
  if(tableLP2[index]==key)
  {
    return true;
  }
  else
  {
    for(int i=0;i<tableSize;i++)
    {
      if(tableLP2[i]==key)
      {
        return true;
      }
    }

  }
  return false;

}
bool HashTable::insertItemLP(int key)
{
  int index = hashFunctionOne(key);

    for(int i=index;i<tableSize;i++)
    {
      if(tableLP[i]==-1)
      {
        tableLP[i]=key;
        return true;
      }
      if(i==tableSize-1)
      {
        for(int j=0;j<index;j++)
        {
          if(tableLP[j]==-1)
          {
            tableLP[j]=key;
            return true;
          }
        }
      }
    }
    return false;
}
void HashTable::printTableLP()
{
  for(int i=0;i<tableSize;i++)
  {
    cout << i <<"|| ";
    cout <<tableLP[i];

    cout<<endl;
  }


}
void HashTable::deleteItemLP2(int key)
{
  int index = hashFunctionTwo(key);
  if(tableLP2[index]==key)
  {
    tableLP2[index]=-1;
  }
  else
  {
    for(int i=0;i<tableSize;i++)
    {
      if(tableLP2[i]==key)
      {
        tableLP2[i]=-1;
      }
    }

  }
}
void HashTable::deleteItemLP(int key)
{
  int index = hashFunctionOne(key);
  if(tableLP[index]==key)
  {
    tableLP[index]=-1;
  }
  else
  {
    for(int i=0;i<tableSize;i++)
    {
      if(tableLP[i]==key)
      {
        tableLP[i]=-1;
      }
    }

  }
}
bool HashTable::searchItemLP(int key)
{
  int index = hashFunctionOne(key);
  if(tableLP[index]==key)
  {
    return true;
  }
  else
  {
    for(int i=0;i<tableSize;i++)
    {
      if(tableLP[i]==key)
      {
        return true;
      }
    }

  }
  return false;

}
bool searchKeyHelper(Node* currNode, int data){
    if(currNode == NULL)
    {
        return false;
    }
    if(currNode->key == data)
    {
        return true;
      }
    if(currNode->key > data)
    {
        return searchKeyHelper(currNode->left, data);
    }

    return searchKeyHelper (currNode->right, data);
}
bool HashTable::searchItemBST(int key)
{
  int index=hashFunctionOne(key);
  Node* phil=tableBST[index];
  return searchKeyHelper(phil,key);

}
Node* addNodeHelper(Node* currNode, int data)
{
    if(currNode == NULL){
      Node* nw = new Node;
      nw->key = data;
      nw->left = NULL;
      nw->right=NULL;
      return nw;
    }
    else if(currNode->key < data)
    {
        currNode->right = addNodeHelper(currNode->right,data);
    }
    else if(currNode->key > data)
    {
        currNode->left = addNodeHelper(currNode->left,data);
    }
    return currNode;
}
bool HashTable::insertItemBST(int key)
{
  Node* phil=NULL;
    int slot=hashFunctionOne(key);

      tableBST[slot]=addNodeHelper(tableBST[slot],key);
      return true;



}
void printTreeHelper(Node* currNode){
     if(currNode!=NULL)
     {
        printTreeHelper( currNode->left);
        cout << " "<< currNode->key;
        printTreeHelper( currNode->right);
     }
 }
 Node* deleteNode(Node* currNode,int value)
 {
   if(currNode == NULL)
    {
      return NULL;
    }
    else if(value < currNode->key)
    {
      currNode->left = deleteNode(currNode->left, value);
    }
    else if(value > currNode->key)
    {
      currNode->right = deleteNode(currNode->right, value);
    }
    else
    {
      if (currNode->left == NULL)
      {
          Node *temp = currNode->right;
          free(currNode);
          return temp;
      }
      else if (currNode->right == NULL)
      {
          Node *temp = currNode->left;
          free(currNode);
          return temp;
        }

      else
      {
        Node* current = currNode->right;

        while (current && current->left != NULL)
            current = current->left;

        currNode=current;
        currNode->key = current->key;

        currNode->right = deleteNode(currNode->right, current->key);
      }
      return currNode;

      }

  return currNode;
  }
  Node* HashTable::deleteItemBST2(int value)
  {
    Node *currNode=tableBST2[hashFunctionTwo(value)];
    return deleteNode(currNode,value);

  }
 Node* HashTable::deleteItemBST(int value)
 {
   Node *currNode=tableBST[hashFunctionOne(value)];
   return deleteNode(currNode,value);

 }
void HashTable::printTableBST()
{
  for(int i=0;i<tableSize;i++)
  {
    cout << i <<"|| ";
    if(tableBST[i]!=NULL)
    {
      printTreeHelper(tableBST[i]);
    }

    cout<<endl;
  }

}

bool HashTable::insertItemBST2(int key)
{
  Node* phil=NULL;
    int slot=hashFunctionTwo(key);
    tableBST2[slot]=addNodeHelper(tableBST2[slot],key);
    return true;
}
void HashTable::printTableBST2()
{
  for(int i=0;i<tableSize;i++)
  {
    cout << i <<"|| ";
    if(tableBST2[i]!=NULL)
    {
      printTreeHelper(tableBST2[i]);
    }

    cout<<endl;
  }

}
bool HashTable::searchItemBST2(int key)///change this to match new one
{

    int index=hashFunctionTwo(key);
    Node* phil=tableBST2[index];
    return searchKeyHelper(phil,key);

}
bool HashTable::insertItemLL2(int key)
{

    node* phil=NULL;

      int slot=hashFunctionTwo(key);
      if(slot>=tableSize)
      {
        return false;
      }
        if(tableLL2[slot]!=NULL)
        {

          phil=tableLL2[slot];
        }

        tableLL2[slot]=createNodeLL(key, phil);
        return true;

}
void HashTable::printTableLL2()
{
  node *phil;

    for (int i = 0; i < tableSize; i++)
    {
        cout << i <<"|| ";
        phil=tableLL2[i];
        while(phil!=NULL)
        {
          cout<<phil->key<<" ";
          phil=phil->next;
        }
        cout<<endl;
    }

}
node* HashTable::searchItemLL2(int key)
{
  //Compute the index by using the hash function
  int index = hashFunctionTwo(key);
  node* phil=tableLL2[index];
  while(phil!=NULL)
  {
    if(phil->key==key)
    {
      return phil;
    }
    phil=phil->next;
  }
  return  NULL;

}
node* HashTable::searchItemLL(int key)
{
    //Compute the index by using the hash function
    int index = hashFunctionOne(key);
    node* phil=tableLL[index];
    while(phil!=NULL)
    {
      if(phil->key==key)
      {
        return phil;
      }
      phil=phil->next;
    }
    return  NULL;
}
//function to insert item on to linked list using chaining as collision resolution
bool HashTable::insertItemLL(int key)
{
  node* phil=NULL;

    int slot=hashFunctionOne(key);
  if(slot>=tableSize)
  {
    return false;
  }
  //  if(!searchItemLL(key))
    //{
      if(tableLL[slot]!=NULL)
      {

        phil=tableLL[slot];
      }

      tableLL[slot]=createNodeLL(key, phil);
      return true;
    //}
    /*else
    {
        cout<<"duplicate entry: "<<key<<endl;
        return false;
    }*/

}
int HashTable::getBucketsLL()
{
  int buckets=0;
  for(int i=0;i<tableSize;i++)
  {
    if(tableLL[i]!=NULL)
    {
      buckets=buckets+1;
    }
  }
  return buckets;
}
int HashTable::getBucketsLL2()
{
  int buckets=0;
  for(int i=0;i<tableSize;i++)
  {
    if(tableLL2[i]!=NULL)
    {
      buckets=buckets+1;
    }
  }
  return buckets;
}
void HashTable::deleteItemLL(int key)
{

  bool test=true;
  node* head=tableLL[hashFunctionOne(key)];
  node* pres=head;
  node *prev = NULL;
if(head==NULL)
{
  return;
}
      if (head->key == key)
      {

        head=pres->next;
        free(pres);
        return;
      }
    while(test)
    {
      if(pres->next!=NULL)
      {
        if (pres->next->key==key)
        {
          prev=pres->next;
          pres->next=pres->next->next;
          free(prev);
          return;
        }
        else
        {
          if(searchItemLL(key)==NULL)
          {
            return;
          }
          pres=pres->next;
        }
      }
      else
      {
        return;
      }
    }
}
void HashTable::deleteItemLL2(int key)
{

  bool test=true;
  node* head=tableLL2[hashFunctionTwo(key)];
  node* pres=head;
  node *prev = NULL;
if(head==NULL)
{
  return;
}
      if (head->key == key)
      {
        head=pres->next;
        free(pres);
        return;
      }
    while(test)
    {
      if (pres->next->key==key)
      {
        prev=pres->next;
        pres->next=pres->next->next;
        free(prev);
        return;
      }
      else
      {
        if(searchItemLL2(key)==NULL)
        {
          return;
        }
        pres=pres->next;
      }
    }
}
// function to display hash table
void HashTable::printTableLL()
{
  node *phil;

    for (int i = 0; i < tableSize; i++)
    {
        cout << i <<"|| ";
        phil=tableLL[i];
        while(phil!=NULL)
        {
          cout<<phil->key<<" ";
          phil=phil->next;
        }
        cout<<endl;
    }

 }
