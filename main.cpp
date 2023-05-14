#include <random>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <cctype>
#include <regex>

using std::cout, std::cin, std::endl;

void trim(std::string& str) {
    const auto trailingSpaces = str.find_last_not_of(" \t\r\n");

    if (trailingSpaces != std::string::npos) {
        str.erase(trailingSpaces + 1);
    } else {
        str.erase();
    }
}

void fillCategories(std::string const& path, std::vector<std::string>& categories) {
    auto file = std::ifstream(path, std::ios::in);

    for (auto line = std::string(); std::getline(file, line); ) {
        auto word = std::string();
        auto stream = std::stringstream(line);

        std::regex regex("\\x02");

        auto lineSplit = std::vector<std::string>
                (std::sregex_token_iterator(line.begin(), line.end(), regex, -1),
                 std::sregex_token_iterator());

        for (int i = 2; i < lineSplit.size(); i += 3) {
            if(std::ranges::find(categories, lineSplit[i]) == categories.end())
                categories.push_back(lineSplit[i]);
        }
    }
}

std::string addCategory(std::vector<std::string>& categories) {
    cout << "Enter category name: ";
    auto name = std::string();
    std::getline(cin >> std::ws, name);

    categories.push_back(name);
    return name;
}

void printCategories(std::vector<std::string>& categories) {
    for (int i = 0; i < categories.size(); ++i) {
        cout << i + 1 << ". " << categories[i] << endl;
    }
}

void deleteCategory(std::vector<std::string>& categories) {
    cout << "Choose a category from the list to delete: " << endl;
    printCategories(categories);
}

// TODO Introduce password complexity check
void addPassword(std::string const& path, std::vector<std::string>& categories) {

    auto file = std::ofstream(path, std::ios::app);

    cout << "Password name: ";

    auto name = std::string();
    std::getline(cin, name);
    trim(name);
    file << "\n" + name + (char) 2; // (char) 2 is used as a random character to split a line

    for (auto answer = int(); answer != 1 && answer != 2;) {
        cout << "Enter 1 to enter your own password, 2 to generate a random one: ";
        cin >> answer;

        auto password = std::string();
        switch (answer) {
            case 1:
                cout << "Password: ";
                cin >> password;
                trim(password);
                file << password + (char) 2;
                break;
            case 2:
            {
                cout << "Enter password length: ";
                auto length = int();
                cin >> length;

                cout << "Lowercase or uppercase letters? L for lower, U for upper, B for both: ";
                auto letters = char();
                cin >> letters;
                letters = (char)std::toupper(letters);

                cout << "Include special characters? Y for yes, N for no: ";
                auto specialChars = char();
                cin >> specialChars;
                specialChars = (char)std::toupper(specialChars);

                std::random_device rd;
                std::uniform_int_distribution<int> lowercase(97, 122);
                std::uniform_int_distribution<int> uppercase(65, 90);
                std::uniform_int_distribution<int> special(35, 38);

                int low;
                int high;
                if (letters == 'L' && specialChars == 'N') {
                    high = low = 1;
                } else if (letters == 'L' && specialChars == 'Y') {
                    for (int i = 0; i < length; ++i) {
                        std::uniform_int_distribution<int>typeOfChar(1, 2);
                        switch (typeOfChar(rd)) {
                            case 1:
                                password += (char) lowercase(rd);
                            case 2:
                                password += (char) special(rd);
                        }
                    }
                } else if (letters == 'U' && specialChars == 'N') {
                    high = low = 2;
                } else if (letters == 'U' && specialChars == 'Y') {
                    low = 2;
                    high = 3;
                } else if (letters == 'B' && specialChars == 'N') {
                    low = 1;
                    high = 2;
                } else if (letters == 'B' && specialChars == 'Y') {
                    low = 1;
                    high = 3;
                }
//                for (int i = 0; i < length; ++i) {
//                    switch (typeOfChar(rd)) {
//                        case 1:
//                            if (letters == 'L' || letters == 'B') {
//                                password += (char) lowercase(rd);
//                                break;
//                            }
//                        case 2:
//                            if (letters == 'U' || letters == 'B') {
//                                password += (char) uppercase(rd);
//                                break;
//                            }
//                        case 3:
//                            if (specialChars == 'Y') {
//                                password += (char) special(rd);
//                            }
//                    }
//                }
//
//                if(letters == 'L') {
//                    if(specialChars == 'Y') {
//                        for (int i = 0; i < length; ++i) {
//                            std::uniform_int_distribution<int> typeOfChar(1, 2);
//                            switch (typeOfChar(rd)) {
//                                case 1:
//                                    password += (char) lowercase(rd);
//                                case 2:
//                                    password += (char) special(rd);
//                            }
//                        }
//                    } else {
//                        for (int i = 0; i < length; ++i) {
//                            password += (char)lowercase(rd);
//                        }
//                    }
//                } else if (letters == 'U') {
//                    if(specialChars == 'Y') {
//                        for (int i = 0; i < length; ++i) {
//                            std::uniform_int_distribution<int> typeOfChar(1, 2);
//                            switch (typeOfChar(rd)) {
//                                case 1:
//                                    password += (char) uppercase(rd);
//                                case 2:
//                                    password += (char) special(rd);
//                            }
//                        }
//                    } else {
//                        for (int i = 0; i < length; ++i) {
//                            password += (char)uppercase(rd);
//                        }
//                    }
//                } else {
//                    if (specialChars == 'Y') {
//                        std::uniform_int_distribution<int> typeOfChar(1, 3);
//                        switch (typeOfChar(rd)) {
//                            case 1:
//                                password += (char) lowercase(rd);
//                            case 2:
//                                password += (char) uppercase(rd);
//                            case 3:
//                                password += (char) special(rd);
//                        }
//                    } else {
//                        std::uniform_int_distribution<int> typeOfChar(1, 3);
//
//                        switch (typeOfChar(rd)) {
//                            case 1:
//                                password += (char) lowercase(rd);
//                            case 2:
//                                password += (char) uppercase(rd);
//                        }
//                    }
//                }

                std::uniform_int_distribution<int> typeOfChar(low, high);
                for (int i = 0; i < length && (letters != 'L' || specialChars != 'Y'); ++i) {
                    switch (typeOfChar(rd)) {
                        case 1:
                            password += (char) lowercase(rd);
                            break;
                        case 2:
                            password += (char) uppercase(rd);
                            break;
                        case 3:
                            password += (char) special(rd);
                    }
                }


                cout << "Your password is " << password << endl;
                file << password + (char) 2;
                break;
            }
            default:
                cout << "Invalid input!";
                break;
        }
    }

    if(categories.empty()) {
        cout << "You don't have any categories for your passwords, let's create a new one." << endl;
        addCategory(categories);

        file << *categories.begin();
    } else {
        auto answer = int();
        while (answer != 1 && answer != 2) {
            cout << "To choose an existing category enter 1, to create a new one enter 2: ";
            cin >> answer;
            switch (answer) {
                case 1: {
                    cout << "Enter category number: " << endl;
                    printCategories(categories);
                    auto category = int();
                    cin >> category;

                    file << categories[category - 1];
                    break;
                }
                case 2:
                    file << addCategory(categories);
                    break;
                default:
                    cout << "Invalid input!";
            }
        }
    }
}

bool searchPassword(std::string const& path) {

    auto file = std::ifstream(path, std::ios::in);

    cout << "Enter a keyword to search for: ";
    auto searchFor = std::string();
    cin >> searchFor;

    bool found = false;
    for (auto line = std::string(); std::getline(file, line); ) {
        auto word = std::string();
        auto stream = std::stringstream(line);
        while (stream >> word) {
            if (word.find(searchFor) != std::string::npos) {
                size_t pos = 0;
                while((pos = line.find((char) 2, pos)) != std::string::npos) {
                    line.replace(pos, 1, " ");
                }
                cout << line << endl;
                found = true;
            }
        }
    }
    if(!found){
        cout << "Not found";
        return false;
    }
    return true;
}

void sortPasswords(std::string const& path) {
    auto file = std::ifstream(path, std::ios::in);

    auto passwordsTable = std::vector<std::vector<std::string>>();

    int i = 0;
    for (auto line = std::string(); std::getline(file, line); ++i) {
        if(line.length() == 0) continue;

        auto word = std::string();
        auto stream = std::stringstream(line);

        passwordsTable.emplace_back();
        for (int counter = 0; stream >> word; ++counter) {
            passwordsTable.back().push_back(word);
        }
    }

    auto answer = int();
    while (answer != 1 && answer != 2) {
        cout << "Type 1 to sort by name, type 2 to sort by category: ";
        cin >> answer;

        switch (answer) {
            case 1:
                std::ranges::sort(passwordsTable, [](auto a, auto b) {
                    if(a[0] == b[0]) return a[2] < b[2];
                    return a[0] < b[0];
                });
            case 2:
                std::ranges::sort(passwordsTable, [](auto a, auto b) {
                    if(a[2] == b[2]) return a[0] < b[0];
                    return a[2] < b[2];
                });
            default:
                cout << "Invalid input!";
        }
    }

    for (auto const& j : passwordsTable) {
        fmt::print("{}\n", j);
    }
}

int main() {
    auto categories = std::vector<std::string>();
    fillCategories("password.txt", categories);
    printCategories(categories);

    sortPasswords("password.txt");

    return 0;
}



//    for (int i = 0; i < 256; ++i) {
//        cout << i << " " << (char) i << endl;
//    }
//
//    cout << "Enter the name of the file: ";
//    auto path = std::string();
//
//    cin >> path;
//
//    if(!std::filesystem::exists(path)) {
//        cout << "Let's create a password for this new file: ";
//        auto file = std::ofstream(path, std::ios::app);
//
//    }