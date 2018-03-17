/**
 * Asks for one token at a time and displays each token to the screen,
 * including on the token class, instance, and line number.
 *
 * Tokens are in the format of {token ID, token instance, line number}.
 */

#include <iostream>
#include "scanner/scanner.h"

void test_scanner(std::string filename)
{
    FiniteAutomatonDriver driver(filename);
    Token token;
    do {
        token = driver.read();
        std::cout << token << std::endl;
    } while (!token.is_eof());
}