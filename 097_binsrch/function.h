#ifndef __FUNCTION_H__
#define __FUNCTION_H__
template <typename R, typename A>
class Function
{
public:
  virtual R invoke(A arg) = 0;
  virtual ~Function() {}
};
#endif

int binarySearchForZero(Function<int, int> *f, int low, int high)
{
  int old_low = low;

  while (low <= high)
  {
    int mid = (high + low) / 2;
    int value = f->invoke(mid);
    if (value <= 0)
    {
      low = mid + 1;
    }
    else
    {
      high = mid - 1;
    }
  }
  return (low == old_low) ? low : low - 1;
}