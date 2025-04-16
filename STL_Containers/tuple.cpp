#include <iostream>
#include <tuple>
#include <string>

// Function returning a tuple
std::tuple<int, std::string, double> getUserData() {
    int id = 101;
    std::string name = "Alice";
    double balance = 2450.75;

    return std::make_tuple(id, name, balance);
}

int main() {
    // Creating a tuple manually
    std::tuple<int, std::string, double> user(100, "Bob", 1500.50);

    // Accessing tuple elements using std::get
    std::cout << "User ID: " << std::get<0>(user) << '\n';
    std::cout << "User Name: " << std::get<1>(user) << '\n';
    std::cout << "Balance: $" << std::get<2>(user) << '\n';

    // Modifying tuple elements
    std::get<1>(user) = "Robert";
    std::cout << "Updated Name: " << std::get<1>(user) << '\n';

    // Using a tuple returned from a function
    auto userData = getUserData();

    // Structured binding (C++17)
    auto [uid, uname, ubalance] = userData;

    std::cout << "\nFrom getUserData():\n";
    std::cout << "ID: " << uid << "\nName: " << uname << "\nBalance: $" << ubalance << '\n';

    return 0;
}
