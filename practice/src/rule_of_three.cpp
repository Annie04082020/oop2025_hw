#include <iostream>
#include <algorithm>

class IntBuffer
{
private:
    int *data;
    size_t size;

public:
    // 一般建構子
    IntBuffer(size_t s) : size(s), data(new int[s])
    {
        for (size_t i = 0; i < size; ++i)
            data[i] = 0;
        std::cout << "Constructed\n";
    }

    // TODO: 請在此實作 Copy Constructor
    // IntBuffer(const IntBuffer& other) ...
    // other 是要被複製的內容，this 才是新的
    IntBuffer(const IntBuffer &other) : size(other.size), data(new int[other.size])
    {
        for (int i = 0; i < other.size; ++i)
        {
            this->setValue(i, other.getValue(i));
        }
    }
    // TODO: 請在此實作 Destructor
    // ~IntBuffer() ...
    ~IntBuffer()
    {
        delete[] this->data;
    }

    void setValue(size_t index, int value)
    {
        if (index < size)
            data[index] = value;
    }

    int getValue(size_t index) const
    {
        return (index < size) ? data[index] : -1;
    }
};

int main_r3()
{
    IntBuffer buf1(5);
    buf1.setValue(0, 100);

    IntBuffer buf2 = buf1; // 觸發 Copy Constructor

    // 測試 Deep Copy：修改 buf2 不應影響 buf1
    buf2.setValue(0, 999);

    std::cout << "Buf1[0]: " << buf1.getValue(0) << std::endl; // 應為 100
    std::cout << "Buf2[0]: " << buf2.getValue(0) << std::endl; // 應為 999

    return 0;
}