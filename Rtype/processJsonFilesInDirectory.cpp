//
// Created by Niels Ouvrard on 31/10/2023.
//

#include "../Haze/inc/json.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

using ActionFunction = std::function<void(std::ifstream &, const std::string &)>;

void processJsonFilesInDirectory(const std::string &directoryPath, const ActionFunction &action)
{
    for (const auto &entry: std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            std::string filePath = entry.path().string();
            std::ifstream fileStream(filePath);

            if (fileStream.is_open()) {
                try {
                    action(fileStream, filePath);
                } catch (nlohmann::json::parse_error &e) {
                    std::cerr << "Error parsing JSON file: " << filePath << std::endl;
                    std::cerr << e.what() << std::endl;
                }

                fileStream.close();
            } else {
                std::cerr << "Failed to open file: " << filePath << std::endl;
            }
        }
    }
}
