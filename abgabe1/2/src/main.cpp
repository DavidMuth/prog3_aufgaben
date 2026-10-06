#include <analyze.hpp>
#include <cassert>

int main(int argc, char** argv) {
    // count number of digits (incl. Sign) or chars
    assert(analyze(0) == 1);              // one digit
    assert(analyze(9) == 1);              // one digit
    assert(analyze(-1) == 2);             // one digit+1 char
    assert(analyze(1234) == 4);           // 4 digits
    assert(analyze(-90) == 3);            // 2 digits+1 char
    assert(analyze("Hello World") == 11); // 11 chars
    assert(analyze("ABC") == 3);          // 3 chars
}
