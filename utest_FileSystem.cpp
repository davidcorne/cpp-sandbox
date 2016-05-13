//=============================================================================

#include "FileSystem.h"
#include "FileSystem.h"

#include <UnitCpp.h>

//=============================================================================
TEST(FileSystem, temporary_directory)
{
  FileSystem fs;
  Path tmp = fs.temporary_directory();
  TEST_TRUE(tmp.exists());
  TEST_TRUE(tmp.is_directory());
}

//=============================================================================
TEST(FileSystem, empty_directories)
{
  // Create and delete empty directories.
  FileSystem fs;
  bool result = false;
  Path directory("FileSystem_empty_directories");
  TEST_FALSE(directory.exists(), "The directory shouldn't already exist.");
  
  result = fs.create_directory(directory);
  TEST_TRUE(result, "Should have been able to create this directory.");
  TEST_TRUE(directory.exists(), "The directory should now exist.");

  result = fs.delete_directory(directory);
  TEST_TRUE(result, "Should have been able to delete this directory.");
  TEST_FALSE(directory.exists(), "The directory should no longer exist.");
}

//=============================================================================
TEST(FileSystem, list_directories)
{
  // Create and delete empty directories.
  // <nnn> FileSystem fs;
  // <nnn> std::vector<Path> contents = fs.list_contents(Path("data"));
  // <nnn> TEST_EQUAL(contents, std::vector<Path>{Path("test.txt")});
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}
