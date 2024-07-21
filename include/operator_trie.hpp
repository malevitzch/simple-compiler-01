#include <string>
#include <vector>
#include <memory>
using std::string;
class Trie
{ 
private:
  std::vector<char> alphabet;
  int get_index(char target);
  friend struct TrieNode;
  struct TrieNode
  {
    std::vector<std::shared_ptr<TrieNode>> ptrs;
    char symbol;
    bool finish;
    TrieNode(char symbol, bool finish, int alphabet_size);
    bool possible_next(int index);
    friend class Trie;
  };
  std::shared_ptr<TrieNode> root;
public:
  Trie(std::vector<char> alphabet);
  Trie(std::vector<char> alphabet, std::vector<string> words);
  Trie(std::vector<string> words);
  std::vector<string> split_string(string str);
  void insert(string word);
  bool contains(string word);
};
//TODO: if we want to support deletion, we need TrieNode to keep usecount and delete nodes by calling shared_ptr<TrieNode>.reset()
