#ifndef SHARED_PTR_H
#define SHARED_PTR_H
#include <stdexcept>
#include <optional>
#include <mutex>

template <typename T>
class SharedPtr
{
public:
    // Default Constructor
    SharedPtr();
    // Share pointer
    explicit SharedPtr(T *rawPtr);
    // Copy Constructor
    SharedPtr(const SharedPtr<T> &other);
    // Destructor
    ~SharedPtr();
    // Copy Assignment Operator
    SharedPtr<T> &operator=(const SharedPtr<T> &other);
    // Dereferencer
    T &operator*() const;
    // Get reference count
    int reference_count() const;
    // Reset Shared pointer
    void reset();

private:
    T *_ptr;
    int *_ref_count;
    std::mutex *_mtx;
};

template <typename T>
SharedPtr<T>::SharedPtr() : _ptr(nullptr), _ref_count(nullptr) {}
template <typename T>
SharedPtr<T>::SharedPtr(T *rawPtr) : _ptr(rawPtr), _ref_count(nullptr), _mtx(nullptr)
{
    if (_ptr != nullptr)
    {
        _ref_count = new int(1);
        _mtx = new std::mutex();
    }
}
template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T> &other) : _ptr(other._ptr), _ref_count(other._ref_count), _mtx(other._mtx)
{
    if (_ref_count != nullptr)
    {
        std::lock_guard<std::mutex> lock(*_mtx);
        (*_ref_count)++;
    }
}
template <typename T>
SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr<T> &other)
{
    if (this == &other)
    {
        return *this;
    }
    this->reset();
    this->_ptr = other._ptr;
    this->_ref_count = other._ref_count;
    this->_mtx = other._mtx;
    if (other._ref_count != nullptr)
    {
        std::lock_guard<std::mutex> lock(*_mtx);
        (*other._ref_count)++;
    }
    return *this;
}
template <typename T>
SharedPtr<T>::~SharedPtr()
{
    if (_ptr == nullptr)
    {
        return;
    }
    bool delete_resource = false;
    {
        std::lock_guard<std::mutex> lock(*_mtx);
        (*_ref_count)--;
        if (*_ref_count == 0)
        {
            delete_resource = true;
        }
    }
    if (delete_resource)
    {
        delete _ptr;
        delete _ref_count;
        delete _mtx;
    }
}
template <typename T>
T &SharedPtr<T>::operator*() const
{
    if (this->_ptr == nullptr)
    {
        throw std::bad_optional_access();
    }
    return *this->_ptr;
}
template <typename T>
int SharedPtr<T>::reference_count() const
{
    if (this->_ref_count == nullptr)
    {
        return 0;
    }
    return *this->_ref_count;
}
template <typename T>
void SharedPtr<T>::reset()
{
    if (_ptr == nullptr)
    {
        return;
    }
    bool delete_resource = false;
    {
        std::lock_guard<std::mutex> lock(*_mtx);
        (*_ref_count)--;
        if (*_ref_count == 0)
        {
            delete_resource = true;
        }
    }
    if (delete_resource)
    {
        delete _ptr;
        delete _ref_count;
        delete _mtx;
    }
    _ptr = nullptr;
    _ref_count = nullptr;
}
#endif // SHARED_PTR_H
