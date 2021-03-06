#include "list.hpp"

namespace WikiMarkup { namespace Components { namespace PostProcessors {
//####################################################################################
    PrimalList postProcessList(PlainList::const_iterator i, PlainList::const_iterator end, unsigned int depth)
    {
        PrimalList curList;
        for (; i != end; ++i)
        {
            auto const& r = *i;
            if (r.prefix.size() - 1 > depth) {
                // new sublist starts!
                curList.elements.push_back(sutil::make_value <PrimalList> (postProcessList(i, end, depth + 1)));

                do {
                    ++i;
                } while (i != end && i->prefix.size() - 1 > depth);
                --i;
                continue;
            }

            if (depth > r.prefix.size() - 1) {
                return curList;
            }

            // i.prefix[depth] is always safe here
            curList.type = getTypeFromChar(r.prefix[depth]);
            curList.elements.push_back(sutil::make_value <ListTextLine> (r.data));
        }
        return curList;
    }
//-----------------------------------------------------------------------------------
    PrimalList postProcessList(PlainList const& plainList)
    {
        return postProcessList(plainList.cbegin(), plainList.cend(), 0);
    }
//####################################################################################
} // namespace PostProcessors
} // namespace Components
} // namespace WikiMarkup
