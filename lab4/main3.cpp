#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <utility>

namespace stepik
{
  template <class Type>
  struct node
  {
    Type value;
    node* next;
    node* prev;

    node(const Type& value, node<Type>* next, node<Type>* prev)
      : value(value), next(next), prev(prev)
    {
    }
  };

  template <class Type>
  class list; //forward declaration

  template <class Type>
  class list_iterator
  {
  public:
    typedef ptrdiff_t difference_type;
    typedef Type value_type;
    typedef Type* pointer;
    typedef Type& reference;
    typedef size_t size_type;
    typedef std::forward_iterator_tag iterator_category;

    list_iterator()
      : m_node(NULL)
    {
    }

    list_iterator(const list_iterator& other)
      : m_node(other.m_node)
    {
    }

    list_iterator& operator = (const list_iterator& other)
    {
      // implement this
         m_node = other.m_node;
          return *this;
    }

    bool operator == (const list_iterator& other) const
    {
      // implement this
        if(m_node == other.m_node)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator != (const list_iterator& other) const
    {
      // implement this
       if(m_node != other.m_node)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    reference operator * ()
    {
      // implement this
        return m_node->value;
    }

    pointer operator -> ()
    {
      // implement this
        return &(m_node->value);
    }

    list_iterator& operator ++ ()
    {
      // implement this
        if(m_node != nullptr)
      {
          m_node = m_node->next;
      }  		
	  return *this;
    }

    list_iterator operator ++ (int)
    {
      // implement this
        if(m_node != nullptr)
      {
          m_node = m_node->next;
      }  		
	  return *this;
    }

  private:
    friend class list<Type>;

    list_iterator(node<Type>* p)
      : m_node(p)
    {
    }

    node<Type>* m_node;
  };

  template <class Type>
  class list
  {
  public:
    typedef Type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef list_iterator<Type> iterator;

    list()
      : m_head(nullptr), m_tail(nullptr)
    {
    }
    void clear()
        {
          node<Type>* tmp;
          while(m_head != nullptr)
          {
              tmp = m_head -> next;
              delete m_head;
              m_head = tmp;
          }

        }
    bool empty() const
    {
      if (m_head == nullptr)
      {
          return true;
      }
      else
      {
          return false;
      }
    }  
    ~list()
    {
        clear();
      // use previous step implementation
    }

    list::iterator begin()
    {
      return iterator(m_head);
    }

    list::iterator end()
    {
      return iterator();
    }

    void push_back(const value_type& value)
    {
      // use previous step implementation
        if (empty())
         {

             node<Type>* tmp = new node<Type>(value,nullptr,nullptr);
             m_head = tmp;
             m_tail = tmp;
         }
        else
        {
            node<Type>* tmp = new node<Type>(value,nullptr,m_tail);
            m_tail->next = tmp;
            m_tail = tmp;
        }
    }

    reference front()
    {
      // use previous step implementation
        return m_head->value;
    }

    reference back()
    {
      // use previous step implementation
        return m_tail->value;
    }

  private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik
