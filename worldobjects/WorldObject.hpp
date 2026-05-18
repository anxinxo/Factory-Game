class worldobjects
{
public:
    virtual ~worldobjects() = default;

    virtual const std::vector<std::unique_ptr<PlacementRule>>& getRules() const = 0;

    bool canPlaceOn(const CellView& view) const
    {
        for (const auto& r : getRules())
            if (!r->check(view)) return false;
        return true;
    }

    virtual void update(float dt) {}
    virtual void draw(sf::RenderWindow& window) {}
};