//=============================================================================
// D from
// http://webcache.googleusercontent.com/search?q=cache:3ZVUKlbaWkkJ:www.moythreads.com/wordpress/2007/09/14/overriding-the-virtual-table-in-a-c-object/+&cd=1&hl=en&ct=clnk&gl=uk

#include <string.h>
#include <iostream>

using namespace std;

class Parent
{
    public:
        virtual void VirtFunc1() { cout << "Parent::VirtFunc1" << endl; }

        virtual void VirtFunc2() { cout << "Parent::VirtFunc2" << endl; }
};

class Child : public Parent
{
    public:

        void VirtFunc1() { cout << "Child::VirtFunc1" << endl; }
        void VirtFunc2() { cout << "Child::VirtFunc2" << endl; }
};

typedef void (*virtual_function)();

struct FakeVirtualTable {
    virtual_function virtual_one;

    virtual_function virtual_two;
};

void fake_virtual_one()
{
    cout << "Faked virtual call 1" << endl;
}

void fake_virtual_two()
{
    cout << "Faked virtual call 2" << endl;
}

int main()
{
    /* declare a Child class and a base pointer to it. */
    Child child_class_obj;
    Parent* parent_class_ptr = &child_class_obj;

    /* create our fake virtual table with pointers to our fake methods */
    FakeVirtualTable custom_table;
    custom_table.virtual_one = fake_virtual_one;

    custom_table.virtual_two = fake_virtual_two;

    /* take the address of our stack virtual table and override the real object pointer to the virtual table */
    FakeVirtualTable* table_ptr = &custom_table;

    memcpy(parent_class_ptr, &table_ptr, sizeof(void*));

    /* call the methods ( but we're really calling the faked functions ) */

    parent_class_ptr->VirtFunc1();
    parent_class_ptr->VirtFunc2();

    return 0;
}
