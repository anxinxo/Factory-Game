#pragma once

#include <core/ItemDatabase.hpp>
#include <vector>

// 1 stack loại item
struct ItemStack
{
    int id = -1;
    int amount = 0;

    bool empty() const { return id == -1 || amount == 0; }
};

// 1 slot inventory
struct InventorySlot
{
    ItemStack stack;
};

class Inventory
{
private:
    std::vector<InventorySlot> slots;
public:
    Inventory(int size);

    int Size() const;

    const InventorySlot& GetSlot(int i) const;

    bool AddItem(int id, int amount);

    bool RemoveItem(int id, int amount);

    int CountItem(int id) const;

    void SwapSlot(int a, int b);
};
