#include <iostream>
#include <string>

class Test {
private:
  std::string someText;

public:
  std::string getText();
  void setText(std::string text);
};