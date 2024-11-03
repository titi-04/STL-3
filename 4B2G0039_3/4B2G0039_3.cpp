// 4B2G0039_3.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。

#include <iostream>
#include <list>
#include <forward_list>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

// 定義圖書結構
struct Book {
    std::string title;  // 書名
    std::string author; // 作者
    std::string id;     // 圖書編號

    // 定義小於運算符，用於圖書排序
    bool operator<(const Book& other) const {
        return id < other.id;
    }
};

// 定義借閱者結構
struct Borrower {
    std::string name;                // 姓名
    std::vector<std::string> bookIds; // 借閱的圖書圖書編號列表
};

// 驗證圖書編號是否合法
bool isValidId(const std::string& id) {
    if (id.size() != 5 || !std::isalpha(id[0])) return false;
    for (size_t i = 1; i < id.size(); ++i) {
        if (!std::isdigit(id[i])) return false;
    }
    return true;
}

// 添加新圖書
void addBook(std::list<Book>& books) {
    Book book;
    std::cout << "書名: ";
    std::getline(std::cin, book.title);
    std::cout << "作者: ";
    std::getline(std::cin, book.author);
    do {
        std::cout << "圖書編號 (1 letter followed by 4 digits): ";
        std::getline(std::cin, book.id);
        if (!isValidId(book.id)) {
            std::cout << "無效的圖書編號格式。請再試一次。\n";
        }
    } while (!isValidId(book.id));
    books.push_back(book);
    std::cout << "圖書添加成功。\n";
}

// 刪除指定圖書編號的圖書
void deleteBook(std::list<Book>& books) {
    std::string id;
    std::cout << "輸入要刪除的圖書編號: ";
    std::getline(std::cin, id);
    auto it = std::find_if(books.begin(), books.end(), [&id](const Book& book) {
        return book.id == id;
        });
    if (it != books.end()) {
        books.erase(it);
        std::cout << "圖書刪除成功。\n";
    }
    else {
        std::cout << "未找到圖書。\n";
    }
}

// 搜索指定圖書編號的圖書
void searchBook(const std::list<Book>& books) {
    std::string id;
    std::cout << "輸入要搜索的圖書編號: ";
    std::getline(std::cin, id);
    auto it = std::find_if(books.begin(), books.end(), [&id](const Book& book) {
        return book.id == id;
        });
    if (it != books.end()) {
        std::cout << "找到圖書:\n";
        std::cout << "書名: " << it->title << "  作者: " << it->author << "  圖書編號: " << it->id << "\n";
    }
    else {
        std::cout << "未找到圖書。\n";
    }
}

// 依照圖書編號排序列出所有圖書
#include <iomanip> // for std::setw

void listBooks(std::list<Book>& books) {
    books.sort();
    std::cout << "列出所有圖書:\n\n";
    std::cout << std::left << std::setw(10) << "圖書編號"
        << std::setw(20) << "書名"
        << std::setw(20) << "作者" << "\n";
    std::cout << "---------------------------------------------\n";
    for (const auto& book : books) {
        std::cout << std::left << std::setw(10) << book.id
            << std::setw(20) << book.title
            << std::setw(20) << book.author << "\n";
    }
}

// 添加新借閱者
void addBorrower(std::forward_list<Borrower>& borrowers) {
    Borrower borrower;
    std::cout << "輸入借閱者姓名: ";
    std::getline(std::cin, borrower.name);

    std::string bookId;
    std::cout << "輸入借閱的圖書編號 (輸入 'done' 結束): ";
    while (true) {
        std::getline(std::cin, bookId);
        if (bookId == "done") {
            break;
        }
        if (isValidId(bookId)) {
            borrower.bookIds.push_back(bookId);
        }
        else {
            std::cout << "無效的圖書編號格式。請再試一次。\n";
        }
        std::cout << "輸入借閱的圖書編號 (輸入 'done' 結束): ";
    }

    borrowers.push_front(borrower);
    std::cout << "借閱者添加成功。\n";
}


// 刪除指定姓名的借閱者
void deleteBorrower(std::forward_list<Borrower>& borrowers) {
    std::string name;
    std::cout << "輸入要刪除的借閱者姓名: ";
    std::getline(std::cin, name);
    borrowers.remove_if([&name](const Borrower& borrower) {
        return borrower.name == name;
        });
    std::cout << "借閱者刪除成功。\n";
}

// 搜索指定姓名的借閱者
void searchBorrower(const std::forward_list<Borrower>& borrowers) {
    std::string name;
    std::cout << "輸入要搜索的借閱者姓名: ";
    std::getline(std::cin, name);
    auto it = std::find_if(borrowers.begin(), borrowers.end(), [&name](const Borrower& borrower) {
        return borrower.name == name;
        });
    if (it != borrowers.end()) {
        std::cout << "找到借閱者: " << it->name << "\n";
        std::cout << "借閱的圖書: ";
        for (const auto& id : it->bookIds) {
            std::cout << id << " ";
        }
        std::cout << "\n";
    }
    else {
        std::cout << "未找到借閱者。\n";
    }
}

// 列出所有借閱者及其借閱的圖書
#include <iomanip> // for std::setw

void listBorrowers(const std::forward_list<Borrower>& borrowers) {
    std::cout << "列出所有借閱者:\n\n";
    std::cout << std::left << std::setw(20) << "借閱者姓名"
        << "借閱的圖書編號" << "\n";
    std::cout << "---------------------------------------------\n";
    for (const auto& borrower : borrowers) {
        std::cout << std::left << std::setw(20) << borrower.name;
        for (const auto& id : borrower.bookIds) {
            std::cout << id << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    std::list<Book> books = {
        {"紅樓夢",     "曹雪芹",     "A1234"},
        {"西遊記",     "吳承恩",     "B2345"},
        {"水滸傳",     "施耐庵",     "B3456"},
        {"三國演義",   "羅貫中",     "C4567"},
        {"金瓶梅",     "蘭陵笑笑生", "C5678"},
        {"聊齋志異",   "蒲松齡",     "D6789"},
        {"儒林外史",   "吳敬梓",     "D7890"},
        {"封神演義",   "許仲琳",     "E8901"},
        {"鏡花緣",     "李汝珍",     "E9012"},
        {"老殘遊記",   "劉鶚",       "F0123"}
    };

    std::forward_list<Borrower> borrowers = {
        {"小明", {"A1234", "B2345"}},
        {"小華", {"C4567"}},
        {"小美", {"D6789", "E8901"}},
        {"小強", {"F0123"}},
        {"小麗", {"B3456", "C5678"}}
    };

    int choice;

    do {
        std::cout << "圖書館管理系統\n";
        std::cout << "1. 添加新圖書\n";
        std::cout << "2. 刪除指定圖書編號的圖書\n";
        std::cout << "3. 搜索指定圖書編號的圖書\n";
        std::cout << "4. 依照圖書編號排序列出所有圖書\n";
        std::cout << "5. 添加新借閱者\n";
        std::cout << "6. 刪除指定姓名的借閱者\n";
        std::cout << "7. 搜索指定姓名的借閱者\n";
        std::cout << "8. 列出所有借閱者及其借閱的圖書\n";
        std::cout << "9. 退出\n\n";
        std::cout << "選擇你需要的資訊: ";
        std::cin >> choice;
        std::cin.ignore(); // 忽略換行符

        switch (choice) {
        case 1:
            addBook(books);
            break;
        case 2:
            deleteBook(books);
            break;
        case 3:
            searchBook(books);
            break;
        case 4:
            listBooks(books);
            break;
        case 5:
            addBorrower(borrowers);
            break;
        case 6:
            deleteBorrower(borrowers);
            break;
        case 7:
            searchBorrower(borrowers);
            break;
        case 8:
            listBorrowers(borrowers);
            break;
        case 9:
            std::cout << "退出...\n";
            break;
        default:
            std::cout << "無效的選擇。請再試一次。\n";
        }
    } while (choice != 9);

    return 0;
}
