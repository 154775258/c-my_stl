#pragma once

#include <cstring>
#include <stdexcept>
#include <typeinfo>

namespace yazi {
    namespace stl {

        template <typename T>
        class Vector
        {
        public:
            Vector();
            ~Vector();
            Vector(int nums);
            Vector(int nums,T val);

            void push_back(const T& value);
            void pop_back();
            int size() const;
            int capacity() const;
            void reserve(int size);
            void resize(int size);
            T& at(int index);
            T& front();
            T& back();
            bool empty() const;
            void clear();
            T& operator [] (int index);
            Vector<T>& operator = (const Vector<T>& other);
            T* data();
            void swap(Vector<T>& other);

            class iterator
            {
            public:
                iterator() : m_pointer(nullptr) {}
                iterator(T* pointer) : m_pointer(pointer) {}
                ~iterator() {}

                bool operator == (const iterator& other)
                {
                    return m_pointer == other.m_pointer;
                }

                bool operator != (const iterator& other)
                {
                    return m_pointer != other.m_pointer;
                }

                iterator& operator = (const iterator& other)
                {
                    m_pointer = other.m_pointer;
                    return *this;
                }

                iterator& operator ++ ()
                {
                    m_pointer += 1;
                    return *this;
                }

                iterator operator ++ (int)
                {
                    iterator it = *this;
                    ++(*this);
                    return it;
                }

                iterator operator + (int i)
                {
                    iterator it = *this;
                    it.m_pointer += i;
                    return it;
                }

                iterator& operator += (int i)
                {
                    m_pointer += i;
                    return *this;
                }

                iterator operator - (int i)
                {
                    iterator it = *this;
                    it.m_pointer -= i;
                    return it;
                }

                iterator& operator -= (int i)
                {
                    m_pointer -= i;
                    return *this;
                }

                int operator - (const iterator& other) const
                {
                    return m_pointer - other.m_pointer;
                }

                T& operator * ()
                {
                    return *m_pointer;
                }

                T* operator -> ()
                {
                    return m_pointer;
                }

            private:
                T* m_pointer;
            };

            iterator begin();
            iterator end();

            class reverse_iterator
            {
            public:
                reverse_iterator() : m_pointer(nullptr) {}
                reverse_iterator(T* pointer) : m_pointer(pointer) {}
                ~reverse_iterator() {}

                bool operator == (const reverse_iterator& other)
                {
                    return m_pointer == other.m_pointer;
                }

                bool operator != (const reverse_iterator& other)
                {
                    return m_pointer != other.m_pointer;
                }

                reverse_iterator& operator = (const reverse_iterator& other)
                {
                    m_pointer = other.m_pointer;
                    return *this;
                }

                reverse_iterator& operator ++ ()
                {
                    m_pointer -= 1;
                    return *this;
                }

                reverse_iterator operator ++ (int)
                {
                    reverse_iterator it = *this;
                    ++(*this);
                    return it;
                }

                reverse_iterator operator + (int i)
                {
                    reverse_iterator it = *this;
                    it.m_pointer -= i;
                    return it;
                }

                reverse_iterator& operator += (int i)
                {
                    m_pointer -= i;
                    return *this;
                }

                reverse_iterator operator - (int i)
                {
                    reverse_iterator it = *this;
                    it.m_pointer += i;
                    return it;
                }

                reverse_iterator& operator -= (int i)
                {
                    m_pointer += i;
                    return *this;
                }

                T& operator * ()
                {
                    return *m_pointer;
                }

                T* operator -> ()
                {
                    return m_pointer;
                }

            private:
                T* m_pointer;
            };

            reverse_iterator rbegin();
            reverse_iterator rend();

            iterator find(const T& value);
            iterator rfind(const T& value);

            iterator insert(iterator pos, const T& value);
            iterator insert(iterator pos, int n, const T& value);

            iterator erase(iterator pos);
            iterator erase(iterator first, iterator last);

        private:
            bool is_basic_type();

        protected:
            T* m_data;
            int m_size;
            int m_capacity;
        };

        template <typename T>
        Vector<T>::Vector(int nums)
        {
            m_data = new T[nums];
            m_capacity = nums;
        }

        template <typename T>
        Vector<T>::Vector(int nums,T val)
        {
            m_data = new T[nums];
            m_capacity = nums;
            m_size = nums;
            for (int i = 0; i < m_size; i++) {
                m_data[i] = val;
            }
        }

        template <typename T>
        Vector<T>::Vector() : m_data(nullptr), m_size(0), m_capacity(0)
        {
        }

        template <typename T>
        Vector<T>::~Vector()
        {
            if (m_data != nullptr)
            {
                delete[] m_data;
                m_data = nullptr;
            }
            m_size = 0;
            m_capacity = 0;
        }

        template <typename T>
        void Vector<T>::push_back(const T& value)
        {
            if (m_size < m_capacity)
            {
                m_data[m_size] = value;
                m_size++;
                return;
            }
            if (m_capacity == 0)
            {
                m_capacity = 1;
            }
            else
            {
                m_capacity *= 2;
            }
            T* data = new T[m_capacity];
            if (is_basic_type())
            {
                std::memcpy(data, m_data, m_size * sizeof(T));
            }
            else
            {
                for (int i = 0; i < m_size; i++)
                {
                    data[i] = m_data[i];
                }
            }

            if (m_data != nullptr)
            {
                delete[] m_data;
                m_data = nullptr;
            }
            m_data = data;
            m_data[m_size] = value;
            m_size++;
        }

        template <typename T>
        void Vector<T>::pop_back()
        {
            if (m_size > 0)
            {
                m_size--;
            }
        }

        template <typename T>
        int Vector<T>::size() const
        {
            return m_size;
        }

        template <typename T>
        int Vector<T>::capacity() const
        {
            return m_capacity;
        }

        template <typename T>
        void Vector<T>::reserve(int size)
        {
            if (m_capacity >= size)
            {
                return;
            }
            while (m_capacity < size)
            {
                if (m_capacity == 0)
                {
                    m_capacity = 1;
                }
                else
                {
                    m_capacity *= 2;
                }
            }
            T* data = new T[m_capacity];
            if (is_basic_type())
            {
                std::memcpy(data, m_data, m_size * sizeof(T));
            }
            else
            {
                for (int i = 0; i < m_size; i++)
                {
                    data[i] = m_data[i];
                }
            }
            if (m_data != nullptr)
            {
                delete[] m_data;
                m_data = nullptr;
            }
            m_data = data;
        }

        template <typename T>
        void Vector<T>::resize(int size)
        {
            if (m_size >= size)
            {
                m_size = size;
                return;
            }
            if (size <= m_capacity)
            {
                for (int i = m_size; i < size; i++)
                {
                    m_data[i] = T();
                }
                m_size = size;
                return;
            }
            while (m_capacity < size)
            {
                if (m_capacity == 0)
                {
                    m_capacity = 1;
                }
                else
                {
                    m_capacity *= 2;
                }
            }
            T* data = new T[m_capacity];
            if (is_basic_type())
            {
                std::memcpy(data, m_data, m_size * sizeof(T));
            }
            else
            {
                for (int i = 0; i < m_size; i++)
                {
                    data[i] = m_data[i];
                }
            }
            for (int i = m_size; i < size; i++)
            {
                data[i] = T();
            }

            if (m_data != nullptr)
            {
                delete[] m_data;
                m_data = nullptr;
            }
            m_data = data;
            m_size = size;
        }

        template <typename T>
        T& Vector<T>::at(int index)
        {
            if (index < 0 || index >= m_size)
            {
                throw std::logic_error("out of range");
            }
            return m_data[index];
        }

        template <typename T>
        T& Vector<T>::front()
        {
            if (m_size <= 0)
            {
                throw std::logic_error("vector is empty");
            }
            return m_data[0];
        }

        template <typename T>
        T& Vector<T>::back()
        {
            if (m_size <= 0)
            {
                throw std::logic_error("vector is empty");
            }
            return m_data[m_size - 1];
        }

        template <typename T>
        bool Vector<T>::empty() const
        {
            return m_size == 0;
        }

        template <typename T>
        void Vector<T>::clear()
        {
            m_size = 0;
        }

        template <typename T>
        T& Vector<T>::operator [] (int index)
        {
            return at(index);
        }

        template <typename T>
        Vector<T>& Vector<T>::operator = (const Vector<T>& other)
        {
            if (m_capacity < other.m_size)
            {
                if (m_data != nullptr)
                {
                    delete[] m_data;
                    m_data = nullptr;
                    m_size = 0;
                    m_capacity = 0;
                }
                while (m_capacity < other.m_size)
                {
                    if (m_capacity == 0)
                    {
                        m_capacity = 1;
                    }
                    else
                    {
                        m_capacity *= 2;
                    }
                }
                m_data = new T[m_capacity];
            }
            if (is_basic_type())
            {
                std::memcpy(m_data, other.m_data, m_size * sizeof(T));
            }
            else
            {
                for (int i = 0; i < other.m_size; i++)
                {
                    m_data[i] = other.m_data[i];
                }
            }
            m_size = other.m_size;
            return *this;
        }

        template <typename T>
        T* Vector<T>::data()
        {
            return m_data;
        }

        template <typename T>
        void Vector<T>::swap(Vector<T>& other)
        {
            T* data = other.m_data;
            int size = other.m_size;
            int capacity = other.m_capacity;

            other.m_data = m_data;
            other.m_size = m_size;
            other.m_capacity = m_capacity;

            m_data = data;
            m_size = size;
            m_capacity = capacity;
        }

        template <typename T>
        typename Vector<T>::iterator Vector<T>::begin()
        {
            Vector<T>::iterator it(m_data);
            return it;
        }

        template <typename T>
        typename Vector<T>::iterator Vector<T>::end()
        {
            Vector<T>::iterator it(m_data + m_size);
            return it;
        }

        template <typename T>
        typename Vector<T>::reverse_iterator Vector<T>::rbegin()
        {
            Vector<T>::reverse_iterator it(m_data + m_size - 1);
            return it;
        }

        template <typename T>
        typename Vector<T>::reverse_iterator Vector<T>::rend()
        {
            Vector<T>::reverse_iterator it(m_data - 1);
            return it;
        }

        template <typename T>
        typename Vector<T>::iterator Vector<T>::find(const T& value)
        {
            for (Vector<T>::iterator it = begin(); it != end(); it++)
            {
                if (*it == value)
                {
                    return it;
                }
            }
            return end();
        }

        template <typename T>
        typename Vector<T>::iterator Vector<T>::rfind(const T& value)
        {
            for (Vector<T>::reverse_iterator it = rbegin(); it != rend(); it++)
            {
                if (*it == value)
                {
                    return Vector<T>::iterator(it.operator->());
                }
            }
            return end();
        }

        template <typename T>
        typename Vector<T>::iterator Vector<T>::insert(Vector<T>::iterator pos, const T& value)
        {
            return insert(pos, 1, value);
        }

        template <typename T>
        typename Vector<T>::iterator Vector<T>::insert(Vector<T>::iterator pos, int n, const T& value)
        {
            int size = pos - begin();
            if (m_size + n <= m_capacity)
            {
                if (is_basic_type())
                {
                    std::memmove(m_data + size + n, m_data + size, (m_size - size) * sizeof(T));
                }
                else
                {
                    for (int i = m_size; i > size; i--)
                    {
                        m_data[i + n - 1] = m_data[i - 1];
                    }
                }
                for (int i = 0; i < n; i++)
                {
                    m_data[size + i] = value;
                }
                m_size += n;
                return Vector<T>::iterator(m_data + size);
            }
            while (m_size + n > m_capacity)
            {
                if (m_capacity == 0)
                {
                    m_capacity = 1;
                }
                else
                {
                    m_capacity *= 2;
                }
            }
            T* data = new T[m_capacity];
            if (is_basic_type())
            {
                std::memcpy(data, m_data, size * sizeof(T));
            }
            else
            {
                for (int i = 0; i < size; i++)
                {
                    data[i] = m_data[i];
                }
            }

            for (int i = 0; i < n; i++)
            {
                data[size + i] = value;
            }

            if (is_basic_type())
            {
                std::memcpy(data + size + n, m_data + size, (m_size - size) * sizeof(T));
            }
            else
            {
                for (int i = size; i < m_size; i++)
                {
                    data[i + n] = m_data[i];
                }
            }
            if (m_data != nullptr)
            {
                delete[] m_data;
                m_data = nullptr;
            }
            m_data = data;
            m_size += n;
            return Vector<T>::iterator(m_data + size);
        }

        template <typename T>
        typename Vector<T>::iterator Vector<T>::erase(Vector<T>::iterator pos)
        {
            if (end() - pos == 1)
            {
                m_size -= 1;
                return end();
            }
            int size = pos - begin();
            if (is_basic_type())
            {
                std::memmove(m_data + size, m_data + size + 1, (m_size - size - 1) * sizeof(T));
            }
            else
            {
                for (int i = size; i < m_size - 1; i++)
                {
                    m_data[i] = m_data[i + 1];
                }
            }
            m_size -= 1;
            return pos;
        }

        template <typename T>
        typename Vector<T>::iterator Vector<T>::erase(Vector<T>::iterator first, Vector<T>::iterator last)
        {
            int f = first - begin();
            int l = last - begin();
            int n = last - first;
            if (is_basic_type())
            {
                std::memmove(m_data + f, m_data + l, (m_size - l) * sizeof(T));
            }
            else
            {
                for (int i = 0; i < m_size - l; i++)
                {
                    m_data[f] = m_data[l];
                }
            }
            m_size -= n;
            return first;
        }

        template <typename T>
        bool Vector<T>::is_basic_type()
        {
            if (std::is_pointer<T>::value)
            {
                return true;
            }
            return (typeid(T) == typeid(bool)) ||
                (typeid(T) == typeid(char)) ||
                (typeid(T) == typeid(unsigned char)) ||
                (typeid(T) == typeid(short)) ||
                (typeid(T) == typeid(unsigned short)) ||
                (typeid(T) == typeid(int)) ||
                (typeid(T) == typeid(unsigned int)) ||
                (typeid(T) == typeid(long)) ||
                (typeid(T) == typeid(unsigned long)) ||
                (typeid(T) == typeid(float)) ||
                (typeid(T) == typeid(double));
        }

    }
}

