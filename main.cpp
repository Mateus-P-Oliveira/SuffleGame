#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

std::vector<int> createDeck() {
    std::vector<int> deck;
    // Add cards 1-10 (4 times each to simulate suits)
    for (int i = 1; i <= 10; i++) {
        for (int j = 0; j < 4; j++) {
            deck.push_back(i);
        }
    }
    return deck;
}

void shuffleDeck(std::vector<int>& deck) {
    static std::mt19937 rng(static_cast<unsigned>(time(nullptr)));
    std::shuffle(deck.begin(), deck.end(), rng);
}

int drawCard(std::vector<int>& deck) {
    int card = deck.back();
    deck.pop_back();
    return card;
}



int main() {
    std::vector<int> deck = createDeck();
    shuffleDeck(deck);

    std::vector<int> playerHand;
    std::vector<int> dealerHand;

    // Initial deal
    playerHand.push_back(drawCard(deck));
    playerHand.push_back(drawCard(deck));
    dealerHand.push_back(drawCard(deck));
    dealerHand.push_back(drawCard(deck));

    int playerTotal = playerHand[0] + playerHand[1];
    int dealerTotal = dealerHand[0] + dealerHand[1];

    std::cout << "You are dealt: " << playerHand[0] << " and " << playerHand[1]
              << " (Total = " << playerTotal << ")\n";
    std::cout << "Dealer shows: " << dealerHand[0] << " and ?\n";

    // Player's turn
    char choice;
    while (true) {
        if (playerTotal > 21) {
            std::cout << "You busted! Dealer wins.\n";
            return 0;
        }
        std::cout << "Do you want another card? (y/n): ";
        std::cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            int card = drawCard(deck);
            playerHand.push_back(card);
            playerTotal += card;
            std::cout << "You drew a " << card
                      << " (Total = " << playerTotal << ")\n";
        } else {
            break;
        }
    }

    std::cout << "\nDealer's turn...\n";
    std::cout << "Dealer has: " << dealerHand[0] << " and " << dealerHand[1]
              << " (Total = " << dealerTotal << ")\n";

    // Dealer plays: draw until >= 17
    while (dealerTotal < 17) {
        int card = drawCard(deck);
        dealerHand.push_back(card);
        dealerTotal += card;
        std::cout << "Dealer draws " << card
                  << " (Total = " << dealerTotal << ")\n";
    }

    // Decide outcome
    if (dealerTotal > 21) {
        std::cout << "Dealer busted! You win!\n";
    } else if (playerTotal > dealerTotal) {
        std::cout << "You win with " << playerTotal
                  << " against dealer's " << dealerTotal << "!\n";
    } else if (playerTotal < dealerTotal) {
        std::cout << "Dealer wins with " << dealerTotal
                  << " against your " << playerTotal << ".\n";
    } else {
        std::cout << "It's a tie! Both have " << playerTotal << ".\n";
    }

    return 0;
}