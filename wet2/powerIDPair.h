#ifndef PAIR_H
#define PAIR_H
#include <ostream>

class PowerIDPair{

  int power;
  int id;

public:
  PowerIDPair(const int& power, const int& id) : power(power), id(id) {}
  ~PowerIDPair() {}
  PowerIDPair(const PowerIDPair& pair) : power(pair.power), id(pair.id) {}

  bool operator==(const PowerIDPair& pair) const{
    if(this->power == pair.power && this->id == pair.id){
      return true;
    }
    return false;
  }
  bool operator!=(const PowerIDPair& pair) const{
    if(*this == pair){
      return false;
    }
    return true;
  }
  bool operator>(const PowerIDPair& pair) const{
    if(this->power > pair.power){
      return true;
    }
    else if(this->power == pair.power){
      if(this->id < pair.id){
        return true;
      }
    }
    return false;
  }
  bool operator<(const PowerIDPair& pair) const{
    if(this->power < pair.power){
      return true;
    }
    else if(this->power == pair.power){
      if(this->id > pair.id){
        return true;
      }
    }
    return false;
  }


friend std::ostream& operator<<(std::ostream& os, const PowerIDPair& pair);

  friend int operator+(int num, const PowerIDPair& pair);

  friend int operator-(int num, const PowerIDPair& pair);
};

int operator+(int num, const PowerIDPair& pair){
  return num + pair.power;
}

int operator-(int num, const PowerIDPair& pair){
  return num - pair.power;
}

std::ostream& operator<<(std::ostream& os, const PowerIDPair& pair){
os << "id is: " << pair.id << " power is: " << pair.power;
return os;
}

#endif
