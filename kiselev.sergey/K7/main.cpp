#include <functional>
#include <ostream>
#include <stdexcept>
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
  if (!node)
  {
    return false;
  }
  BiTree< T >* temp = node;
  if (temp->left)
  {
    return true;
  }
  while (temp->parent && temp == temp->parent->left)
  {
    temp = temp->parent;
  }
  return !temp->parent;
}

template< typename T >
bool BiTreeIterator< T >::hasNext() const
{
  if (!node)
  {
    return false;
  }
  BiTree< T >* temp = node;
  if (temp->right)
  {
    return true;
  }
  while (temp->parent && temp->parent->right)
  {
    temp = temp->parent;
  }
  return !temp->parent;
}

template< typename T >
BiTreeIterator< T > BiTreeIterator< T >::next() const
{
  if (!hasNext())
  {
    throw std::logic_error("No next");
  }
  BiTree< T >* temp = node;
  if (temp->right)
  {
    temp = temp->right;
    while (temp->left)
    {
      temp = temp->left;
    }
    return BiTreeIterator< T >{ temp };
  }
  while (temp->parent && temp == temp->parent->right)
  {
    temp = temp->parent;
  }
  return BiTreeIterator< T >{ temp->parent };
}

template< typename T >
BiTreeIterator< T > BiTreeIterator< T >::prev() const
{
  if (!hasPrev())
  {
    throw std::logic_error("No prev");
  }
  BiTree< T >* temp = node;
  if (temp->left)
  {
    temp = temp->left;
    while (temp->right)
    {
      temp = temp->right;
    }
    return BiTreeIterator< T >{ temp };
  }
  while (temp->parent && temp == temp->parent->left)
  {
    temp = temp->parent;
  }
  return BiTreeIterator< T >{ temp };
}

template< typename T >
const T& BiTreeIterator< T >::data() const
{
  assert(!node);
  return node->data;
}

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

template< typename T >
std::ostream& output(std::ostream& out, BiTree< T >* root, const std::string& text)
{
  BiTreeIterator< T > it{ root };
  if (text == "tomax")
  {
    while (it.hasPrev())
    {
      it = it.prev();
    }
    out << it.data();
    it = it.next();
    while (it.hasNext())
    {
      out << " " << it.data();
      it = it.next();
    }
  }
  else if (text == "tomin")
  {
    while (it.hasNext())
    {
      it = it.next();
    }
    out << it.data();
    while (it.hasPrev())
    {
      out << " " << it.data();
      it = it.prev();
    }
  }
  else
  {
    throw std::logic_error("Unknown command");
  }
}
int main()
{}
