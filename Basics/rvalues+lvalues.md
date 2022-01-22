# lvalue and rvalue in C #

Source: [James Fisher Blog](https://jameshfisher.com/2017/01/21/c-lvalue-rvalue/)

TL;DR: “lvalue” either means “expression which can be placed on the left-hand side of the assignment operator”, or means “expression which has a memory address”. “rvalue” is defined as “all other expressions”.

- This divides up all expressions into two disjoint sets:
    - **lvalues** are “left values”: expressions that can be assigned to, which can be on the left of an assignment
    - **rvalues** are “right values”: everything else, which must be on the right of an assignment

> An lvalue (locator value) represents an object that occupies some identifiable location in memory (i.e. has an address).

> rvalues are defined by exclusion, by saying that every expression is either an lvalue or an rvalue. Therefore, from the above definition of lvalue, an rvalue is an expression that does not represent an object occupying some identifiable location in memory.

#### Example1 ####

This program generates an error

```C
int foo() { return 4; }
int main(void) {
  int* f = &foo();
  return 0;
}
```

Output:

```
lvalue.c:3:12: error: cannot take the address of an rvalue of type 'int'
  int* f = &foo();
```

Because rvalues are ones which do “not represent an object occupying some identifiable location in memory”, we cannot use the & (addressof) operator on them.

#### Example2 ####

You may think this program generates an error, but it doesn't

```C
int main(void) {
  void* f = &"some string";
  return 0;
}
```

It turns out this one is just fine, because ... string literals are lvalues! When we write "```foo```", we reserve memory for that string in an addressable location.
