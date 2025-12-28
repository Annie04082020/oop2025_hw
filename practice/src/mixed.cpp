#include <iostream>
#include <vector>
#include <stdexcept>

// 抽象父類別
class BaseJob
{
private:
    int *data; // 主要資料 (Class Resource)
    size_t size;

public:
    BaseJob(size_t s) : size(s), data(new int[s])
    {
        std::cout << "Job Constructed\n";
    }

    // --- 任務 1: Rule of Three ---
    // TODO: 實作 Copy Constructor (Deep Copy)
    // BaseJob(const BaseJob& other) ...
    BaseJob(const BaseJob &other) : size(other.size), data(new int[other.size])
    {
        for (size_t i = 0; i < this->size; ++i)
        {
            this->data[i] = other.data[i];
        }
    }

    // TODO: 實作 Destructor
    // ~BaseJob() ...
    ~BaseJob()
    {
        delete[] this->data;
    }

    // --- 任務 2 & 3: Template Method & Exception Safety ---
    // 這是一個樣板方法，負責建立暫存區 -> 處理 -> 刪除暫存區
    // TODO A: 加入關鍵字，禁止子類別 override 這個函式
    virtual void execute() final
    {
        std::cout << "Starting execution...\n";

        // 危險！這裡配置了一個「區域性」的動態記憶體
        int *tempBuffer = new int[100];

        try
        {
            // 呼叫子類別實作的步驟
            stepProcess(tempBuffer);
        }
        catch (...)
        {
            // TODO B: 如果 stepProcess 爆了，tempBuffer 會洩漏！
            delete[] tempBuffer;
            std::cout << "Execution finished with exception, but memory is cleaned.\n";
            throw;
        }

        // 正常結束後的清理
        delete[] tempBuffer;
        std::cout << "Execution finished safely.\n";
    }

protected:
    // 純虛擬函式，強迫子類別實作
    virtual void stepProcess(int *tempBuf) = 0;

    // 讓子類別可以存取 data 的 helper
    int &getData(size_t i) { return data[i]; }
    size_t getSize() const { return size; }
};

// 子類別 (模擬會出錯的實作)
class MyJob : public BaseJob
{
public:
    using BaseJob::BaseJob; // 使用父類別建構子

    void stepProcess(int *tempBuf) override
    {
        std::cout << "Processing step...\n";
        // 模擬發生例外
        throw std::runtime_error("Calculation Error!");
    }
};

int main()
{
    try
    {
        MyJob job1(10);
        // 測試 Copy Constructor
        MyJob job2 = job1;

        // 測試 Exception Handling
        job2.execute();
    }
    catch (const std::exception &e)
    {
        std::cout << "Caught in main: " << e.what() << "\n";
    }
    return 0;
}