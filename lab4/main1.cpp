#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>

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

    list()
      : m_head(nullptr), m_tail(nullptr)
    {
    }

    void push_back(const value_type& value)
    {
        //resize(size() + 1);
        //at(size() - 1) = value;
      // implement this
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

    void push_front(const value_type& value)
    {
        if (empty())
         {
             node<Type>* tmp = new node<Type>(value,nullptr,nullptr);
             m_head = tmp;
             m_tail = tmp;
         }
        else
        {
            node<Type>* tmp = new node<Type>(value,m_head,nullptr);
            m_head->prev = tmp;
            m_head = tmp;
        }
      // implement this
    }

    reference front()
    {
        return m_head->value;
      // implement this
    }

    const_reference front() const
    {
        return m_head->value;
      // implement this
    }

    reference back()
    {
        return m_tail->value;
      // implement this
    }

    const_reference back() const
    {
        return m_tail->value;
      // implement this
    }

    void pop_front()
    {
      // implement this
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
      // implement this
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

    void clear()
    {
      // implement this 
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
      // implement this
        if (m_head == nullptr)
      {
          return true;
      }
      else
      {
          return false;
      }
    }

    size_t size() const
    {
      // implement this
        if (empty()){return 0;}
        else
        {
            size_t kol = 0;
            node<Type>* pre = m_head;
            while(pre != nullptr)
            {
                pre = pre->next;
                kol++;
            }
            return kol;
        }
    }

  private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik
