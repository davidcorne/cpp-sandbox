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
list<T> sort(function<bool(const T&, const T&)> order, const list<T>& in)
//
//D Sorts a list using the function order such that if order returns true then
//D the first value is "lower" in the order than the second, i.e it has a lower
//D index in the sorted list.
//
{
  list<T> sorted;
  // for each element in the input list, loop over the sorted list and when you
  // get to an element it is "smaller" than place it immediately before it.
  for (auto iter = in.cbegin(); iter != in.cend(); ++iter) {
    bool added = false;
    for (
      auto inner_iter = sorted.begin();
      inner_iter != sorted.end();
      ++inner_iter
    ) {
      if (order(*iter, *inner_iter)) {
        sorted.insert(inner_iter, *iter);
        added = true;
        break;
      }
    }
    // if you get to the end without adding, it's "larger" than the rest of the
    // list so add it to the end.
    if (!added) {
      sorted.push_back(*iter);
    }
  }
  return sorted;
}

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
int main()
//
//D Makes a list of doubles, orders then prints the results of the following
//D orderings; minimum value, maximum value, minimum absolute value.
// Then makes a list of strings and 
//
{
  list<double> random_list;
  random_list.push_back(5.0);
  random_list.push_back(-4.0);
  random_list.push_back(8.0);
  random_list.push_back(3.0);
  random_list.push_back(-4.5);
  random_list.push_back(6.0);

  // print the original list
  print_list<double>(random_list, "original doubles");
  
  // sort by minimum first
  list<double> min_sorted = sort<double>(
    [](double x, double y){return x < y;},
    random_list
  );
  print_list<double>(min_sorted, "doubles sorted by minimum");

  // sort by maximum first
  list<double> max_sorted = sort<double>(
    [](double x, double y){return x > y;},
    random_list
  );
  print_list<double>(max_sorted, "doubles sorted by maximum");

  // sort by absolue minimum
  list<double> abs_min_sorted = sort<double>(
    [](double x, double y){return fabs(x) < fabs(y);},
    random_list
  );
  print_list<double>(
    abs_min_sorted,
    "doubles sorted by minimum absolute value"
  );

  // make a list of strings
  list<string> strings;
  strings.push_back("aaaaaaaaaaaa");
  strings.push_back("see");
  strings.push_back("b");

  // print the original list
  print_list<string>(strings, "original strings");
  
  // sort by minimum length
  list<string> length_sorted_strings = sort<string>(
    [](string x, string y){return x.length() < y.length();},
    strings
  );
  print_list<string>(length_sorted_strings, "strings sorted by length");

  return 0;
}
