//=============================================================================
//
// 

//=============================================================================
template <typename T>
class LinkedList {
public:

  LinkedList();

  ~LinkedList();

  void append(T i);

  void prepend(T i);

  int size() const;

  const T& operator[](int i) const;
  
private:

  //===========================================================================
  struct Node {
    T data;
    Node* next;
    Node* prev;
  };
  
  Node* last_node() const;
  
  LinkedList& operator=(const LinkedList&);
  LinkedList(LinkedList&);
  // Can't be copied
  
  friend class utest_LinkedList;
  
  Node* m_head;
  int m_size;
};

