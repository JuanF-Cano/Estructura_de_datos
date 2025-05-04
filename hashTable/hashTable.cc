#include <iostream>
#include <vector>
#include <list>
#include <functional>

using namespace std;

template <typename KeyT, typename ValueT>
class Hash {
  private:
    vector<list<pair<KeyT, ValueT>>> table_;
    unsigned int capacity_;
    unsigned int size_;
    float maxLoadFactor_;

    float currentLoadFactor() const { return (float)size_ / capacity_; }

    unsigned int hashFunction(const KeyT& key) const {
      hash<KeyT> hasher;
      return hasher(key) % capacity_;
    }
    void rehash() {
      capacity_ *= 2;
      vector<list<pair<KeyT, ValueT>>> newTable(capacity_);
      for (auto& bucket : table_) {
        for (auto& pair : bucket) {
          unsigned int newIndex = hashFunction(pair.first);
          newTable[newIndex].push_back(pair);
        }
      }
      table_.clear();
      table_ = newTable;
    }
  public:
    Hash(unsigned int initialCapacity = 16, float loadFactor = 0.75f)
      : table_(initialCapacity), size_(0), capacity_(initialCapacity), maxLoadFactor_(loadFactor)
    {}
    unsigned int size() const { return size_; }
    bool isEmpty() const { return (size_ == 0); }

    void insert(const KeyT& key, const ValueT& value) {
      unsigned int index = hashFunction(key);
      for (auto& pair : table_[index]) {
        if (pair.first == key) {
          pair.second = value;
          return;
        }
      }
      table_[index].push_back({key, value});
      size_++;
      if (currentLoadFactor() >= maxLoadFactor_) rehash();
    }
    bool remove(const KeyT& key) {
      unsigned int index = hashFunction(key);
      auto& bucket = table_[index];
      for (auto it = bucket.begin(); it != bucket.end(); it++) {
        if (it->first == key) {
          bucket.erase(it);
          size_--;
          return true;
        }
      }
      return false;
    }
    ValueT* get(const KeyT& key) {
      unsigned int index = hashFunction(key);
      auto& bucket = table_[index];
      for (auto it = bucket.begin(); it != bucket.end(); it++) {
        if (it->first == key) return &(it->second);
      }
      return nullptr;
    }
    bool contains(const KeyT& key) const {
      unsigned int index = hashFunction(key);
      const auto& bucket = table_[index];
      for (auto it = bucket.begin(); it != bucket.end(); it++) {
        if (it->first == key) return true;
      }
      return false;
    }
    void clear() {
      for (auto& bucket : table_) {
        bucket.clear();
      }
      size_ = 0;
    }
    void print() const {
      int i = 0;
      for (auto& bucket : table_) {
        cout << "[" << i++ << "] -> {";
        bool first = true;
        for (const auto& pair : bucket) {
            if (!first) cout << " ";
            cout << "(" << pair.first << "," << pair.second << ")";
            first = false;
        }
        cout << "}" << endl;
      }
    }
};

int main() {
  Hash<string, int> map;

  // Inserting key-value pairs
  map.insert("apple", 5);
  map.insert("banana", 3);
  map.insert("orange", 7);

  // Inserting a key that already exists should update the value
  map.insert("banana", 10);

  // Checking size (should be 3 because "banana" was updated, not added again)
  cout << "Size: " << map.size() << endl;  // Expected: 3

  // Checking if keys exist
  cout << "Contains 'apple'? " << (map.contains("apple") ? "Yes" : "No") << endl;   // Expected: Yes
  cout << "Contains 'grape'? " << (map.contains("grape") ? "Yes" : "No") << endl;   // Expected: No

  // Getting values
  if (auto* value = map.get("orange")) {
      cout << "Value for 'orange': " << *value << endl;  // Expected: 7
  }

  // Trying to get a non-existing key
  if (map.get("grape") == nullptr) {
      cout << "'grape' not found." << endl;  // Expected: 'grape' not found.
  }

  // Removing a key
  map.remove("apple");
  cout << "After removing 'apple':" << endl;
  map.print();  // Should no longer contain "apple"

  // Inserting more elements to trigger rehashing (depending on maxLoadFactor)
  map.insert("grape", 4);
  map.insert("melon", 9);
  map.insert("kiwi", 6);
  map.insert("mango", 11);
  map.insert("berry", 2);
  map.insert("peach", 8);

  // Print final hash table
  cout << "Final table after multiple insertions (rehashing should have occurred):" << endl;
  map.print();

  // Clearing the table
  map.clear();
  cout << "After clearing, is the table empty? " << (map.isEmpty() ? "Yes" : "No") << endl;  // Expected: Yes
}