#include "Box.h"

Box:: Box(Box const& b)
{
    for(auto& g: b.tab_ptr_grains) {
        tab_ptr_grains.push_back(g->copie());
    }
}
