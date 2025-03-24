#ifndef BETREE_HPP
#define BETREE_HPP
#include <functional>

namespace kiselev
{
  template< class T, class Cmp = std::less< T > >
  struct BiTree
  {
    T data;
    Cmp cmp;
    BiTree< T >* left;
    BiTree< T >* right;
    BiTree< T >* parent;
  };
  template< class T >
  std::pair< const BiTree< T >*, BiTree< T >* > findWithParent(const BiTree< T >* root, const T& value);

  template< typename T >
  const BiTree< T >* find(const BiTree< T >* root, const T& value);

  template< class T >
  BiTree< T >* pushTree(BiTree< T >* root, const T& value);

  template< typename T>
  const BiTree< T >* find(const BiTree< T >* root, const T& value)
  {
    return findWithParent(root, value).first;
  }
  template< class T >
  std::pair< const BiTree< T >*, BiTree< T >* > findWithParent(const BiTree< T >* root, const T& value)
  {
    BiTree< T >* parent = nullptr;
    while (root)
    {
      parent = const_cast< BiTree< T >* >(root);
      if (cmp(root->data, value))
      {
        root = root->right;
      }
      else if (cmp(value, root->data))
      {
        root = root->left;
      }
      else
      {
        return { root, parent };
      }
    }
    return { nullptr, parent };
  }

  template< class T, class Cmp >
  BiTree< T >* pushTree(BiTree< T >* root, const T& value, Cmp cmp)
  {
    if (!root)
    {
      root = new BiTree< T >{value, nullptr, nullptr };
    }
    BiTree< T >* temp = root;
    BiTree< T >* parentTemp = findWithParent(temp, value, cmp).second;
    if (cmp(value, parentTemp->data))
    {
      parentTemp->left = new BiTree< T >{ value, nullptr, nullptr };
    }
    else
    {
      parentTemp->right = new BiTree< T >{ value, nullptr, nullptr };
    }
    return root;
  }
  template< typename T >
  void deleteTree(BiTree< T >* root)
  {
    if (!root)
    {
      return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
  }
}
#endif
