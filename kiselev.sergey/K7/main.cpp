#include <functional>
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
struct BiTreeIterator
{
  BiTree< T >* node;

  bool hasPrev() const;
  bool hasNext() const;
  BiTreeIterator< T > next() const;
  BiTreeIterator< T > prev() const;

  const T& data() const;
};

template< typename T >
bool BiTreeIterator< T >::hasPrev() const
{
  BiTree< T >* temp = node;
  if (temp->left)
  {
    return true;
  }
}

template< typename T >
bool BiTreeIterator< T >::hasNext() const
{
  BiTree< T >* temp = node;
  if (temp->right)
  {
    return true;
  }
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
int main()
{}
