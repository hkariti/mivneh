#include <exception>
#include <cstddef>

static const int INIT_SIZE = 32;

template <class Key, class Value> class HashTableEntry {
private:
  enum entryState { free, deleted, full };
  entryState state;
  Key key;
  Value* value;
public:
  HashTableEntry() : state(free), value(NULL) {};
  ~HashTableEntry() {
    delete value;
  }
  bool isFree() { return state == free; }
  bool isFull() { return state == full; }
  bool isDeleted() { return state == deleted; }
  // Init the entry with the given key and an empty value
  void init(const Key& new_key, const Value& new_value) {
    key = new_key;
    state = full;
    value = new Value(new_value);
  }
  const Key& getKey() const { return key; };
  Value& getValue() { return *value; }
  void markDeleted() { state = deleted; }
};

template <class Key, class Value> class HashTable {
private:
  typedef HashTableEntry<Key, Value> TableEntry;
  int size, used;
  TableEntry *array;
public:
  class NoSuchEntry : public std::exception {};
  class EntryExists : public std::exception {};
  HashTable() : size(INIT_SIZE), used(0) {
    array = new TableEntry[size];
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
      return array[i].getValue();
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
    array[i].markDeleted();
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

    TableEntry *old_array = array;
    int old_size = size;
    array = new TableEntry[new_size];
    size = new_size;
    used = 0;
    // Copy all full elements from old array, rehashing them
    for (int i = 0; i < old_size; i++) {
      if (!old_array[i].isFull()) continue;
      Key key = old_array[i].getKey();
      insert(key, old_array[i].getValue());
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
