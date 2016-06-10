//=============================================================================
// The idea here is a class with a std::list like interface, but backed by
// a contiguous array.

#ifndef ArrayList_H
#define ArrayList_H

#include <algorithm>
#include <initializer_list>
#include <type_traits>
#include <vector>

#include <cassert>

//=============================================================================
template <typename tCONTAINS>
class ArrayList {
private:

  //===========================================================================
  struct Node {
    tCONTAINS value;
    Node* previous;
    Node* next;
    bool operator==(const Node&) const;
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

    NodeIteratorBase();
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
    // Note, I would prefer this private and ArrayList being a friend. However
    // VS implementation comes up with "error C3855: 'ArrayList': template
    // parameter 'tCONTAINS' is incompatible with the declaration".
    
  protected:

    tNODE_TYPE m_current;
  };
  
  //===========================================================================
  class NodeIteratorConst :
    public NodeIteratorBase<NodeIteratorConst, const Node*> {
  public:
    
    NodeIteratorConst();
    
    NodeIteratorConst(const Node*);
    
    const tCONTAINS& operator*();
    
    const tCONTAINS* operator->();
  
  };
  
  //===========================================================================
  class NodeIterator : public NodeIteratorBase<NodeIterator, Node*> {
  public:
    
    NodeIterator();
    
    NodeIterator(Node*);
    
    operator NodeIteratorConst() const;
    
    tCONTAINS& operator*();
    
    tCONTAINS* operator->();
    
    using NodeIteratorBase<NodeIterator, Node*>::m_current;
  };

  std::vector<Node> m_storage;

public:

  using value_type = tCONTAINS;
  using allocator_type = std::allocator<tCONTAINS>;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = typename allocator_type::reference;
  using const_reference = typename allocator_type::const_reference;
  using pointer = typename allocator_type::pointer;
  using const_pointer = typename allocator_type::const_pointer;
  using iterator = NodeIterator;
  using const_iterator = NodeIteratorConst;
  using reverse_iterator = NodeIterator; // <nnn> 
  using const_reverse_iterator = NodeIteratorConst; // <nnn>
  
  //----- Constructors
  ArrayList();
  
  ArrayList(std::initializer_list<tCONTAINS>);

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

  template <typename tINPUT_ITERATOR>
  void assign(tINPUT_ITERATOR first, tINPUT_ITERATOR last);

  void assign(size_type size, value_type value);

  void swap(ArrayList<tCONTAINS>& list);

  void resize(size_type size, value_type value=value_type());
  
  void push_back(const tCONTAINS& value);

  void push_front(const tCONTAINS& value);

  void pop_back();

  void pop_front();

  //----- Operations
  void splice(iterator position, ArrayList<tCONTAINS>& list);

  void remove(const value_type& value);

  template <typename tPREDICATE>
  void remove_if(tPREDICATE predicate);

  void unique();

  void merge(ArrayList<tCONTAINS>& list);

  void sort();

  template <typename tCOMPARATOR>
  void sort(tCOMPARATOR comparator);

  void reverse();

private:

  typename std::vector<Node>::iterator find(const_iterator it);
  typename std::vector<Node>::const_iterator find(const_iterator it) const;
  
  size_type front_node_index() const;
  size_type back_node_index() const;

};

//----- Non-member functions
template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::iterator begin(ArrayList<tCONTAINS>&);

template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::const_iterator begin(const ArrayList<tCONTAINS>&);

template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::iterator end(ArrayList<tCONTAINS>&);

template <typename tCONTAINS>
typename ArrayList<tCONTAINS>::const_iterator end(const ArrayList<tCONTAINS>&);

template <typename tCONTAINS>
bool operator==(const ArrayList<tCONTAINS>&, const ArrayList<tCONTAINS>&);

template <typename tCONTAINS>
bool operator!=(const ArrayList<tCONTAINS>&, const ArrayList<tCONTAINS>&);

//----- Source
#include "ArrayList_tsource.h"
#include "ArrayList_non_member_tsource.h"
#include "ArrayList_iterator_tsource.h"



#endif
