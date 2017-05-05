#ifndef PAIR_H
#define PAIR_H


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




};


#endif
