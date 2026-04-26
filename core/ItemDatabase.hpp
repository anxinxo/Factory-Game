#pragma once

#include <unordered_map>
#include <string>

// Dữ liệu item
struct ItemDef
{
    int id;
    std::string name;
    int maxStack;
    bool stackable;
};

// Tra cứu thông tin item
class ItemDatabase
{
public:
    static std::unordered_map<int, ItemDef> data;

    static const ItemDef& Get(int id)
    {
        return data.at(id);
    }
};