#ifndef _INCLUDED_ITEM_
#define _INCLUDED_ITEM_

#include <iosfwd>

#include "../production/production.h"
#include "../lookaheadset/lookaheadset.h"

class Item
{
    friend std::ostream &operator<<(std::ostream &out, Item const &item);

    Production const *d_production;
    size_t                d_dot;

    static std::ostream &(Item::*s_insert[])(std::ostream &out) const;
    
    public:
        typedef std::vector<Item>                   Vector;
        typedef std::vector<Item>::const_iterator   ConstIter;

        Item();

        Item(Production const *start);      // initial item, starts at the 
                                            // start-production. Dot = 0, 
                                            // Lookahead = EOF

        Item(Item const *item, size_t dot);

        Item(Production const *prod, size_t dot);
                                        //, LookaheadSet const &laSet);

            // see State::beforeDot() to read why this function is only called
            // when d_dot > 0
        Symbol const *dotSymbol() const;        // symbol at the dot (must 
        Symbol const *dotSymbolOr0() const;     // symbol at the dot or 0
        Symbol const *symbolBeforeDot() const;  // symbol before the dot

        Item incDot() const;
                                                // true: returned FirstSet 
                                                // contained (now removed) 
                                                // epsilon
        bool firstBeyondDot(FirstSet *firstSet) const;

        Production const *production() const;   // *rhs() const

        Symbol const *lhs() const;

        bool empty() const;                     // if no size
        bool hasRightOfDot(Symbol const &symbol) const;
        bool operator==(Item const &other) const;
        bool isReducible() const;               // if dot at end
        bool transitsTo(Item const &other) const;

        size_t dot() const;
        size_t productionSize() const;

    private:
        std::ostream &insertStd(std::ostream &out) const;
        std::ostream &insertExt(std::ostream &out) const;
        std::ostream &insert(std::ostream &out, Production const *prod) const;
};

inline Symbol const *Item::dotSymbol() const    // symbol at the dot (must 
{                                               // exist!)
    return &(*d_production)[d_dot];
}

inline Symbol const *Item::dotSymbolOr0() const // symbol at the dot or 0
{                                       // if dot at end of production
    return d_dot == d_production->size() ?
                0
            :
                dotSymbol();
}

inline Symbol const *Item::symbolBeforeDot() const  // symbol before the dot
{
    return &(*d_production)[d_dot - 1];
}

inline size_t Item::dot() const
{
    return d_dot;
}

inline Item Item::incDot() const
{
    return Item(this, d_dot + 1);
}

inline Production const *Item::production() const  
{
    return d_production;
}


inline Symbol const *Item::lhs() const
{
    return d_production->lhs();
}

inline bool Item::isReducible() const                // if dot at end
{
    return d_dot == productionSize();
}

inline bool Item::empty() const                 // if no size
{
    return productionSize() == 0;
}

inline size_t Item::productionSize() const
{
    return d_production->size();
}

inline std::ostream &operator<<(std::ostream &out, Item const &item)
{
    return (item.*Item::s_insert[OM::type()])(out);
}


#endif
