#ifndef TProiz_H
#define TProiz_H
#include <iostream>

class Proiz
{
private:
  std::string Manufacturer;
  std::string Model;

public:
  Proiz();
  ~Proiz();
  Proiz(
      std::string lManufacturer,
      std::string lModel
      );

  void setManufacturer(const std::string lManufacturer);
  std::string getManufacturer() const;

  void setModel(const std::string lModel);
  std::string getModel() const;

  void show();
};

#endif // TProiz_H
