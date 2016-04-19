//=============================================================================
//
// A tree. In this the nodes keep the parent tree alive without the root
// needing to remain in scope.

#include "ObserverPointer.h"

#include <deque>
#include <memory>
#include <iostream>

//=============================================================================
class Node : public std::enable_shared_from_this<Node> {
public:

  static std::shared_ptr<Node> create(int value);
  // Create a new node.

  std::shared_ptr<Node> add_child(int value);
  // Adds a child with given value, then returns it.

  ObserverPtr<const Node> parent() const;
  // Returns the childs parent. If the node is a root, this will be nullptr.

  int value() const;
  // Return the node's value.

  void output(std::ostream& os) const;
  // Output the Node and it's children.
  
  ~Node();
  
private:

  Node(ObserverPtr<const Node> parent, int value);
  // Can't publicly construct a node.

  void output(std::ostream& os, int level) const;
  // Internal output method. This takes into account the recursion level, so
  // that you can indent the output accordingly.
  
  int m_value;
  ObserverPtr<const Node> m_parent;
  std::deque<std::shared_ptr<Node>> m_children;
};

//=============================================================================
int main()
{
  {
    std::shared_ptr<Node> child;
    {
      std::shared_ptr<Node> root = Node::create(0);
      child = root->add_child(1);
    }
    std::ostream& os = std::cout;
    os
      << "Child: "
      << child->value()
      << "\n"
      << "Parent: "
      << child->parent()->value()
      << std::endl;
    child->add_child(2);
    child->add_child(3);
    child->add_child(4);
    child->add_child(5)->add_child(6)->add_child(7);
    auto under = child->add_child(8);
    under->add_child(9);
    under->add_child(10);
    under->add_child(11)->add_child(12);
    child->add_child(13);
    os << "Child:\n";
    child->output(os);
    os << "Parent:\n";
    child->parent()->output(os);
  }
  return 0;
}

//=============================================================================
Node::Node(ObserverPtr<const Node> parent, int value)
  : m_value(value),
    m_parent(parent),
    m_children()
{

}

//=============================================================================
Node::~Node()
{
  std::cout << "Node: " << m_value << " destroyed." << std::endl;
}

//=============================================================================
std::shared_ptr<Node> Node::create(int value)
// Create a new node.
{
  // Can't use std::make_shared, private constructor.
  ObserverPtr<Node> parent = nullptr;
  return std::shared_ptr<Node>(new Node(parent, value));
}

//=============================================================================
std::shared_ptr<Node> Node::add_child(int value)
// Adds a child with given value, then returns it.
{
  std::shared_ptr<Node> self = shared_from_this();
  m_children.push_back(
    std::unique_ptr<Node>(new Node(ObserverPtr<Node>(this), value))
  );
  // Now make shared_ptr that shares the ownership with self. This uses the
  // aliasing constructor.
  std::shared_ptr<Node> child(self, m_children.back().get());
  return child;
}

//=============================================================================
ObserverPtr<const Node> Node::parent() const
// Returns the childs parent. If the node is a root, this will be nullptr.
{
  return m_parent;
}

//=============================================================================
int Node::value() const
// Return the node's value.
{
  return m_value;
}

//=============================================================================
void Node::output(std::ostream& os) const
// Output the Node and it's children.
{
  output(os, 0);
}

//=============================================================================
void Node::output(std::ostream& os, int level) const
// Internal output method. This takes into account the recursion level, so
// that you can indent the output accordingly.
{
  for (int i = 0; i < level; ++i) {
    os << "  ";
  }
  os << m_value << "\n";
  for (const std::shared_ptr<Node>& child : m_children) {
    child->output(os, level + 1);
  }
}
