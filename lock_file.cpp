//=============================================================================
//
//D An RAII file locker. On creation, this will lock the file given.
//

#include "UnitTest.h"
#include "LockedFile.h"

//=============================================================================
class utest_lock_file : public UnitTest {
public:

  void run_tests() {
    print(__FILE__);
#ifdef DGC_WINDOWS_DEV
    test_lock();
    test_multiple_lock();
    test_read();
    test_write();
    test_multiple_read();
    test_overwrite();
#endif
  }

private:

  void test_lock();
  void test_multiple_lock();
  void test_read();
  void test_write();
  void test_multiple_read();
  void test_overwrite();
  void write_file(Path path, std::string contents)
    {
      std::ofstream file_stream(path.path());
      file_stream << contents;
      file_stream.close();
    }

};

//=============================================================================
void utest_lock_file::test_write()
{
  print(DGC_CURRENT_FUNCTION);
  // write a file
  Path path("lock_file.txt");
  write_file(path, "");
  {
    ErrorPtr error;
    LockedFile lock_file(path, error);
    assert(!error);
    std::string new_contents("New file contents\n\nEven multiline.");
    lock_file.write(new_contents);
    std::string whole_file = lock_file.read();
    test(whole_file == new_contents, "Write incorrect.");
  }
  // Clean up
  int result = remove(path.path().c_str());
  assert(result == 0);
}

//=============================================================================
void utest_lock_file::test_overwrite()
{
  print(DGC_CURRENT_FUNCTION);
  // write a file
  Path path("lock_file.txt");
  write_file(path, "");
  {
    ErrorPtr error;
    LockedFile lock_file(path, error);
    assert(!error);
    std::string new_contents("New file contents\n\nEven multiline.");
    lock_file.write(new_contents);
    assert(lock_file.read() == new_contents);
    lock_file.write("");
    test(lock_file.read() == std::string(""), "Overwriting file fails.");
  }
  // Clean up
  int result = remove(path.path().c_str());
  assert(result == 0);
}

//=============================================================================
void utest_lock_file::test_multiple_read()
{
  print(DGC_CURRENT_FUNCTION);
  // write a file
  Path path("lock_file.txt");
  std::string contents("File contents\n\nOn multiple lines");
  write_file(path, contents);
  {
    ErrorPtr error;
    LockedFile locked_file(path, error); 
    assert(!error);
    std::string first_read(locked_file.read());
    assert(first_read == contents);
    std::string second_read(locked_file.read());
    test(first_read == second_read, "Read inconsistent.");
  }
  // Clean up
  int result = remove(path.path().c_str());
  assert(result == 0);
}

//=============================================================================
void utest_lock_file::test_read()
{
  print(DGC_CURRENT_FUNCTION);
  // write a file
  Path path("lock_file.txt");
  std::string contents("File contents\n\nOn multiple lines");
  write_file(path, contents);
  {
    ErrorPtr error;
    LockedFile lock_file(path, error);
    assert(!error);
    test(lock_file.read() == contents, "Contents is wrong.");
  }
  // Clean up
  int result = remove(path.path().c_str());
  assert(result == 0);
}

//=============================================================================
void utest_lock_file::test_lock()
{
  print(DGC_CURRENT_FUNCTION);
  // write a file
  Path path("lock_file.txt");
  write_file(path, "Test file\n");
  int result = 0;
  {
    ErrorPtr error;
    LockedFile lock(path, error);
    assert(!error);
    result = remove(path.path().c_str());
    test(result != 0, "Locked file was deleted.");
  }
  result = remove(path.path().c_str());
  test(result == 0, "Unlocked file could not be deleted.");
}

//=============================================================================
void utest_lock_file::test_multiple_lock()
{
  print(DGC_CURRENT_FUNCTION);
  // write a file
  Path path("lock_file.txt");
  write_file(path, "Test file\n");
  int result = 0;
  {
    ErrorPtr error;
    LockedFile lock(path, error);
    assert(!error);
    LockedFile second_lock(path, error);
    test(!!error, "Error expected.");
    Error* err = error.get();
    test(dynamic_cast<LockFileError*>(err), "Wrong error type.");
  }
  result = remove(path.path().c_str());
  test(result == 0, "Unlocked file could not be deleted.");
}

//=============================================================================
int main() {
  utest_lock_file test;
  test.run_tests();
  return 0;
}
