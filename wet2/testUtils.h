#include <exception>
#include <string>
#include <iostream>

#define Q(x) #x
#define THROWS(expr, excep) try { expr; throw ExpectedException("expected " Q(excep)); } catch (excep& e) {}

#define RUN_TEST(test) try { test(); std::cout << "Test " Q(test) " succeeded" << std::endl; } catch (std::exception& e) { std::cout << "Test " Q(test) " failed: " << e.what() << std::endl; }
class ExpectedException : public std::exception {
  const std::string msg;
public:
  ExpectedException(const std::string& msg) : msg(msg) {};
  const char* what() const throw() { return msg.c_str(); }
  ~ExpectedException() throw() {};
};
