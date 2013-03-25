//=============================================================================
//
//D An experiment with lambda functions and passing functions into another
//D function.
//

#include <functional>
#include <iostream>
#include <list>
#include <math.h>
#include <string>

using std::cout;
using std::endl;
using std::function;
using std::list;
using std::string;

//=============================================================================
template <typename T>
void print_list(const list<T>& to_print, const string& title)
//
//D Prints the title (if non-empty) then prints each item in the list and a
//D blank line at the end.
//
{
  if (!title.empty()) {
    cout << "Printing list: " << title << endl;
  }
  for(
    list<T>::const_iterator iter = to_print.cbegin();
    iter != to_print.cend();
    ++iter
  ) {
    cout << *iter << endl;
  }
  cout << endl;
}

//=============================================================================
int ascii_sum(const string& in)
//
//D Sums the values of the elements of the string as integers, probably a
//D little dodgy.
//
{
  int sum = 0;
  for (int i = 0; i < in.length(); ++i) {
    sum += static_cast<int>(in[i]);
  }
  return sum;
}

//=============================================================================
bool ascii_order(const string& first, const string& second)
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
  list<string> strings;
  strings.push_back("aaaaa"); // 5 * ascci value of a is 485
  strings.push_back("zzzz"); // 4 * ascii value of z is 488
  strings.push_back("b");

  // print the original list
  print_list<string>(strings, "original strings");
  
  // sort by minimum length
  list<string> length_sorted_strings = strings;
  length_sorted_strings.sort(
    [](string x, string y){return x.length() < y.length();}
  );
  print_list<string>(length_sorted_strings, "strings sorted by length");

  auto ascii_order_function = ascii_order;
  
  list<string> ascii_sorted_strings = strings;
  ascii_sorted_strings.sort(ascii_order);
  print_list<string>(ascii_sorted_strings, "strings sorted by ascii value");

  return 0;
}
