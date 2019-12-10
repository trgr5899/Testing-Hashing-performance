#include<iostream>
#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <chrono>
#include<fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include "Finalhashclass.hpp"
using namespace std;
//main driver for data structures final project
int main(int argc, char *argv[])
{
  string numberS;//string used to grab values from the file
  int number;//int used to convert string to int
  int size1=0;//these will determine the size of the data sets
  int size2=0;
  int dS1[16384];//These are arrays that are going to hold all the data values, i could have used vectors to make this more versatile
  int dS2[16384];
  ifstream dataSet1;//these are the two different instream files
  ifstream dataSet2;
  dataSet2.open(argv[2]);//THese open the files
  dataSet1.open(argv[1]);
  HashTable ht,ht2;//these are the two hash tables for each data set
  if(dataSet1.is_open())//opening the first file
  {
    while (getline(dataSet1,numberS,','))//putting data set one and putting all the values in an array
    {
      number=stoi(numberS);//converting from number to string
      dS1[size1]=number;//data set 1 array
      size1=size1+1;//incrementing the array and getting the size of the array
    }
  }
  else//if the file does not open then end the program
  {
    cout<<"DATA set one did not open"<<endl;
    return 0;
  }
  if(dataSet2.is_open())//open the second data set
  {
    while (getline(dataSet2,numberS,','))//putting data set two into an array
    {
      number=stoi(numberS);//converting from number to string
      dS2[size2]=number;//data set 2 array
      size2=size2+1;//incrementing and gettting the size of the second data set
    }
  }
  else//ends the program fi the file does not open
  {
    cout<<"DATA set two did not open"<<endl;
    return 0;
  }


  //NOW WE WILL BEGIN TESTING
  /*
  *
  *             DATA SET ONE
  *
  *
  */
  //Linked list Tesing hashFunctionOne and data set one
  double LoadFactor=0.0;//load factor variable
  bool Test=true;//this tells the loop when to end
  int testNum=1;
  int random;
  bool insert=false;
  bool search=false;
  bool deleteT=false;
  int startTime,endTime;
  int buckets;
  buckets=0;
  double execTime;
  double totTimeI,totTimeD,totTimeS,totTime;
  double start,end;
  totTimeI=0.000000;
  totTimeD=0.000;
  totTimeS=0.000;
  totTime=0.000;
  double time_taken;

  int index=0;//keeps the index at which the correct load factor has been reached
  cout<<"--LINKED LIST USING HASH FUNC 1 AND DATA SET 1--"<<endl;
  while(Test)//runs until we have finished the test
  {

    if(search==true&&deleteT==true&&insert==true)//this resets the tests but increments the test number
    {
      insert=false;
      search=false;
      deleteT=false;
      testNum=testNum+1;

    }
    ht.insertItemLL(dS1[index]);//insert into hash table until the load factor is met
    LoadFactor=index/10009.0;//sets the load factor per index
    if(LoadFactor>=0.1&&insert!=true&&testNum==1)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLL(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.1&&deleteT!=true&&testNum==1)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLL(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.1&&search!=true&&testNum==1)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLL(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.1: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.2&&insert!=true&&testNum==2)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLL(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.2&&deleteT!=true&&testNum==2)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLL(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.2&&search!=true&&testNum==2)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLL(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.2: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.5&&insert!=true&&testNum==3)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLL(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.5&&deleteT!=true&&testNum==3)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLL(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.5&&search!=true&&testNum==3)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLL(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.5: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.7&&insert!=true&&testNum==4)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLL(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.7&&deleteT!=true&&testNum==4)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLL(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.7&&search!=true&&testNum==4)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLL(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.7: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.9&&insert!=true&&testNum==5)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLL(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.9&&deleteT!=true&&testNum==5)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLL(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.9&&search!=true&&testNum==5)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLL(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.9: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=1&&insert!=true&&testNum==6)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLL(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=1&&deleteT!=true&&testNum==6)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLL(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=1&&search!=true&&testNum==6)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLL(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 1.0: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      Test=false;//ends the loop
      //need something that averages the time for insert
    }

    index=index+1;//increments the index

    }
  /*
  *
  *             DATA SET ONE
  *
  *
  */
  //Linked list Tesing hashFunctionTwo and data set one
  LoadFactor=0.0;//load factor variable
  Test=true;//this tells the loop when to end
  testNum=1;
  insert=false;
  search=false;
  deleteT=false;
  buckets=0;        //reseting all my variables back to their orignial values;
  totTimeI=0;
  totTimeD=0;
  totTimeS=0;
  totTime=0;
  execTime=0;
  endTime=0;
  startTime=0;
  index=0;//keeps the index at which the correct load factor has been reached
  cout<<"--LINKED LIST USING HASH FUNC 2 AND DATA SET 1--"<<endl;
  while(Test)//runs until we have finished the test
  {

    if(search==true&&deleteT==true&&insert==true)//this resets the tests but increments the test number
    {
      insert=false;
      search=false;
      deleteT=false;
      testNum=testNum+1;
    }
    ht.insertItemLL2(dS1[index]);//insert into hash table until the load factor is met
    LoadFactor=index/10009.0;//sets the load factor per index


    if(LoadFactor>=0.1&&insert!=true&&testNum==1)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLL2(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.1&&deleteT!=true&&testNum==1)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLL2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.1&&search!=true&&testNum==1)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLL2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.1: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.2&&insert!=true&&testNum==2)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLL2(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.2&&deleteT!=true&&testNum==2)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLL2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.2&&search!=true&&testNum==2)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLL2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.2: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.5&&insert!=true&&testNum==3)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLL2(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.5&&deleteT!=true&&testNum==3)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLL2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.5&&search!=true&&testNum==3)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLL2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.5: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.7&&insert!=true&&testNum==4)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLL2(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.7&&deleteT!=true&&testNum==4)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLL2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.7&&search!=true&&testNum==4)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLL2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.7: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.9&&insert!=true&&testNum==5)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLL2(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.9&&deleteT!=true&&testNum==5)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLL2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.9&&search!=true&&testNum==5)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLL2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.9: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=1&&insert!=true&&testNum==6)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLL2(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=1&&deleteT!=true&&testNum==6)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLL2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=1&&search!=true&&testNum==6)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLL2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 1.0: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      Test=false;//ends the loop
      //need something that averages the time for insert
    }

    index=index+1;//increments the index

  }

  /*
  *
  *             DATA SET ONE
  *
  *
  */
  //BST Tesing hashFunctionone and data set one
  LoadFactor=0.0;//load factor variable
  Test=true;//this tells the loop when to end
  testNum=1;
  insert=false;
  search=false;
  deleteT=false;
  buckets=0;        //reseting all my variables back to their orignial values;
  totTimeI=0;
  totTimeD=0;
  totTimeS=0;
  totTime=0;
  execTime=0;
  endTime=0;
  startTime=0;
  index=0;//keeps the index at which the correct load factor has been reached
  cout<<"--BST USING HASH FUNC 1 AND DATA SET 1--"<<endl;
  while(Test)//runs until we have finished the test
  {

    if(search==true&&deleteT==true&&insert==true)//this resets the tests but increments the test number
    {
      insert=false;
      search=false;
      deleteT=false;
      testNum=testNum+1;
    }
    ht.insertItemBST(dS1[index]);//insert into hash table until the load factor is met
    LoadFactor=index/10009.0;//sets the load factor per index


    if(LoadFactor>=0.1&&insert!=true&&testNum==1)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemBST(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.1&&deleteT!=true&&testNum==1)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemBST(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.1&&search!=true&&testNum==1)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemBST(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.1: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.2&&insert!=true&&testNum==2)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemBST(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.2&&deleteT!=true&&testNum==2)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemBST(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.2&&search!=true&&testNum==2)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemBST(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.2: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.5&&insert!=true&&testNum==3)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemBST(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.5&&deleteT!=true&&testNum==3)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemBST(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.5&&search!=true&&testNum==3)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemBST(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.5: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.7&&insert!=true&&testNum==4)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemBST(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.7&&deleteT!=true&&testNum==4)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemBST(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.7&&search!=true&&testNum==4)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemBST(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.7: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.9&&insert!=true&&testNum==5)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemBST(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.9&&deleteT!=true&&testNum==5)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemBST(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.9&&search!=true&&testNum==5)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemBST(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.9: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=1&&insert!=true&&testNum==6)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemBST(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=1&&deleteT!=true&&testNum==6)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemBST(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=1&&search!=true&&testNum==6)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemBST(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 1.0: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      Test=false;//ends the loop
      //need something that averages the time for insert
    }

    index=index+1;//increments the index

  }
  /*
  *
  *             DATA SET ONE
  *
  *
  */
  //BST Tesing hashFunctiontwo and data set one
  LoadFactor=0.0;//load factor variable
  Test=true;//this tells the loop when to end
  testNum=1;
  insert=false;
  search=false;
  deleteT=false;
  buckets=0;        //reseting all my variables back to their orignial values;
  totTimeI=0;
  totTimeD=0;
  totTimeS=0;
  totTime=0;
  execTime=0;
  endTime=0;
  startTime=0;
  index=0;//keeps the index at which the correct load factor has been reached
  cout<<"--BST USING HASH FUNC 2 AND DATA SET 1--"<<endl;
  while(Test)//runs until we have finished the test
  {

    if(search==true&&deleteT==true&&insert==true)//this resets the tests but increments the test number
    {
      insert=false;
      search=false;
      deleteT=false;
      testNum=testNum+1;
    }
    ht.insertItemBST2(dS1[index]);//insert into hash table until the load factor is met
    LoadFactor=index/10009.0;//sets the load factor per index


    if(LoadFactor>=0.1&&insert!=true&&testNum==1)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemBST2(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.1&&deleteT!=true&&testNum==1)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemBST2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.1&&search!=true&&testNum==1)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemBST2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.1: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.2&&insert!=true&&testNum==2)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemBST2(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.2&&deleteT!=true&&testNum==2)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemBST2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.2&&search!=true&&testNum==2)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemBST2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.2: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.5&&insert!=true&&testNum==3)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemBST2(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.5&&deleteT!=true&&testNum==3)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemBST2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.5&&search!=true&&testNum==3)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemBST2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.5: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.7&&insert!=true&&testNum==4)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemBST2(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.7&&deleteT!=true&&testNum==4)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemBST2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.7&&search!=true&&testNum==4)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemBST2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.7: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.9&&insert!=true&&testNum==5)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemBST2(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.9&&deleteT!=true&&testNum==5)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemBST2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.9&&search!=true&&testNum==5)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemBST2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.9: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=1&&insert!=true&&testNum==6)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemBST2(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=1&&deleteT!=true&&testNum==6)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemBST2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=1&&search!=true&&testNum==6)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemBST2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 1.0: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      Test=false;//ends the loop
      //need something that averages the time for insert
    }

    index=index+1;//increments the index

  }
  /*
  *
  *             DATA SET ONE
  *
  *
  */
  //Linear Probing Tesing hashFunctionone and data set one
  LoadFactor=0.0;//load factor variable
  Test=true;//this tells the loop when to end
  testNum=1;
  insert=false;
  search=false;
  deleteT=false;
  buckets=0;        //reseting all my variables back to their orignial values;
  totTimeI=0;
  totTimeD=0;
  totTimeS=0;
  totTime=0;
  execTime=0;
  endTime=0;
  startTime=0;
  index=0;//keeps the index at which the correct load factor has been reached
  cout<<"--linear probing USING HASH FUNC 1 AND DATA SET 1--"<<endl;
  while(Test)//runs until we have finished the test
  {

    if(search==true&&deleteT==true&&insert==true)//this resets the tests but increments the test number
    {
      insert=false;
      search=false;
      deleteT=false;
      testNum=testNum+1;
    }
    ht.insertItemLP(dS1[index]);//insert into hash table until the load factor is met
    LoadFactor=index/10009.0;//sets the load factor per index


    if(LoadFactor>=0.1&&insert!=true&&testNum==1)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLP(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.1&&deleteT!=true&&testNum==1)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLP(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.1&&search!=true&&testNum==1)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLP(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.1: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.2&&insert!=true&&testNum==2)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLP(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.2&&deleteT!=true&&testNum==2)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLP(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.2&&search!=true&&testNum==2)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLP(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.2: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.5&&insert!=true&&testNum==3)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLP(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.5&&deleteT!=true&&testNum==3)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLP(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.5&&search!=true&&testNum==3)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLP(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.5: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.7&&insert!=true&&testNum==4)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLP(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.7&&deleteT!=true&&testNum==4)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLP(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.7&&search!=true&&testNum==4)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLP(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.7: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.9&&insert!=true&&testNum==5)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLP(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.9&&deleteT!=true&&testNum==5)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLP(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.9&&search!=true&&testNum==5)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLP(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.9: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=1&&insert!=true&&testNum==6)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLP(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=1&&deleteT!=true&&testNum==6)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLP(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=1&&search!=true&&testNum==6)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLP(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 1.0: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      Test=false;//ends the loop
      //need something that averages the time for insert
    }



    index=index+1;//increments the index

  }
  /*
  *
  *             DATA SET ONE
  *
  *
  */
  //Linear Probing Tesing hashFunctiontwo and data set one
  LoadFactor=0.0;//load factor variable
  Test=true;//this tells the loop when to end
  testNum=1;
  insert=false;
  search=false;
  deleteT=false;
  buckets=0;        //reseting all my variables back to their orignial values;
  totTimeI=0;
  totTimeD=0;
  totTimeS=0;
  totTime=0;
  execTime=0;
  endTime=0;
  startTime=0;
  index=0;//keeps the index at which the correct load factor has been reached
  cout<<"--linear probing USING HASH FUNC 2 AND DATA SET 1--"<<endl;
  while(Test)//runs until we have finished the test
  {

    if(search==true&&deleteT==true&&insert==true)//this resets the tests but increments the test number
    {
      insert=false;
      search=false;
      deleteT=false;
      testNum=testNum+1;
    }
    ht.insertItemLP2(dS1[index]);//insert into hash table until the load factor is met
    LoadFactor=index/10009.0;//sets the load factor per index


    if(LoadFactor>=0.1&&insert!=true&&testNum==1)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLP2(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.1&&deleteT!=true&&testNum==1)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLP2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.1&&search!=true&&testNum==1)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLP2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.1: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.2&&insert!=true&&testNum==2)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLP2(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.2&&deleteT!=true&&testNum==2)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLP2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.2&&search!=true&&testNum==2)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLP2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.2: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.5&&insert!=true&&testNum==3)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLP2(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.5&&deleteT!=true&&testNum==3)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLP2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.5&&search!=true&&testNum==3)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLP2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.5: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.7&&insert!=true&&testNum==4)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLP2(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.7&&deleteT!=true&&testNum==4)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLP2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.7&&search!=true&&testNum==4)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLP2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.7: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.9&&insert!=true&&testNum==5)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLP2(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.9&&deleteT!=true&&testNum==5)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLP2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.9&&search!=true&&testNum==5)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLP2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.9: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=1&&insert!=true&&testNum==6)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLP2(dS1[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=1&&deleteT!=true&&testNum==6)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLP2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=1&&search!=true&&testNum==6)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLP2(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 1.0: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      Test=false;//ends the loop
      //need something that averages the time for insert
    }
    index=index+1;//increments the index

  }
  /*
  *
  *             DATA SET ONE
  *
  *
  */
  //CUCKOO Tesing and data set one
  LoadFactor=0.0;//load factor variable
  Test=true;//this tells the loop when to end
  testNum=1;
  insert=false;
  search=false;
  deleteT=false;
  buckets=0;        //reseting all my variables back to their orignial values;
  totTimeI=0;
  totTimeD=0;
  totTimeS=0;
  totTime=0;
  execTime=0;
  endTime=0;
  startTime=0;
  bool checkcycle=true;
  bool checkcycle2=true;
  float tableCS=10009;//table size variable
  int resized=0;//checks how many times we increased the table size
  index=0;//keeps the index at which the correct load factor has been reached
  cout<<"--CUCKOO Hashing using DATA SET 1--"<<endl;
  while(Test)//runs until we have finished the test
  {

    if(search==true&&deleteT==true&&insert==true)//this resets the tests but increments the test number
    {
      insert=false;
      search=false;
      deleteT=false;
      resized=0;
      testNum=testNum+1;
    }
    checkcycle=ht.insertItemCuckoo(dS1[index]);
    if (checkcycle==false)
    {
      ht.changeTablesize();
      ht.resetTable();
      resized=resized+1;
      index=0;
      tableCS=tableCS+2;
    }
    LoadFactor=index/tableCS;//sets the load factor per index
    //cout<<LoadFactor<<endl;

    if(LoadFactor>=0.01&&insert!=true&&testNum==1)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        checkcycle2=ht.insertItemCuckoo(dS1[random]);
        if (checkcycle2==false)
        {
          ht.changeTablesize();
          ht.resetTable();
          resized=resized+1;
        }
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeI=totTimeI+time_taken;
      }

      totTimeI=totTimeI/100;//averages the time
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      insert=true;
      LoadFactor=0;
      //need something that averages the time for insert
    }

    if(LoadFactor>=0.01&&deleteT!=true&&testNum==1)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemCuckoo(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;
      }
      totTimeD=totTimeD/100;
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.01&&search!=true&&testNum==1)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.searchItemCuckoo(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.01: "<<fixed<<totTime<<setprecision(15)<<" seconds and resized: "<<resized<<" times"<<endl;
      totTime=0;
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;           //reseting all the times for another test
      totTime=0;
      time_taken=0;
      resized=0;
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.02&&insert!=true&&testNum==2)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        checkcycle2=ht.insertItemCuckoo(dS1[random]);
        if (checkcycle2==false)
        {
          ht.changeTablesize();
          ht.resetTable();
          resized=resized+1;
        }
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeI=totTimeI+time_taken;
      }

      totTimeI=totTimeI/100;//averages the time
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      insert=true;
      LoadFactor=0;
      //need something that averages the time for insert
    }

    if(LoadFactor>=0.02&&deleteT!=true&&testNum==2)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemCuckoo(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;
      }
      totTimeD=totTimeD/100;
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.02&&search!=true&&testNum==2)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.searchItemCuckoo(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.02: "<<fixed<<totTime<<setprecision(15)<<" seconds and resized: "<<resized<<" times"<<endl;
      totTime=0;
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;           //reseting all the times for another test
      totTime=0;
      time_taken=0;
      resized=0;
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.03&&insert!=true&&testNum==3)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        checkcycle2=ht.insertItemCuckoo(dS1[random]);
        if (checkcycle2==false)
        {
          ht.changeTablesize();
          ht.resetTable();
          resized=resized+1;
        }
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeI=totTimeI+time_taken;
      }

      totTimeI=totTimeI/100;//averages the time
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      insert=true;
      LoadFactor=0;
      //need something that averages the time for insert
    }

    if(LoadFactor>=0.03&&deleteT!=true&&testNum==3)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemCuckoo(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;
      }
      totTimeD=totTimeD/100;
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.03&&search!=true&&testNum==3)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.searchItemCuckoo(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.03: "<<fixed<<totTime<<setprecision(15)<<" seconds and resized: "<<resized<<" times"<<endl;
      totTime=0;
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;           //reseting all the times for another test
      totTime=0;
      time_taken=0;
      resized=0;
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.04&&insert!=true&&testNum==4)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        checkcycle2=ht.insertItemCuckoo(dS1[random]);
        if (checkcycle2==false)
        {
          ht.changeTablesize();
          ht.resetTable();
          resized=resized+1;
        }
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeI=totTimeI+time_taken;
      }

      totTimeI=totTimeI/100;//averages the time
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      insert=true;
      LoadFactor=0;
      //need something that averages the time for insert
    }

    if(LoadFactor>=0.04&&deleteT!=true&&testNum==4)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemCuckoo(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;
      }
      totTimeD=totTimeD/100;
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.04&&search!=true&&testNum==4)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.searchItemCuckoo(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.04: "<<fixed<<totTime<<setprecision(15)<<" seconds and resized: "<<resized<<" times"<<endl;
      totTime=0;
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;           //reseting all the times for another test
      totTime=0;
      time_taken=0;
      resized=0;
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.05&&insert!=true&&testNum==5)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        checkcycle2=ht.insertItemCuckoo(dS1[random]);
        if (checkcycle2==false)
        {
          ht.changeTablesize();
          ht.resetTable();
          resized=resized+1;
        }
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeI=totTimeI+time_taken;
      }

      totTimeI=totTimeI/100;//averages the time
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      insert=true;
      LoadFactor=0;
      //need something that averages the time for insert
    }

    if(LoadFactor>=0.05&&deleteT!=true&&testNum==5)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemCuckoo(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;
      }
      totTimeD=totTimeD/100;
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.05&&search!=true&&testNum==5)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.searchItemCuckoo(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.05: "<<fixed<<totTime<<setprecision(15)<<" seconds and resized: "<<resized<<" times"<<endl;
      totTime=0;
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;           //reseting all the times for another test
      totTime=0;
      time_taken=0;
      resized=0;
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.0555&&insert!=true&&testNum==6)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        checkcycle2=ht.insertItemCuckoo(dS1[random]);
        if (checkcycle2==false)
        {
          ht.changeTablesize();
          ht.resetTable();
          resized=resized+1;
        }
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeI=totTimeI+time_taken;
      }

      totTimeI=totTimeI/100;//averages the time
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      insert=true;
      LoadFactor=0;
      //need something that averages the time for insert
    }

    if(LoadFactor>=0.0555&&deleteT!=true&&testNum==6)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemCuckoo(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;
      }
      totTimeD=totTimeD/100;
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.0555&&search!=true&&testNum==6)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.searchItemCuckoo(dS1[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.0555: "<<fixed<<totTime<<setprecision(15)<<" seconds and resized: "<<resized<<" times"<<endl;
      totTime=0;
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;           //reseting all the times for another test
      totTime=0;
      time_taken=0;
      resized=0;
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      Test=false;
      //need something that averages the time for insert
    }
    //cout<<tableCS<<"**"<<LoadFactor<<endl;
    index=index+1;//increments the index
  }

    /*
    *
    *             DATA SET Two
    *
    *
    */
    //Linked list Tesing hashFunctionone and data set two
    ht.resetTable();
    ht.resetAnyTable(1);
    ht.resetAnyTable(2);
    ht.resetAnyTable(3);
    ht.resetAnyTable(4);
    ht.resetAnyTable(5);
    ht.resetAnyTable(6);
    LoadFactor=0.0;//load factor variable
    Test=true;//this tells the loop when to end
    testNum=1;
    insert=false;
    search=false;
    deleteT=false;
    buckets=0;        //reseting all my variables back to their orignial values;
    totTimeI=0;
    totTimeD=0;
    totTimeS=0;
    totTime=0;
    index=0;//keeps the index at which the correct load factor has been reaches
  cout<<"--LINKED LIST USING HASH FUNC 1 AND DATA SET 2--"<<endl;
  while(Test)//runs until we have finished the test
  {

    if(search==true&&deleteT==true&&insert==true)//this resets the tests but increments the test number
    {
      insert=false;
      search=false;
      deleteT=false;
      testNum=testNum+1;

    }
    ht.insertItemLL(dS2[index]);//insert into hash table until the load factor is met
    LoadFactor=index/10009.0;//sets the load factor per index
    if(LoadFactor>=0.1&&insert!=true&&testNum==1)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLL(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.1&&deleteT!=true&&testNum==1)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLL(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.1&&search!=true&&testNum==1)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLL(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.1: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.2&&insert!=true&&testNum==2)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLL(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.2&&deleteT!=true&&testNum==2)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLL(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.2&&search!=true&&testNum==2)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLL(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.2: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.5&&insert!=true&&testNum==3)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLL(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.5&&deleteT!=true&&testNum==3)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLL(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.5&&search!=true&&testNum==3)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLL(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.5: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.7&&insert!=true&&testNum==4)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLL(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.7&&deleteT!=true&&testNum==4)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLL(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.7&&search!=true&&testNum==4)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLL(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.7: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.9&&insert!=true&&testNum==5)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLL(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.9&&deleteT!=true&&testNum==5)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLL(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.9&&search!=true&&testNum==5)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLL(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.9: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=1&&insert!=true&&testNum==6)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLL(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=1&&deleteT!=true&&testNum==6)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLL(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=1&&search!=true&&testNum==6)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLL(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 1.0: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(1);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      Test=false;//ends the loop
      //need something that averages the time for insert
    }

    index=index+1;//increments the index

    }
  /*
  *
  *             DATA SET 2
  *
  *
  */
  //Linked list Tesing hashFunctionTwo and data set one
  LoadFactor=0.0;//load factor variable
  Test=true;//this tells the loop when to end
  testNum=1;
  insert=false;
  search=false;
  deleteT=false;
  buckets=0;        //reseting all my variables back to their orignial values;
  totTimeI=0;
  totTimeD=0;
  totTimeS=0;
  totTime=0;
  index=0;//keeps the index at which the correct load factor has been reached
  cout<<"--LINKED LIST USING HASH FUNC 2 AND DATA SET 2--"<<endl;
  while(Test)//runs until we have finished the test
  {

    if(search==true&&deleteT==true&&insert==true)//this resets the tests but increments the test number
    {
      insert=false;
      search=false;
      deleteT=false;
      testNum=testNum+1;
    }
    ht.insertItemLL2(dS2[index]);//insert into hash table until the load factor is met
    LoadFactor=index/10009.0;//sets the load factor per index


    if(LoadFactor>=0.1&&insert!=true&&testNum==1)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLL2(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.1&&deleteT!=true&&testNum==1)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLL2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.1&&search!=true&&testNum==1)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLL2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.1: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.2&&insert!=true&&testNum==2)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLL2(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.2&&deleteT!=true&&testNum==2)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLL2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.2&&search!=true&&testNum==2)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLL2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.2: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.5&&insert!=true&&testNum==3)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLL2(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.5&&deleteT!=true&&testNum==3)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLL2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.5&&search!=true&&testNum==3)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLL2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.5: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.7&&insert!=true&&testNum==4)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLL2(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.7&&deleteT!=true&&testNum==4)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLL2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.7&&search!=true&&testNum==4)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLL2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.7: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.9&&insert!=true&&testNum==5)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLL2(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.9&&deleteT!=true&&testNum==5)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLL2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.9&&search!=true&&testNum==5)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLL2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.9: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=1&&insert!=true&&testNum==6)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLL2(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=1&&deleteT!=true&&testNum==6)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLL2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=1&&search!=true&&testNum==6)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLL2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 1.0: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(2);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      Test=false;//ends the loop
      //need something that averages the time for insert
    }

    index=index+1;//increments the index

  }

  /*
  *
  *             DATA SET 2
  *
  *
  */
  //BST Tesing hashFunctionone and data set one
  LoadFactor=0.0;//load factor variable
  Test=true;//this tells the loop when to end
  testNum=1;
  insert=false;
  search=false;
  deleteT=false;
  buckets=0;        //reseting all my variables back to their orignial values;
  totTimeI=0;
  totTimeD=0;
  totTimeS=0;
  totTime=0;
  index=0;//keeps the index at which the correct load factor has been reached
  cout<<"--BST USING HASH FUNC 1 AND DATA SET 2--"<<endl;
  while(Test)//runs until we have finished the test
  {

    if(search==true&&deleteT==true&&insert==true)//this resets the tests but increments the test number
    {
      insert=false;
      search=false;
      deleteT=false;
      testNum=testNum+1;
    }
    ht.insertItemBST(dS2[index]);//insert into hash table until the load factor is met
    LoadFactor=index/10009.0;//sets the load factor per index


    if(LoadFactor>=0.1&&insert!=true&&testNum==1)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemBST(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.1&&deleteT!=true&&testNum==1)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemBST(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.1&&search!=true&&testNum==1)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemBST(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.1: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.2&&insert!=true&&testNum==2)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemBST(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.2&&deleteT!=true&&testNum==2)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemBST(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.2&&search!=true&&testNum==2)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemBST(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.2: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.5&&insert!=true&&testNum==3)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemBST(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.5&&deleteT!=true&&testNum==3)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemBST(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.5&&search!=true&&testNum==3)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemBST(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.5: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.7&&insert!=true&&testNum==4)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemBST(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.7&&deleteT!=true&&testNum==4)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemBST(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.7&&search!=true&&testNum==4)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemBST(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.7: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.9&&insert!=true&&testNum==5)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemBST(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.9&&deleteT!=true&&testNum==5)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemBST(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.9&&search!=true&&testNum==5)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemBST(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.9: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=1&&insert!=true&&testNum==6)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemBST(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=1&&deleteT!=true&&testNum==6)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemBST(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=1&&search!=true&&testNum==6)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemBST(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 1.0: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(3);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      Test=false;//ends the loop
      //need something that averages the time for insert
    }

    index=index+1;//increments the index

  }
  /*
  *
  *             DATA SET 2
  *
  *
  */
  //BST Tesing hashFunctiontwo and data set one
  LoadFactor=0.0;//load factor variable
  Test=true;//this tells the loop when to end
  testNum=1;
  insert=false;
  search=false;
  deleteT=false;
  buckets=0;        //reseting all my variables back to their orignial values;
  totTimeI=0;
  totTimeD=0;
  totTimeS=0;
  totTime=0;
  execTime=0;
  endTime=0;
  startTime=0;
  index=0;//keeps the index at which the correct load factor has been reached
  cout<<"--BST USING HASH FUNC 2 AND DATA SET 2--"<<endl;
  while(Test)//runs until we have finished the test
  {

    if(search==true&&deleteT==true&&insert==true)//this resets the tests but increments the test number
    {
      insert=false;
      search=false;
      deleteT=false;
      testNum=testNum+1;
    }
    ht.insertItemBST2(dS2[index]);//insert into hash table until the load factor is met
    LoadFactor=index/10009.0;//sets the load factor per index


    if(LoadFactor>=0.1&&insert!=true&&testNum==1)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemBST2(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.1&&deleteT!=true&&testNum==1)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemBST2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.1&&search!=true&&testNum==1)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemBST2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.1: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.2&&insert!=true&&testNum==2)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemBST2(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.2&&deleteT!=true&&testNum==2)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemBST2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.2&&search!=true&&testNum==2)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemBST2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.2: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.5&&insert!=true&&testNum==3)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemBST2(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.5&&deleteT!=true&&testNum==3)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemBST2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.5&&search!=true&&testNum==3)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemBST2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.5: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.7&&insert!=true&&testNum==4)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemBST2(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.7&&deleteT!=true&&testNum==4)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemBST2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.7&&search!=true&&testNum==4)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemBST2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.7: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.9&&insert!=true&&testNum==5)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemBST2(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.9&&deleteT!=true&&testNum==5)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemBST2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.9&&search!=true&&testNum==5)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemBST2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.9: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=1&&insert!=true&&testNum==6)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemBST2(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=1&&deleteT!=true&&testNum==6)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemBST2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=1&&search!=true&&testNum==6)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemBST2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 1.0: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(4);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      Test=false;//ends the loop
      //need something that averages the time for insert
    }

    index=index+1;//increments the index

  }
  /*
  *
  *             DATA SET 2
  *
  *
  */
  //Linear Probing Tesing hashFunctionone and data set one
  LoadFactor=0.0;//load factor variable
  Test=true;//this tells the loop when to end
  testNum=1;
  insert=false;
  search=false;
  deleteT=false;
  buckets=0;        //reseting all my variables back to their orignial values;
  totTimeI=0;
  totTimeD=0;
  totTimeS=0;
  totTime=0;
  index=0;//keeps the index at which the correct load factor has been reached
  cout<<"--linear probing USING HASH FUNC 1 AND DATA SET 2--"<<endl;
  while(Test)//runs until we have finished the test
  {

    if(search==true&&deleteT==true&&insert==true)//this resets the tests but increments the test number
    {
      insert=false;
      search=false;
      deleteT=false;
      testNum=testNum+1;
    }
    ht.insertItemLP(dS2[index]);//insert into hash table until the load factor is met
    LoadFactor=index/10009.0;//sets the load factor per index


    if(LoadFactor>=0.1&&insert!=true&&testNum==1)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLP(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.1&&deleteT!=true&&testNum==1)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLP(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.1&&search!=true&&testNum==1)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLP(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.1: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.2&&insert!=true&&testNum==2)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLP(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.2&&deleteT!=true&&testNum==2)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLP(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.2&&search!=true&&testNum==2)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLP(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.2: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.5&&insert!=true&&testNum==3)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLP(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.5&&deleteT!=true&&testNum==3)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLP(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.5&&search!=true&&testNum==3)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLP(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.5: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.7&&insert!=true&&testNum==4)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLP(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.7&&deleteT!=true&&testNum==4)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLP(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.7&&search!=true&&testNum==4)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLP(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.7: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.9&&insert!=true&&testNum==5)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLP(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.9&&deleteT!=true&&testNum==5)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLP(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.9&&search!=true&&testNum==5)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLP(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.9: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=1&&insert!=true&&testNum==6)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLP(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=1&&deleteT!=true&&testNum==6)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLP(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=1&&search!=true&&testNum==6)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLP(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 1.0: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(5);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      Test=false;//ends the loop
      //need something that averages the time for insert
    }



    index=index+1;//increments the index

  }
  /*
  *
  *             DATA SET 2
  *
  *
  */
  //Linear Probing Tesing hashFunctiontwo and data set one
  LoadFactor=0.0;//load factor variable
  Test=true;//this tells the loop when to end
  testNum=1;
  insert=false;
  search=false;
  deleteT=false;
  buckets=0;        //reseting all my variables back to their orignial values;
  totTimeI=0;
  totTimeD=0;
  totTimeS=0;
  totTime=0;
  index=0;//keeps the index at which the correct load factor has been reached
  cout<<"--linear probing USING HASH FUNC 2 AND DATA SET 2--"<<endl;
  while(Test)//runs until we have finished the test
  {

    if(search==true&&deleteT==true&&insert==true)//this resets the tests but increments the test number
    {
      insert=false;
      search=false;
      deleteT=false;
      testNum=testNum+1;
    }
    ht.insertItemLP2(dS1[index]);//insert into hash table until the load factor is met
    LoadFactor=index/10009.0;//sets the load factor per index


    if(LoadFactor>=0.1&&insert!=true&&testNum==1)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLP2(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.1&&deleteT!=true&&testNum==1)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLP2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.1&&search!=true&&testNum==1)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLP2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.1: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.2&&insert!=true&&testNum==2)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLP2(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.2&&deleteT!=true&&testNum==2)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLP2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.2&&search!=true&&testNum==2)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLP2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.2: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.5&&insert!=true&&testNum==3)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLP2(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.5&&deleteT!=true&&testNum==3)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLP2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.5&&search!=true&&testNum==3)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLP2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.5: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.7&&insert!=true&&testNum==4)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLP2(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.7&&deleteT!=true&&testNum==4)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLP2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.7&&search!=true&&testNum==4)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLP2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.7: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.9&&insert!=true&&testNum==5)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLP2(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=0.9&&deleteT!=true&&testNum==5)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLP2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=0.9&&search!=true&&testNum==5)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLP2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.9: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=1&&insert!=true&&testNum==6)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));//gets a random index
        auto start = chrono::high_resolution_clock::now();//starts taking the time
        ios_base::sync_with_stdio(false);//chrono syntax
        ht.insertItemLP2(dS2[random]);//insert into the hash
        auto end = chrono::high_resolution_clock::now();//end the time
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();//convert to nanoseconds
        time_taken *= 1e-9;//convert to seconds
        totTimeI=totTimeI+time_taken;//add all 100 times together
      }

      totTimeI=totTimeI/100;//average all the times
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      insert=true;//this is so that we do not insert again
      LoadFactor=0;//reset load factor
    }

    if(LoadFactor>=1&&deleteT!=true&&testNum==6)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemLP2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;

      }
      totTimeD=totTimeD/100;
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
    }
    if(LoadFactor>=1&&search!=true&&testNum==6)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)//all the same as insert
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();//used chrono to find the time
        ios_base::sync_with_stdio(false);
        ht.searchItemLP2(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 1.0: "<<fixed<<totTime<<setprecision(15)<<" seconds"<<endl;
      totTime=0;//reset all the time values
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;
      time_taken=0;
      ht.resetAnyTable(6);//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      Test=false;//ends the loop
      //need something that averages the time for insert
    }
    index=index+1;//increments the index

  }
  /*
  *
  *             DATA SET 2
  *
  *
  */
  //CUCKOO Tesing and data set one
  LoadFactor=0.0;//load factor variable
  Test=true;//this tells the loop when to end
  testNum=1;
  insert=false;
  search=false;
  deleteT=false;
  buckets=0;        //reseting all my variables back to their orignial values;
  totTimeI=0;
  totTimeD=0;
  totTimeS=0;
  totTime=0;
   checkcycle=true;
  checkcycle2=true;
  resized=0;//checks how many times we increased the table size
  index=0;//keeps the index at which the correct load factor has been reached
  cout<<"--CUCKOO Hashing using DATA SET 2--"<<endl;
  while(Test)//runs until we have finished the test
  {

    if(search==true&&deleteT==true&&insert==true)//this resets the tests but increments the test number
    {
      insert=false;
      search=false;
      deleteT=false;
      resized=0;
      testNum=testNum+1;
    }
    checkcycle=ht.insertItemCuckoo(dS2[index]);
    if (checkcycle==false)
    {
      ht.changeTablesize();
      ht.resetTable();
      resized=resized+1;
      index=0;
      tableCS=tableCS+2;
    }
    LoadFactor=index/tableCS;//sets the load factor per index
    //cout<<LoadFactor<<endl;

    if(LoadFactor>=0.01&&insert!=true&&testNum==1)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        checkcycle2=ht.insertItemCuckoo(dS2[random]);
        if (checkcycle2==false)
        {
          ht.changeTablesize();
          ht.resetTable();
          resized=resized+1;
        }
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeI=totTimeI+time_taken;
      }

      totTimeI=totTimeI/100;//averages the time
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      insert=true;
      LoadFactor=0;
      //need something that averages the time for insert
    }

    if(LoadFactor>=0.01&&deleteT!=true&&testNum==1)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemCuckoo(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;
      }
      totTimeD=totTimeD/100;
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.01&&search!=true&&testNum==1)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.searchItemCuckoo(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.01: "<<fixed<<totTime<<setprecision(15)<<" seconds and resized: "<<resized<<" times"<<endl;
      totTime=0;
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;           //reseting all the times for another test
      totTime=0;
      time_taken=0;
      resized=0;
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.02&&insert!=true&&testNum==2)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        checkcycle2=ht.insertItemCuckoo(dS2[random]);
        if (checkcycle2==false)
        {
          ht.changeTablesize();
          ht.resetTable();
          resized=resized+1;
        }
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeI=totTimeI+time_taken;
      }

      totTimeI=totTimeI/100;//averages the time
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      insert=true;
      LoadFactor=0;
      //need something that averages the time for insert
    }

    if(LoadFactor>=0.02&&deleteT!=true&&testNum==2)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemCuckoo(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;
      }
      totTimeD=totTimeD/100;
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.02&&search!=true&&testNum==2)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.searchItemCuckoo(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.02: "<<fixed<<totTime<<setprecision(15)<<" seconds and resized: "<<resized<<" times"<<endl;
      totTime=0;
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;           //reseting all the times for another test
      totTime=0;
      time_taken=0;
      resized=0;
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.028&&insert!=true&&testNum==3)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        checkcycle2=ht.insertItemCuckoo(dS2[random]);
        if (checkcycle2==false)
        {
          ht.changeTablesize();
          ht.resetTable();
          resized=resized+1;
        }
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeI=totTimeI+time_taken;
      }

      totTimeI=totTimeI/100;//averages the time
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      insert=true;
      LoadFactor=0;
      //need something that averages the time for insert
    }

    if(LoadFactor>=0.028&&deleteT!=true&&testNum==3)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemCuckoo(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;
      }
      totTimeD=totTimeD/100;
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.028&&search!=true&&testNum==3)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.searchItemCuckoo(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.028: "<<fixed<<totTime<<setprecision(15)<<" seconds and resized: "<<resized<<" times"<<endl;
      totTime=0;
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;           //reseting all the times for another test
      totTime=0;
      time_taken=0;
      resized=0;
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.0299&&insert!=true&&testNum==4)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        checkcycle2=ht.insertItemCuckoo(dS2[random]);
        if (checkcycle2==false)
        {
          ht.changeTablesize();
          ht.resetTable();
          resized=resized+1;
        }
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeI=totTimeI+time_taken;
      }

      totTimeI=totTimeI/100;//averages the time
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      insert=true;
      LoadFactor=0;
      //need something that averages the time for insert
    }

    if(LoadFactor>=0.0299&&deleteT!=true&&testNum==4)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemCuckoo(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;
      }
      totTimeD=totTimeD/100;
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.0299&&search!=true&&testNum==4)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.searchItemCuckoo(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.0299: "<<fixed<<totTime<<setprecision(15)<<" seconds and resized: "<<resized<<" times"<<endl;
      totTime=0;
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;           //reseting all the times for another test
      totTime=0;
      time_taken=0;
      resized=0;
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      Test=false;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.029917&&insert!=true&&testNum==5)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        checkcycle2=ht.insertItemCuckoo(dS2[random]);
        if (checkcycle2==false)
        {
          ht.changeTablesize();
          ht.resetTable();
          resized=resized+1;
        }
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeI=totTimeI+time_taken;
      }

      totTimeI=totTimeI/100;//averages the time
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      insert=true;
      LoadFactor=0;
      //need something that averages the time for insert
    }

    if(LoadFactor>=0.029917&&deleteT!=true&&testNum==5)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemCuckoo(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;
      }
      totTimeD=totTimeD/100;
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.029917&&search!=true&&testNum==5)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.searchItemCuckoo(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.029917: "<<fixed<<totTime<<setprecision(15)<<" seconds and resized: "<<resized<<" times"<<endl;
      totTime=0;
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;           //reseting all the times for another test
      totTime=0;
      time_taken=0;
      resized=0;
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.0555&&insert!=true&&testNum==6)//checks the load factor and see if we have done the insert test
    {
      for(int j=index+1;j<index+101;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        checkcycle2=ht.insertItemCuckoo(dS2[random]);
        if (checkcycle2==false)
        {
          ht.changeTablesize();
          ht.resetTable();
          resized=resized+1;
        }
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeI=totTimeI+time_taken;
      }

      totTimeI=totTimeI/100;//averages the time
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      insert=true;
      LoadFactor=0;
      //need something that averages the time for insert
    }

    if(LoadFactor>=0.0555&&deleteT!=true&&testNum==6)//checks the load factor and see if we have done the delete test
    {
      for(int j=0;j<100;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.deleteItemCuckoo(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeD=totTimeD+time_taken;
      }
      totTimeD=totTimeD/100;
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      deleteT=true;
      //need something that averages the time for insert
    }
    if(LoadFactor>=0.0555&&search!=true&&testNum==6)//checks the load factor and see if we have done the search test
    {
      for(int j=0;j<100;j++)
      {
        //THIS IS where i would need something to measure the time
        random=(rand() % (16384 - 0 + 1));
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);
        ht.searchItemCuckoo(dS2[random]);
        auto end = chrono::high_resolution_clock::now();
        time_taken =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTimeS=totTimeS+time_taken;
      }
      totTimeS=totTimeS/100;
      totTime=(totTimeD+totTimeI+totTimeS)/3;
      cout<<"EXECUTION TIME at LF 0.0555: "<<fixed<<totTime<<setprecision(15)<<" seconds and resized: "<<resized<<" times"<<endl;
      totTime=0;
      totTimeD=0;
      totTimeI=0;
      totTimeS=0;           //reseting all the times for another test
      totTime=0;
      time_taken=0;
      resized=0;
      ht.resetTable();//resets the table
      index=0;//set index back to zer0
      LoadFactor=0;
      search=true;
      Test=false;
      //need something that averages the time for insert
    }
    //cout<<tableCS<<"**"<<LoadFactor<<endl;
    index=index+1;//increments the index
  }















}
