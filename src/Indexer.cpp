#include "Indexer.h"
#include <fstream>
#include <sstream>

void Indexer::indexDocument(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> tokens;
        tokenize(line, tokens);
        for (const auto& token : tokens) {
            index[token].push_back(filePath);
        }
    }
}

std::unordered_map<std::string, std::vector<std::string>> Indexer::getIndex() {
    return index;
}

void Indexer::tokenize(const std::string& text, std::vector<std::string>& tokens) {
    std::istringstream stream(text);
    std::string token;
    while (stream >> token) {
        tokens.push_back(token);
    }
}
