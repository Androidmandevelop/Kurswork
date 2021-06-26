#ifndef PLOTTER_H
#define PLOTTER_H
#include "proiz.hpp"


class Plotter : public Proiz
{
public:
  enum EnumFormFactor{Def,Jet,Uneversal};
  enum EnumFormat{Default,A0,A1,A2};
  struct Properties
  {
    short SPEED_PRINT;
    short Max_widht_print;
  };

private:
  EnumFormFactor FormFactor;
  EnumFormat Format;
  Properties properties;
  int Price;

public:
  Plotter();
  ~Plotter();
  Plotter(
      Proiz lProiz,
      EnumFormFactor lFormFactor,
      EnumFormat lFormat,
      Properties lProperties,
      int lPrice
      );
  Plotter(const Plotter& rhs);

  Plotter operator=(const Plotter& rhs);

  void setFormFactor(const EnumFormFactor lFormFactor);
  EnumFormFactor getFormFactor() const;

  void setFormat (const EnumFormat lFormat);
  EnumFormat getFormat () const;

  void setProperties (const Properties lProperties);
  Properties getProperties () const;

  void setPrice(const int lPrice);
  int getPrice() const;

  void show();
};

#endif // PLOTTER_H
