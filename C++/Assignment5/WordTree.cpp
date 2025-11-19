#include "WordTree.hpp"
#include <queue>
#include <algorithm>

WordTree::WordTree()
{
    root = std::make_shared<TreeNode>();
}

// walk to node of string if exists, else nullptr
std::shared_ptr<TreeNode> WordTree::walk(const std::string& key)
{
    std::shared_ptr<TreeNode> cur = root;
    for (char c : key) {
        int idx = idxFromChar(c);
        if (idx < 0 || idx >= 26) return nullptr;
        if (!cur->children[idx]) return nullptr;
        cur = cur->children[idx];
    }
    return cur;
}

// add word to tree
void WordTree::add(std::string word)
{
    if (word.empty()) return;
    if (!isAlphaString(word)) return;

    toLowerInPlace(word);

    std::shared_ptr<TreeNode> cur = root;
    for (char c : word) {
        int idx = idxFromChar(c);
        if (idx < 0) return;

        if (!cur->children[idx]) {
            cur->children[idx] = std::make_shared<TreeNode>();
        }
        cur = cur->children[idx];
    }

    cur->endOfWord = true;
}

// search tree for word
bool WordTree::find(std::string word)
{
    if (word.empty()) return false;
    if (!isAlphaString(word)) return false;

    toLowerInPlace(word);
    std::shared_ptr<TreeNode> node = walk(word);
    return (node && node->endOfWord);
}

// return howMany predictions
std::vector<std::string> WordTree::predict(std::string partial, std::uint8_t howMany)
{
    std::vector<std::string> result;
    if (partial.empty()) return result;
    if (!isAlphaString(partial)) return result;

    toLowerInPlace(partial);
    std::shared_ptr<TreeNode> node = walk(partial);
    if (!node) return result;

    std::queue<std::pair<std::shared_ptr<TreeNode>, std::string>> q;
    q.push({node, partial});

    while (!q.empty() && result.size() < howMany) {
        auto [curNode, curWord] = q.front();
        q.pop();

        if (curNode->endOfWord && curWord != partial) {
            result.push_back(curWord);
            if (result.size() >= howMany) break;
        }

        for (int i = 0; i < 26; ++i) {
            if (curNode->children[i]) {
                char nextChar = static_cast<char>('a' + i);
                q.push({curNode->children[i], curWord + nextChar});
            }
        }
    }

    return result;
}

// return how many nodes in the tree
std::size_t WordTree::size()
{
    return countWords(root);
}

