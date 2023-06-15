#include <cassert>
#include <cmath>
#include <stdexcept>

class Sphere {
public:
  /**
   * @brief Sphere constructor
   *
   * @param[in] radius: sets the radius of the sphere
   * 
   * @throws invalid_argument exception if values passed in <= 0
   */
  Sphere(int radius);

  // Accessors
  int Radius() const { return radius_; }
  int Volume() const { return volume_; }

  // Mutators
  /**
   * @brief radius_setter
   *
   * @param[in] radius: sets the radius of the sphere
   * 
   * @throws invalid_argument exception if values passed in <= 0
   */
  void Radius(int radius);

private:
  // Private members
  static float constexpr kPi{3.14159}; 
  int radius_;
  float volume_;
  /**
   * @brief Checks that the set radius is > 0, if so sets the volume
   * 
   * @throws invalid_argument exception if values passed in <= 0
   */
  void SetVolume();
};

Sphere::Sphere(int radius) : radius_(radius)
{
  SetVolume();
}

void Sphere::SetVolume()
{
  if (radius_ <= 0) {
    throw std::invalid_argument("radius must be positive");
  }
  volume_ = kPi * 4./3. * pow(radius_, 3);
}

void Sphere::Radius(int radius)
{
  radius_ = radius;
  SetVolume();
}

// Show static members example with this class
class Sphere2 {
public:
  static float Volume(int radius)
  {
    return pi_ * 4/3 * pow(radius,3);
  }
private:
  static float constexpr pi_{3.14159};
};

// Test
int main(void) {
  Sphere sphere(5);
  assert(sphere.Radius() == 5);
  assert(abs(sphere.Volume() - 523.6) < 1);

  sphere.Radius(3);
  assert(sphere.Radius() == 3);
  assert(abs(sphere.Volume() - 113.1) < 1);

  bool caught{false};
  try {
    sphere.Radius(-1);
  } catch (...) {
    caught = true;
  }
  assert(caught);

  assert(abs(Sphere2::Volume(5) - 523.6) < 1);
}
