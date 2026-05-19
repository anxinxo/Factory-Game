#include <worldobjects/WorldObject.hpp>
#include <worldobjects/PlacementRule.hpp>

bool WorldObject::canPlaceOn(const CELL& cell) const
{
    for (const auto& r : getRules())
        if (!r->check(cell))
            return false;

    return true;
}