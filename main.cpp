#include <random>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>

using std::cout, std::cin;

// TODO Introduce password complexity check
void addPassword(std::string const& path) {

    auto file = std::ofstream(path, std::ios::app);

    cout << "Password name: ";

    auto name = std::string();
    cin >> name;
    file << "\n" + name + " ";

    for (auto answer = int(); answer != 1 && answer != 2;) {
        cout << "Enter 1 to enter your own password, 2 to generate a random one: ";
        cin >> answer;

        auto password = std::string();
        switch (answer) {
            case 1:
                cout << "Password: ";
                cin >> password;
                file << password + " ";
                break;
            case 2:
            {
                cout << "Enter password length: ";
                auto length = int();
                cin >> length;

                cout << "Lowercase or uppercase letters? L for lower, U for upper, B for both: ";
                auto letters = char();
                cin >> letters;

                cout << "Include special characters? Y for yes, N for no: ";
                auto specialChars = char();
                cin >> specialChars;

                std::random_device rd;
                std::uniform_int_distribution<int> lowercase(97, 122);
                std::uniform_int_distribution<int> uppercase(65, 90);
                std::uniform_int_distribution<int> special(35, 38);
                std::uniform_int_distribution<int> typeOfChar(1, 3);

                for (int i = 0; i < length; ++i) {
                    switch (typeOfChar(rd)) {
                        case 1:
                            if (letters == 'L' || letters == 'B') {
                                password += (char) lowercase(rd);
                                break;
                            }
                        case 2:
                            if (letters == 'U' || letters == 'B') {
                                password += (char) uppercase(rd);
                                break;
                            }
                        case 3:
                            if (specialChars == 'Y') {
                                password += (char) special(rd);
                            }
                    }
                }
                file << password + " ";
                break;
            }
            default:
                cout << "Wrong input!";
                break;
        }
    }

    cout << "Category: ";

    auto category = std::string();
    cin >> category;
    file << category + "\n";
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
                cout << line;
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

    for (int j = 0; j < passwordsTable.size(); ++j) {
        fmt::print("{}\n", passwordsTable[j]);
    }
}

int main() {
    sortPasswords("password.txt");

    return 0;
}



//    for (int i = 0; i < 256; ++i) {
//        cout << i << " " << (char) i << std::endl;
//    }

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