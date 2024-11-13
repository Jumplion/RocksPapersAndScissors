#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

// Define the Object struct
// Each "Object" is a choice in the game. The user can add a new object to the list of objects.
struct Object {
    std::string name;
    std::vector<std::string> beats;
    std::vector<std::string> loses;
};

// Default starting objects for Rock, Paper, Scissors
std::vector<Object> objects = {
    {"rock", {"scissors"}, {"paper"}},
    {"paper", {"rock"}, {"scissors"}},
    {"scissors", {"paper"}, {"rock"}}
};

// Tracks each game played
struct GameResult {
    Object userChoice;
    Object computerChoice;
    int result;
};
std::vector<GameResult> gameResults;

std::string getUserChoice() {
    std::string choice;
    while (true) {
        std::cout << "Choose from: ";
        for (const auto& object : objects) {
            std::cout << object.name << ", ";
        }
        std::cout << "or [quit] to exit: ";
        std::cin >> choice;

        if(choice == "quit") {
            return "quit";
        }
        else if(choice == "add") {
            AddNewObject();
        }
        else if(std::find(objects.begin(), objects.end(), choice) == objects.end()) {
            std::cout << "Invalid input. Please try again." << std::endl;
        } 
        else {
            return choice;
        }
    }
    return "ERROR";
}

void AddNewObject() {
    std::cout << "Enter the name of the new object: ";
    std::string objectName;
    std::cin >> objectName;
    
    std::vector<std::string> beats;
    std::vector<std::string> loses;
    
    std::cout << "List of objects you can choose from: ";
    for (const auto& object : objects) {
        std::cout << object.name << ", ";
    }
    std::cout << std::endl;

    std::cout << "Enter the name(s) of the object that " << objectName << " beats (enter nothing to continue): ";
    std::string otherObject;
    while(true){
        std::cin >> otherObject;
        if(otherObject == ""){
            break;
        }
        // Check for keywords "add" and "quit"
        else if(otherObject == "add" || otherObject == "quit"){
            std::cout << "Certain keywords cannot be objects. Please enter a valid object: ";
        }
        else if(otherObject == objectName){
            std::cout << "An object cannot beat itself. Please enter a valid object: ";
        }
        // If the object was already added to the object's "beats" list, it is invalid.
        else if(std::find(beats.begin(), beats.end(), otherObject) != beats.end()){
            std::cout << objectName << " is already set to beat " << otherObject << ". Please enter a valid object: ";
        }
        // Check if the object exists in objects[]
        else if(std::find(objects.begin(), objects.end(), beats) != objects.end()){
            beats.push_back(otherObject);
            std::cout << objectName << " is set to beat " << otherObject << std::endl;
        }
        // If the object does not exist, prompt the user to enter a valid object
        else{
            std::cout << "Object does not exist in the valid list of objects. Please enter a valid object: ";
        }
    }

    std::cout << "Enter the name(s) of the object that " << objectName << " loses to (enter nothing to continue): ";
    while(true){
        std::cin >> otherObject;
        if(otherObject == ""){
            break;
        }
        // Check for keywords "add" and "quit"
        else if(otherObject == "add" || otherObject == "quit"){
            std::cout << "Certain keywords cannot be objects. Please enter a valid object: ";
        }
        else if(otherObject == objectName){
            std::cout << "An object cannot lose to itself. Please enter a valid object: ";
        }
        // If the object was already added to the object's "beats" list, it is invalid.
        else if(std::find(beats.begin(), beats.end(), otherObject) != beats.end()){
            std::cout << objectName << " is already set to beat " << otherObject << ". Please enter a valid object: ";
        }
        // If the object was already added to the object's "loses" list, it is invalid.
        else if(std::find(loses.begin(), loses.end(), otherObject) != loses.end()){
            std::cout << objectName << " is already set to lose to " << otherObject << ". Please enter a valid object: ";
        }
        // Check if the object exists in objects[]
        else if(std::find(objects.begin(), objects.end(), loses) != objects.end()){
            loses.push_back(otherObject);
            std::cout << objectName << " is set to lose to " << otherObject << std::endl;
        }
        // If the object does not exist, prompt the user to enter a valid object
        else{
            std::cout << "Object does not exist in the valid list of objects. Please enter a valid object: ";
        }
    }

    objects.push_back({objectName, beats, loses});
    std::cout << "All objects not listed in 'beats' or 'loses' are assumed to tie with " << objectName << std::endl;
    std::cout << "New object added: " << objectName << std::endl;
    return;
}

int determineWinner(const Object userChoice, const Object computerChoice) {
    if (std::find(userChoice.beats.begin(), userChoice.beats.end(), computerChoice.name) != userChoice.beats.end()) {
        std::cout << "You win!" << std::endl;
        return 1;
    } else if (std::find(userChoice.loses.begin(), userChoice.loses.end(), computerChoice) != userChoice.loses.end()) {
        std::cout << "You lose!" << std::endl;
        return -1;
    } else {
        std::cout << "It's a tie!" << std::endl;
        return 0;
    }
}


int main() {
    std::srand(std::time(0));
    std::string userChoice;

    std::cout << "Welcome to Rock, Paper, Scissors!" << std::endl;
    
    while (true) {
        std::cout << "Choose your object." << std::endl;
        std::cout << "Input 'add' to add a new object." << std::endl;

        userChoice = getUserChoice();
        if (userChoice == "quit") {
            break;
        }
        
        std::string computerChoice = objects[std::rand() % objects.size()].name;
        std::cout << "Computer chose: " << computerChoice << std::endl;
        
        Object userObject = *std::find(objects.begin(), objects.end(), userChoice);
        Object computerObject = *std::find(objects.begin(), objects.end(), computerChoice);
        
        gameResults.push_back({userObject, computerObject, determineWinner(userObject, userObject)});
    }
    
    std::cout << "Thanks for playing!" << std::endl;

    // Print out the results of each game
    // and the total number of wins, losses, and ties
    int wins = 0;
    int losses = 0;
    int ties = 0;
    for (const auto& gameResult : gameResults) {
        if (gameResult.result == 1) {
            wins++;
        } else if (gameResult.result == -1) {
            losses++;
        } else {
            ties++;
        }
    }
    std::cout << "Wins: " << wins << std::endl;
    std::cout << "Losses: " << losses << std::endl;
    std::cout << "Ties: " << ties << std::endl;
    
    return 0;
}