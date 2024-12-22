#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>

// Base class for financial instruments
class FinancialInstrument {
public:
    virtual double getMarketValue() const = 0;
    virtual std::string getName() const = 0;
    virtual ~FinancialInstrument() {}
};

// Derived class for Stocks
class Stock : public FinancialInstrument {
private:
    std::string ticker;
    int shares;
    double pricePerShare;
public:
    Stock(const std::string& ticker, int shares, double price)
        : ticker(ticker), shares(shares), pricePerShare(price) {}

    double getMarketValue() const override {
        return shares * pricePerShare;
    }

    std::string getName() const override {
        return ticker;
    }

    void updatePrice(double newPrice) {
        pricePerShare = newPrice;
    }

    int getShares() const {
        return shares;
    }

    void buyShares(int amount) {
        shares += amount;
    }

    bool sellShares(int amount) {
        if (amount > shares) return false;
        shares -= amount;
        return true;
    }
};

// Portfolio class to manage multiple financial instruments
class Portfolio {
private:
    std::vector<std::shared_ptr<FinancialInstrument>> assets;
public:
    void addAsset(const std::shared_ptr<FinancialInstrument>& asset) {
        assets.push_back(asset);
    }

    void removeAsset(const std::string& name) {
        assets.erase(std::remove_if(assets.begin(), assets.end(),
            [&name](const std::shared_ptr<FinancialInstrument>& asset) {
                return asset->getName() == name;
            }), assets.end());
    }

    double getTotalValue() const {
        double total = 0.0;
        for (const auto& asset : assets) {
            total += asset->getMarketValue();
        }
        return total;
    }

    void displayPortfolio() const {
        std::cout << "Portfolio:\n";
        for (const auto& asset : assets) {
            std::cout << asset->getName() << ": $" << asset->getMarketValue() << "\n";
        }
        std::cout << "Total Portfolio Value: $" << getTotalValue() << "\n";
    }

    std::shared_ptr<Stock> findStock(const std::string& ticker) const {
        for (const auto& asset : assets) {
            auto stock = std::dynamic_pointer_cast<Stock>(asset);
            if (stock && stock->getName() == ticker) {
                return stock;
            }
        }
        return nullptr;
    }
};

// Function to simulate fetching market price (stub function)
double fetchMarketPrice(const std::string& ticker) {
    // In a real application, this function would fetch current market prices from an API
    // Here, we'll simulate it with a fixed price for demonstration purposes
    return 100.0; // Simulated price
}

// User interface functions
void displayMenu() {
    std::cout << "1. Add Stock\n";
    std::cout << "2. Remove Stock\n";
    std::cout << "3. Buy Shares\n";
    std::cout << "4. Sell Shares\n";
    std::cout << "5. View Portfolio\n";
    std::cout << "6. Exit\n";
    std::cout << "Enter your choice: ";
}

void addStock(Portfolio& portfolio) {
    std::string ticker;
    int shares;
    double price;

    std::cout << "Enter stock ticker: ";
    std::cin >> ticker;
    std::cout << "Enter number of shares: ";
    std::cin >> shares;
    price = fetchMarketPrice(ticker); // Simulate fetching market price

    auto stock = std::make_shared<Stock>(ticker, shares, price);
    portfolio.addAsset(stock);
    std::cout << "Added " << shares << " shares of " << ticker << " at $" << price << " per share.\n";
}

void removeStock(Portfolio& portfolio) {
    std::string ticker;
    std::cout << "Enter stock ticker to remove: ";
    std::cin >> ticker;
    portfolio.removeAsset(ticker);
    std::cout << "Removed stock " << ticker << " from portfolio.\n";
}

void buyShares(Portfolio& portfolio) {
    std::string ticker;
    int shares;
    std::cout << "Enter stock ticker to buy: ";
    std::cin >> ticker;
    auto stock = portfolio.findStock(ticker);
    if (stock) {
        std::cout << "Enter number of shares to buy: ";
        std::cin >> shares;
        stock->buyShares(shares);
        std::cout << "Bought " << shares << " additional shares of " << ticker << ".\n";
    } else {
        std::cout << "Stock " << ticker << " not found in portfolio.\n";
    }
}

void sellShares(Portfolio& portfolio) {
    std::string ticker;
    int shares;
    std::cout << "Enter stock ticker to sell: ";
    std::cin >> ticker;
    auto stock = portfolio.findStock(ticker);
    if (stock) {
        std::cout << "Enter number of shares to sell: ";
        std::cin >> shares;
        if (stock->sellShares(shares)) {
            std::cout << "Sold " << shares << " shares of " << ticker << ".\n";
        } else {
            std::cout << "Not enough shares to sell.\n";
        }
    } else {
        std::cout << "Stock " << ticker << " not found in portfolio.\n";
    }
}

int main() {
    Portfolio portfolio;
    int choice;

    do {
        displayMenu();
        std::cin >> choice;
        switch (choice) {
            case 1:
                addStock(portfolio);
                break;
            case 2:
                removeStock(portfolio);
                break;
            case 3:
                buyShares(portfolio);
                break;
            case 4:
                sellShares(portfolio);
                break;
            case 5:
                portfolio.displayPortfolio();
                break;
            case 6:
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
