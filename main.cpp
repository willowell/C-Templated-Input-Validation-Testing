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
	/* REQUIRES C++20
    template<typename T>
    concept Arithmetic = std::is_arithmetic<T>::value;

    template<Arithmetic A>
    A add2(A x, A y) { return x + y; }
    */
	template <typename T>
	using Arithmetic = typename
			std::enable_if<std::is_arithmetic<T>::value, T>::type;
	
	/**
	 * Prints a prompt to STDOUT, reads in a T value from STDIN, and validates the input using `validator`
	 * 	as a predicate.
	 * @tparam T The type of the user's input.
	 * @param prompt Message to display to user.
	 * @param validator return-type: bool argument-type: T A lambda that determines the predicate on the input.
	 * @return A T value, valid for the given predicate.
	 *
	 *
	 */
	template <typename T>
	T input(const std::string& prompt, function <bool(T)> validator) {
		T user_input {};
		
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
		return user_input;
	}
}

template<class T>
void get(typename std::enable_if<std::is_arithmetic<T>::value, T>::type &val,
           const T& low, const T& high, std::string message)
{
    for (std::cout << message; 
            !(std::cin >> val) || val < low || val > high; 
            std::cout << message) 
    { 
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

template <typename T>
T getValidatedInput(function <bool(T)> validator) {
    T tmp;
    cin >> tmp;
    if (!validator(tmp)) {
        throw ios_base::failure("Invalid input.");
    }
    return tmp;
}


int main() {
  int x = 0;
  
  //get<int>(x, 0, 10, "enter a number between (0, 10): ");

  //input = getValidatedInput<int>([] (int arg) -> bool { return (arg > 0 && arg < 100); });
  
  int my_input = MyIO::input<int>("Enter a number between 0 and 10: ", [] (int arg) -> bool {
		return (arg >= 0 && arg <= 10);
	});
	
  double my_input_2 = MyIO::input<double>("Enter a number between 0 and 10: ", [] (int arg) -> bool {
		return (arg >= 0 && arg <= 10);
  });
  
  auto my_str = MyIO::input<std::string>("What's my name? ", [] (const std::string& arg) -> bool {
  	return (arg == "Bob");
  });
  
  return 0;
}
