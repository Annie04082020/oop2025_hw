#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <filesystem>
#include "book.h"
#include "ebook.h"
#include "reference_book.h"
#include "library_item.h"
#include "library_management_system.h"

LibraryManagementSystem::LibraryManagementSystem() {};

void LibraryManagementSystem::add_item(LibraryItem *item)
{
    library.push_back(item);
};
bool LibraryManagementSystem::remove_item(long id)
{
    std::vector<LibraryItem *>::iterator rmv_item = std::find_if(library.begin(), library.end(),
                                                                 [id](LibraryItem *item)
                                                                 { return item != nullptr && item->get_unique_id() == id; });
    if (rmv_item != library.end())
    {
        library.erase(rmv_item);
        return true;
    };
    return false;
};
std::vector<LibraryItem *> LibraryManagementSystem::search_by_title(std::string title)
{
    std::vector<LibraryItem *> result;
    std::string search_title = title;
    std::transform(search_title.begin(), search_title.end(), search_title.begin(), ::tolower);
    for (auto item : library)
    {
        std::string item_title = item->get_title();
        std::transform(item_title.begin(), item_title.end(), item_title.begin(), ::tolower);
        if (item_title.find(search_title) != std::string::npos)
        {
            result.push_back(item);
        };
    }
    return result;
};
std::vector<LibraryItem *> LibraryManagementSystem::search_by_author(std::string author)
{
    std::vector<LibraryItem *> result;
    std::string search_author = author;
    std::transform(search_author.begin(), search_author.end(), search_author.begin(), ::tolower);
    for (auto item : library)
    {
        std::string item_author = item->get_author();
        std::transform(item_author.begin(), item_author.end(), item_author.begin(), ::tolower);
        if (item_author.find(search_author) != std::string::npos)
        {
            result.push_back(item);
        };
    }
    return result;
};

int LibraryManagementSystem::get_total_items()
{
    return library.size();
};
void LibraryManagementSystem::save_to_file(const std::filesystem::path &output_path)
{
    std::ofstream output_file(output_path);
    if (!output_file.is_open())
    {
        throw std::runtime_error("Could not open file for writing: " + output_path.string());
        return;
    }
    for (const auto &item : library)
    {
        if (item)
        {
            output_file << item->get_unique_id() << ","
                        << item->get_type() << ","     // 取得類型
                        << item->get_title() << ","    // 取得標題
                        << item->get_author() << "\n"; // 取得作者，並換行
        }
    }
};
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
            throw std::runtime_error("Warning: Skipping malformed line (Wrong field count): " + line);
            continue;
        }
        LibraryItem *new_item = nullptr;
        long unique_id = 0;
        try
        {
            // 欄位 0: unique_id
            unique_id = std::stoll(parts[0]);
            // 欄位 1: type
            const std::string &type = parts[1];
            // 欄位 2: title
            const std::string &title = parts[2];
            // 欄位 3: author
            const std::string &author = parts[3];
            // 步驟 6: 根據 Type 實例化正確的子類別 (多型)
            if (type == "Book")
            { // 注意：如果檔案讀取時 type 前有空格，需要處理
                new_item = new Book(unique_id, title, author);
            }
            else if (type == "ReferenceBook")
            {
                new_item = new ReferenceBook(unique_id, title, author);
            }
            else if (type == "EBook")
            {
                new_item = new EBook(unique_id, title, author);
            }
            else
            {
                throw std::runtime_error("Warning: Skipping malformed line (Unknown type): " + line);
                continue;
            }
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Warning: Skipping malformed line (Exception): " + line + "-" + e.what());
            continue;
        }
        if (new_item != nullptr)
        {
            this->add_item(new_item);
        }
    }
};
void LibraryManagementSystem::clear()
{
    library.clear();
};