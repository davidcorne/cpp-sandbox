#include <algorithm>
#include <iostream>
#include <vector>

int main() 
{
   // Create a vector object that contains 10 elements.
   std::vector<int> v;
   for (int i = 0; i < 10; ++i) {
      v.push_back(i);
   }

   // Count the number of even numbers in the vector by 
   // using the for_each function and a lambda.
   int evenCount = 0;
   std::for_each(v.begin(), v.end(), [&evenCount] (int n) {
      std::cout << n;

      if (n % 2 == 0) {
         std::cout << " is even " << std::endl;
         ++evenCount;
      } else {
         std::cout << " is odd " << std::endl;
      }
   });

   // Print the count of even numbers to the console.
   std::cout << "There are " << evenCount 
        << " even numbers in the vector." << std::endl;
}
