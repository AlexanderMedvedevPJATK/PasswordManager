#include <iostream>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <random>

using std::cout, std::cin;

void addPassword(std::ofstream &file) {
    cout << "Password name: ";

    auto name = std::string();
    cin >> name;
    file << "\n" + name + " ";

    cout << "Enter 1 to enter your own password, 2 to generate a random one: ";
    auto answer = int();
    cin >> answer;

    auto password = std::string();
    switch (answer) {
        case 1:
            cout << "Password: ";
            cin >> password;
            file << password + " ";
            break;
        case 2:
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
            std::uniform_int_distribution<int>lowercase(97, 122);
            std::uniform_int_distribution<int>uppercase(65, 90);
            std::uniform_int_distribution<int>special(35, 38);
            std::uniform_int_distribution<int>typeOfChar(1, 3);

            for (int i = 0; i < length; ++i) {
                switch (typeOfChar(rd)) {
                    case 1:
                        if(letters == 'L' || letters == 'B') {
                            password += (char) lowercase(rd);
                            break;
                        }
                    case 2:
                        if(letters == 'U' || letters == 'B') {
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
    }

    cout << "Category: ";

    auto category = std::string();
    cin >> category;
    file << category + "\n";
}

int main() {
    for (int i = 0; i < 256; ++i) {
        cout << i << " " << (char) i << std::endl;
    }
//    cout << "Enter the name of the file: ";
//    auto path = std::string();

//    cin >> path;

//    if(!std::filesystem::exists(path)) {
//        cout << "Let's create a password for this new file: ";
//        auto file = std::ofstream(path, std::ios::app);
//
//    }

    auto file = std::ofstream("password.txt", std::ios::app);

    addPassword(file);

    return 0;
}
