#include "proiz.hpp"
#include <iostream>

using namespace std;

Proiz::Proiz():
  Manufacturer(""),
  Model("")
{

}

Proiz::~Proiz()
{

}

Proiz::Proiz(std::string lManufacturer, std::string lModel):
  Manufacturer(lManufacturer),
  Model(lModel)
{

}

void Proiz::setManufacturer(const string lManufacturer)
{
  Manufacturer = lManufacturer;
}

string Proiz::getManufacturer() const
{
  return Manufacturer;
}

void Proiz::setModel(const string lModel)
{
  Model = lModel;
}

string Proiz::getModel() const
{
  return Model;
}

void Proiz::show()
{
  cout<<"Manufacturer: "<< Manufacturer << "\n"
        <<"Model: "<<Model<<"\n";
}
