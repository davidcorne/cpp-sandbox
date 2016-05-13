//=============================================================================

#include "FileSystem.h"
#include "FileSystem.h"

#include <UnitCpp.h>

//=============================================================================
TEST(FileSystem, temporary_directory)
{
  FileSystem fs;
  Path tmp = fs.temporary_directory();
  std::cout << "Temporary directory: " << tmp << std::endl;
  // If it exists, it should be a directory.
  if (tmp.exists()) {
    TEST_TRUE(tmp.is_directory());
  }
}

//=============================================================================
TEST(FileSystem, empty_directories)
{
  // Create and delete empty directories.
  FileSystem fs;
  Path directory("FileSystem_empty_directories");
  TEST_FALSE(directory.exists(), "The directory shouldn't already exist.");
  
  FileSystemError error = fs.create_directory(directory);
  TEST_FALSE(error, "Should have been able to create this directory.");
  TEST_TRUE(directory.exists(), "The directory should now exist.");
  if (error) {
    std::cout << error.message() << std::endl;
  }

  error = fs.delete_directory(directory);
  TEST_FALSE(error, "Should have been able to delete this directory.");
  TEST_FALSE(directory.exists(), "The directory should no longer exist.");
  if (error) {
    std::cout << error.message() << std::endl;
  }
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
