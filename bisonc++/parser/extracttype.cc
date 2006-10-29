#include "parser.ih"

    // expect <typename> or not, if not at a  `<' character

size_t Parser::extractType(string *type, size_t pos)
{
    if (pos >= d_block.length())    // block ends prematurely.
        throw 1;


    if (d_block[pos] != '<')        // no explicit type
        return 0;

    size_t begin = pos + 1;       // first char of the type

                                    // saw the opening bracket, find the `>'
    size_t end = d_block.find('>', begin);

    if (end == string::npos)        // no `>' found
        throw 1;                    // caught as incomplete $ specification

    *type = d_block.substr(begin, end - begin);

    return end + 1 - pos;           // length of <type> specification
}
