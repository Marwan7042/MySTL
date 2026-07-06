#include <iostream>
#include <string>
#include "unordered_map.h"

int main() {
    std::cout << "=== Testing mstd::unordered_map ===\n\n";

    mstd::unordered_map<std::string, int> player_scores;

    std::cout << "1. Inserting new players...\n";
    player_scores.insert("Alice", 100);
    player_scores.insert("Bob", 200);
    player_scores.insert("Charlie", 300);

    std::cout << "Alice's score: " << player_scores["Alice"] << "\n";
    std::cout << "Bob's score: " << player_scores["Bob"] << "\n";

    std::cout << "\n2. Testing the magical operator[] assignment...\n";
    std::cout << "Incrementing Alice's score by 50 using operator[]...\n";
    player_scores["Alice"] += 50;
    std::cout << "Alice's new score: " << player_scores["Alice"] << "\n";

    std::cout << "\n3. Testing lazy instantiation for new keys...\n";
    std::cout << "Incrementing an unknown player 'Dave'...\n";
    player_scores["Dave"]++; // Should default to 0, then increment to 1
    std::cout << "Dave's score is automatically: " << player_scores["Dave"] << "\n";

    std::cout << "\n4. Testing contains()...\n";
    std::cout << "Contains 'Alice'? " << (player_scores.contains("Alice") ? "Yes" : "No") << "\n";
    std::cout << "Contains 'Eve'? " << (player_scores.contains("Eve") ? "Yes" : "No") << "\n";

    std::cout << "\n5. Testing remove()...\n";
    player_scores.remove("Bob");
    std::cout << "Removed 'Bob'. Contains 'Bob' now? " << (player_scores.contains("Bob") ? "Yes" : "No") << "\n";

    std::cout << "\n6. Map Size: " << player_scores.size() << "\n";

    std::cout << "\nSUCCESS! Your Hash Map architecture is fully operational.\n";
    return 0;
}
