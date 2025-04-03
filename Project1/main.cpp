//
//  main.cpp
//  Project 1-Daniel Rios
//
//  Created by Danny Rios on 2/28/25.
#include <iostream>
#include "map.h"
#include <cassert>
using namespace std;


int key;
int value;

//constructor
Map:: Map() {
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}

//destructor
Map::~Map() {
    Node* current = head;
    while (current!= nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}


//copy constructor
Map:: Map(const Map& other) {
    head = nullptr;
    tail = nullptr;
    m_size = 0;
    KeyType k;
    ValueType v;
    for (int i = 0; i < other.size(); i++) {
        other.get(i, k, v);
        insert(k,v);
    }
}


//asignment operator
Map& Map::operator=(const Map& other){
    if(this == &other)
        return *this;
    
    //clears current map
    Node* current = head;
    while(current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    m_size = 0;
    
    //copies content form other map
    KeyType k;
    ValueType v;
    for(int i = 0; i < other.size(); i++) {
        other.get(i, k, v);
        insert(k,v);
    }
    return *this;
}


bool Map:: empty() const {
    if (m_size == 0 ) return true;
    else return false;
    
}


//returns size of map
int Map:: size() const {
    return m_size;
}


//adds new pair to list
bool Map:: insert(const KeyType &key, const ValueType &value){
   Node* current = head;
    while (current!= nullptr){
        if (current->key ==key) return false;
        
        current = current-> next;
    }
    Node* newNode = new Node(key, value);
    if (head == nullptr ) {
        head = newNode;
        tail = newNode;
    }
    else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    m_size +=1;
    return true;
};


//checks if map has a given key
bool Map::contains(const KeyType& key) const {
    Node* current= head;
    while( current != nullptr){
        if(current->key == key)
            return true;
        current = current->next;
        }
    
return false;
}


//removes the node that has the key passed through if it exists otherwise false
bool Map::erase(const KeyType &key) {
    
    Node* current = head;
    while(current != nullptr){
        if(current->key == key) {
            if (current == head && current == tail){
                head = nullptr;
                tail = nullptr;
            }
            else if(current == head) {
                head = head->next;
                head->prev = nullptr;
            }
            else if( current == tail) {
                tail = tail->prev;
                tail->next = nullptr;
            }
            else {
                current->prev->next = current->next;
                current->next->prev = current ->prev;
                
            }
            delete current;
            m_size -= 1;
            return true;
          
        }
        current = current->next;
    }
    return false;
}


//updates the value of a key or returns false if the key DNE
bool Map::update(const KeyType &key, const ValueType &value)
{
    Node* current = head;
    while(current != nullptr) {
        if (current->key == key){
            current->value = value;
            return true;
        }
        
        current = current->next;
    }
    return false;
        }


//gets the value that is attached to key
bool Map::get(const KeyType &key, ValueType &value)const {
    Node* current = head;
    while(current != nullptr) {
        if(current-> key == key) {
            value = current-> value;
            return true;
        }
        current = current->next;
    
    }
    return false;
}


//gets the key value pair that is at i
bool Map::get(int i, KeyType& key, ValueType& value) const{
    Node* current = head;
    if (i<0 || i>= m_size) return false;
    int count = 0;
    while (count < i) {
        if (current == nullptr) return false;
        current = current->next;
        count++;
    }
    key = current->key;
    value = current->value;
    return true;
}


//if key exists it updates it if it doesnt then it inserts a new pair
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value){
    if(contains(key)){
        update(key,value);
        return true;
    }
    else{
        insert(key, value);
        return true;
    }
}


//swaps all data between one man and another
void Map::swap(Map& other){
    // swapping head pointers
    Node* tempHead = head;
    head = other.head;
    other.head = tempHead;
    
    //swapping tail pointers
    Node* tempTail = tail;
    tail = other.tail;
    other.tail = tempTail;
    
    // swapping sizes
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
  
}


//creates a temp map that contains all unqiue keys from m1 and m2 or matching key and value pairs otherwise doesnt inculde in temp
bool combine(const Map& m1, const Map& m2, Map& result){
    
    Map temp;
   bool setError = false;
    
    for(int i = 0; i < m1.size(); i++) {
        KeyType k;
        ValueType v1;
        m1.get(i,k,v1);
        
        if(m2.contains(k)) {
            ValueType v2;
            m2.get(k, v2);
            
            if (v1 == v2) {
                temp.insert(k, v1);
            }
            else{
                setError = true;
            }
        }
        else{
            temp.insert(k,v1);
        }
    }
    
        for ( int i = 0; i < m2.size(); i++) {
            KeyType  k;
            ValueType v;
            m2.get(i, k ,v);
          if(!m1.contains(k))
            {
                temp.insert(k,v);
            }
        }
        result.swap(temp);
        return !setError;
    }


//adds all pairs from m1 that do not apear in m2 to temp then swaps with result
void subtract(const Map& m1, const Map& m2, Map& result) {
    Map temp;
    for( int i = 0; i< m1.size(); i++){
        
        KeyType key;
        ValueType value;
        m1.get(i,key, value);
        if(!m2.contains(key)){
            temp.insert(key,value);
        }
    }
    result.swap(temp);
}



void FunctionTests(){
    Map myMap;
    
    // assertions are under here vvvvvvvvvvvv
    assert(myMap.empty() == true); // tests empt()
    assert(myMap.size() == 0);     // test size()
    cerr << "\n Phase 1 test passed map empty and size is 0\n" << endl;
    
    
    // tests bool insert
    
    // Test Case 1 for insert
    assert(myMap.insert("A", 10) == true);
    assert(myMap.size() == 1);
    // Test case 2 for insert
    assert(myMap.insert("A",20) == false);
    assert(myMap.size() == 1);
    // Test case 3 for instert
    assert(myMap.insert("B", 20) == true);
    assert(myMap.insert("C", 30) == true);
    assert(myMap.size() == 3);
    //Test case 4 for insert
    assert(myMap.contains("A")== true);
    assert(myMap.contains("B")== true);
    assert(myMap.contains("C")== true);
    assert(myMap.contains("D")== false);
    cerr<< " All tests for insert() have passed \n" << endl;
    
    // tests for contains function
    assert(myMap.contains("x") == false); // Should be false to show an empty map
    assert(myMap.contains("abc") == false);
    assert(myMap.insert("abcd", 40) == true);
    assert(myMap.contains("abcd") == true);
    assert(myMap.contains ("abc") == false); // makes sure after inserting abcd abc isnt picked up as part of abcd
    //assert(myMap.erase("B") == true) // erases key for next assertion to check if B still exists
    //assert(myMap.contains("B") == false);
    assert(myMap.size() == 4);
    cerr << " All tests for contains() have passed \n" << endl;
    
    // tests for erase function
    
    assert(myMap.erase("X") == false);
    assert(myMap.erase("D") == false);
    assert(myMap.erase("A") == true );
    assert(myMap.contains("A")== false);
    assert(myMap.size() == 3);
    assert(myMap.erase("C") == true);
    assert(myMap.contains("C") == false);
    assert(myMap.size() == 2);
    assert(myMap.erase("B") == true);
    assert(myMap.size() == 1);
    assert(myMap.erase("abcd") == true);
    assert(myMap.empty() == true);
    
    cerr << " All tests for erase() functions has passed \n" << endl;
    
    //Tests for update() function
    
    assert(myMap.update("X", 100) == false); // X DNE so it shouldnt be found
    assert(myMap.insert("A", 10) == true);
    assert(myMap.update("A", 50) == true);
    assert(myMap.size() == 1); // no new keys added so this should pass
    assert(myMap.update("B" ,200) == false); // double checking to see if update works properly with a non exicstent key
    cerr<< "All tests for update() have passed \n" << endl;
    
    
    //test Case for get() function
    double Val;
    assert(myMap.get("X",Val) == false);
    assert(myMap.get("A", Val) == true);
    assert(Val == 50);
    assert(myMap.get("C",Val) == false);
    assert(myMap.get( "Z", Val)== false); //Z DNE
    assert(myMap.size() == 1);
    cerr << "All tests for get() fucntion have passed \n" << endl;
    
    // test cases for three argument get() function
    string key;
    
    //Clearing map for test
    myMap.erase("A");
    myMap.erase("B");
    myMap.erase("C");
    assert(myMap.get(0,key,Val) == false);
    
    //filling values for test
    assert(myMap.insert("X", 100) == true);
    assert(myMap.insert("Y", 200) == true);
    assert(myMap.insert("Z", 300) == true);
    assert(myMap.size() == 3);
    
    //Retrieving elements in order
    assert(myMap.get(0,key,Val) == true);
    assert(key == "X");
    assert(Val == 100);
    
    assert(myMap.get(1,key,Val) == true);
    assert(key == "Y");
    assert(Val == 200);
    
    assert(myMap.get(2,key,Val) == true);
    assert(key == "Z");
    assert(Val == 300);
    
    //out of scope cases
    assert(myMap.get(3, key, Val) == false); // node 3 DNE
    assert(myMap.get(-1, key, Val) == false); //negative size DNE
    cerr << "All tests for the 3 argument get() function have passed \n " << endl;
    
    
    //tests for insertOrUpdate()
    
    //insert a new key A with value 10
    assert(myMap.insertOrUpdate("A",10) == true);
    assert(myMap.get("A",Val) == true);
    assert(Val ==10);
    
    //update existing key a to 50
    assert(myMap.insertOrUpdate("A",50) == true);
    assert(myMap.get("A",Val) == true);
    assert(Val ==50);
    
    //insert new key B with value 20
    assert(myMap.insertOrUpdate("B",20) == true);
    assert(myMap.get("B",Val) == true);
    assert(Val ==20);
    
    //update exisiting key B to 100
    assert(myMap.insertOrUpdate("B",100) == true);
    assert(myMap.get("B",Val) == true);
    assert(Val ==100);
    
    //checks if map size is correct
    assert(myMap.size() == 5);
    cerr<< "All tests for InsertOrUpdate() function have passed \n" << endl;
    
    
    // swap test cases
    myMap.erase("A");
    myMap.erase("B");
    myMap.erase("C");
    myMap.erase("X");
    myMap.erase("Z");
    myMap.erase("Y");
    myMap.erase("abcd");
    
    //inserts data into map
    Map otherMap;
    assert(myMap.insert("A",10));
    assert(myMap.insert("B",20));
    
    assert(otherMap.insert("X",30));
    assert(otherMap.insert("Y",40));
    assert(otherMap.insert("Z",50));
    
    //checks the size of map before swap
    assert(myMap.size()== 2);
    assert(otherMap.size() == 3);
    
    myMap.swap(otherMap);
    
    //checks if swap worked
    assert(myMap.contains("X"));
    assert(myMap.contains("Y"));
    assert(myMap.contains("Z"));
    assert(!myMap.contains("A"));
    assert(myMap.size()== 3);
    
    assert(otherMap.contains("A"));
    assert(otherMap.contains("B"));
    assert(!otherMap.contains("X"));
    assert(otherMap.size()== 2);
    cerr << "All tests for Swap() function have passed \n" << endl;
    
   
    // Cases for combine function (7 test cases)
    
    Map m1;
    Map m2;
    Map result;
    ValueType val;
    
    //unique key in m2 only
    m1.insert("A", 1);
    assert(combine(m1,m2,result) == true);
    assert(result.size() == 1);
    assert(result.contains("A") && result.get("A",val) && val == 1);
    
    //unique key in m2 only
    m1= Map(); m2 = Map(); result = Map();
    m2.insert("B", 2);
    assert(combine(m1, m2, result) == true);
    assert(result.size() ==1);
    assert(result.contains("B") && result.get("B", val) && val == 2);
    
    //Case 3: shared key same value
    m1= Map(); m2 = Map(); result = Map();
    m1.insert("A", 10);
    m2.insert("A", 10);
    assert(combine(m1,m2,result) == true);
    assert(result.size() == 1);
    assert(result.contains("A") && result.get("A", val) && val == 10);
    
    // Case 4: shared key diffrent Values setError:
    m1= Map(); m2 = Map(); result = Map();
    m1.insert("A", 10);
    m2.insert("A", 20);
    assert(combine(m1,m2,result) == false);
    assert(result.size() == 0);
    
    //case 5: Working function no setError:
    m1= Map(); m2 = Map(); result = Map();
    m1.insert("Fred",123);
    m1.insert("Ethel",456);
    m1.insert("Lucy",789);
    m2.insert("Lucy",789);
    m2.insert("Ricky",321);
    assert(combine(m1,m2,result) == true);
    assert(result.size() == 4);
    assert(result.contains("Fred"));
    assert(result.contains("Ethel"));
    assert(result.contains("Lucy"));
    assert(result.contains("Ricky"));
    
    //case 6 Function with setError
    m1= Map(); m2 = Map(); result = Map();
    m1.insert("Fred",123);
    m1.insert("Ethel",456);
    m1.insert("Lucy",789);
    m2.insert("Lucy",567); //Set Error
    m2.insert("Ricky",321);
    assert(combine(m1,m2,result) == false);
    assert(result.size() == 3);
    assert(result.contains("Fred"));
    assert(result.contains("Ethel"));
    assert(result.contains("Ricky"));
    assert(!result.contains("Lucy"));
    
    //case 7 empty maps
    m1= Map(); m2 = Map(); result = Map();
    assert(combine(m1,m2,result) == true);
    assert(result.empty());
    
    cerr << "All tests for combine() function have passed \n" << endl;
    
    //test cases for subtract() function
    
    m1 = Map();
    m2 = Map();
    result = Map();
    
    //case 1 keys in m1 only should be coppied
    m1.insert("A",1);
    m1.insert("B",2);
    m2.insert("C",3);
    subtract(m1,m2,result);
    assert(result.size()== 2);
    assert(result.contains("A") && result.get("A", val) && val ==1);
    assert(result.contains("B") && result.get("B", val) && val ==2);
    
    //case 2 keys shared between m1 and m2 are skipped
    m1 = Map(); m2 = Map(); result = Map();
    m1.insert("A",1);
    m1.insert("B", 2);
    m2.insert("B",2);
    subtract(m1, m2, result);
    assert(result.size() == 1);
    assert(result.contains("A") && result.get("A", val) && val ==1);
    assert(!result.contains("B"));
    
    //case 3 shared keys with dif values are skipped
    m1 = Map(); m2 = Map(); result = Map();
    m1.insert("A",1);
    m1.insert("B", 2);
    m2.insert("B",222);
    subtract(m1, m2, result);
    assert(result.size() == 1);
    assert(result.contains("A") && result.get("A", val) && val ==1);
    assert(!result.contains("B"));
    
    //case 4 all keys in m1 and m2 resulting in empty
    m1 = Map(); m2 = Map(); result = Map();
    m1.insert("A",1);
    m1.insert("B", 2);
    m2.insert("A",1);
    m2.insert("B", 2);
    subtract(m1, m2, result);
    assert(result.empty());
    
    //case 5 m1 is empty
    m1 = Map(); m2 = Map(); result = Map();
    m2.insert("A",1);
    subtract(m1, m2, result);
    assert(result.empty());
    
    //case 6 m2 is empty
    m1 = Map(); m2 = Map(); result = Map();
    m1.insert("X", 10);
    m1.insert("Y", 20);
    subtract (m1,m2,result);
    assert(result.size() == 2);
    assert(result.contains("X") && result.get("X", val) && val == 10);
    assert(result.contains("Y") && result.get("Y", val) && val == 20);
    
    //case 7 both maps are empty
    m1 = Map(); m2 = Map(); result = Map();
    subtract(m1,m2, result);
    assert(result.empty());
    
    cerr << "All tests for subtract() function have passed \n" << endl;
}

// GIVEN FINAL TESTS

//void test()
//       {
//           Map m;
//           assert(m.insert("Fred", 123));
//           assert(m.insert("Ethel", 456));
//           assert(m.size() == 2);
//           double d = 42;
//           assert(m.get("Fred", d)  &&  d == 123);
//           d = 42;
//           string s1;
//           assert(m.get(0, s1, d)  &&
//                  ((s1 == "Fred"  &&  d == 123)  ||  (s1 == "Ethel"  &&  d == 456)));
//           string s2;
//           assert(m.get(1, s2, d)  &&  s1 != s2  &&
//                  ((s2 == "Fred"  &&  d == 123)  ||  (s2 == "Ethel"  &&  d == 456)));
//       }

//void test2()
//        {
//            Map m;
//            assert(m.insert(123, "Fred"));
//            assert(m.insert(456, "Ethel"));
//            assert(m.size() == 2);
//            string s;
//            assert(m.get(123, s)  &&  s == "Fred");
//            s = "";
//            int i1;
//            assert(m.get(0, i1, s)  &&
//                   ((i1 == 123  &&  s == "Fred")  ||  (i1 == 456  &&  s == "Ethel")));
//            int i2;
//            assert(m.get(1, i2, s)  &&  i1 != i2  &&
//                   ((i2 == 123  &&  s == "Fred")  ||  (i2 == 456  &&  s == "Ethel")));
//        }

int main(){
  
   // FunctionTests();
    
    //test2();
    //cout << "Passed all tests" << endl;
    
    return 0;
};
