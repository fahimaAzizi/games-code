#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <string>

// Character class definition
class Character {
public:
    std::string name;
    int health;
    int attackPower;
    sf::RectangleShape body;
    sf::RectangleShape head;
    sf::RectangleShape leftArm;
    sf::RectangleShape rightArm;
    sf::RectangleShape leftLeg;
    sf::RectangleShape rightLeg;

    Character(std::string name, int health, int attackPower) 
        : name(name), health(health), attackPower(attackPower) {
        // Setup character parts
        body.setSize(sf::Vector2f(40, 100));
        body.setFillColor(sf::Color::Blue);
        body.setPosition(100, 150);

        head.setSize(sf::Vector2f(50, 50));
        head.setFillColor(sf::Color::Red);
        head.setPosition(85, 100);

        leftArm.setSize(sf::Vector2f(20, 60));
        leftArm.setFillColor(sf::Color::Blue);
        leftArm.setPosition(60, 150);

        rightArm.setSize(sf::Vector2f(20, 60));
        rightArm.setFillColor(sf::Color::Blue);
        rightArm.setPosition(120, 150);

        leftLeg.setSize(sf::Vector2f(20, 60));
        leftLeg.setFillColor(sf::Color::Blue);
        leftLeg.setPosition(100, 250);

        rightLeg.setSize(sf::Vector2f(20, 60));
        rightLeg.setFillColor(sf::Color::Blue);
        rightLeg.setPosition(120, 250);
    }

    void punch(Character& opponent) {
        opponent.health -= attackPower;
        std::cout << name << " punches " << opponent.name << " causing " << attackPower << " damage!" << std::endl;
    }

    void performCombo(Character& opponent) {
        opponent.health -= attackPower * 3;  // Example combo multiplier
        std::cout << name << " performs a combo on " << opponent.name << " causing " << attackPower * 3 << " damage!" << std::endl;
    }

    void moveRightArm() {
        rightArm.move(0, -20); // Move the right arm up
        if (rightArm.getPosition().y < 130) {
            rightArm.move(0, 20); // Move it back down
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(body);
        window.draw(head);
        window.draw(leftArm);
        window.draw(rightArm);
        window.draw(leftLeg);
        window.draw(rightLeg);
    }
};

// HealthBar class definition
class HealthBar {
public:
    int maxHealth;
    int currentHealth;

    HealthBar(int maxHealth) : maxHealth(maxHealth), currentHealth(maxHealth) {}

    void update(int damage) {
        currentHealth -= damage;
        if (currentHealth < 0) currentHealth = 0;
    }

    void display() const {
        std::cout << "Health: " << currentHealth << "/" << maxHealth << std::endl;
    }
};

// Timer class definition
class Timer {
public:
    int duration;

    Timer(int duration) : duration(duration) {}

    void tick() {
        if (duration > 0) duration--;
        std::cout << "Time remaining: " << duration << " seconds" << std::endl;
    }
};

// Team class definition for tag-team system
class Team {
public:
    std::vector<Character> characters;
    Character* currentCharacter;

    Team(std::vector<Character> characters) : characters(characters), currentCharacter(&characters[0]) {}

    void switchCharacter(int index) {
        if (index < characters.size()) {
            currentCharacter = &characters[index];
            std::cout << "Switched to " << currentCharacter->name << std::endl;
        }
    }
};

// Scene class definition for the background
class Scene {
public:
    std::string backgroundImage;

    Scene(std::string backgroundImage) : backgroundImage(backgroundImage) {}

    void render() const {
        std::cout << "Rendering background: " << backgroundImage << std::endl;
    }
};

// Function to handle player input
void handleInput(char key, Character& currentCharacter, Character& opponent) {
    if (key == 'p') {
        currentCharacter.punch(opponent);
    } else if (key == 'c') {
        currentCharacter.performCombo(opponent);
    }
}

// Main game loop
void gameLoop(Team& team1, Team& team2, Scene& scene, Timer& timer) {
    bool gameOver = false;

    // SFML Setup
    sf::RenderWindow window(sf::VideoMode(800, 600), "Fighting Game");

    while (!gameOver && timer.duration > 0) {
        scene.render();
        timer.tick();

        // Display health bars
        std::cout << team1.currentCharacter->name << "'s ";
        team1.currentCharacter->display();
        std::cout << team2.currentCharacter->name << "'s ";
        team2.currentCharacter->display();

        // Clear the window
        window.clear();

        // Draw characters
        team1.currentCharacter->draw(window);
        team2.currentCharacter->draw(window);

        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Placeholder for player input
        char playerInput;
        std::cout << "Enter action (p for punch, c for combo): ";
        std::cin >> playerInput;

        // Handle player input for team 1's current character
        handleInput(playerInput, *team1.currentCharacter, *team2.currentCharacter);

        // Check for victory conditions
        if (team1.currentCharacter->health <= 0) {
            std::cout << team2.currentCharacter->name << " wins!" << std::endl;
            gameOver = true;
        } else if (team2.currentCharacter->health <= 0) {
            std::cout << team1.currentCharacter->name << " wins!" << std::endl;
            gameOver = true;
        }

        // Display the window
        window.display();
    }

    window.close();
}

// Main function to initialize game setup
int main() {
    // Create characters
    Character character1("Fighter1", 100, 10);
    Character character2("Fighter2", 100, 10);

    // Initialize teams
    Team team1({ character1 });
    Team team2({ character2 });

    // Create a scene and timer
    Scene scene("background.jpg");
    Timer timer(30);

    // Start the game loop
    gameLoop(team1, team2, scene, timer);

    return 0;
}
