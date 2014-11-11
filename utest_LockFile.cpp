//=============================================================================
//
//D An RAII file locker. On creation, this will lock the file given.
//

#include "Compiler.h"
#include <assert.h>

#include <UnitCpp/Test.h>

#include "LockedFile.h"
#include "LockFileError.h"

//=============================================================================
void write_file(Path path, std::string contents)
{
  std::ofstream file_stream(path.path());
  file_stream << contents;
  file_stream.close();
}

//=============================================================================
TEST(LockedFile, write)
{
  // write a file
  Path path("lock_file.txt");
  write_file(path, "");
  {
    ErrorPtr error;
    LockedFile lock_file(path, error);
    TEST_TRUE(!error);
    std::string new_contents("New file contents\n\nEven multiline.");
    lock_file.write(new_contents);
    std::string whole_file = lock_file.read();
    TEST_EQUAL(whole_file, new_contents, "Write incorrect.");
  }
  // Clean up
  int result = remove(path.path().c_str());
  TEST_EQUAL(result, 0);
}

//=============================================================================
TEST(LockedFile, overwrite)
{
  // write a file
  Path path("lock_file.txt");
  write_file(path, "");
  {
    ErrorPtr error;
    LockedFile lock_file(path, error);
    TEST_TRUE(!error);
    std::string new_contents("New file contents\n\nEven multiline.");
    lock_file.write(new_contents);
    TEST_EQUAL(lock_file.read(), new_contents);
    lock_file.write("");
    TEST_EQUAL(lock_file.read(), std::string(""), "Overwriting file fails.");
  }
  // Clean up
  int result = remove(path.path().c_str());
  TEST_EQUAL(result, 0);
}

//=============================================================================
TEST(LockedFile, multiple_read)
{
#if COMPILER_TYPE != COMPILER_TYPE_VS
  // write a file
  Path path("lock_file.txt");
  std::string contents("File contents\n\nOn multiple lines");
  write_file(path, contents);
  {
    ErrorPtr error;
    LockedFile locked_file(path, error); 
    TEST_TRUE(!error);
    std::string first_read(locked_file.read());
    TEST_EQUAL(first_read, contents);
    std::string second_read(locked_file.read());
    TEST_EQUAL(first_read, second_read, "Read inconsistent.");
  }
  // Clean up
  int result = remove(path.path().c_str());
  TEST_EQUAL(result, 0);
#endif
}

//=============================================================================
TEST(LockedFile, read)
{
#if COMPILER_TYPE != COMPILER_TYPE_VS
  // write a file
  Path path("lock_file.txt");
  std::string contents("File contents\n\nOn multiple lines");
  write_file(path, contents);
  {
    ErrorPtr error;
    LockedFile lock_file(path, error);
    TEST_TRUE(!error);
    TEST_EQUAL(lock_file.read(), contents, "Contents is wrong.");
  }
  // Clean up
  int result = remove(path.path().c_str());
  TEST_EQUAL(result, 0);
#endif
}

//=============================================================================
TEST(LockedFile, lock)
{
  // write a file
  Path path("lock_file.txt");
  write_file(path, "Test file\n");
  int result = 0;
  {
    ErrorPtr error;
    LockedFile lock(path, error);
    TEST_TRUE(!error);
    result = remove(path.path().c_str());
    TEST_NOT_EQUAL(result, 0, "Locked file was deleted.");
  }
  result = remove(path.path().c_str());
  TEST_EQUAL(result, 0, "Unlocked file could not be deleted.");
}

//=============================================================================
TEST(LockedFile, multiple_lock)
{
  // write a file
  Path path("lock_file.txt");
  write_file(path, "Test file\n");
  int result = 0;
  {
    ErrorPtr error;
    LockedFile lock(path, error);
    TEST_TRUE(!error);
    LockedFile second_lock(path, error);
    TEST_TRUE(!!error, "Error expected.");
    Error* err = error.get();
    TEST_TRUE(dynamic_cast<LockFileError*>(err), "Wrong error type.");
  }
  result = remove(path.path().c_str());
  TEST_EQUAL(result, 0, "Unlocked file could not be deleted.");
}

//=============================================================================
int main(int argc, char** argv) 
{
#if DGC_WINDOWS_DEV
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
#else
  return 0;
#endif // DGC_WINDOWS_DEV
}
