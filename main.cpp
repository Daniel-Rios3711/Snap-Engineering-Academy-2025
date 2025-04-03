//
//  main.cpp
//  Exceptions_Video_Work_#2-Daniel Rios
//
//  Created by Danny Rios on 3/2/25.
//
// THIS CODE HERE IS FROM THE SECOND VIDEO ON EXCEPTIONS
#include <iostream>
#include <stdexcept>
using namespace std;

class DividebyZero: public  runtime_error  // a class is crated inheriting runtime_error in order to show                                              more details about error
{
public:
    DividebyZero(int numerator, const char* s)
    : m_numerator(numerator), runtime_error(s)
    {}
    int getNumerator() const { return m_numerator;}
private:
    int m_numerator;
   
};

int main() {
    try{
        int a = 2, b = 0;
        if(b == 0) {
            throw DividebyZero(a,"divde by zero");
            cout << a/b;
        }
    }
    catch(DividebyZero& e){
        cout << "Main: DivideByZero caught " << endl;
        cout << "message: " <<e.what() << endl;
        cout << "numerator: " << e.getNumerator() << endl;
    }
    catch(runtime_error& e){
        cout << "Main: runtime error caught " << endl;
        cout << "message: " <<e.what() << endl;
   
    }
}
