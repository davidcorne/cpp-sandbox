//=============================================================================
#include "Path.h"
#include <sstream>

#include "UnitTest.h"

using namespace std;

//=============================================================================
class utest_Path : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
    test_path();
    test_extension();
    test_is_file();
    test_is_directory();
    test_exists();
    test_copyable();
    test_equal();
    test_moveable();
    test_swapable();
    test_stream();
  }

private:

  void test_path();

  void test_exists();

  void test_extension();

  void test_is_file();

  void test_is_directory();

  void test_copyable();

  void test_moveable();

  void test_swapable();

  void test_equal();

  void test_stream();

};

//=============================================================================
void utest_Path::test_path()
{
  print(DGC_CURRENT_FUNCTION);
  Path path("This is a path");
  test(path.path() == "This is a path", "Path returned incorrectly.");
}

//=============================================================================
void utest_Path::test_extension()
{
  print(DGC_CURRENT_FUNCTION);
  Path path_1("t.txt");
  test(path_1.extension() == ".txt", "Incorrect extension returned.");
  
  Path path_2("t.md.txt");
  test(path_2.extension() == ".md.txt", "Incorrect extension returned.");

  Path path_3("t.");
  test(path_3.extension() == ".", "Incorrect extension returned.");

  Path path_4("t");
  test(path_4.extension() == "", "Incorrect extension returned.");

}

//=============================================================================
void utest_Path::test_exists()
{
  print(DGC_CURRENT_FUNCTION);
  Path non_existant("non existant");
  test(!non_existant.exists(), "non_existant should not exist");

  Path test_file("data/test.txt");
  test(test_file.exists(), "data/test.txt should exist.");

  Path test_directory("data");
  test(test_directory.exists(), "data should exist.");

  Path test_nonexistant_directory("data2");
  test(!test_nonexistant_directory.exists(), "data2 should not exist.");

}

//=============================================================================
void utest_Path::test_is_directory()
{
  print(DGC_CURRENT_FUNCTION);
  // not implemented yet
}

//=============================================================================
void utest_Path::test_is_file()
{
  print(DGC_CURRENT_FUNCTION);
  // not implemented yet
}

//=============================================================================
void utest_Path::test_copyable()
{
  print(DGC_CURRENT_FUNCTION);
  Path one("test");
  Path two(one);
  test(one.path() == two.path(), "Copy constructor not working.");
  Path three = one;
  test(one.path() == three.path(), "Copy assignment not working.");
}

//=============================================================================
void utest_Path::test_moveable()
{
  print(DGC_CURRENT_FUNCTION);
  Path one("test");
  Path two(std::move(one));
  test(two.path() == "test", "Didn't move one into two.");
  Path three = std::move(two);
  test(three.path() == "test", "Didn't move two into three.");
}

//=============================================================================
void utest_Path::test_swapable()
{
  print(DGC_CURRENT_FUNCTION);
  Path one("one");
  Path two("two");
  std::swap(one, two);
  test(one.path() == "two", "One did not swap.");
  test(two.path() == "one", "Two did not swap.");
}

//=============================================================================
void utest_Path::test_equal()
{
  print(DGC_CURRENT_FUNCTION);
  Path one("test");
  Path two("test");
  Path three("t3st");
  test(one == one, "One should be equal to itself.");
  test(one == two, "One should be equal to two.");
  test(two == one, "Two should be equal to one.");
  test(one != three, "One should not be equal to three.");
  test(three != one, "Three should not be equal to one.");

}

//=============================================================================
void utest_Path::test_stream()
{
  print(DGC_CURRENT_FUNCTION);
  stringstream ss;
  Path test_path("test");
  ss << test_path;
  test(ss.str() == "test", "Correct string output.");
}

//=============================================================================
int main() {
  utest_Path test;
  test.run_tests();
  return 0;
}
