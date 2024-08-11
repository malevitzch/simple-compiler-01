#include <algorithm>
#include <set>

#include "operator_trie.hpp"

int Trie::get_index(char target)
{
  //I'm not actually sure if using binary search here makes it noticeably faster but well, it's cool isn't it?
  //NOTE: this could probably be replaced with a hashmap or something like that
  int l = 0;
  int r = alphabet.size() - 1;
  //just regular binary search to find the index of the character we want 
  while(l <= r)
  {
    int mid = (l + r) / 2;
    if(alphabet[mid] < target)
    {
      l = mid + 1;
    }
    else if(alphabet[mid] > target)
    {
      r = mid - 1;
    }
    else
    {
      return mid;
    }
  }
  return -1;
}

//every pointer is initialized to nullptr, making use of the vector constructor
Trie::TrieNode::TrieNode(char symbol, bool finish, int alphabet_size) : symbol(symbol), finish(finish), ptrs(alphabet_size, nullptr) {}

bool Trie::TrieNode::possible_next(int index)
{
  //basically we just check if the position at index is occupied by a non-null pointer
  return ptrs[index] != nullptr;
}

Trie::Trie(std::vector<char> alphabet) : alphabet(alphabet), root(std::make_shared<TrieNode>('\0', false, alphabet.size()))
{
  //alphabet needs to be sorted for binary search
  std::sort(alphabet.begin(), alphabet.end());
}
Trie::Trie(std::vector<char> alphabet, std::vector<string> words) : alphabet(alphabet), root(std::make_shared<TrieNode>('\0', false, alphabet.size()))
{
  //alphabet needs to be sorted for binary search
  std::sort(alphabet.begin(), alphabet.end());
  insert(words);
}

Trie::Trie(std::vector<string> words) 
{
  //we use a set to gather all the characters in words gievn to us and automatically sort them
  std::set<char> chars;
  
  //put all characters found in the words into our set
  for(string& word : words) for(char ch : word) chars.insert(ch);
  
  //alphabet is just the set dumped into a vector since it will be sorted and without duplicates
  for(char ch : chars) alphabet.push_back(ch);
  
  //we create root now rather than in initializer list since back then we didn't know the alphabet size
  root = std::make_shared<TrieNode>('\0', false, alphabet.size());
  
  //finally, we insert all the words into our Trie
  insert(words);
}

//TODO: add some sort of diagnostics rather than just returning an empty vector
std::vector<string> Trie::split_string(string str)
{
  std::vector<string> result;
  string buf = "";
  
  //lambda that unloads the current buffer into our result vector
  auto unload = [&buf, &result]()
  {
    if(buf.size() > 0)
    {
        result.push_back(buf);
        buf = "";
    }
  };

  //we store the current node that we are in, starting at the root
  std::shared_ptr<TrieNode> cur = root;

  for(char ch : str)
  {
    int index = get_index(ch);
    //TODO: error handling
    if(index == -1) return {};
    //if we cannot move from current node to the one we would want to, we finish the token
    if(!cur->possible_next(index))
    {
      //if Trie contains no token same as the one in the buffer, we return an empty vector
      //TODO: error handling
      if(!cur->finish) return {};
      unload();
      cur = root;
      //if the character cannot be the start of the token then we have an error
      if(!cur->possible_next(index))
      {
        //TODO: error handling
        return {};
      }
    }
    //move to the next node
    cur = cur->ptrs[index];
    //add character to buffer
    buf += ch;
  }
  
  //check token legality before unloading
  //TODO: error handling
  if(!cur->finish) return {};
  unload();
  return result; 
}
void Trie::insert(string word)
{
  //we keep track of which node we are currently in, starting at root
  std::shared_ptr<TrieNode> cur = root;

  for(char ch : word)
  {
    int index = get_index(ch);
    
    //if the node we want to move to does not exist, we need to create it
    if(!cur->possible_next(index))
    { 
      //creating the node
      cur->ptrs[index] = std::make_shared<TrieNode>(ch, false, alphabet.size());
    }
    
    //move to the next node
    cur = cur->ptrs[index];
  }
  //set the finish flag to true so that the Trie knows that the word is legal
  cur->finish = true;
}

void Trie::insert(std::vector<string> words)
{
  for(string& word : words) insert(word);
}

bool Trie::contains(string word)
{
  //keep track of the node we are in, starting at root
  std::shared_ptr<TrieNode> cur = root;

  for(char ch : word)
  {
    int index = get_index(ch);
    //if we can't move to the next node we want then our word is definitely not in the trie
    if(!cur->possible_next(index))
    {
      return false;
    }
    //move to the next node
    cur = cur->ptrs[index];
  }
  //return whether or not there is a word that ends at the final node
  return cur->finish;
}
