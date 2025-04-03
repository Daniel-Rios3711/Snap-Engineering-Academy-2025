//
//  main.cpp
//  EXEPTIONS_LABS
//
//  Created by Danny Rios on 3/11/25.
//

#include <vector>
#include <iostream>
#include <stdexcept>
using namespace std;


class InvalidSize: public ::invalid_argument{
    public :
    explicit InvalidSize(const char* message) : invalid_argument(message) {}
};



class StackFull: public runtime_error{
    private: int failedValue;
public:
    StackFull(const char* message, int value) : runtime_error(message), failedValue(value) {}
        
    
    int getValue() const { return failedValue; }
};

class stackEmpty : public runtime_error{
public:
    explicit stackEmpty(const char* message): runtime_error(message) {}
};



class IntStack
{
public:
    // MaxSize should be an unsigned int, but for the sake of example...
    IntStack(int MaxSize){
    
        if (MaxSize < 0){
        
            throw InvalidSize("Cannot create a negative size stack");
        }
        
        data.resize(MaxSize);
        cur_index = 0;
    }
    
    void push(int new_data)
    {
        if (cur_index == data.size())
        {
            throw StackFull("Push to full stack", new_data);
        }
        else
        {
            data.at(cur_index) = new_data;
            cur_index++;
        }
    }


    
    int pop()
    {
        if (cur_index == 0)
        {
            throw stackEmpty("Pop from empty Stack");
        }
        else
        {
            // pop off the int and return it
            cur_index--;
            return data.at(cur_index);
        }
    }

private:
    vector<int> data;
    unsigned int cur_index;
};






int main()
{
    //try catch for constructor
    try{
        IntStack stack(-10);
    }
    catch(const InvalidSize& e){
        cerr<< e.what() << "\n" <<endl ;
    }
    
    
    try{
        // Testing push
        IntStack push_test(5);
        
        for (unsigned int i = 0; i < 7; i++) {
            push_test.push(i);
        }
    }
    catch(const StackFull& e){
        cerr << e.what() << ", Value = " << e.getValue() <<"\n" << endl;
    }
    try{
        // Testing pop
        IntStack pop_test(2);
        
        pop_test.push(1);
        pop_test.push(2);
        pop_test.pop();
        pop_test.pop();
        pop_test.pop();
    }
    catch (const stackEmpty& e) {
        
        cerr <<e.what() <<"\n" << endl;
    }
    cout << "completed!" << "\n"<< endl;
}
