#include <iostream>
#include <filesystem>
#include <optional>
#include <span>
#include <variant>
#include <vector>


namespace fs = std::filesystem;

// │ 
//
// └─

// ├
//
// ─
//
// // └

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

		FileObjectPrinter(const PrintOptions& printOptions) : mOptions{printOptions}{

		}
		void print(){
			std::visit(FileObjectPrinter {mOptions}, 
				PrintableFileObject {Root {  mOptions.dir_to_print }});

		}
		void operator()(const File &file){
			if(exceedDepth()) return;
			std::cout << file.path.filename() << '\n';

		}


		void operator()(const Directory &directory){

			if (exceedDepth()){
				return ;
			}
			std::cout << directory.path.filename() << '\n';
			printChildren(directory.path);

		}

		void operator()(const Root &root){
			if(exceedDepth()) return;
			std::cout << ".\n";
			printChildren(root.path);

		}
		void printPrefix(bool is_last){

			for(bool has_more: m_stack){

				if(has_more){

					std::cout << "│ " ;

				} else {

					std::cout << "  ";

				}
			}

			std::cout << (is_last ? "└──" : "├──");
// ─



		}

		void printChildren(const fs::path& path){
			if(mOptions.maxDepth.has_value() && m_stack.size() >= *mOptions.maxDepth) return;

			std::vector<fs::path> children{};

			for (const auto& child: fs::directory_iterator(path)){
				children.push_back(child);
			}

			for(size_t i {}; i < children.size(); i++){

				bool is_last {i + 1 == children.size()};

				printPrefix(is_last);

				m_stack.push_back(!is_last);

				std::visit(*this, createPrintable(children[i]));

				m_stack.pop_back();

			}

		}

		PrintableFileObject createPrintable(const fs::path& path){
			if(fs::is_directory(path)){
				return Directory{path};
			}

			return File{path};
		}


		bool exceedDepth(){
			return mOptions.maxDepth.has_value() && m_stack.size() > *mOptions.maxDepth;
		}

	private:
		std::vector<bool> m_stack{};
		PrintOptions mOptions{};
		





};

int main(int argc, char **argv){

	auto print_options{createPrintOptions({argv, static_cast<size_t>(argc)})};


	std::cout <<" ---OPTION----" << '\n';

	std::cout << "dir to print " << print_options.dir_to_print.filename() << '\n';
	std::cout << "max Depth " << (print_options.maxDepth.has_value() ? std::to_string(print_options.maxDepth.value()) : "infinite") << '\n';

	FileObjectPrinter printer{print_options};

	printer.print();


	return 0;
}
