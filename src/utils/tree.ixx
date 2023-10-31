

export module aoc.tree;
import std;

export
{
	/* 2022 day 7
		struct file
		{
			std::string name;
			i64         size{0};
		};

		struct directory
		{
			directory(std::string n, i64 s) : name(n), size(s) {}
			std::string            name;
			i64                    size{0};
			std::vector<file>      files;
			std::vector<directory> dirs;
		};

		i64 dir_visitor(directory &dir, std::vector<directory> &dirs)
		{
			for (auto &d : dir.dirs)
				dir.size += dir_visitor(d, dirs);

			for (const auto &f : dir.files)
				dir.size += f.size;

			dirs.push_back(directory(dir.name, dir.size));
			return dir.size;
		}
	*/

} // namespace aoc
