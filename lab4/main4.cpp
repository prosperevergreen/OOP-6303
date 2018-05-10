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
      // use previous step implementation
        m_node = other.m_node;
      return *this;
    }

    bool operator == (const list_iterator& other) const
    {
      // use previous step implementation
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
      // use previous step implementation
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
      // use previous step implementation
         return m_node->value;
    }

    pointer operator -> ()
    {
      // use previous step implementation
        return &(m_node->value);
    }

    list_iterator& operator ++ ()
    {
      // use previous step implementation
        if(m_node != nullptr)
      {
          m_node = m_node->next;
      }  		
	  return *this;
    }

    list_iterator operator ++ (int)
    {
      // use previous step implementation
        if(m_node != nullptr)
      {
          m_node = m_node->next;
      }  		
	  return *this;	return *this;
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

    ~list()
    {
      // use previous step implementation
        clear();
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

    iterator insert(iterator pos, const Type& value)
    {
      // implement this
        node<value_type>* tmp = new node<value_type>(value, pos.m_node, pos.m_node->prev);
        if(begin() == pos)
        {
           m_head = tmp;
        } 
        else
        {
            pos.m_node->prev->next = tmp;
        }
        pos.m_node->prev = tmp;

        pos.m_node = tmp;

      return pos;
    }
    
    void pop_front()
    {
        if(!empty())
      {
          if(m_head->next)
          {
              m_head = m_head->next;
              delete m_head->prev;
              m_head->prev = nullptr;
          }
          else
          {
              m_tail = nullptr;
              delete m_head;
              m_head = nullptr;
          }
      }
    }

    void pop_back()
    {
      if(!empty())
      {
          if(m_head->next)
          {
              m_tail = m_tail->prev;
              delete m_tail->next;
              m_tail->next = nullptr;
          }
          else
          {
              m_head = nullptr;
              delete m_tail;
              m_tail = nullptr;
          }
      }
    }

    iterator erase(iterator pos)
    {
      // implement this
        if (pos != m_head && pos !=m_tail)
        {
            node<value_type>* tmp = pos.m_node;
            //right ->
            pos.m_node->prev->next = pos.m_node->next;
            //left <-
            pos.m_node->next->prev = pos.m_node->prev;
            
            delete tmp;
            
            return pos.m_node->next;
        }
        if (pos.m_node == m_head)
        {
            pop_front();
            return begin();
        }
        if (pos.m_node == m_tail) 
        {
            pop_back();
            return end();
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
