#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <memory>
#include <iostream>
using namespace std;


template<typename T>
class Array
{
public:
  // (default) constructor
  Array(const size_t size = 0)
    : m_size(size)
    , m_array(m_size ? new T[m_size]() : nullptr)
  {
  }

  const size_t size() const
  {
    return m_size;
  }

  T& operator [](const size_t index)
  {
    assert(index < m_size);
    return m_array[index];
  }

  Array(const Array& other)
      : m_size(other.m_size),
      m_array(m_size ? new T[m_size] : nullptr) {
      std::copy(other.m_array.get(), other.m_array.get() + m_size, m_array.get());
     }

  Array & operator = (Array const& object) {
          if (this != &object) {
                Array(object).swap(*this);
              }
          return *this;
      }

  void swap(Array & object) {
        std::swap(this->m_size, object.m_size);
        std::swap(this->m_array, object.m_array);
      }

  Array(Array&& other)
    : Array()
    {
      swap(*this, other);
    }

private:
  size_t m_size;
  //T* m_array;
  unique_ptr<T[]> m_array;
};


int main(){

        return 0;
    }
