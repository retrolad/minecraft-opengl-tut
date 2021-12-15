#ifndef NONMOVABLE_H
#define NONMOVABLE_H

class NonMovable 
{
    public:
        NonMovable(NonMovable&&) = delete;

        NonMovable& operator=(NonMovable&&) = delete;

    protected:
        NonMovable() = default;
};

#endif 