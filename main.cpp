// Incorporating several different ideas here:
// Constraining input to be numeric: https://codereview.stackexchange.com/questions/161061/user-input-validation-that-might-be-unbreakable-for-c
// Lambda for validator: https://stackoverflow.com/questions/25666047/c-input-validation

#include <functional>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

template<class T>
void input(typename std::enable_if<std::is_arithmetic<T>::value, T>::type &val, 
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
  
  input<int>(x, 0, 10, "enter a number between (0, 10): ");

  int input = getValidatedInput<int>([] (int arg) -> bool {
    return arg >= 0;
  });

  input = getValidatedInput<int>([] (int arg) -> bool { return (arg > 0 && arg < 100); });
}
