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
  class list
  {
  public:
    typedef Type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
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
      
    list()
      : m_head(nullptr), m_tail(nullptr)
    {
    }

    ~list()
    {
        clear();
      // implement this    
    }

    list(const list& other)
    {
      m_head = m_tail = nullptr;
        *this = other;  
      // implement this
    }

    list(list&& other)
    {
        m_head = m_tail = nullptr;
        *this = other;
        other.clear();
      // implement this
    }

    list& operator= (const list& other)
    {
        clear();
        node <Type>* tmp = other.m_head;
        while(tmp != nullptr)
        {
            push_back(tmp->value);
            tmp = tmp->next;
        }
        return *this;
      // implement this
    }

    void push_back(const value_type& value)
    {
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
      // use previous step implementation
    }
    
    reference front()
    {
        return m_head->value;
      // use previous step implementation
    }

    reference back()
    {
        return m_tail->value;
      // use previous step implementation
    }


  private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik
