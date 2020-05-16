// Incorporating several different ideas here:
// Constraining input to be numeric: https://codereview.stackexchange.com/questions/161061/user-input-validation-that-might-be-unbreakable-for-c
// Lambda for validator: https://stackoverflow.com/questions/25666047/c-input-validation

#include <functional>
#include <iostream>
#include <limits>
#include <string>
#include <type_traits>

using namespace std;

namespace MyIO {
	// REQUIRES C++20
    template<typename T>
    concept Arithmetic = std::is_arithmetic<T>::value;

    template<Arithmetic A>
    A add(A x, A y) { return x + y; }
    
    template<typename T>
    concept Printable = requires(T elem, std::ostream& os) {
		{ os << elem };
    };
    
    template<Printable P>
    void printIt(P a) { std::cout << a << std::endl; }
	
	/**
	 * Prints a prompt to STDOUT, reads in an Arithmetic value from STDIN, and validates the input using `validator`
	 * 	as a predicate.
	 * @tparam A The type of the user's input. Must fulfill Arithmetic concept.
	 * @param prompt Message to display to user.
	 * @param validator return-type: bool argument-type: Arithmetic A lambda that determines the predicate on the input.
	 * 		e.g., [] (int arg) -> bool { return (arg >= 0 && arg <= 10); }
	 * @return An Arithmetic value, valid for the given predicate.
	 *
	 *
	 */
	template <Arithmetic A>
	A input(const std::string& prompt, std::function <bool(A)> validator) {
		A user_input {};
		
		// Shorthand to clean up the for-loop.
		auto prompt_for_input = [&]() {
			std::cout << prompt;
			std::cin >> user_input;
		};
		
		for (prompt_for_input(); !validator(user_input); prompt_for_input()) {
			
			std::cout << "Invalid input. Please try again." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		return user_input;
	}
}

struct Point {
	float x;
	float y;
	float z;
};

std::ostream& operator << (std::ostream& os, const Point& p) {
	os << p.x << ' ' << p.y << ' ' << p.z << '\n';
	return os;
}



auto main() -> int {
  int x = 0;
  
  Point a {5.0, 10.0, 20.0 };
  
  MyIO::printIt(x);
  
  MyIO::printIt(a);
  
  auto y = MyIO::add(2, 3);
  
  auto my_input = MyIO::input<int>("Enter a number between 0 and 10: ", [] (int arg) -> bool {
		return (arg >= 0 && arg <= 10);
  });
	
  auto my_input_2 = MyIO::input<double>("Enter a floating point number between 0 and 10: ", [] (int arg) -> bool {
		return (arg >= 0 && arg <= 10);
  });
  
  return 0;
}
