#include<iostream>
using namespace std;

class Person
{
    int age;
    char* pName;

    public:
        Person(): pName(0),age(0)
        {
        }
        Person(char* pName, int age): pName(pName), age(age)
        {
        }
        ~Person()
        {
			cout<<"destructor is called";
        }
        void Display()
        {
            cout<<"Name ="<<pName<<"\n"<<"Age ="<<age<<"\n";
        }
       
};

template<typename T>
class SP
{
private:
    T*    pData; // pointer to person class
public:
    SP(T* pValue) : pData(pValue)
    {
    }
    ~SP()
    {
        // pointer no longer requried
        delete pData;
    }

    T& operator* ()
    {
        return *pData;
    }

    T* operator-> ()
    {    
        return pData;
    }
};


int main()
{
    SP<Person>p(new Person(const_cast<char*>("Scott"), 25));
    //SP p(new Person(const_cast<char*>("Scott"), 25));
    p->Display();
    //delete pPerson;
}
