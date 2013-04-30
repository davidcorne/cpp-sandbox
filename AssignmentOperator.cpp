//
// This comes from.
// http://www.icu-project.org/docs/papers/cpp_report/the_anatomy_of_the_assignment_operator.html
//
// The question is as follows:
// 
// Consider the following class definition:
// 
// class TFoo : public TSuperFoo {
//     TBar* fBar1;
//     TBar* fBar2;
//     // various method definitions go here...
// }
//
// You have a class, TFoo, which descends from a class, TSuperFoo, and which
// has two data members, both of which are pointers to objects of class TBar.
// For the purposes of this exercise, consider both pointers to have owning
// semantics and TBar to be a monomorphic class. Write the assignment operator
// for this class.

class TBar {

};

class TSuperFoo {

};

//=============================================================================
class TFoo : public TSuperFoo {
  TBar* fBar1;
  TBar* fBar2;
public:
  TFoo& operator=(const TFoo&);
};

TFoo& TFoo::operator=(const TFoo& other)
{
  this->TSuperFoo::operator=(other);
  
  // assignment is done on an existing instance, so delete the existing members
  delete fBar1;
  delete fBar2;
  
  fBar1 = new TBar(*other.fBar1);
  fBar2 = new TBar(*other.fBar2);
  
  return *this;
}

int main()
{
  return 0;
}
