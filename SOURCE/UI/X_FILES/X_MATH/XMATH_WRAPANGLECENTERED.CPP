#include "COMMON/OBJRECAT3CV2.H"
#include "MATH/DOUBLEBITS.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "MATH/math_double.H"
#include "UI/X_FILES/X_MATH.H"

inline static f32 wrap_centered(f32 angle)
{
  f32 angleReductionValue;
  f32 value;

  f32 originalAngle;
  value = angle;
  originalAngle = value;
  if (1)
  {
    if (((long long) (k_xmathCenteredAngleUpperThreshold < originalAngle)) || (originalAngle < k_xmathCenteredAngleLowerThreshold))
    {
      value = (f32) FloatModulo((f64) value, k_xmathCenteredAnglePeriodDouble);
    }
    else
    {
      if (k_xmathCenteredAngleUpperLimit < value)
      {
        angleReductionValue = k_xmathCenteredAngleUpperLimit;
        do
        {
          value -= angleReductionValue;
          if (1)
          {
          }
        }
        while (angleReductionValue < value);
      }
      if (value < 0.0f)
      {
        do
        {
          value += k_xmathCenteredAnglePeriod;
        }
        while (value < (angleReductionValue = 0.0f));
      }
    }
  }
  return value;
}

f32 XMath_WrapAnglePositive(f32 angle)
{
  f32 angleReductionValue;
  f32 value;
  f32 *angleWrapConstants;
  f32 originalAngle;
  value = angle;
  originalAngle = value;
  if (1)
  {
    if (((long long) (k_xmathPositiveAngleModuloThreshold < originalAngle)) || (originalAngle < (-25.13274383544922f)))
    {
      value = (f32) FloatModulo((f64) value, k_xmathPositiveAnglePeriodDouble);
    }
    else
    {
      if (k_xmathPositiveAngleWrapConstants[0] < value)
      {
        angleReductionValue = k_xmathPositiveAngleWrapConstants[0];
        do
        {
          value -= angleReductionValue;
          if (1)
          {
          }
        }
        while (angleReductionValue < value);
      }
      if (value < 0.0f)
      {
        do
        {
          angleWrapConstants = k_xmathPositiveAngleWrapConstants;
          value += angleWrapConstants[1];
        }
        while (value < (angleReductionValue = 0.0f));
      }
    }
  }
  return value;
}

f32 XMath_WrapAngleCentered(f32 x)
{
  f32 centerOffset;
  float shiftedAngle;
  f32 wrappedAngle;
  centerOffset = k_xmathAngleCenterOffset;
  wrappedAngle = x + centerOffset;
  {
    shiftedAngle = wrappedAngle;
  }
  wrappedAngle = wrap_centered(shiftedAngle);
  return wrappedAngle - k_xmathCenteredAngleOffset;
}
