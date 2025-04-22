#ifndef TRITREE_HPP
#define TRITREE_HPP
#include <functional>
#include <stdexcept>
#include "triTreeIterator.hpp"

namespace kiselev
{
  template< class T >
  struct TreeNode
  {
    std::pair< T, T > data;
    TreeNode< T >* left;
    TreeNode< T >* middle;
    TreeNode< T >* right;
    TreeNode< T >* parent;

    TreeNode(const std::pair< T, T >& d, TreeNode< T >* p = nullptr):
      data(d.first < d.second ? d : std::pair< T, T >(d.second, d.first)),
      left(nullptr),
      middle(nullptr),
      right(nullptr),
      parent(p)
    {
      if (data.first == data.second)
      {
        throw std::invalid_argument("Incorrect pair");
      }
    }
  };

  template< class T, class Cmp = std::less< T > >
  struct TriTree
  {
    using Iterator = TriTreeIterator< T >;
    using Node = TreeNode< T >;

    TriTree() = default;
    ~TriTree();
    std::pair< TriTreeIterator< T >, bool > insert(std::pair< T, T >);
    void clear() noexcept;
    void clear(Node* root) noexcept;
    TriTreeIterator< T > begin() const noexcept;
    TriTreeIterator< T > rbegin() const noexcept;
    TriTreeIterator< T > end() const noexcept;

    Node* root;
    Cmp cmp;
  };

  template< class T, class Cmp >
  TriTree< T, Cmp >::~TriTree()
  {
    clear();
  }

  template< class T, class Cmp >
  void TriTree< T, Cmp >::clear() noexcept
  {
    clear(root);
  }
  template< class T, class Cmp >
  void TriTree< T, Cmp >::clear(Node* root) noexcept
  {
    if (!root)
    {
      return;
    }
    clear(root->left);
    clear(root->middle);
    clear(root->right);
    delete root;
  }

  template< class T, class Cmp >
  std::pair< TriTreeIterator< T >, bool > TriTree< T, Cmp >::insert(std::pair< T, T > value)
  {
    if (!root)
    {
      root = new Node(value);
      return std::make_pair(Iterator(root), true );
    }
    Node* temp = root;
    Node* parent = nullptr;
    while (temp)
    {
      parent = temp;
      if (cmp(value.first, temp->data.first))
      {
        temp = temp->left;
      }
      else if (!cmp(temp->data.first, value.first) && cmp(value.second, temp->data.second))
      {
        temp = temp->middle;
      }
      else if (cmp(temp->data.second, value.second))
      {
        temp = temp->right;
      }
      else
      {
        return std::make_pair(Iterator(temp), false );
      }
    }
    Node* newNode = new Node(value, parent);
    if (cmp(newNode->data.first, parent->data.first))
    {
      parent->left = newNode;
    }
    else if (cmp(parent->data.first, newNode->data.first) && cmp(newNode->data.second, parent->data.second))
    {
      parent->middle = newNode;
    }
    else
    {
      parent->right = newNode;
    }
    return std::make_pair(Iterator(newNode), true);
  }

  template< class T, class Cmp >
  TriTreeIterator< T > TriTree< T, Cmp >::begin() const noexcept
  {
    return Iterator(min(root));
  }

  template< class T, class Cmp >
  TriTreeIterator< T > TriTree< T, Cmp >::rbegin() const noexcept
  {
    return Iterator(max(root));
  }

  template< class T, class Cmp >
  TriTreeIterator< T > TriTree< T, Cmp >::end() const noexcept
  {
    return Iterator(nullptr);
  }
}
#endif
