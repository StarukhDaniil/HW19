#include <iostream>
#include <boost/program_options.hpp>

int main(int argc, char* argv[]) {
	try {
		boost::program_options::options_description desc("Allowed options");
		desc.add_options()
			("help,h", "Help message")
			("name,n", boost::program_options::value<std::string>(), "Your name")
			("age,a", boost::program_options::value<int>(), "Your age");
		boost::program_options::variables_map vm;
		boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
		vm.notify();

		if (vm.count("help")) {
			std::cout << desc << std::endl;
		}
		if (vm.count("name")) {
			std::cout << "Your name is " << vm["name"].as<std::string>() << std::endl;
		}
		if (vm.count("age")) {
			std::cout << "Your age is " << vm["age"].as<int>() << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}