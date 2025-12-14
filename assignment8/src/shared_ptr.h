#ifndef SHARED_PTR_H
#define SHARED_PTR_H
#include <stdexcept>

template <typename T>
class SharedPtr
{
public:
    SharedPtr();

    explicit SharedPtr(T *rawPtr);

    SharedPtr(const SharedPtr<T> &other);

    ~SharedPtr();

    SharedPtr<T> &operator=(const SharedPtr<T> &other);

    T &operator*() const;

    int reference_count() const;

    void reset();

private:
    T *_ptr;
    int *_ref_count;
};

template <typename T>
SharedPtr<T>::SharedPtr() : _ptr(nullptr), _ref_count(nullptr) {}
template <typename T>
SharedPtr<T>::SharedPtr(T *rawPtr) : _ptr(rawPtr), _ref_count(nullptr)
{
    if (_ptr != nullptr)
    {
        _ref_count = new int(1);
    }
}
template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T> &other) : _ptr(other._ptr), _ref_count(other._ref_count)
{
    if (_ref_count != nullptr)
    {
        *(_ref_count)++;
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
    if (other._ref_count != nullptr)
    {
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
    (*_ref_count)--;
    if (*_ref_count == 0)
    {
        delete _ptr;
        delete _ref_count;
    }
}
template <typename T>
T &SharedPtr<T>::operator*() const
{
    if (this->_ptr == nullptr)
    {
        throw std::runtime_error("This pointer owns nothing.");
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

    (*_ref_count)--;

    if (*_ref_count == 0)
    {
        delete _ptr;
        delete _ref_count;
    }
    _ptr = nullptr;
    _ref_count = nullptr;
}
#endif // SHARED_PTR_H
