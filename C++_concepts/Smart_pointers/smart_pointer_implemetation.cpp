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

class SP
{
private:
    Person*    pData; // pointer to person class
public:
    SP(Person* pValue) : pData(pValue)
    {
    }
    ~SP()
    {
        // pointer no longer requried
        delete pData;
    }

    Person& operator* ()
    {
        return *pData;
    }

    Person* operator-> ()
    {    
        return pData;
    }
};


int main()
{
    SP p(new Person("Scott", 25));
    p->Display();
    //delete pPerson;
}