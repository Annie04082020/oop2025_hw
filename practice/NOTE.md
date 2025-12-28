# C++ 期末考試小抄

## 📋 核心概念檢查清單

### Rule of Three 必檢項目
```cpp
// 1. Copy Constructor - 記得檢查是否正確複製動態配置的記憶體
BankAccount(const BankAccount &other) {
    // 檢查：是否有深層複製？還是只複製指標？
    this->history.push_back(new Transaction(*other_history)); // ✅ 深層複製
}

// 2. Copy Assignment Operator - 記得檢查自我賦值和記憶體清理
BankAccount &operator=(const BankAccount &other) {
    if (this != &other) { // ✅ 自我賦值檢查
        // 檢查：是否先釋放舊記憶體？
        for (Transaction *p : this->history) delete p; // ✅ 清理舊記憶體
    }
}

// 3. Destructor - 記得檢查是否釋放所有動態配置的記憶體
~BankAccount() {
    for (Transaction *p : history) delete p; // ✅ 釋放所有
    history.clear(); // ✅ 清空容器
}
``` [1](#1-0) 

### Template 函式實作要點
```cpp
// 檢查：template 語法是否正確？
template <typename RandomIt>
void bubble_sort(RandomIt first, RandomIt last) {
    // 檢查：邊界條件
    if (first == last) return;
    
    // 檢查：迭代器使用是否正確？
    for (auto it = first; it != last - 1; it++) {
        if (*it > *(it + 1)) {
            std::swap(*it, *(it + 1));
        }
    }
}

// 檢查：自定義比較器版本
template <typename RandomIt, typename Compare>
void bubble_sort(RandomIt first, RandomIt last, Compare comp) {
    // 檢查：比較器的使用方式
    if (comp(*(it + 1), *it)) { // 注意參數順序
        std::swap(*it, *(it + 1));
    }
}
``` [2](#1-1) 

### Exception Handling 檢查
```cpp
// 檢查：throw 的時機和訊息
void deposit(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Must deposit a positive amount."); // ✅ 明確錯誤訊息
    }
}

// 檢查：catch 的處理方式
try {
    account.deposit(-100);
    FAIL() << "Expected std::invalid_argument"; // 測試用
} catch (const std::invalid_argument &e) {
    EXPECT_STREQ(e.what(), "Must deposit a positive amount."); // ✅ 檢查錯誤訊息
}
``` [3](#1-2) 

## 🐛 常見錯誤和Debug要點

### 記憶體管理錯誤
```cpp
// ❌ 錯誤：淺層複製導致雙重釋放
history = other.history; // 只複製指標，不是物件

// ✅ 正確：深層複製
for (const Transaction* other_tx : other.history) {
    this->history.push_back(new Transaction(*other_tx));
}

// ❌ 錯誤：忘記檢查自我賦值
*this = other; // 可能導致自我破壞

// ✅ 正確：檢查自我賦值
if (this != &other) { /* 賦值邏輯 */ }
``` [4](#1-3) 

### Polymorphism 錯誤
```cpp
// ❌ 錯誤：物件切片
Shape s = Circle(); // 失去多型特性

// ✅ 正確：使用指標或參考
Shape* ptr = new Circle(); // 保持多型
Shape& ref = circle_obj;   // 保持多型

// 檢查：虛擬函式是否正確覆寫？
class Circle : public Shape {
public:
    double area() override { /* 實作 */ } // ✅ 使用 override
    // double area() { /* 實作 */ } // ❌ 可能拼錯而不自知
};
``` [5](#1-4) 

### File I/O 錯誤
```cpp
// 檢查：檔案是否成功開啟
std::ifstream file(path);
if (!file.is_open()) {
    throw std::runtime_error("Could not open file: " + path.string()); // ✅ 錯誤處理
}

// 檢查：CSV 解析是否處理異常情況
while (std::getline(file, line)) {
    if (line.empty()) continue; // ✅ 跳過空行
    // 檢查：欄位數量是否正確？
    if (parts.size() != expected_count) {
        std::cerr << "Warning: Malformed line: " << line << std::endl;
        continue; // ✅ 跳過格式錯誤的行
    }
}
``` [6](#1-5) 

## 🔧 重要函式簽名速查

### Banking System
```cpp
class BankAccount {
    // 建構子
    BankAccount(const std::string &owner, const std::string &bank_code);
    
    // Rule of Three
    BankAccount(const BankAccount &other);
    BankAccount &operator=(const BankAccount &other);
    ~BankAccount();
    
    // 操作
    void deposit(double amount);
    void withdraw(double amount);
    BankAccount &operator+=(double amount);
    
    // 存取函式
    long get_id() const;
    std::string get_owner() const;
    double get_balance() const;
    std::vector<Transaction*> get_history() const;
};
``` [7](#1-6) 

### Geometry System
```cpp
// 抽象基底類別
class Shape {
public:
    virtual double area() = 0;
    virtual double perimeter() = 0;
    virtual std::string to_string() = 0;
};

// 工具函式
std::vector<Shape*> read_shapes_from_file(const std::filesystem::path &filename);
void write_shapes_to_file(const std::vector<Shape*> &shapes, const std::filesystem::path &filename);
void cleanup_shapes(std::vector<Shape*> &shapes);
``` [8](#1-7) 

## 📝 考試時的Debug檢查步驟

### 1. 記憶體檢查
- [ ] 所有 `new` 都有對應的 `delete`？
- [ ] Copy constructor 做深層複製？
- [ ] Assignment operator 檢查自我賦值？
- [ ] Destructor 釋放所有動態記憶體？

### 2. Template 檢查
- [ ] `template <typename T>` 語法正確？
- [ ] 迭代器使用正確（`it != last - 1`）？
- [ ] 比較器參數順序正確？

### 3. Exception 檢查
- [ ] `throw` 在適當時機？
- [ ] 錯誤訊息明確？
- [ ] `catch` 正確處理例外類型？

### 4. Polymorphism 檢查
- [ ] 基底類別有 `virtual` 關鍵字？
- [ ] 衍生類別使用 `override`？
- [ ] 使用指標/參考保持多型？

### 5. File I/O 檢查
- [ ] 檢查檔案是否成功開啟？
- [ ] 處理空行和格式錯誤？
- [ ] 正確解析 CSV 欄位？

## ⚡ 快速參考程式碼

### Factory Pattern 範例
```cpp
Shape* create_shape_from_string(const std::string& line) {
    std::stringstream ss(line);
    std::string type;
    ss >> type;
    
    if (type == "Circle") {
        double x, y, r;
        ss >> x >> y >> r;
        return new Circle(Point(x, y), r);
    } else if (type == "Triangle") {
        // 解析三角形參數
        return new Triangle(p1, p2, p3);
    }
    return nullptr;
}
``` [9](#1-8) 

### 記憶體清理函式
```cpp
void cleanup_shapes(std::vector<Shape*> &shapes) {
    for (Shape* shape : shapes) {
        delete shape; // 釋放每個形狀
    }
    shapes.clear(); // 清空向量
}
``` [10](#1-9) 

## Notes

- 這個小抄涵蓋了 Assignment 4-7 的所有核心概念
- SharedPtr 和 DFS iterator 不在考試範圍內
- 重點放在 Rule of Three、Template、Exception、Polymorphism 和記憶體管理
- 考試時記得檢查編譯警告，通常會指出潛在問題

Wiki pages you might want to explore:
- [Home (Annie04082020/oop2025_hw)](/wiki/Annie04082020/oop2025_hw#1)
- [Banking System (Assignment 7) (Annie04082020/oop2025_hw)](/wiki/Annie04082020/oop2025_hw#2)

### Citations

**File:** assignment7/src/bank_account.cpp (L18-55)
```cpp
BankAccount::BankAccount(const BankAccount &other)
{
    this->owner = other.owner;
    this->bank_code = other.bank_code;
    this->id = id_counter++;
    this->balance = 0;
    this->history.clear();
}
// Copy Assignment Operator
BankAccount &BankAccount::operator=(const BankAccount &other)
{
    if (this != &other)
    {
        for (Transaction *p : this->history)
        {
            delete p;
        }
        this->history.clear();
        this->owner = other.owner;
        this->bank_code = other.bank_code;
        this->id = other.id;
        this->balance = other.balance;
        for (const Transaction *other_history : other.history)
        {
            this->history.push_back(new Transaction(*other_history));
        }
    }
    return *this;
}
// Destructor
BankAccount::~BankAccount()
{
    for (Transaction *p : history)
    {
        delete p;
    }
    history.clear();
}
```

**File:** assignment7/src/bank_account.cpp (L83-97)
```cpp
void BankAccount::deposit(double amount)
{
    // this->balance+=amount;
    if (amount <= 0)
    {
        throw std::invalid_argument("Must deposit a positive amount.");
    }
    else
    {
        this->balance += amount;
        static const std::string type = "Deposit";
        Transaction *deposit = new Transaction{type, amount, this->balance};
        this->history.push_back(deposit);
    };
}
```

**File:** assignment7/src/utils.h (L7-49)
```text
void bubble_sort(RandomIt first, RandomIt last)
{
    // Implementation
    if (first == last)
        return;
    bool swapped = true;
    while (swapped)
    {
        swapped = false;
        for (auto it = first; it != last - 1; it++)
        {
            // Default ascending
            if (*it > *(it + 1))
            {
                std::swap(*it, *(it + 1));
                swapped = true;
            }
        }
        last--;
    }
}

template <typename RandomIt, typename Compare>
void bubble_sort(RandomIt first, RandomIt last, Compare comp)
{
    if (first == last)
        return;
    // Implementation
    bool swapped = true;
    while (swapped)
    {
        swapped = false;
        for (auto it = first; it != last - 1; it++)
        {
            if (comp(*(it + 1), *it))
            {
                std::swap(*it, *(it + 1));
                swapped = true;
            }
        }
        last--;
    }
}
```

**File:** assignment6/tests/ut_geo_utils.cpp (L116-146)
```cpp
TEST_F(GeoIOTest, PolymorphismWithStackObjectsTest)
{
    // 1. 在「堆疊 (Stack)」上創建子類別的物件
    Circle stack_circle = circle1;
    Triangle stack_triangle = unit_triangle;
    ConvexPolygon stack_polygon = rect;

    // 2. 宣告「基底類別指標」
    Shape *ptr_to_circle;
    Shape *ptr_to_triangle;
    Shape *ptr_to_polygon;

    // 3. 將「堆疊物件的位址(&)」指派給「基底類別指標」
    //"reference assign給 BaseClass*"
    ptr_to_circle = &stack_circle;
    ptr_to_triangle = &stack_triangle;
    ptr_to_polygon = &stack_polygon;

    // 4. 透過基底類別指標，驗證虛擬函式 (virtual function) 是否能正確運作
    // 檢查 Circle
    EXPECT_EQ(ptr_to_circle->to_string(), "Circle 0.00 0.00 5.00");
    EXPECT_NEAR(ptr_to_circle->area(), circle1.area(), 1e-9);

    // 檢查 Triangle
    EXPECT_EQ(ptr_to_triangle->to_string(), "Triangle 0.00 0.00 1.00 0.00 0.00 1.00");
    EXPECT_NEAR(ptr_to_triangle->area(), unit_triangle.area(), 1e-9);

    // 檢查 ConvexPolygon
    EXPECT_EQ(ptr_to_polygon->to_string(), "ConvexPolygon 0.00 0.00 2.00 0.00 2.00 1.00 0.00 1.00");
    EXPECT_NEAR(ptr_to_polygon->area(), rect.area(), 1e-9);
}
```

**File:** assignment5/src/library_management_system.cpp (L90-115)
```cpp
void LibraryManagementSystem::load_from_file(const std::filesystem::path &input_path)
{
    this->clear();
    std::ifstream input_file(input_path);
    if (!input_file.is_open())
    {
        throw std::runtime_error("Could not open file for reading: " + input_path.string());
        return;
    };
    std::string line;
    while (std::getline(input_file, line))
    {
        if (line.empty())
            continue;
        std::stringstream ss(line);
        std::string segment;
        std::vector<std::string> parts;
        while (std::getline(ss, segment, ','))
        {
            parts.push_back(segment);
        }
        if (parts.size() != 4)
        {
            std::cerr << "Warning: Skipping malformed line (Wrong field count): " << line << std::endl;
            continue;
        }
```

**File:** assignment7/src/bank_account.h (L21-43)
```text
    // Constructor
    BankAccount(const std::string &owner, const std::string &bank_code);
    // Rule of three:
    // 1. Copy constructor
    BankAccount(const BankAccount &other);
    // 2. Copy assignment operator
    BankAccount &operator=(const BankAccount &other);
    // 3. Destructor
    ~BankAccount();
    // Overloaded operator +=,  // receive double and return address
    // operator(double amount);
    BankAccount &operator+=(double amount);

    long get_id() const;
    std::string get_owner() const;
    std::string get_bank_code() const;
    double get_balance() const;
    std::vector<Transaction *> get_history() const;

    void deposit(const double amount);
    void withdraw(const double amount);

    void export_to_csv(const std::filesystem::path &folder_path) const;
```

**File:** assignment6/src/geo_utils.h (L10-18)
```text
std::vector<Shape *> read_shapes_from_file(const std::filesystem::path &filename);

// 將形狀寫入文件的函數
void write_shapes_to_file(const std::vector<Shape *> &shapes, const std::filesystem::path &filename);

// 根據屬性和順序排序形狀的函數
void sort_shapes_by_property(std::vector<Shape *> &shapes, const std::string &property, const std::string &order);

void cleanup_shapes(std::vector<Shape *> &shapes);
```
