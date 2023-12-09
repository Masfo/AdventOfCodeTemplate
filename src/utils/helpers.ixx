export module aoc.helpers;
import std;
import aoc.debug;
import aoc.stringhelper;
import aoc.types;

export
{
	// sort
	template<typename T>
	void sort(std::vector<T> & v)
	{
		std::ranges::sort(v);
	};

	template<typename T>
	void sort_greater(std::vector<T> & v)
	{
		std::ranges::sort(v, std::greater{});
	}

	// compare keys
	// example: const auto [min, max] = std::ranges::minmax_element(map, compare_keys);
	auto compare_keys         = [](const auto &e1, const auto &e2) { return e1.first < e2.first; };
	auto compare_keys_greater = [](const auto &e1, const auto &e2) { return e1.first > e2.first; };

	// compare values
	// example: const auto [min, max] = std::ranges::minmax_element(map, compare_values);
	auto compare_values         = [](const auto &e1, const auto &e2) { return e1.second < e2.second; };
	auto compare_values_greater = [](const auto &e1, const auto &e2) { return e1.second > e2.second; };

	// ###########################

	template<typename T>
	concept ContainerResize = requires(T a) {
		a.size();
		a.resize(0);
		a.begin();
		a.rbegin();
	};

	// take n elements
	template<ContainerResize T>
	auto take(const T &container, size_t count)
	{
		assert_msg(count <= container.size(), "Count is larger than the container");

		if (count == container.size())
			return container;

		T result{};
		result.resize(count);
		std::ranges::copy_n(container.begin(), count, result.begin());
		return result;
	}

	// last n elements
	template<ContainerResize T>
	auto last(const T &container, size_t count)
	{
		assert_msg(count <= container.size(), "Count is larger than the container");

		if (count == container.size())
			return container;

		T result{};
		result.resize(count);
		std::ranges::copy_n(container.rbegin(), count, result.rbegin());
		return result;
	}

	// top
	auto top(const auto &container, size_t count)
	{
		assert_msg(container.size() <= count, "Container not big enough");
		auto c = container;
		std::ranges::sort(c);
		return take(c, count);
	}

	auto top(const auto &container) { return top(container, 1)[0]; }

	// bottom
	auto bottom(const auto &container, size_t count)
	{
		assert_msg(container.size() <= count, "Container not big enough");

		auto c = top(container, count);
		return last(c, count);
	}

	auto bottom(const auto &container) { return bottom(container, 1)[0]; }

	// move index
	template<typename T>
	void move_index(T & v, size_t oldIndex, size_t newIndex)
	{
		if (oldIndex > v.size() || newIndex > v.size() || oldIndex == newIndex)
			return;

		if (oldIndex > newIndex)
			std::rotate(v.rend() - oldIndex - 1, v.rend() - oldIndex, v.rend() - newIndex);
		else
			std::rotate(v.begin() + oldIndex, v.begin() + oldIndex + 1, v.begin() + newIndex + 1);
	}

	template<typename T, typename U>
	size_t index_of(T & v, U find)
	{
		auto result = std::ranges::find(v, find);
		if (result == v.end())
		{
			dbgln("index_of: could not find '{}' from container", find);
			return std::numeric_limits<size_t>::max();
		}

		return std::ranges::distance(v.begin(), result);
	}

	template<typename T>
	bool contains(const std::vector<T> &v, const auto &value) noexcept
	{
		return std::find(v.begin(), v.end(), value) != v.end();
	}

	// Shunting Yard

	auto apply_binary_op(std::deque<i64> & values, std::vector<char> & op)->i64
	{
		assert_msg(values.size() >= 2, "There should be two values for binary operations");

		auto v1 = values.front();
		values.pop_front();

		auto v2 = values.front();
		values.pop_front();

		i64 calc = 0;
		switch (op.back())
		{
			case '+': calc = v1 + v2; break;
			case '-': calc = v1 - v2; break;
			case '*': calc = v1 * v2; break;
			case '/': calc = v1 / v2; break;
			case '%': calc = v1 % v2; break;

			default: panic("'{}' not implemented", op.back());
		}
		op.pop_back();
		values.push_back(calc);
		return calc;
	};
	using PrecedenceType = std::unordered_map<char, i32>;
	/*
		default_precedence['*'] = 10;
		default_precedence['/'] = 10;
		default_precedence['%'] = 10;

		default_precedence['+'] = 5;
		default_precedence['-'] = 5;

		default_precedence['('] = 0;
		default_precedence[')'] = 0;
	*/

	auto shunting(std::string_view input, const PrecedenceType &precedence)->i64
	{
		std::vector<char> operators;
		std::deque<i64>   values;
		for (int i = 0; i < input.size(); ++i)
		{
			char c = input[i];
			switch (c)
			{
				case ' ': continue;
				case '(': operators.push_back(c); continue;
				case ')':
				case '+':
				case '-':
				case '*':
				case '%':
				case '/':
				{
					while (!operators.empty() && operators.back() != '(' && (precedence.at(operators.back()) >= precedence.at(c)))
						apply_binary_op(values, operators);

					if (c == ')')
					{
						operators.pop_back();
						continue;
					}

					operators.push_back(c);
					continue;
				}
				default:
				{
					assert_msg(isdigit(c), std::format("Only digits supported. Trying to parse '{}'", c));

					i64 digit = 0;
					while (isdigit(c) && i <= input.size())
					{
						digit = digit * 10 + to_number(c);

						if (i + 1 >= input.size())
							break;
						if (!isdigit(input[i + 1]))
							break;

						c = input[++i];
					}

					values.push_back(digit);
					continue;
				}
			}
		}

		while (!operators.empty())
			apply_binary_op(values, operators);

		assert_msg(values.size() == 1, "There should be just one answer on the stack");

		return values.back();
	};

	class pratt final
	{
	public:
		enum TokenType
		{
			NUMBER,
			OPERATOR,
			PAREN_OPEN,
			PAREN_CLOSE
		};

		struct token
		{
			TokenType   type;
			std::string value;
		};

		pratt(std::string_view i)
			: input(i)
		{
		}

		auto parse() { return parse_expression(0); }

		auto parse_expression(int precedence) -> i64 { return precedence; }

	private:
		std::string input;
		i64         pos;
	};
}
