#include <iostream>
#include "plotter.hpp"

Plotter::Plotter():
  Proiz("", ""),
  FormFactor(Def),
  Format(Default),
  Price(0)
{

}

Plotter::~Plotter()
{

}

Plotter::Plotter(Proiz lProiz
           , Plotter::EnumFormFactor lFormFactor
           , Plotter::EnumFormat lFormat
           , Plotter::Properties lProperties
           , int lPrice):
  Proiz(lProiz),
  FormFactor(lFormFactor),
  Format(lFormat),
  properties(lProperties),
  Price(lPrice)
{

}

Plotter::Plotter(const Plotter &rhs):
  Proiz(rhs),
  FormFactor(rhs.FormFactor),
  Format(rhs.Format),
  properties(rhs.properties),
  Price(rhs.Price)
{

}

Plotter Plotter::operator=(const Plotter &rhs)
{
  if (this == &rhs)
    return *this;

  Proiz::operator=(rhs);
  FormFactor = rhs.FormFactor;
  Format = rhs.Format;
  properties = rhs.properties;
  Price = rhs.Price;
  return *this;
}

void Plotter::setFormFactor(const Plotter::EnumFormFactor lFormFactor)
{
  FormFactor = lFormFactor;
}

Plotter::EnumFormFactor Plotter::getFormFactor() const
{
  return FormFactor;
}

void Plotter::setFormat(const Plotter::EnumFormat lFormat)
{
  Format = lFormat;
}

Plotter::EnumFormat Plotter::getFormat() const
{
  return Format;
}

void Plotter::setProperties(const Plotter::Properties lProperties)
{
  properties = lProperties;
}

Plotter::Properties Plotter::getProperties() const
{
  return properties;
}

void Plotter::setPrice(const int lPrice)
{
  Price = lPrice;
}

int Plotter::getPrice() const
{
  return Price;
}

void Plotter::show()
{
  const char *StrFormFactor[]={"Default", "Jet", "Uneversal"};
  const char *StrFormat[]={"Default", "A0", "A1", "A2"};
  Proiz::show();
  std::cout << "Plotter type: " << StrFormFactor[FormFactor] << "\n" <<
               "Format type: " << StrFormat[Format]<<"\n" <<
               "Timings:\n" <<
               "\tSPEED_PRINT   " << properties.SPEED_PRINT<<"\n" <<
               "\tMax widht print" << properties.Max_widht_print<<"\n" <<
               "Price: " << Price << std::endl;
}
