#include <iostream>

// 抽象父類別
class DataProcessor
{
public:
    // 1. Template Method (樣板方法)
    // TODO: 請實作 process() 函式
    // 要求 A: 依序呼叫 readData(), parseData(), saveData()
    // 要求 B: 使用 C++11 關鍵字，禁止子類別修改(override) 這個函式，確保流程固定
    virtual void process() final
    {
        readData();
        parseData();
        saveData();
        // 在此填寫邏輯
    }

    virtual ~DataProcessor() {}

protected:
    // 2. Primitive Operations (基本操作)
    // 這些是給子類別去實作的細節
    // TODO: 將這兩個宣告為「純虛擬函式 (Pure Virtual Functions)」
    virtual void readData() = 0;
    virtual void parseData() = 0;

    // Hook Method (掛鉤方法)
    // 父類別提供預設實作，子類別"可以"改寫，也可以不改
    virtual void saveData()
    {
        std::cout << "[Base] Saving data to default SQL Database.\n";
    }
};

// 子類別
class CSVProcessor : public DataProcessor
{
public:
    // TODO: 實作 CSVProcessor 必要的函式
    // 模擬讀取 CSV，並輸出 "Reading CSV file..."
    void readData() override
    {
        std::cout << "Reading CSV file...";
    }
    // 模擬解析 CSV，並輸出 "Parsing CSV data..."
    void parseData() override
    {
        std::cout << "Parsing CSV data...";
    }
};

int main_tmp()
{
    std::cout << "--- Starting CSV Processing ---\n";
    // 不能直接用 DataProcessor 因為有虛擬函數
    CSVProcessor csv;

    // 客戶端只知道呼叫 process，不需要知道內部細節
    csv.process();

    return 0;
}