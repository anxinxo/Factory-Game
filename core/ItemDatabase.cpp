#include <core/ItemDatabase.hpp>

std::unordered_map<int, ItemDef> ItemDatabase::data = {
    {1, {1, "Wood", 64, true}},
    {2, {2, "Stone", 64, true}},
    {3, {3, "Raw iron", 64, true}},
    {4, {4, "Raw copper", 64, true}},
    {5, {5, "Raw platinum", 64, true}},
    {6, {6, "Coal", 64, true}},
    {7, {7, "Iron ingot", 64, true}},
    {8, {8, "Copper ingot", 64, true}},
    {9, {9, "Platinum nuggets", 32, true}},
    {10, {10, "Platinum ingot", 64, true}}
};