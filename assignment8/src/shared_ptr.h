#ifndef SHARED_PTR_H
#define SHARED_PTR_H

template <typename T>
class SharedPtr{
public:
    SharedPtr();

    explicit SharedPtr(T* rawPtr);

    SharedPtr(const SharedPtr<T> &other);

    ~SharedPtr();

    SharedPtr<T>& operator=(const SharedPtr<T> &other);

    T& operator*() const;

    int reference_count() const;

    void reset();

private:

};

#endif // SHARED_PTR_H
