#include "WordTree.hpp"
#include "rlutil.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>


static std::shared_ptr<WordTree> readDictionary(const std::string& filename) 
{
    std::shared_ptr<WordTree> tree = std::make_shared<WordTree>();
    std::ifstream in(filename.c_str(), std::ios::in);
    if (!in) {
        std::cerr << "Failed to open dictionary: " << filename << "\n";
        return tree;
    }

    std::string word;
    while (std::getline(in, word)) {
        if (!word.empty() && word[word.size() - 1] == '\r') {
            word.erase(word.end() - 1);
        }

        // keep only alphabetic words
        bool ok = true;
        for (std::size_t i = 0; i < word.size(); ++i) {
            unsigned char uc = static_cast<unsigned char>(word[i]);
            if (!std::isalpha(uc)) { 
                ok = false; 
                break; 
            }
        }

        if (ok) {
            // to lower (manually, no lambda)
            for (std::size_t i = 0; i < word.size(); ++i) {
                unsigned char uc = static_cast<unsigned char>(word[i]);
                word[i] = static_cast<char>(std::tolower(uc));
            }
            tree->add(word);
        }
    }

    return tree;
}

static std::string lastWord(const std::string& line) 
{
    // Trim trailing spaces
    std::size_t end = line.size();
    while (end > 0 && std::isspace(static_cast<unsigned char>(line[end-1]))) --end;
    if (end == 0) {
        return std::string();
    }

    // Find start of last word
    std::size_t start = end;
    while (start > 0 && !std::isspace(static_cast<unsigned char>(line[start-1]))) {
        --start;
    }

    return line.substr(start, end - start);
}

static void render(const std::string& line,
                   const std::vector<std::string>& preds,
                   std::uint8_t maxPreds)
{
    rlutil::cls();

    // Input line on row 1
    rlutil::locate(1, 1);
    std::cout << "***************** TypeAhead: press ESC to exit *****************";
    
    rlutil::locate(1, 2);
    std::cout << line;

    // Prediction on row 4
    int row = 4;
    rlutil::locate(1, row++);
    std::cout << "--- prediction ---";

    // Predictions start on the next row
    for (std::size_t i = 0; i < preds.size() && i < maxPreds; ++i) {
        rlutil::locate(1, row++);
        std::cout << preds[i];
    }

    // Return cursor to end of input line so the user can keep typing
    rlutil::locate(1 + static_cast<int>(line.size()), 2);
}


int main(int argc, char** argv) 
{
    (void)argc;
    (void)argv;

    std::shared_ptr<WordTree> tree = readDictionary("dictionary.txt");

    std::string line;
    bool running = true;

    while (running) 
    {
        // compute predictions for last word
        std::string part = lastWord(line);

        // rows and how many predictions to show (leave last line empty)
        int rows = rlutil::trows();
        int usableRows = rows - 5; // 1 tilt + 1 input + 1 blank + 1 title + keep last row
        if (usableRows < 0) {
            usableRows = 0;
        }
        std::uint8_t howMany = usableRows > 255 ? 255 : static_cast<std::uint8_t>(usableRows);

        std::vector<std::string> preds;
        if (!part.empty()) {
            preds = tree->predict(part, howMany);
        }

        render(line, preds, howMany);

        int key = rlutil::getkey(); // blocking
        if (key == rlutil::KEY_BACKSPACE) {
            if (!line.empty()) line.pop_back();
        } else if (key == rlutil::KEY_ESCAPE) {
            running = false;
        } else if (key == '\r' || key == '\n') {
            // new line: keep it simple—clear current line
            line.clear();
        } else {
            // printable?
            if (key >= 32 && key <= 126) {
                line.push_back(static_cast<char>(key));
            }
        }
    }

    rlutil::cls();
    return 0;
}
