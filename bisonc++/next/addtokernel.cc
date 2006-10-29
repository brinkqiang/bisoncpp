#include "next.ih"

size_t Next::addToKernel(Next::Vector &next,
                        Symbol const *symbol, size_t stateItemOffset)
{
    Iterator it = find_if(next.begin(), next.end(), 
            Wrap1c<Next, Symbol, bool>(hasSymbol, symbol));
    
    it->d_kernel.push_back(stateItemOffset);
    return it - next.begin();
}
