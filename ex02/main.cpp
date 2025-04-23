#include "PmergeMe.hpp"


int	main(int argc, char **argv)
{
	if (argc < 2) {
        std::cerr << "Usage: ./PmergeMe [numbers]" << std::endl;
        return (1);
    }

	std::vector<int> vec;

	try {
		vec = parseArgs(&argv[1]);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return (1);
	}
	std::deque<int> deque(vec.begin(), vec.end());
	startSorts(vec, deque);
	return (0);
}