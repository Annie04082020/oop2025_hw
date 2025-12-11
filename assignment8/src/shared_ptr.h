#ifndef SHARED_PTR_H
#define SHARED_PTR_H

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

#endif // SHARED_PTR_H
