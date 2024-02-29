//Delegating Constructors: In C++11 a constructor may call another constructor of the same class:
// Constructor delegation
A(int z) : A()
{
    this->z = z; // Only update z
}
