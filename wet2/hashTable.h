#ifndef HASH_TABLE
#define HASH_TABLE
#include <exception>
#include <cstddef>

static const int INIT_SIZE = 32;


template <class Key, class Value> class HashTable {
private:
  class HashTableEntry {
  private:
    enum entryState { free, deleted, full };
    entryState state;
    Key key;
    Value* value;
  public:
    class EntryAlreadyFull : public std::exception {};
    HashTableEntry() : state(free), value(NULL) {};
    ~HashTableEntry() {
      if (state == full) delete value;
    }
    bool isFree() { return state == free; }
    bool isFull() { return state == full; }
    bool isDeleted() { return state == deleted; }
    // Init the entry with the given key and value
    void init(const Key& new_key, const Value& new_value) {
      if (state == full) throw EntryAlreadyFull();
      value = new Value(new_value);
      key = new_key;
      state = full;
    }
    const Key& getKey() const { return key; };
    Value& getValue() { return *value; }
    void clearEntry() {
      if (value) {
        delete value;
        value = NULL;
      }
      state = deleted;
    }
    // Only mark entry as deleted without freeing the value
    // Dangerous! Used by hash.resize() only
    void markDeleted() {
      state = deleted;
    }
  };
  int size, used;
  HashTableEntry *array;
public:
  class NoSuchEntry : public std::exception {};
  class EntryExists : public std::exception {};
  HashTable() : size(INIT_SIZE), used(0) {
    array = new HashTableEntry[size];
  }

  ~HashTable() {
    delete[] array;
  }

  // Insert new keys
  Value& insert(const Key& key, const Value& value) {
    try {
      searchFull(key);
      throw EntryExists();
    } catch (NoSuchEntry) {
      int i;
      i = searchEmpty(key);
      array[i].init(key, value);
      used++;
      if (used == size) resize(2*size);
      return (*this)[key];
    }
  }

  // Fetch existing keys
  const Value& operator[](const Key& key) const {
    int i = searchFull(key);
    return array[i].getValue();
  }
  Value& operator[](const Key& key) {
    int i = searchFull(key);
    return array[i].getValue();
  }

  void remove(const Key& key) {
    int i = searchFull(key);
    array[i].clearEntry();
    used--;
    if (used <= size/4) resize(size/2);
  }

  int length() { return used; }
private:
  int hash(const Key& key, int step) const {
    static double phi = 0.61803; // (sqrt(5) - 1)/2
    static int step_length = 3;
    double product = phi*double(key);
    double fraction = product - int(product);
    int initPlace = int(size*fraction);
    return (initPlace + step*step_length) % size;
  }

  void resize(int new_size) {
    if (new_size < INIT_SIZE) return;

    HashTableEntry *old_array = array;
    int old_size = size;
    array = new HashTableEntry[new_size];
    size = new_size;
    // Copy all full elements from old array, rehashing them
    for (int i = 0; i < old_size; i++) {
      if (!old_array[i].isFull()) continue;
      Key key = old_array[i].getKey();
      int new_index = searchEmpty(key);
      array[new_index] = old_array[i];
      old_array[i].markDeleted();
    }
    delete[] old_array;
  }

  int searchFull(const Key& key) const {
    int step = 0;
    int index;
    do {
      index = hash(key, step);
      if (array[index].isFull() && array[index].getKey() == key)
        return index;
      step++;
      if (step > size) break;
    } while (!array[index].isFree());
    throw NoSuchEntry();
  }

  int searchEmpty(const Key& key) const {
    int step = 0;
    int index;
    do {
      index = hash(key, step);
      step++;
    } while (array[index].isFull());
    return index;
  }
};
#endif
