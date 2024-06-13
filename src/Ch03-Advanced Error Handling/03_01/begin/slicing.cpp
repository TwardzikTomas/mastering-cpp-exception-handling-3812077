#include <stdexcept>
#include <iostream>
#include <string>

// Base exception class
class BaseException : public std::runtime_error
{
public:
    BaseException() : std::runtime_error("BaseException occurred") {}

    virtual const char *what() const noexcept override
    {
        return "Base Exception";
    }
    virtual const std::string test() const
    {
        return std::string("Base class string");
    }
};

// Derived exception class
class DerivedException : public BaseException
{
public:
    DerivedException() : BaseException() {}

    const char *what() const noexcept override
    {
        return "Derived Exception";
    }

    const std::string test() const
    {
        return std::string("Derived class string.");
    }
};

// Function that throws a DerivedException
void triggerException()
{
    throw DerivedException();
}

int main()
{
    try
    {
        triggerException();
    }
    // catch (DerivedException e){
    //     std::cerr << "Caught by value: " << e.what() << std::endl;
    // }

    catch (const BaseException & e)
    { // Catching by value - Slicing occurs here
        std::cerr << "Caught by value: " << e.what() << ", test string: " << e.test() << std::endl;
    }
    return 0;
}
