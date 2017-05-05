#include <exception>

#define THROWS(expr, excep) try { expr; throw ExpectedException(); } catch (excep& e) {}

class ExpectedException : public std::exception {};
