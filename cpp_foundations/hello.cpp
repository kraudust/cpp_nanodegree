#include <iostream>
#include <chrono>
#include <unistd.h>

int main() {
  std::chrono::steady_clock::time_point t0;
  std::chrono::steady_clock::time_point t1;
  t0 = std::chrono::steady_clock::now();
  std::cout << "Hello!\n";
  sleep(5);
  t1 = std::chrono::steady_clock::now();

  std::chrono::duration<double> elapsed_seconds = t1 - t0;
  std::chrono::duration<int64_t, std::micro> microseconds = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
  // std::chrono::microseconds().count();

  std::cout << "seconds: " << elapsed_seconds.count() << std::endl;
  std::cout << "microseconds: " << microseconds.count() << std::endl;

}

