#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

const unsigned NNODE = 26;

struct TreeNode 
{
    bool endOfWord;
    std::array<std::shared_ptr<TreeNode>, NNODE> children;
    TreeNode() : endOfWord(false), children{} {}
};

class WordTree 
{
public:
    WordTree();
    void add(std::string word);
    bool find(std::string word);
    std::vector<std::string> predict(std::string partial, std::uint8_t howMany);
    std::size_t size();

private:
    std::shared_ptr<TreeNode> root;

    std::shared_ptr<TreeNode> walk(const std::string& key);

    inline bool isAlphaString(const std::string& s)
    {
        for (std::size_t i = 0; i < s.size(); ++i) {
            unsigned char uc = static_cast<unsigned char>(s[i]);
            if (!std::isalpha(uc)) {
                return false;
            } 
        }

        return true;
    }

    inline void toLowerInPlace(std::string& s)
    {
        for (std::size_t i = 0; i < s.size(); ++i) {
            unsigned char uc = static_cast<unsigned char>(s[i]);
            s[i] = static_cast<char>(std::tolower(uc));
        }
    }

    // 'a'..'z' -> 0..25, returns -1 otherwise
    inline int idxFromChar(char c)
    {
        if (c >= 'a' && c <= 'z') {
            return static_cast<int>(c - 'a');
        }

        if (c >= 'A' && c <= 'Z') {
            return static_cast<int>(c - 'A');
        }

        return -1;
    }

    inline std::size_t countWords(const std::shared_ptr<TreeNode>& n)
    {
        if (!n) {
            return 0;
        }

        std::size_t total = n->endOfWord ? 1u : 0u;
        for (std::size_t i = 0; i < 26; ++i) {
            if (n->children[i]) {
                total += countWords(n->children[i]);
            }
        }

        return total;
    }
};
