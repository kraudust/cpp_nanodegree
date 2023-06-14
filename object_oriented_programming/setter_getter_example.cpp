#include <string>
#include <cstring>
#include <iostream>

class Car {
private:
    float horsepower_;
    float weight_;
    char* brand_;

public:
    float Horsepower() const {return horsepower_;}
    void Horsepower(float hp);
    float Weight() const {return weight_;}
    void Weight(float lbs);
    std::string Brand() const;
    void Brand(std::string make);
};

// Define getters
std::string Car::Brand() const {
    std::string result = "Brand name: ";
    // Specifying string for output of brand name
    result += Car::brand_;
    return result;
};

// Define setters
void Car::Horsepower(float hp){
    if (horsepower_ > 0){
        horsepower_ = hp;
    }
}

void Car::Weight(float lbs){
    if (lbs > 0){
        weight_ = lbs;
    }
}

void Car::Brand(std::string brand_name) {
    // Initialization of char array
    Car::brand_ = new char[brand_name.length() + 1];
    // copying every character from string to char array;
    strcpy(Car::brand_, brand_name.c_str());
}

// Test in main()
int main() 
{
    Car car;
    car.Brand("Peugeot");
    std::cout << car.Brand() << "\n";   
}