export module aoc.walker;
import aoc.vec;
import aoc.grid;
export
{
	// Direction
	struct direction4
	{
		ivec2 dir{north};

		void rotate_cw(int count = 1)
		{
			while (count--)
				dir.rotate_cw();
		}

		void rotate_cw(ivec2 point, int count = 1)
		{
			while (count--)
				dir.rotate_cw(point);
		}

		void turn_left(int count = 1)
		{
			while (count--)
			{
				dir.rotate_cw();
				dir.rotate_cw();
				dir.rotate_cw();
			}
		}

		void turn_right(int count = 1)
		{
			while (count--)
			{
				dir.rotate_cw();
			}
		}

		operator ivec2() const { return dir; };

		std::string to_string() const { return dir_to_string.at(dir); }
	};

	struct walker2d
	{
		ivec2      position;
		direction4 dir;

		void face_north() { dir.dir = north; }

		void face_south() { dir.dir = south; }

		void face_east() { dir.dir = east; }

		void face_west() { dir.dir = west; }

		void turn_left(int times = 1) { dir.turn_left(times); }

		void turn_right(int times = 1) { dir.turn_right(times); }

		void forward(int steps = 1)
		{
			while (steps--)
				position += dir;
		}

		void backward(int steps = 1)
		{
			while (steps--)
				position -= dir;
		}

		u64 distance(ivec2 from = ZERO_IVEC2) const noexcept { return position.distance(from); };
	};

} // export

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
