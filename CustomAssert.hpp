// Defines a custom assert macro for testing and debugging.

#ifndef _CUSTOM_ASSERT_
#define _CUSTOM_ASSERT_

#include <iostream> // cerr, endl
#include <cstdlib> // abort

inline void AssertCheck(const bool cond, // evaluated expression/condition
                        const std::string exp, // literal expression
                        const std::string msg, // test message for success/failure
                        const bool sup, // suppression flag for successful conditions
                        const std::string func, // function name
                        const std::string file, // file name
                        const int line) // line number
{
  if (!cond) {
    std::cerr << "Assertion failed: \"" << exp
              << "\", function: " << func
              << ", file: " << file << ":" << line
              << std::endl
              << "Error message: " << msg
              << std::endl;
    abort();
  }
  else if (!sup) // show message if not suppressed
    std::cerr << msg << "...passed!" << std::endl;
}

#define ASSERT_CONDITION(exp, msg) \
  AssertCheck((exp), (#exp), (msg), true, __func__, __FILE__, __LINE__)

// Used to ensure that the assert is actually called in the test code.
#define ASSERT_CONDITION_SHOW_PASS(exp, msg) \
  AssertCheck((exp), (#exp), (msg), false, __func__, __FILE__, __LINE__)

#endif // _CUSTOM_ASSERT_

