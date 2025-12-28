#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

// 抽象基底類別 (類似你的 Shape 或 Transaction)
class Command
{
public:
    virtual void execute() = 0;
    virtual Command *clone() const = 0; // 支援 Deep Copy 的關鍵
    virtual ~Command() {}
};

// 子類別 A
class PrintCmd : public Command
{
    std::string msg;

public:
    PrintCmd(std::string m) : msg(m) {}
    void execute() override { std::cout << "Print: " << msg << "\n"; }
    // 實作 clone 讓外面可以複製我
    Command *clone() const override { return new PrintCmd(msg); }
};

// 子類別 B
class CalculateCmd : public Command
{
    int val;

public:
    CalculateCmd(int v) : val(v) {}
    void execute() override { std::cout << "Calc: " << val * 2 << "\n"; }
    Command *clone() const override { return new CalculateCmd(val); }
};

// --- 核心類別：命令佇列 ---
class CommandQueue
{
private:
    std::vector<Command *> queue; // 就像 BankAccount::history

public:
    CommandQueue() {}

    // TODO 1: 實作 Destructor
    // 提示：參考 BankAccount::~BankAccount (L48-55)
    ~CommandQueue()
    {
        for (auto cmd : queue)
        {
            delete cmd;
        }
    } // TODO 2: 實作 Copy Constructor (Deep Copy)
    // 提示：參考 BankAccount::BankAccount (L18-25)
    // 注意：不能直接 copy pointer，要利用 other_cmd->clone()
    CommandQueue(const CommandQueue &other)
    {
        for (int i = 0; i < other.queue.size(); ++i)
        {
            // this->queue.push_back(other.queue[i]->clone());
            // Deep copy, since the queue holds pointers
            if (other.queue[i])
            { // 檢查非空是好習慣
                this->queue.push_back(other.queue[i]->clone());
            }
        }
    }

    // 支援加入命令
    void add(Command *cmd)
    {
        queue.push_back(cmd);
    }

    // 執行所有命令
    void runAll()
    {
        for (auto cmd : queue)
            cmd->execute();
    }
};

// --- 全域 Helper 函式 ---
// 模擬從字串建立命令 (工廠模式)
Command *createCommand(const std::string &type)
{
    if (type == "print")
        return new PrintCmd("Hello");
    if (type == "calc")
        return new CalculateCmd(10);
    if (type == "error")
        throw std::runtime_error("Unknown Command!");
    return nullptr;
}

// TODO 3: 實作 Exception Safe 的批次載入
// 提示：參考 geo_utils.cpp (L15-66) 的寫法
// 這裡模擬一次讀入三個指令，放入 raw vector，最後才交給 CommandQueue
std::vector<Command *> loadBatch(const std::vector<std::string> &inputs)
{
    std::vector<Command *> temp_cmds;

    try
    {
        for (const auto &type : inputs)
        {
            // 嘗試建立並加入 temp_cmds
            temp_cmds.push_back(createCommand(type));
        }
    }
    catch (...)
    {
        // 萬一 inputs = {"print", "print", "error"}
        // 這邊是看103行的變數
        // 前兩個 print 已經 new 了，必須在這裡刪除它們！
        for (const auto cmd : temp_cmds)
        {
            delete cmd;
        }
        temp_cmds.clear();
        std::cout << "Cleaned up partial commands due to error.\n";
        throw; // 繼續往外丟
    }
    return temp_cmds;
}
int main_poly()
{
    try
    {
        // 測試 1: 正常的載入與 Deep Copy
        std::vector<std::string> inputs1 = {"print", "calc"};
        CommandQueue q1;
        std::vector<Command *> cmds = loadBatch(inputs1);
        for (auto c : cmds)
            q1.add(c);

        CommandQueue q2 = q1; // 觸發 Copy Constructor
        std::cout << "q1 run:\n";
        q1.runAll();
        std::cout << "q2 run:\n";
        q2.runAll();

        // 測試 2: 例外與記憶體洩漏
        std::cout << "Testing Exception...\n";
        std::vector<std::string> inputs2 = {"print", "error", "calc"};
        loadBatch(inputs2); // 這裡應該爆掉，但不能 memory leak
    }
    catch (const std::exception &e)
    {
        std::cout << "Caught: " << e.what() << "\n";
    }
    return 0;
}
