//=============================================================================
//
//D An experiment with lambda functions and passing functions into another
//D function.
//

#include <functional>
#include <iostream>
#include <list>
#include <string>

//=============================================================================
template <typename T>
void print_list(const std::list<T>& to_print, const std::string& title)
//
//D Prints the title (if non-empty) then prints each item in the list and a
//D blank line at the end.
//
{
  if (!title.empty()) {
    std::cout << "Printing list: " << title << std::endl;
  }
  for(
    typename std::list<T>::const_iterator iter = to_print.cbegin();
    iter != to_print.cend();
    ++iter
  ) {
    std::cout << *iter << std::endl;
  }
  std::cout << std::endl;
}

//=============================================================================
int ascii_sum(const std::string& in)
//
//D Sums the values of the elements of the string as integers, probably a
//D little dodgy.
//
{
  int sum = 0;
  for (unsigned int i = 0; i < in.length(); ++i) {
    sum += static_cast<int>(in[i]);
  }
  return sum;
}

//=============================================================================
bool ascii_order(const std::string& first, const std::string& second)
//
//D Compare strings by the sums of the values of the elements cast to ints.
//
{
  int first_sum = ascii_sum(first);
  int second_sum = ascii_sum(second);
  return first_sum < second_sum;
}

//=============================================================================
int main()
//
//D Makes a list of doubles, orders then prints the results of the following
//D orderings; minimum value, maximum value, minimum absolute value.
// Then makes a list of strings and 
//
{
  // make a list of strings
  std::list<std::string> strings;
  strings.push_back("aaaaa"); // 5 * ascci value of a is 485
  strings.push_back("zzzz"); // 4 * ascii value of z is 488
  strings.push_back("b");

  // print the original list
  print_list(strings, "original strings");
  
  // sort by minimum length
  std::list<std::string> length_sorted_strings = strings;
  length_sorted_strings.sort(
    [](std::string x, std::string y){return x.length() < y.length();}
  );
  print_list(length_sorted_strings, "strings sorted by length");

  auto ascii_order_function = ascii_order;
  
  std::list<std::string> ascii_sorted_strings = strings;
  ascii_sorted_strings.sort(ascii_order_function);
  print_list(ascii_sorted_strings, "strings sorted by ascii value");

  return 0;
}
