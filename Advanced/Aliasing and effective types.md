# Aliasing and effective type #

**Aliasing** is the property of two pointers `a` and `b` that refer to the same object, that is that `a == b`.

**The effective type** of a data object is used by C to determine which operations can be done on that object. In particular the effective type is used to determine if two pointers can *alias* each other.

Violations of aliasing rules and of violating the effective type of an object are two different things and should not be confounded.

C's strict aliasing rules refers to cases in the compiler may assume which objects do (or do not) alias each other. There are two rules of thumb that you always should have in mind for data pointers.

- Unless said otherwise, two pointers with the same base type may alias.

- Two pointers with different base type cannot alias, unless at least one of the two types is a character type.

Here **base type** means that we put aside type qualifications such as `const`, e.g. If `a` is `double*` and `b` is `const double*`, the compiler must generally assume that a change of `*a` may change `*b`.

Violating the second rule can have catastrophic results.



Unless the `source` or `target` type is `void`, all pointer conversions between pointers with different base type must be **explicit**.
Or in other words, they need a **cast**, unless you do a conversion that just adds a qualifier such as `const` to the target type.

## What is an effective type ##

The effective type of a data object is the last type information that was associated with it, if any.

```C
// a normal variable, effective type uint32_t, and this type never changes
uint32_t a = 0.0;

// effective type of *pa is uint32_t, too, simply
// because *pa is the object a
uint32_t* pa = &a;

// the object pointed to by q has no effective type, yet
void* q = malloc(sizeof uint32_t);
// the object pointed to by q still has no effective type,
// because nobody has written to it
uint32_t* qb = q;
// *qb now has effective type uint32_t because a uint32_t value was written
*qb = 37;

// the object pointed to by r has no effective type, yet, although
// it is initialized
void* r = calloc(1, sizeof uint32_t);
// the object pointed to by r still has no effective type,
// because nobody has written to or read from it
uint32_t* rc = r;
// *rc now has effective type uint32_t because a value is read
// from it with that type. The read operation is valid because we used calloc.
// Now the object pointed to by r (which is the same as *rc) has
// gained an effective type, although we didn't change its value.
uint32_t c = *rc;

// the object pointed to by s has no effective type, yet.
void* s = malloc(sizeof uint32_t);
// the object pointed to by s now has effective type uint32_t
// because an uint32_t value is copied into it.
memcpy(s, r, sizeof uint32_t);
```