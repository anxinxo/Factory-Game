#pragma once

class worldobjects;

class CellView
{
public:
    virtual bool isInside(int dx, int dy) const = 0;

    virtual TTYPE getCellType(int dx, int dy) const = 0;
    virtual RESOURCE getResource(int dx, int dy) const = 0;
    virtual float getAmount(int dx, int dy) const = 0;
    virtual const worldobjects* getObject(int dx, int dy) const = 0;

    virtual ~CellView() = default;
};