#include <cassert>
#include <stdexcept>

class Pyramid
{
public:
  /**
   * @brief Pyramid constructor
   *
   * @param[in] length: sets the length of the pyramid
   * @param[in] width: sets the width of the pyramid
   * @param[in] height: sets the height of the pyramid
   * 
   * @throws invalid_argument exception if values passed in <= 0
   */
  Pyramid(int length, int width, int height);

  // Accessors
  int Length() const
  {
    return length_;
  }
  int Width() const
  {
    return width_;
  }
  int Height() const
  {
    return height_;
  }

  // Mutators
  /**
   * @brief length_ mutator
   *
   * @param[in] length: sets the length of the pyramid
   * 
   * @throws invalid_argument exception if value passed in <= 0
   */
  void Length(int length);

  /**
   * @brief width_ mutator
   *
   * @param[in] width: sets the width of the pyramid
   * 
   * @throws invalid_argument exception if value passed in <= 0
   */
  void Width(int width);

  /**
   * @brief height_ mutator
   *
   * @param[in] heigth: sets the height of the pyramid\
   * 
   * @throws invalid_argument exception if value passed in <= 0
   */
  void Height(int height);

  // Compute Volume
  /**
   * @brief Computes and returns the volume of the pyramid
   *
   * @return Float containing the volume of the pyramid
   */
  float Volume();

private:
  int length_;
  int width_;
  int height_;
};

Pyramid::Pyramid(int length, int width, int height)
{
  Length(length);
  Width(width);
  Height(height);
}
void Pyramid::Length(int length)
{
  if (length > 0) {
    length_ = length;
  } else {
    throw std::invalid_argument("Value must be greater than 0.");
  }
}
void Pyramid::Width(int width)
{
  if (width > 0) {
    width_ = width;
  } else {
    throw std::invalid_argument("Value must be greater than 0.");
  }
}
void Pyramid::Height(int height)
{
  if (height > 0) {
    height_ = height;
  } else {
    throw std::invalid_argument("Value must be greater than 0.");
  }
}
float Pyramid::Volume()
{
  return length_ * width_ * height_ / 3.0f;
}

// Test
int main() {
  Pyramid pyramid(4, 5, 6);
  assert(pyramid.Length() == 4);
  assert(pyramid.Width() == 5);
  assert(pyramid.Height() == 6);
  assert(pyramid.Volume() == 40);

  bool caught{false};
  try {
    Pyramid invalid(-1, 2, 3);
  } catch (...) {
    caught = true;
  }
  assert(caught);
}
