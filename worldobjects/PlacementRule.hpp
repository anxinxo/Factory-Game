#pragma once
#include <world/CellView.hpp>

class PlacementRule
{
public:
    virtual bool check(const CellView& view) const = 0;
    virtual ~PlacementRule() = default;
};