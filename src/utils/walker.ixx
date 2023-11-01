export module aoc.walker;
import aoc.vec;

export
{
	struct walker2d
	{
		ivec2 position;
	};
}

#if 0
class Walker final
{

public:
    Walker() {}
    Walker(ivec2 p) : pos(p) {}
    Walker(i64 x, i64 y) : pos(x, y) {}
    Walker *operator+=(const Walker &w)
    {
        pos.x += w.pos.x;
        pos.y += w.pos.y;
        return this;
    }

    Walker *operator-=(const Walker &w)
    {
        pos.x -= w.pos.x;
        pos.y -= w.pos.y;
        return this;
    }

    void  set(ivec2 p) { pos = p; }
    ivec2 get() const { return pos; }
    ivec2 in_front()
    {
        forward();
        auto front = pos;
        backward();
        return front;
    }
    ivec2 in_back()
    {
        backward();
        auto back = pos;
        forward();
        return back;
    }

    void north(i64 value = 1) noexcept { *this -= Walker{0, value}; }
    void south(i64 value = 1) noexcept { *this += Walker{0, value}; }
    void east(i64 value = 1) noexcept { *this += Walker{value, 0}; }
    void west(i64 value = 1) noexcept { *this -= Walker{value, 0}; }

    void left(i64 times) noexcept { angle = (angle + (360 - (times))) % 360; }
    void right(i64 times) noexcept { angle = (angle + (times)) % 360; }

    void turn_left(i64 rotations = 1)
    {
        left(rotations * 270);

        //   while (rotations--)
        //       *this = {y, -x};
    }

    void turn_right(i64 rotations = 1)
    {
        right(rotations * 270);
        // while (rotations--)
        //    *this = {-y, x};
    }

    void forward(i64 times = 1)
    {

        switch (angle)
        {
            case 0:
                east(times);
                break;
            case 90:
                north(times);
                break;
            case 180:
                west(times);
                break;
            case 270:
                south(times);
        }
    }

    void backward(i64 times = 1)
    {
        turn_right(2);
        forward(times);
        turn_right(2);
    }

    u64 manhattan_distance(i64 dx = 0, i64 dy = 0) const noexcept
    {
        //
        return static_cast<u64>(std::abs(dx - pos.x) + std::abs(dy - pos.y));
    }

    ivec2 pos{};

    i64 angle{0};
};

#endif
