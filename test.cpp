#include "taveren.hpp"

#include <iostream>

using namespace std;

int main () {
    cout << echaozh::format_string (
        "abc   #{1+2*3+y^4}   #{hex(x)}   "
        "#{xpath('/root/node[@foo=\"bar\"]/text()')}",
        "{\"x\": \"123\", \"y\":2, "
        " \"page\": \"<root><node foo=\\\"bar\\\">sample text</node></root>\"}")
         << endl;
    return 0;
}
