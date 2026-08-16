// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>

//Custom exception used to report a failure in the apps custom business logic
class CustomApplicationException : public std::exception {
private:
	std::string message;

public:
	explicit CustomApplicationException(const std::string& msg) : message(msg) {}
    //returns the error associated with this exception
	const char* what() const noexcept override {
		return message.c_str();
	}
};

bool do_even_more_custom_application_logic()
{
    //throw any standard exception

    std::cout << "Running Even More Custom Application Logic." << std::endl;

	throw std::runtime_error("Even more custom application logic failed!");
	//this cannot be reached after the exception is thrown, but is here to satisfy the compiler
    return true;
}
void do_custom_application_logic()
{
    // Wrap the call to do_even_more_custom_application_logic()
    //  with an exception handler that catches std::exception, displays
    //  a message and the exception.what(), then continues processing
    std::cout << "Running Custom Application Logic." << std::endl;

	//catch exceptions derived from std::exception
    //nested function does not abruptly terminate the program

    try {
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
	}
	catch (const std::exception& e) {
		std::cout << "Caught an exception in do_custom_application_logic: " << e.what() << std::endl;
	}

    // Throw a custom exception derived from std::exception
    //  and catch it explictly in main

	throw CustomApplicationException("Custom Application Logic Failed!");

	//line unreachable, but once again, is here to satisfy the compiler

    std::cout << "Leaving Custom Application Logic." << std::endl;

}

float divide(float num, float den)
{
    //Throw an exception to deal with divide by zero errors using
    //  a standard C++ defined exception

    if (den == 0.0f)
    {
        throw std::invalid_argument("Denominator cannot be zero.");
    }
    return (num / den);
}

void do_division() noexcept
{
    //  create an exception handler to capture ONLY the exception thrown
    //  by divide.

    const float numerator = 10.0f;
    const float denominator = 0;

    // this catches only std::invalid_argument exceptions thrown by divide
    // catching the exception inside this noexcept function is necessary
	// any exception that escapes a noexcept function will call std::terminate() and end the program
    
    try {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
	}
	catch (const std::invalid_argument& e) {
		std::cout << "Caught an exception in do_division: " << e.what() << std::endl;
    }
}

int main()
{
    std::cout << "Exceptions Tests!" << std::endl;

    // Create exception handlers that catch (in this order):
    //  your custom exception
    //  std::exception
    //  uncaught exception 
    //  that wraps the whole main function, and displays a message to the console.


    //catch handlers ordered from most specific to general\
    // customapplicationexception is derived from std::exception, so it must be caught first
    try {
        do_division();
        do_custom_application_logic();
    }
	catch (const CustomApplicationException& e) {
		std::cout << "Caught a CustomApplicationException in main: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "Caught a std::exception in main: " << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Caught an unknown exception in main." << std::endl;
	}

	std::cout << "Program completed successfully." << std::endl;
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu