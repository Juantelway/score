#pragma once
#include <Curve/CurveStyle.hpp>

namespace Interpolation
{
class Colors
{
public:
  Colors(const score::Skin& s);

  const auto& style() const
  {
    return m_style;
  }

private:
  Curve::Style m_style;
};
}
