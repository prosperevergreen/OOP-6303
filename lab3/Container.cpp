include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

namespace stepik
{
  template <typename Type>

  class vector
  {
  public:
    typedef Type* iterator;
    typedef const Type* const_iterator;

    typedef Type value_type;

    typedef value_type& reference;
    typedef const value_type& const_reference;

    typedef std::ptrdiff_t difference_type;

    explicit vector(size_t count = 0) : m_first(count ? new value_type[count] : nullptr),
                                         m_last(count ? m_first+count : nullptr)
    {}

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
       size_t size = last - first;
       if (size) {
           m_first = new value_type[size];
           m_last = m_first + size;
           std::copy(first,last,m_first);
       }
       else
           m_first = m_last = nullptr;
    }


    vector(std::initializer_list<Type> init) : m_first(init.size() ? new value_type[init.size()] : nullptr),
                                               m_last(init.size() ? m_first+init.size() : nullptr)
    {
        if (m_first != nullptr)
            std::copy(init.begin(), init.end(), m_first);
    }

    vector(const vector& other) : m_first (other.size() ? new value_type[other.size()] : nullptr),
                                   m_last (other.size() ? m_first + other.size() : m_first)
    {
        if (m_first != nullptr)
            std::copy(other.begin(), other.end(), m_first);
    }

    vector(vector&& other) : m_first(other.m_first), m_last(other.m_last)
    {
        other.m_first = nullptr; //
        other.m_last = nullptr;
    }

    ~vector()
    {
        delete[] m_first;
    }

    //assignment operators
        vector& operator=(const vector& other)
        {
              if (this != &other){
               if (m_first != m_last)
                   delete [] m_first;

               if (other.size()) {
                   m_first = new value_type[other.size()];
                   m_last = m_first + other.size();
                   std::copy(other.begin(), other.end(), m_first);
               }
               else
                   m_first = m_last = nullptr;
           }
           return *this;
        }

        vector& operator=(vector&& other)
        {
            if(this != &other)
            {
                delete [] m_first;
                m_first = other.m_first;
                m_last = other.m_last;
                other.m_first = nullptr;
                other.m_last = nullptr;
            }
             return *this;
        }

        // assign method
        template <typename InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
           size_t size = last-first;
           delete [] m_first;
           m_first = m_last = nullptr;
           if (size){
               m_first = new value_type[size];
               m_last = m_first + size;
               std::copy (first,last,m_first);
           }
        }


        // resize methods
            void resize(size_t count)
            {
              vector buffer(*this);
              delete [] m_first;
              m_first = new value_type[count];
              m_last = m_first + count;
              if (count > buffer.size())
                   std::copy(buffer.m_first,buffer.m_last,m_first);
              else
                   std::copy(buffer.m_first,buffer.m_first + count, m_first);
            }

            //erase methods
            iterator erase(const_iterator pos)
            {
             if ((pos < m_first) || (pos > m_last))
               throw std::out_of_range("Pos error");
             size_t offset = pos - m_first;
             std::rotate (m_first + offset, m_first + offset + 1, m_last);
             resize(m_last - m_first - 1);
             return m_first + offset;
            }

            iterator erase(const_iterator first, const_iterator last)
            {
              if ((first < m_first) || (first > m_last) || (last > m_last) || (last < m_first))
                   throw std::out_of_range("iterators error");
              size_t offset = first - m_first;
              size_t length = last - first;
              std::rotate(m_first + offset, m_first + offset + length, m_last);
              resize(m_last - m_first - length);
              return m_first + offset;
            }


            //insert methods
                iterator insert(const_iterator pos, const Type& value)
                {
                   size_t offset = pos - m_first;
                   push_back(value);
                   std::rotate (m_first + offset, m_last - 1, m_last);
                   return m_first + offset;
                }

                template <typename InputIterator>
                iterator insert(const_iterator pos, InputIterator first, InputIterator last)
                {
                   size_t lentgh = last - first;
                   size_t offset = pos - m_first;
                   size_t pastSize = size();

                   resize(pastSize + lentgh);
                   std::copy(first, last, m_first + pastSize);
                   std::rotate(m_first + offset, m_last - lentgh, m_last);
                   return m_first + offset;
                }

                //push_back methods
                void push_back(const value_type& value)
                {
                  
                   resize(size() + 1);
                   at(size() - 1) = value;
                }


    //at methods
    reference at(size_t pos)
    {
      return checkIndexAndGet(pos);
    }

    const_reference at(size_t pos) const
    {
      return checkIndexAndGet(pos);
    }

    //[] operators
    reference operator[](size_t pos)
    {
      return m_first[pos];
    }

    const_reference operator[](size_t pos) const
    {
      return m_first[pos];
    }

    //*begin methods
    iterator begin()
    {
      return m_first;
    }

    const_iterator begin() const
    {
      return m_first;
    }

    //*end methods
    iterator end()
    {
      return m_last;
    }

    const_iterator end() const
    {
      return m_last;
    }

    //size method
    size_t size() const
    {
      return m_last - m_first;
    }

    //empty method
    bool empty() const
    {
      return m_first == m_last;
    }

  private:
    reference checkIndexAndGet(size_t pos) const
    {
      if (pos >= size())
      {
        throw std::out_of_range("out of range");
      }

      return m_first[pos];
    }

    //your private functions

  private:
    iterator m_first;
    iterator m_last;
  };
}// namespace stepik
