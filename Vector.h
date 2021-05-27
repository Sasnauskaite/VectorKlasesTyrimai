#include <bits/stdc++.h>
template<class T, class Allocator = std::allocator<T>>
class Vector 
{
public:
    // Member funkcijos
    //konstruktoriai
    Vector() : size_(0), capacity_(0){data_ = allocator_.allocate(capacity_);}

    Vector(size_t count, const T& value = T()) : size_(count), capacity_(capacity()>maxsize_()-capacity()/2?count:capacity()*1.5<count?count:capacity()*1.5)
    {
        data_ = allocator_.allocate(capacity_);
        std::fill_n(data_, count, value);
    }

    Vector(T* first, T* last) 
    {
        size_ = last - first;
        capacity_ = last - first;
        data_ = allocator_.allocate(capacity_);

        std::copy(first, last, data_);
    }

    Vector(const Vector& A) 
    {
        size_ = A.size();
        capacity_ = A.capacity();
        data_ = allocator_.allocate(capacity_);

        std::copy(A.begin(), A.end(), data_);
    }

    Vector(Vector&& A) 
    {
        size_ = A.size();
        capacity_ = A.capacity();

        data_ = allocator_.allocate(capacity_);
        std::move(A.begin(), A.end(), data_);

        A.clear();
    }

    Vector(std::initializer_list<T> temp) 
    {
        size_ = temp.size();
        capacity_ = capacity()>maxsize_()-capacity()/2?size_:capacity()*1.5<size_?size_:capacity()*1.5;
        data_ = allocator_.allocate(capacity_);

        std::copy(temp.begin(), temp.end(), data_);
    }
    //////////////////
    //destruktorius
    ~Vector() 
    {
        auto n = size();
        if (data_ != NULL) 
        {
            for (size_t i = 0; i < n; i++) 
            {
                allocator_.destroy(&data_[i]);
            }
            allocator_.deallocate(data_, capacity());
            data_ = NULL;
        }
    }
    ///////////////////

    Vector& operator=(const Vector& A) 
    {
        size_ = A.size();
        capacity_ = A.capacity();
        data_ = allocator_.allocate(capacity_);

        std::copy(A.begin(), A.end(), data_);
        return *this;
    }

    void assign(size_t count, const T& value) 
    {
        clear();

        if (count > capacity()) {
            deallocate(count);
        }

        for (int i = 0; i < count; i++) {
            data_[i] = value;
        }

        size_ = count;
    }

    void assign(T* first, T* last) 
    {
        clear();
        const std::ptrdiff_t count = last - first;
        
        if (count > capacity()) 
        {
            deallocate(count);
        }

        std::copy(first, last, data_);
        size_ = count;
    }
    Allocator getallocator_() const {
        return allocator_;
    }
    ////////////////////////////////////////////
    // Element access
    T& at(size_t ind) 
    {
        if (ind < size() && ind >= 0) 
        {
            return data_[ind];
        }

        throw ("out of range");
    }

    const T& at(size_t ind) const 
    {
        if (ind < size() && ind >= 0) 
        {
            return data_[ind];
        }
        
        throw ("out of range");
    }

    T& operator[](size_t ind) 
    {
        return data_[ind];
    }

    const T& operator[](size_t ind) const 
    {
        return data_[ind];
    }

    T& front() 
    {
        return data_[0];
    }

    const T& front() const 
    {
        return data_[0];
    }

    T& back() 
    {
        return data_[size() - 1];
    }

    const T& back() const 
    {
        return data_[size() - 1];
    }

    T* data() 
    {
        return data_;
    }

    const T* data() const 
    {
        return data_;
    }
    //////////////////////////////
    // Iterators
    T* begin() 
    {
        return data_;
    }

    const T* begin() const 
    {
        return data_;
    }

    const T* cbegin() const 
    {
        return begin();
    }

    T* end() 
    {
        return begin() + size_;
    }

    const T* end() const 
    {
        return begin() + size_;
    }

    const T* cend() const 
    {
        return end();
    }

    const T* rbegin() 
    {
        return std::reverse_iterator<T*>(data_ + size_);
    }

    std::reverse_iterator<const T*> rbegin() const 
    {
        return rbegin();
    }

    const T* rend() 
    {
        return std::reverse_iterator<T*>(data_);
    }

    std::reverse_iterator<const T*> rend() const 
    {
        return rend();
    }
    //////////////////////////////
    // Capacity
    bool empty() const 
    {
        return size() == 0;
    }

    size_t size() const
    {
        return size_;
    }

    size_t maxsize_() const 
    {
        return std::numeric_limits<size_t>::max();
    }

    void reserve(size_t newCapacity) 
    {
        if (newCapacity > maxsize_()) 
        {
            throw ("too large");
        }
        
        if (newCapacity > capacity())
        {
            deallocate(capacity() + newCapacity);
        }
        
        capacity_ = newCapacity;
    }

    size_t capacity() const 
    {
        return capacity_;
    }

    void shrink_to_fit() 
    {
        auto n = size();

        for (auto i = n; i < capacity(); i++) 
        {
            allocator_.destroy(data() + i);
        }
        capacity_ = size();
    }
    //////////////////////////////////////////////

    // Modifiers
    void clear() 
    {
        auto n = size();

        for (size_t i = 0; i < n; i++) 
        {
            allocator_.destroy(data() + i);
        }

        size_ = 0;
    }

    T* insert(const T* ind, const T& value) 
    {
        return insert(ind, 1, value);
    }

    T* insert(const T* ind, T&& value) 
    {
        std::ptrdiff_t index = ind - begin();
        
        if (index < 0 || index > size()) 
        {
            throw ("index is out of range");
        }

        if (size() == capacity()) 
        {
            deallocate(capacity() + 1);
        }

        T* it = &data_[index];

        std::move(it, end(), it + 1);
        *it = std::move(value);

        size_++;

        return it;
    }

    T* insert(const T* ind, size_t count, const T& value) 
    {
        const std::ptrdiff_t index = ind - begin();
        
        if (index < 0 || index > size()) 
        {
            throw ("index is out of range");
        }

        if (size() + count > capacity()) 
        {
            deallocate(capacity() + count);
        }

        T* it = &data_[index];

        std::move(it, end(), it + count);
        std::fill_n(it, count, value);

        size_ += count;

        return it;
    }

    T* insert(const T* ind, T* first, T* last) 
    {
        const std::ptrdiff_t count = last - first;
        const std::ptrdiff_t index = ind - begin();
        
        if (size() + count > capacity()) 
        {
            deallocate(capacity() + count);
        }
        
        T* it = &data_[index];
        std::move(it, end(), it + count);
        std::copy(first, last, it);
        
        size_ += count;
        
        return it;
    }

    T* insert(const T* ind, std::initializer_list<T> temp) 
    {
        const std::ptrdiff_t count = temp.size();
        const std::ptrdiff_t index = ind - begin();
        
        if (size() + count > capacity()) 
        {
            deallocate(capacity() + count);
        }
        
        T* it = &data_[index];
        std::move(it, end(), it + count);
        std::copy(temp.begin(), temp.end(), it);
        
        size_ += count;
        
        return it;
    }

    template< class... Args >
    T* emplace(const T* ind, Args&&... args) 
    {
        const std::ptrdiff_t index = ind - begin();
        
        if (index < 0 || index > size()) 
        {
            throw ("out of range");
        }
        
        if (size() == capacity()) 
        {
            deallocate(capacity() + 1);
        }
        
        T* it = &data_[index];
        
        std::move(it, end(), it + 1);
        allocator_.construct(it, args...);
        
        size_++;
        
        return it;
    }

    T* erase(const T* ind) 
    {
        const std::ptrdiff_t index = ind - begin();
        allocator_.destroy(&data_[index]);
        
        for (auto i = index; i < size() - 1; i++) 
        {
            allocator_.destroy(&data_[i + 1]);
            allocator_.construct(&data_[i], data_[i + 1]);
        }
        
        size_--;
        T* it = &data_[index];
        
        return it;
    }

    T* erase(const T* first, const T* last) 
    {
        const std::ptrdiff_t startIndex = first - begin();
        const std::ptrdiff_t endIndex = last - begin();
        
        for (std::ptrdiff_t i = 0; i < endIndex - startIndex; i++) 
        {
            allocator_.destroy(&data_[startIndex + i]);
            allocator_.construct(&data_[startIndex + i], data_[endIndex + i]);
        }
        
        size_ -= endIndex - startIndex;
        T* it = &data_[startIndex];
        
        return it;
    }

    void push_back(const T& item) 
    {
        if (size() == capacity()) 
        {
            deallocate(capacity() + 1);
        }
        allocator_.construct(end(), item);
        ++size_;
    }

    void push_back(T&& value) 
    {
        if (size() == capacity())
        {
            deallocate(capacity() + 1);
        }
        allocator_.construct(end(), std::move(value));
        ++size_;
    }

    template< class... Args >
    void emplace_back(Args&&... args) 
    {
        emplace(end(), std::forward<Args>(args)...);
    }

    void pop_back() 
    {
        allocator_.destroy(end() - 1);
        --size_;
    }

    void resize(size_t count) 
    {
        resize(count, T());
    }

    void resize(size_t count, const T& value) 
    {
        auto n = size();

        if (count > capacity()) 
        {
            deallocate(count);
            for (size_t i = n; i < count; i++) 
            {
                allocator_.construct(data() + i, value);
            }
        }
        else if (count < n) 
        {
            for (size_t i = count; i < n; i++) 
            {
                allocator_.destroy(data() + i);
            }
        }

        size_ = count;
    }

    void swap(Vector& A) 
    {
        std::swap(size_, A.size_);
        std::swap(capacity_, A.capacity_);
        std::swap(allocator_, A.allocator_);
        std::swap(data_, A.data_);
    }
    ////////////////////////////////////////////////////

private:
    size_t size_ = 0;
    size_t capacity_ = 0;
    T* data_;
    Allocator allocator_;

    void deallocate(size_t minSize) //pagalbine funkcija isplesti atminciai
    {
        const size_t tempCapacity = capacity()>maxsize_()-capacity()/2?minSize:capacity()*1.5<minSize?minSize:capacity()*1.5;

        T* tempData = allocator_.allocate(tempCapacity);
        for (size_t i = 0; i < size_; i++) 
        {
            allocator_.construct(&tempData[i], std::move(data_[i]));
            allocator_.destroy(&data_[i]);
        }
        allocator_.deallocate(data_, capacity());

        data_ = tempData;
        capacity_ = tempCapacity;
    }
};
///Non-member functions
template< class T, class Allocator>
bool operator==(const Vector<T, Allocator>& A, const Vector<T, Allocator>& B) {

    auto A_Size = A.size();
    auto B_Size = B.size();

    if (A_Size != B_Size) 
    {
        return false;
    }
    
    for (int i = 0; i < A_Size; i++) 
    {
        if (A.at(i) != B.at(i)) 
        {
            return false;
        }
    }
    
    return true;
}

template< class T, class Allocator>
bool operator!=(const Vector<T, Allocator>& A, const Vector<T, Allocator>& B) 
{
    return !(A == B);
}

template< class T, class Allocator>
bool operator<(const Vector<T, Allocator>& A, const Vector<T, Allocator>& B) 
{
    return std::lexicographical_compare(A.begin(), A.end(), B.begin(), B.end());
}

template< class T, class Allocator>
bool operator>(const Vector<T, Allocator>& A, const Vector<T, Allocator>& B) 
{
    return B < A;
}

template< class T, class Allocator>
bool operator<=(const Vector<T, Allocator>& A, const Vector<T, Allocator>& B) 
{
    return !(B < A);
}

template< class T, class Allocator>
bool operator>=(const Vector<T, Allocator>& A, const Vector<T, Allocator>& B) 
{
    return !(A < B);
}

template< class T, class Allocator>
void swap(Vector<T, Allocator>& A, Vector<T, Allocator>& B)
{
    A.swap(B);
}
