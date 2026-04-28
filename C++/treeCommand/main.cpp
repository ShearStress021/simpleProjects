#include <iostream>
#include <filesystem>
#include <optional>
#include <span>
#include <variant>


namespace fs = std::filesystem;

struct PrintOptions {
	std::optional<size_t> maxDepth{};
	fs::path dir_to_print{fs::current_path()};
};


static constexpr std::string_view PATH_ARGUMENT_BEGIN{"--path="};


int getItem(std::optional<int> x){
	return x.has_value() ?  x.value() + 1 : 0;
}

PrintOptions createPrintOptions(std::span<char*> arguments){
	PrintOptions print_options{};

	size_t i{1};

	while (i < arguments.size()){
		std::string argument{arguments[i]};
		i++;

		if (argument == "-L"){
			if(arguments.size() == i){
				std::cerr << "wrong usecase of -L. Number argument required after -L" << '\n';
				continue;
			}

			std::string number_argument{arguments[i]};
			i++;

			try {
				print_options.maxDepth = std::stoul(number_argument);
			}catch(...){

				std::cerr << "wrong usecase of -L. An integer should be placed after -L." << '\n';
				continue;

			}

		}

		if(argument.starts_with(PATH_ARGUMENT_BEGIN)){

			fs::path path {argument.substr(PATH_ARGUMENT_BEGIN.size())};
			if(!fs::exists(path)){

				std::cerr << "Provide a valid path" << '\n';
				continue;

			}
			print_options.dir_to_print = path;
		

	    }
	}

	return print_options;

}

struct File{
	fs::path path;
};

struct Directory{
	fs::path path;
};
struct Root{
	fs::path path;
};
using PrintableFileObject  = std::variant<File,Directory, Root>;


class FileObjectPrinter {

	public:
		void operator()(const File &file){

		}

		void operator()(const Directory &directory){

		}

		void operator()(const Root &root){

		}
	private:





};

int main(int argc, char **argv){

	auto print_options{createPrintOptions({argv, static_cast<size_t>(argc)})};


	std::cout <<" ---OPTION----" << '\n';

	std::cout << "dir to print " << print_options.dir_to_print.filename() << '\n';
	std::cout << "max Depth " << (print_options.maxDepth.has_value() ? std::to_string(print_options.maxDepth.value()) : "infinite") << '\n';

	return 0;
}
