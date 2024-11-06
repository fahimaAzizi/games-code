#include <iostream>
#include <string>

bool login() {
    std::string usernameOrEmail;
    std::string password;

    // Hardcoded credentials (for demonstration purposes)
    const std::string correctUsernameOrEmail = "user@example.com";
    const std::string correctPassword = "password123";

    // Prompt user to enter their name or email
    std::cout << "Enter your username or email: ";
    std::cin >> usernameOrEmail;

    // Prompt user to enter their password
    std::cout << "Enter your password: ";
    std::cin >> password;

    // Validate the credentials
    if (usernameOrEmail == correctUsernameOrEmail && password == correctPassword) {
        std::cout << "Login successful! Welcome, " << usernameOrEmail << "!\n";
        return true;
    } else {
        std::cout << "Invalid username/email or password. Please try again.\n";
        return false;
    }
}

int main() {
    bool isLoggedIn = false;

    // Keep prompting the user until they enter the correct credentials
    while (!isLoggedIn) {
        isLoggedIn = login();
    }

    // The user has logged in successfully
    std::cout << "You are now logged in.\n";

    return 0;
}
