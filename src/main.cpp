#include <string>
#include <iostream>
#include "Packrat/ast.hpp"
#include "Packrat/symbol.hpp"
#include "Packrat/parser.hpp"
using namespace std;
using namespace packrat;
int main(void)
{
    cout << "Hello World!" << endl;
    cout << Parser::getPParser().parse(
        "program", "/* Boring program */int main() { int a; return 0;}")
        << endl;
    return 0;
}