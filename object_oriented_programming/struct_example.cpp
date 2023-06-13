#include <cassert>
#include <iostream>

struct Date {
 public:
  int Day() { return day; }
  void Day(int day) {this->day = day; }
  int Month() { return month; }
  void Month(int month) { this->month = month; }
  int Year() { return year; }
  void Year(int year) { this->year = year; }
 private:
  int day{1};
  int month{1};
  int year{0};
};

class DateClass {
  public:
    int Day() { return day_; }
    int Month() { return month_; }
    int Year() { return year_; }
    void Day(int d) {
      if (d >= 1 && d <= 31){
        day_ = d;
      }
    }
    void Month(int m) {
      if (m >= 1 && m <= 12){
        month_ = m;
      }
    }
    void Year(int y) {year_ = y;}

 private:
  int day_{1};
  int month_{1};
  int year_{0};
};

// Test in main
int main()
{
  DateClass date_class;
  date_class.Day(-1);
  date_class.Month(14);
  date_class.Year(2000);
  assert(date_class.Day() != -1);
  assert(date_class.Month() != 14);
  assert(date_class.Year() == 2000);

  Date date;
  date.Day(29);
  date.Month(8);
  date.Year(1981);
  assert(date.Day() == 29);
  assert(date.Month() == 8);
  assert(date.Year() == 1981);
  std::cout << date.Day() << "/" << date.Month() << "/" << date.Year() << "\n";
}