//=============================================================================
#include "Path.h"
#include <sstream>

#include <UnitCpp.h>

//=============================================================================
TEST(Path, path)
{
  Path path("This is a path");
  TEST_EQUAL(path.path(), "This is a path");
}

//=============================================================================
TEST(Path, extension)
{
  Path path_1("t.txt");
  TEST_EQUAL(path_1.extension(), ".txt");
  
  Path path_2("t.md.txt");
  TEST_EQUAL(path_2.extension(), ".md.txt");

  Path path_3("t.");
  TEST_EQUAL(path_3.extension(), ".");

  Path path_4("t");
  TEST_EQUAL(path_4.extension(), "");

}

//=============================================================================
TEST(Path, exists)
{
  Path non_existant("non existant");
  TEST_FALSE(non_existant.exists());

  Path test_file("data/test.txt");
  TEST_TRUE(test_file.exists());

  Path test_directory("data");
  TEST_TRUE(test_directory.exists());
  
  Path test_nonexistant_directory("data2");
  TEST_FALSE(test_nonexistant_directory.exists());

}

//=============================================================================
TEST(Path, is_directory)
{
  Path non_existant("non existant");
  TEST_FALSE(non_existant.is_directory());

  Path test_file("data/test.txt");
  TEST_FALSE(test_file.is_directory());

  Path test_directory("data");
  TEST_TRUE(test_directory.is_directory());
  
  Path test_nonexistant_directory("data2");
  TEST_FALSE(test_nonexistant_directory.is_directory());
}

//=============================================================================
TEST(Path, is_file)
{
  Path non_existant("non existant");
  TEST_FALSE(non_existant.is_file());

  Path test_file("data/test.txt");
  TEST_TRUE(test_file.is_file());

  Path test_directory("data");
  TEST_FALSE(test_directory.is_file());
  
  Path test_nonexistant_directory("data2");
  TEST_FALSE(test_nonexistant_directory.is_file());
}

//=============================================================================
TEST(Path, copyable)
{
  Path one("test");
  Path two(one);
  TEST_EQUAL(one.path(), two.path());
  Path three = one;
  TEST_EQUAL(one.path(), three.path());
}

//=============================================================================
TEST(Path, moveable)
{
  Path one("test");
  Path two(std::move(one));
  TEST_EQUAL(two.path(), "test");
  Path three = std::move(two);
  TEST_EQUAL(three.path(), "test");
}

//=============================================================================
TEST(Path, swap)
{
  Path one("one");
  Path two("two");
  std::swap(one, two);
  TEST_EQUAL(one.path(), "two");
  TEST_EQUAL(two.path(), "one");
}

//=============================================================================
TEST(Path, equal)
{
  Path one("test");
  Path two("test");
  Path three("t3st");
  TEST_EQUAL(one, one);
  TEST_EQUAL(one, two);
  TEST_EQUAL(two, one);
  TEST_NOT_EQUAL(one, three);
  TEST_NOT_EQUAL(three, one);

}

//=============================================================================
TEST(Path, stream)
{
  std::stringstream ss;
  Path test_path("test");
  ss << test_path;
  TEST_EQUAL(ss.str(), "test");
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
