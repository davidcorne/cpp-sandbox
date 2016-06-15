//=============================================================================
// The idea here is a class with a std::list like interface, but backed by
// a contiguous array.

#ifndef List_H
#define List_H

#include "IsIterator.h"

#include <iterator>
#include <initializer_list>
#include <type_traits>

#include <cassert>

//=============================================================================
template <typename tCONTAINS>
class List {
private:

  //===========================================================================
  struct Node {
    tCONTAINS value;
    Node* previous;
    Node* next;
  };
  
  //===========================================================================
  template <typename tDERIVED_ITERATOR, typename tNODE_TYPE>
  class NodeIteratorBase {
  public:
    using difference_type = std::ptrdiff_t;
    using value_type = decltype(std::remove_pointer<tNODE_TYPE>::type::value);
    using pointer = value_type*;
    using reference = value_type&;
    using iterator_category = std::bidirectional_iterator_tag;

    NodeIteratorBase(tNODE_TYPE node);
    
    NodeIteratorBase(const NodeIteratorBase&);
    NodeIteratorBase& operator=(const NodeIteratorBase&);

    // iterator interface
    tDERIVED_ITERATOR& operator++();
    tDERIVED_ITERATOR& operator--();
    tDERIVED_ITERATOR operator++(int);
    tDERIVED_ITERATOR operator--(int);
   
    bool operator==(const tDERIVED_ITERATOR& a_it) const;
    bool operator!=(const tDERIVED_ITERATOR& a_it) const;
    
    tNODE_TYPE node() const;
    // Note, I would prefer this private and List being a friend. However
    // VS implementation comes up with "error C3855: 'List': template
    // parameter 'tCONTAINS' is incompatible with the declaration".
    
  protected:

    tNODE_TYPE m_current;

  private:

    virtual void increment() = 0;
    virtual void decrement() = 0;
  };
  
  //===========================================================================
  template <typename tDERIVED_ITERATOR>
  class NodeIteratorConst :
    public NodeIteratorBase<tDERIVED_ITERATOR, const Node*> {
  public:
    
    NodeIteratorConst(const Node*);
    
    const tCONTAINS& operator*();
    
    const tCONTAINS* operator->();
  
  };
  
  //===========================================================================
  class ForwardNodeIteratorConst :
    public NodeIteratorConst<ForwardNodeIteratorConst> {
  public:

    ForwardNodeIteratorConst(const Node*);
    
  private:
    
    using NodeIteratorConst<ForwardNodeIteratorConst>::m_current;

    virtual void increment() override;
    virtual void decrement() override;
  };
  
  //===========================================================================
  class BackwardNodeIteratorConst :
    public NodeIteratorConst<BackwardNodeIteratorConst> {
  public:

    BackwardNodeIteratorConst(const Node*);
    
  private:
    
    using NodeIteratorConst<BackwardNodeIteratorConst>::m_current;

    virtual void increment() override;
    virtual void decrement() override;
  };
  
  //===========================================================================
  template <typename tDERIVED_ITERATOR>
  class NodeIterator : public NodeIteratorBase<tDERIVED_ITERATOR, Node*> {
  public:
    
    NodeIterator(Node*);
    
    tCONTAINS& operator*();
    
    tCONTAINS* operator->();
    
  protected:
    
    using NodeIteratorBase<tDERIVED_ITERATOR, Node*>::m_current;
  };

  //===========================================================================
  class ForwardNodeIterator : public NodeIterator<ForwardNodeIterator> {
  public:

    ForwardNodeIterator(Node*);
    
    operator ForwardNodeIteratorConst() const;
    
  private:
    
    using NodeIterator<ForwardNodeIterator>::m_current;
    
    virtual void increment() override;
    virtual void decrement() override;
  };
  
  //===========================================================================
  class BackwardNodeIterator : public NodeIterator<BackwardNodeIterator> {
  public:

    BackwardNodeIterator(Node*);
    
    operator BackwardNodeIteratorConst() const;

  private:
    
    using NodeIterator<BackwardNodeIterator>::m_current;
    
    virtual void increment() override;
    virtual void decrement() override;
  };
  
  Node m_sentinel;

public:

  using value_type = tCONTAINS;
  using allocator_type = std::allocator<tCONTAINS>;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = typename allocator_type::reference;
  using const_reference = typename allocator_type::const_reference;
  using pointer = typename allocator_type::pointer;
  using const_pointer = typename allocator_type::const_pointer;
  using iterator = ForwardNodeIterator;
  using const_iterator = ForwardNodeIteratorConst;
  using reverse_iterator = BackwardNodeIterator;
  using const_reverse_iterator = BackwardNodeIteratorConst;
  
  //----- Constructors
  List();
  
  List(std::initializer_list<tCONTAINS>);

  List(const List<tCONTAINS>& list);

  List& operator=(const List<tCONTAINS>& list);

  // <nnn> List(const List<tCONTAINS>&& list);

  // <nnn> List& operator=(const List<tCONTAINS>&& list);

  ~List();
  
  //----- Iterators
  iterator begin();
  const_iterator cbegin() const;
  const_iterator begin() const;

  iterator end();
  const_iterator end() const;
  const_iterator cend() const;

  reverse_iterator rbegin();
  reverse_iterator rend();
  
  const_reverse_iterator rbegin() const;
  const_reverse_iterator rend() const;
  
  const_reverse_iterator crbegin() const;
  const_reverse_iterator crend() const;
  
  //----- Capacity
  size_type size() const;

  bool empty() const;

  size_type max_size() const;

  //----- Accessors
  reference front();
  const_reference front() const;
  
  reference back();
  const_reference back() const;
  
  //----- Modifiers
  void clear();

  iterator insert(const_iterator position, const tCONTAINS& value);

  iterator erase(const_iterator position);
  // position must be valid and dereferenceable i.e. can't be end()

  void assign(size_type size, const value_type& value);

  template <typename tINPUT_ITERATOR>
  typename std::enable_if<IsIterator<tINPUT_ITERATOR>::value, void>::type
    assign(tINPUT_ITERATOR first, tINPUT_ITERATOR last);

  void swap(List<tCONTAINS>& list);

  void resize(size_type size, value_type value=value_type());
  
  void push_back(const tCONTAINS& value);

  void push_front(const tCONTAINS& value);

  void pop_back();

  void pop_front();

  //----- Operations
  void splice(iterator position, List<tCONTAINS>& list);

  void remove(const value_type& value);

  template <typename tPREDICATE>
  void remove_if(tPREDICATE predicate);

  void unique();

  void merge(List<tCONTAINS>& list);

  template <typename tCOMPARATOR>
  void merge(List<tCONTAINS>& list, tCOMPARATOR comparator);

  void sort();

  template <typename tCOMPARATOR>
  void sort(tCOMPARATOR comparator);

  void reverse();
  
private:

  
  iterator erase(Node* node);
  
};

//----- Non-member functions
template <typename tCONTAINS>
typename List<tCONTAINS>::iterator begin(List<tCONTAINS>&);

template <typename tCONTAINS>
typename List<tCONTAINS>::const_iterator begin(const List<tCONTAINS>&);

template <typename tCONTAINS>
typename List<tCONTAINS>::iterator end(List<tCONTAINS>&);

template <typename tCONTAINS>
typename List<tCONTAINS>::const_iterator end(const List<tCONTAINS>&);

template <typename tCONTAINS>
bool operator==(const List<tCONTAINS>&, const List<tCONTAINS>&);

template <typename tCONTAINS>
bool operator!=(const List<tCONTAINS>&, const List<tCONTAINS>&);

//----- Source
#include "List_tsource.h"
#include "List_iterator_tsource.h"

#endif
