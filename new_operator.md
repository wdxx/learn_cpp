A normal `new` does two things:
- allocate storage
- construct an object

#### placement new 用法
```c++
#include <new>        // Must #include this to use "placement new"
#include "Fred.h"     // Declaration of class Fred
void someCode()
{
  char memory[sizeof(Fred)];     // Line #1
  void* place = memory;          // Line #2
  Fred* f = new(place) Fred();   // Line #3 (see "DANGER" below)
  // The pointers f and place will be equal
  // ...
}
```
Line #1 creates an array of sizeof(Fred) bytes of memory, which is big enough to hold a Fred object. Line #2 creates a pointer place that points to the first byte of this memory (experienced C programmers will note that this step was unnecessary; it’s there only to make the code more obvious). Line #3 essentially just calls the constructor Fred::Fred(). The this pointer in the Fred constructor will be equal to place. The returned pointer f will therefore be equal to place.

#### 参考
1. https://stackoverflow.com/questions/58900136/custom-allocator-including-placement-new-case
