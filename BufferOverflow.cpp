// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>
//Included limits to use std::numeric_limits
#include <limits>

int main()
{
  std::cout << "Buffer Overflow Example" << std::endl;



  const std::string account_number = "CharlieBrown42";
  char user_input[20] = {};
  std::cout << "Enter a value: ";

  /*
  * getline() will receive the size of the destination buffer
  * it will store no more than 19 user-entered characters in the user_input buffer
  * because the final array element is reserved for the null terminator
  */
  std::cin.getline(user_input, sizeof(user_input));

  /*
  * Now, if user enters more chars than the buffer can hold,
  * getline() sets the streams fail state instead of just writing past the end of the array
  */

  if (std::cin.fail() && !std::cin.eof()) {
	  std::cout << "Error: The entered value is too long." << std::endl;
	  std::cout << "The maximum allowed length is " << sizeof(user_input) - 1 << " characters." << std::endl;
	  //reset the input and remove remaining chars
	  std::cin.clear();
	  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  else {
	  std::cout << "You entered: " << user_input << std::endl;
  }

  //std::cin >> user_input; a problem with this, is that it is unbounded, allowing the user to enter more characters than the buffer can hold, 
  //which can lead to a buffer overflow vulnerability.

  std::cout << "Account Number = " << account_number << std::endl;

  return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
