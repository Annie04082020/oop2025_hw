#include <iostream>
#include <stdexcept>

void dangerousOperation()
{
    std::cout << "Danger comes!\n";
    throw std::runtime_error("Something went wrong!");
}

void functionB()
{
    int *ptr = new int(42);
    std::cout << "Allocated memory.\n";

    try
    {
        dangerousOperation();
        // 如果上面爆了，這行不會執行
        std::cout << "This line will be skipped.\n";
    }
    catch (...)
    {
        // TODO: 這裡要做什麼補救措施？
        std::cout << "Caught exception inside functionB, cleaning up...\n";
        // 有例外的補刪
        delete ptr;
        std::cout << "Freed memory normally.\n";
        throw; // 重新拋出例外給 main 處理
    }

    // 如果沒有例外，這行會執行；但如果有例外，這行會被跳過嗎？
    // 正常執行的刪除
    delete ptr;
    std::cout << "Freed memory normally.\n";
}

int main_exp()
{
    try
    {
        functionB();
    }
    catch (const std::exception &e)
    {
        std::cout << "Caught in main: " << e.what() << std::endl;
    }
    return 0;
}