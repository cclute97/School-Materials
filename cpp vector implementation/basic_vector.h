#include <cstddef>
#include <type_traits>
#include <stdexcept>
#include <math.h>

#ifndef BASIC_VECTOR_H
#define BASIC_VECTOR_H

template <typename T>
class basic_vector {
    public: 

        /*basic_vector()*/
        //Input: None
        //Returns: None
        //Description: Basic 0-arg constructor
        //Implementation: Allocates memory for a new vector of size = 0, capacity = 1.  Uses default constructor of T to initialize values.  
        basic_vector();

        /*basic_vector(size_t n)*/
        //Input: size_t n -- capacity of new vector
        //Returns: None
        //Description: Basic 1-arg constructor
        //Implementation: Allocates memory for a new vector of size = 0, capacity = n.  Uses default constructor of T to initialize values up to n.  
        basic_vector(size_t capacity);

        /*basic_vector(const basic_vector &rhs)*/
        //Input: const basic_vector &rhs -- basic_vector to copy from 
        //Returns: None
        //Description: Copy Constructor
        //Implementation: Allocates memory for a new vector of size = rhs.size() and capacity = rhs.capacity().  Copies each element from rhs to new vector.  
        basic_vector(const basic_vector &rhs); 

        /*operator=(const basic_vector &rhs)*/
        //Input: const basic_vector &rhs -- basic_vector to copy from
        //Returns: basic_vector& -- a reference to our new vector
        //Description: assignment operator 
        //Implementation: Allocates memory for a new vector of size = rhs.size(), capacity = rhs.capacity().  Copies each element from rhs to new vector
        basic_vector& operator=(const basic_vector &rhs); 

        /*size()*/
        //Input: None
        //Returns: size_t -- this.size_
        //Description: Returns current size of vector
        //Implementation: returns size_, which is otherwise private
        size_t size(); 

        /*max_size()*/
        //Input: None
        //Returns: size_t -- maximum size of vector
        //Description: Returns maximum size of vector
        //Implementation: returns the maximum size of a vector containing type T
        size_t max_size(); 

        /*capacity()*/
        //Input: None
        //Returns: size_t -- this.capacity_
        //Description: Returns current capacity of vector
        //Implementation: returns capacity_, which is otherwise private
        size_t capacity(); 

        /*resize(size_t n)*/
        //Input: size_t n -- the size to resize to
        //Returns: None
        //Description: Resizes vector to n
        //Implementation: If n is greater than the capacity of the vector, the capacity is increased to n.  If n is greater than the current size, 
        //then the size is increased to n and the new values are default initialized.  If n is less than the current size, then values that fall within
        //the range of the difference are default initialized and the size is set to n.  if n is greater than the max_size() of the vector, then n is 
        //set to the result of max_size().  size_ is set to n
        void resize(size_t n); 

        /*resize(size_t n, T val)*/
        //Input: size_t n -- the size to resize to, T val -- what to default initialize values to.  
        //Returns: None
        //Description: Resizes vector to n
        //Implementation: If n is greater than the capacity of the vector, the capacity is increased to n.  If n is greater than the current size, 
        //then the size is increased to n and the new values are default initialized.  If n is less than the current size, then values that fall within
        //the range of the difference are default initialized and the size is set to n.  if n is greater than the max_size() of the vector, then n is 
        //set to the result of max_size().  Values are default initialized to the argument given as val.  size_ is set to n
        void resize(size_t n, T val); 

        /*empty()*/
        //Input: None
        //Returns: bool 
        //Description: returns true if vector is empty, false otherwise
        //Implementation: if size_ = 0, returns true
        bool empty();

        /*reserve(size_t n)*/
        //Input: size_t n -- the size of the new capacity
        //Returns: None
        //Description: Reserves space for n elements
        //Implementation: if n is greater than max_size(), n = max_size().  If n is greater than the current capacity of the vector, a new vector with capacity n is allocated,
        //and the elements from our current vector are copied over.  The old memory pointed to by data_ is freed and data_ is pointed to our new array in memory.  capacity_ is 
        //set to n
        void reserve(size_t n); 

        /*shrink_to_fit()*/
        //Input: None
        //Returns: None
        //Description: Shrinks capacity to fit size
        //Implementation: Creates a new vector where size = capacity and copies elements from our current to the new vector.  Frees memory of old array, points data_ to new array.  
        //Sets capacity = size
        void shrink_to_fit(); 

        /*operator[](size_t n)*/
        //Input: size_t n -- index of element in vector to access
        //Returns: T -- a reference to the element at vector[n]
        //Description: Returns element at index n of vector
        //Implementation: returns element at data_[n]
        T &operator[](size_t n); 

        /*at(size_t n)()*/
        //Input: size_t n -- index of element in vector to access
        //Returns: T -- a reference to the element at vector[n]
        //Description: Returns element at index n of vector.  Throws error if index out of bounds. 
        //Implementation: returns element at data_[n] iff n is within the bounds of our array.  Otherwise, throws out_of_range error
        T &at(size_t n); 

        /*front()*/
        //Input: None
        //Returns: T -- a reference to the element at front of vector
        //Description: Returns first element of vector
        //Implementation: returns element at data_[0]
        T &front(); 

        /*back()*/
        //Input: None
        //Returns: T -- a reference to the element at back of vector
        //Description: Returns last element of vector
        //Implementation: returns element at data_[size_ - 1]
        T &back(); 

        /*data()*/
        //Input: None
        //Returns: T -- a pointer to our data array
        //Description: Returns pointer to data array
        //Implementation: returns pointer to data_
        T *data(); 

        /*push_back()*/
        //Input: const T &val -- reference to element being added to vector
        //Returns: None
        //Description: pushes an element to the back of the vector 
        //Implementation: if there is no room (if size = capacity), the capacity is doubled using reserve(2 * capacity_).  Then (or otherwise), the element is added 
        //via data_[size] = val, and the size is incremented
        void push_back(const T &val); 

        /*pop_back()*/
        //Input: None
        //Returns: None
        //Description: pops an element from the back of the vector 
        //Implementation: if the size of the vector is greater than 0, a reference to the last element is retrieved with back(), and then the last element is default 
        //initialized with T()
        void pop_back(); 

        /*swap()*/
        //Input: basic_vector &other
        //Returns: None
        //Description: swaps the contents of two vectors 
        //Implementation: uses pointers and temp variables to swap the values of size_, capacity_, and data_ betwen our current vector and other 
        void swap(basic_vector &other); 

        /*clear()*/
        //Input: None
        //Returns: None
        //Description: clears the vector of data
        //Implementation: for every element of the vector within the range of size_, the values at that location is default initialized with T(), and size_ is set to 0
        void clear(); 

    private: 
        T *data_;
        size_t size_;
        size_t capacity_;
};

template <typename T>
basic_vector<T>::basic_vector() {
    data_ = new T[1];
    size_ = 0;
    capacity_ = 1;
    data_[0] = T();
}

template <typename T>
basic_vector<T>::basic_vector(size_t capacity) {
    data_ = new T[capacity];
    size_ = 0;
    capacity_ = capacity;
    for (size_t i = 0; i < capacity_; i++) {
        data_[i] = T();
    }
}

template <typename T>
basic_vector<T>::basic_vector(const basic_vector &rhs) {
    data_ = new T[rhs.capacity_];
    for (size_t i = 0; i < rhs.capacity_; i++) {
        data_[i] = rhs.data_[i];
    }
    size_ = rhs.size_;
    capacity_ = rhs.capacity_;
}  

template <typename T>
basic_vector<T>& basic_vector<T>::operator=(const basic_vector &rhs) {
    data_ = new T[rhs.capacity_];
    for (size_t i = 0; i < rhs.capacity_; i++) {
        data_[i] = rhs.data_[i];
    }
    size_ = rhs.size_;
    capacity_ = rhs.capacity_;
    return *this;
}

template <typename T>
size_t basic_vector<T>::size() {
    return size_;
}

template <typename T>
size_t basic_vector<T>::max_size() {
    return ((std::pow(2, 32) / sizeof(T)) - 1);
}

template <typename T>
size_t basic_vector<T>::capacity() {
    return capacity_;
}

template <typename T>
void basic_vector<T>::resize(size_t n) {

    if (n > max_size()) {
        n = max_size();
    }

    if (n > capacity_) {
        reserve(n);
        for (size_t i = size_; i < capacity_; i++) {
            data_[i] = T();
        }
    } else if (n < size_) {
        for (size_t i = n; i < size_; i++) {
            data_[i].~T();
        }
    } else if (n > size_) {
        for (size_t i = size_; i < n; i++) {
            data_[i] = T();
        }
    } else {}

    size_ = n;
}

template <typename T>
void basic_vector<T>::resize(size_t n, T val) {

    if (n > max_size()) {
        n = max_size();
    }

    if (n > capacity_) {
        reserve(n);
        for (size_t i = size_; i < capacity_; i++) {
            data_[i] = T();
        }
    } else if (n < size_) {
        T *new_data = new T[n];
        for (size_t i = 0; i < n; i++) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
    } else if (n > size_) {
        for (size_t i = size_; i < n; i++) {
            data_[i] = val;
        }
    } else {}

    size_ = n;
    capacity_ = n;
}

template <typename T>
bool basic_vector<T>::empty() {
    if (size_ == 0) {
        return true;
    }
    return false;
}

template <typename T>
void basic_vector<T>::reserve(size_t n) {
    if (n > max_size()) {
        n = max_size();
    }

    if (n > capacity_) {
        T *new_data = new T[n];
        for (size_t i = 0; i < n; i++) {
            if (i < size_) {
                new_data[i] = data_[i];
            } else {
                new_data[i] = T();
            }
        }
        capacity_ = n;
        delete[] data_;
        data_ = new_data;
    }
}

template <typename T> 
void basic_vector<T>::shrink_to_fit() {
    T *new_data = new T[size_];
    for (size_t i = 0; i < size_; i++) {
        new_data[i] = data_[i];
    }
    capacity_ = size_;
    delete[] data_;
    data_ = new_data;
}

template <typename T>
T& basic_vector<T>::operator[](size_t n) {
    return data_[n];
}

template <typename T>
T& basic_vector<T>::at(size_t n) {
    if (n >= size_ || n < 0) {
        throw std::out_of_range("Index out of range");
    }
    return data_[n]; 
}

template <typename T>
T& basic_vector<T>::front() {
    return data_[0]; 
}

template <typename T>
T& basic_vector<T>::back() {
    return data_[size_ - 1]; 
}

template <typename T>
T* basic_vector<T>::data() {
    return data_;
}

template <typename T>
void basic_vector<T>::push_back(const T &val) {
    if (size_ == capacity_) {
        reserve(capacity_ * 2);
    }
    data_[size_] = val;
    size_++;
}

template <typename T>
void basic_vector<T>::pop_back() {
    if (size_ > 0) {
        T& last_element = back();
        last_element = T();
        size_--;
    }
}

template <typename T>
void basic_vector<T>::swap(basic_vector &other) {
    T *temp_data = data_;
    data_ = other.data_;
    other.data_ = temp_data;

    size_t temp_size = size_;
    size_ = other.size_;
    other.size_ = temp_size;

    size_t temp_capacity = capacity_;
    capacity_ = other.capacity_;
    other.capacity_ = temp_capacity;
}

template <typename T>
void basic_vector<T>::clear() {
    for (size_t i = 0; i < size_; i++) {
        data_[i] = T();
    }
    size_ = 0;
}

#endif