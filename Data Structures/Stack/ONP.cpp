#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include "stack.h"

template <typename T> 
class ONP{
    MyStack <int> numberStack;

    public:
     int myOnp(std::vector<std::string> input){
        for(std::string item : input){
            int first = 0;
            int second = 0;

                if(item == "/"){

                    assert(!numberStack.empty());
                    first = numberStack.top();
                    numberStack.pop();

                    assert(!numberStack.empty());
                    second = numberStack.top();
                    numberStack.pop();

                    if(first != 0){
                    numberStack.push(second/first);
                    }
                    else{
                        std::cerr << "Dzielenie przez zero" << std::endl;
                    }
                }

                else if(item == "*"){

                    assert(!numberStack.empty());
                    first = numberStack.top();
                    numberStack.pop();

                    assert(!numberStack.empty());
                    second = numberStack.top();
                    numberStack.pop();

                    numberStack.push(second*first);
                }

                else if(item == "+"){

                    assert(!numberStack.empty());
                    first = numberStack.top();
                    numberStack.pop();

                    assert(!numberStack.empty());
                    second = numberStack.top();
                    numberStack.pop();

                    numberStack.push(second+first);
                }

                else if(item == "-"){

                    assert(!numberStack.empty());
                    first = numberStack.top();
                    numberStack.pop();

                    assert(!numberStack.empty());
                    second = numberStack.top();
                    numberStack.pop();

                    numberStack.push(second-first);
                }

                else{

                    size_t pos;
                    assert(!numberStack.full());
                    numberStack.push(std::stoi(item, &pos));
                }
            }

        assert(!numberStack.empty());
        return numberStack.top();
    }


    void run(){

        std::vector<std::string> input { "-6", "2", "/" };

        int result = myOnp(input);
        assert(result == -3);

        std::vector<std::string> input8{"7", "2", "3", "*", "-"};

        result = myOnp(input8);
        assert(result == 1);

        std::vector<std::string> input13{"-4", "5", "*", "8", "+"};

        result = myOnp(input13);
        assert(result == -12);

        std::vector<std::string> input14{"2", "3", "*", "3", "/", "5" , "+"}; 

        result = myOnp(input14);
        assert(result == 7);

        std::cout<<"Bledow nie ma, algorytm dziala poprawnie"<<std::endl;

    }
};

int main(){
    ONP<int> calculator;
    calculator.run();
    return 0;
}