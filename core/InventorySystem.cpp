#include <core/InventorySystem.hpp>

Inventory::Inventory(int size) {}

int Inventory::Size() const
{
    return slots.size();
}

const InventorySlot &Inventory::GetSlot(int i) const
{
    return slots[i];
}

bool Inventory::AddItem(int id, int amount)
{   
    const ItemDef& def = ItemDatabase::Get(id);

    // Nếu stack được
    if(def.stackable)
    {
        for(auto& slot: slots)
        {
            if(!slot.stack.empty() && slot.stack.id == id)
            {
                int canAdd = def.maxStack - slot.stack.amount;
                int add = std::min(canAdd, amount);

                slot.stack.amount += add;
                amount -= add;
                if(amount == 0) return true;
            }
        }
    }

    // Bỏ vào các slot trống
    for(auto& slot: slots)
    {
        if(slot.stack.empty())
        {
            int add = std::min(def.maxStack, amount);
            slot.stack = {id, add};
            amount -= add;
            if(amount == 0) return true;
        }
    }

    return false; // inventory full
}

bool Inventory::RemoveItem(int id, int amount)
{   
    for(auto& slot: slots)
    {
        if(!slot.stack.empty() && slot.stack.id == id)
        {
            int take = std::min(slot.stack.amount, amount);
            
            slot.stack.amount -= take;
            amount -= take;
            if(slot.stack.amount == 0) slot.stack = {};
        
            if(amount == 0) return true;
        }
    }

    return false; // Không đủ item cần xóa
}

int Inventory::CountItem(int id) const
{   
    int total = 0;
    for(const auto& slot: slots)
    {
        if(!slot.stack.empty() && slot.stack.id == id) total += slot.stack.amount;
    }

    return total;
}

void Inventory::SwapSlot(int a, int b)
{
    std::swap(slots[a], slots[b]);
}
