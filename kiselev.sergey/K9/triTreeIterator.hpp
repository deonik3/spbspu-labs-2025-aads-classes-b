#ifndef TRITREEITERATOR_HPP
#define TRITREEITERATOR_HPP
#include <functional>
#include <ostream>
#include <utility>

namespace kiselev
{
  template< class T >
  struct TreeNode;
  template< typename T, class Cmp = std::less< T > >
  struct TriTreeIterator
  {
    using this_t = TriTreeIterator< T >;
    using Node = TreeNode< T >;
    TriTreeIterator() = default;
    TriTreeIterator(Node* nod):
      node(nod)
    {}
    bool hasNext() const;
    bool hasPrev() const;

    this_t prev() const;
    this_t next() const;

    std::pair< T, T > & data();

    Node* node;
  };

  template< class T >
  std::ostream& operator<<(std::ostream& output, TriTreeIterator< T >& it)
  {
    std::ostream::sentry sentry(output);
    if (!sentry)
    {
      return output;
    }
    std::pair< T, T >& pair = it.data();
    return output << pair.first << pair.second;
  }

  template< class T >
  TreeNode< T >* max(TreeNode< T >* node)
  {
    while (node->right || node->middle)
    {
      node = (node->right ? node->right : node->middle);
    }
    return node;
  }

  template< class T >
  TreeNode< T >* min(TreeNode< T >* node)
  {
    while (node->left)
    {
      node = node->left;
    }
    return node;
  }

  template< class T, class Cmp >
  bool TriTreeIterator< T, Cmp >::hasNext() const
  {
    if (!node)
    {
      return false;
    }
    if (node->right || node->middle)
    {
      return true;
    }
    Node* temp = node;
    Node* parent = node->parent;
    while (parent)
    {
      if (parent->left == temp && (parent->middle || parent->right))
      {
        return true;
      }
      if (parent->middle == temp && parent->right)
      {
        return true;
      }
      temp = parent;
      parent = parent->parent;
    }
    return !node ? false : true;
  }

  template< class T, class Cmp >
  bool TriTreeIterator< T, Cmp >::hasPrev() const
  {
    if (!node)
    {
      return false;
    }
    if (node->left || node->middle)
    {
      return true;
    }
    Node* temp = node;
    Node* parent = node->parent;
    while (parent)
    {
      if (parent->right == temp && (parent->middle || parent->left))
      {
        return true;
      }
      if (parent->middle == temp && parent->left)
      {
        return true;
      }
      temp = parent;
      parent = parent->parent;
    }
    return false;
  }

  template< class T, class Cmp >
  TriTreeIterator< T > TriTreeIterator< T, Cmp >::next() const
  {
    if (node->middle)
    {
      Node* temp = node->middle;
      return this_t(min(temp));
    }
    if (node->right)
    {
      Node* temp = node->right;
      return this_t(min(temp));
    }
    Node* temp = node;
    Node* parent = node->parent;
    while (parent)
    {
      if (parent->left == temp)
      {
        if (parent->middle)
        {
          Node* temp2 = parent->middle;
          return this_t(min(temp2));
        }
        return this_t{ parent };
      }
      if (parent->middle == temp)
      {
        return this_t(parent);
      }
      temp = parent;
      parent = parent->parent;
    }
    return this_t(nullptr);
  }

  template< class T, class Cmp >
  TriTreeIterator< T > TriTreeIterator< T, Cmp >::prev() const
  {
    if (node->left)
    {
      Node* temp = node->left;
      return this_t(max(temp));
    }
    if (node->middle)
    {
      Node* temp = node->middle;
      return this_t(max(temp));
    }
    Node* temp = node;
    Node* parent = node->parent;
    while (parent)
    {
      if (parent->right == temp)
      {
        if (parent->middle)
        {
          Node* temp2 = parent->middle;
          return this_t(max(temp2));
        }
        return parent;
      }
      if (parent->middle == temp)
      {
        return this_t(parent);
      }
      temp = parent;
      parent = parent->parent;
    }
    return this_t(nullptr);
  }

  template< class T, class Cmp >
  std::pair< T, T >& TriTreeIterator< T, Cmp >::data()
  {
    return node->data;
  }
}
#endif
