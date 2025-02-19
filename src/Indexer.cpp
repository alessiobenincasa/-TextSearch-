#include "Indexer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <set>
#include <filesystem>

namespace fs = std::filesystem;

void Indexer::buildIndex(const std::string& docPath, const std::string& indexPath) {
    std::unordered_map<std::string, std::set<std::string>> index;

    // Lire tous les fichiers de `docPath`
    for (const auto& file : fs::directory_iterator(docPath)) {
        if (file.is_regular_file()) {
            std::string filename = file.path().filename().string();
            std::ifstream inFile(file.path());
            if (!inFile) {
                std::cerr << "Erreur ouverture fichier: " << filename << std::endl;
                continue;
            }

            std::string word;
            while (inFile >> word) {
                word = sanitize(word);
                if (!word.empty()) {
                    index[word].insert(filename);
                }
            }
        }
    }

    // Sauvegarder l'index
    saveIndex(index, indexPath);
}

std::string Indexer::sanitize(const std::string& word) {
    std::string cleanWord;
    for (char c : word) {
        if (std::isalnum(c)) cleanWord += std::tolower(c);
    }
    return cleanWord;
}

void Indexer::saveIndex(const std::unordered_map<std::string, std::set<std::string>>& index, const std::string& indexPath) {
    std::ofstream outFile(indexPath);
    if (!outFile) {
        std::cerr << "Erreur sauvegarde index !" << std::endl;
        return;
    }

    for (const auto& [word, files] : index) {
        outFile << word << " ";
        for (const auto& file : files) {
            outFile << file << " ";
        }
        outFile << "\n";
    }

    std::cout << "Index sauvegardé avec succès !" << std::endl;
}
