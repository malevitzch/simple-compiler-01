#pragma once
#include <string>
#include <vector>
#include <memory>

using std::string;

class Trie
{ 
private:
  std::vector<char> alphabet;
  //returns the index of the target char in the TrieNode array
  int get_index(char target);
  friend struct TrieNode;
  
  struct TrieNode
  {
    std::vector<std::shared_ptr<TrieNode>> ptrs;
    char symbol;
    bool finish;
    TrieNode(char symbol, bool finish, int alphabet_size);

    //a function that checks whether or not the symbol represented by index can be added to the current string
    bool possible_next(int index);
  };

  std::shared_ptr<TrieNode> root;

public:
  //default constructor is deleted as Trie without an alphabet makes no sense
  Trie() = delete;
  //TODO: copy constructor that actually copies the whole Trie with all the nodes? Might be a lot of work but can be considered in the future
  
  //basic Trie constructor
  Trie(std::vector<char> alphabet);
  
  //constructor that builds the trie with an initial set of words
  Trie(std::vector<char> alphabet, std::vector<string> words);
  
  //constructor that deduces the alphabet based on the initial set of words, only use if you know the words contain the whole alphabet you want to use
  Trie(std::vector<string> words);

  //a function that attempts to greedily split a string into words from trie
  std::vector<string> split_string(string str);

  //adds a word to trie
  void insert(string word);

  //adds each string in a vector of strings to trie
  void insert(std::vector<string> words);

  //checks whether the input word is contained in the trie
  bool contains(string word);
};
//TODO: if we want to support deletion, we need TrieNode to keep usecount and delete nodes by calling shared_ptr<TrieNode>.reset()
