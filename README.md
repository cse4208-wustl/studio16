# Studio 16: Template Specializations

Today's lecture and studio focus on how template specializations can be used to customize program behavior for specific types. You will see how full specializations of function templates interact with overloading, why non-template overloads are often the better tool, and how class templates support partial specialization when you need to customize behavior for a whole family of types.

**Record your answers to each exercise in [`ANSWERS.md`](ANSWERS.md).** Number each response so it is easy to match with its exercise.

You are encouraged to work in groups of 2 or 3 people on each studio (groups may change from studio to studio), though you may also complete any studio by yourself.

## Provided Files

- `printit.h`: declares and defines the function template `printit`, which inserts its argument into an `ostream` followed by a newline.
- `studio16.cpp`: a `main` function that calls `printit` with a `std::string`, a string literal, a `const char*`, an `int`, and an `int*`.
- `Makefile`: builds the `studio16` executable.

Put all of your template code (specializations, additional templates, and class templates) in `printit.h`. Because a full specialization of a function template is an ordinary function rather than a template, mark each full function template specialization you define in the header `inline`, just as you would any other function defined in a header file.

## Required Exercises

1. As the answer to the first exercise, list the names of the people who worked together on this studio.

2. First, ssh into `shell.cec.wustl.edu` using your WUSTL Key id and password, then use `qlogin` to log into one of the Linux Lab machines, and confirm that the version of `g++` there is correct (as you did in [Studio 0](https://github.com/cse4208-wustl/studio0)). Then work inside your clone of this repository.

   Read through `printit.h` and `studio16.cpp`, then build the program with `make` and run it. As the answer to this exercise, please show the output that your program produced.

3. In `printit.h`, below the base template, declare and define a full specialization of `printit` for `std::string` that inserts a double quote (`"\""`) before and after the string, so that strings are printed in quotes. The declaration should look something like:

   ```cpp
   template <> inline void printit(std::ostream& os, const std::string& s);
   ```

   (You will also need to include the `<string>` header in `printit.h`.)

   Then, in `main`, after the existing calls, add calls to `printit` with each of the following arguments:

   - a `const std::string` variable,
   - a temporary `std::string`, such as `std::string("temporary")`,
   - the result of concatenating `s` with a string literal, such as `s + " world"`,
   - `s.c_str()`,
   - a string literal passed with an explicit template argument, as in `printit<std::string>(std::cout, "explicit")`,
   - a `char`, and
   - a `double`.

   Before you build and run your program, predict which of the calls in `main` will print their argument in quotes. Then build and run it. As the answer to this exercise, please show the output, say which of your predictions were wrong, and explain:

   - why the `std::string` variable is printed in quotes but the string literal `"literal"` is not (**Hint:** what type does the compiler deduce for `T` when `"literal"` is passed to a parameter of type `const T&`?), and
   - why the string literal passed to `printit<std::string>` *is* printed in quotes.

4. When the base template is passed a pointer such as `ip`, it inserts the pointer itself, so the output is an address like `0x7ffd8478a6e4`. In this exercise you will add two functions that instead print the value the pointer points to, each with a different label so you can tell from the output which one was called.

   In `printit.h`, declare and define these two functions, in this order:

   1. a full specialization of the base template for `int*`. Instead of inserting the pointer itself, its definition should insert `int* to `, then the value the pointer points to (`*p`), then a newline. For example, for `ip` it should print `int* to 42`. Its declaration should look something like:

      ```cpp
      template <> inline void printit(std::ostream& os, int* const& p);
      ```

   2. a second function template overload of `printit` for pointers of any type. Its definition should insert `pointer to `, then the value the pointer points to (`*p`), then a newline. For example, for `ip` it should print `pointer to 42`. Its declaration should look something like:

      ```cpp
      template <typename T>
      void printit(std::ostream& os, T* const& p);
      ```

   Build and run your program, and record its output. Then move the `int*` specialization (both its declaration and its definition) so that it comes *after* the pointer template instead of before it, and build and run your program again.

   As the answer to this exercise, please show the output from both runs, and explain:

   - why moving the `int*` specialization changed which function was called for `ip`, even though the specialization's code did not change (**Hint:** which template does a full specialization specialize, and does a specialization take part in overload resolution, or only the template it specializes?), and
   - why the `const char*` variable `cp` now prints only a single character.

5. In `studio16.cpp`, above `main`, declare and define two non-template overloads of `printit`:

   ```cpp
   void printit(std::ostream& os, const std::string& s);
   void printit(std::ostream& os, const char* p);
   ```

   Have each of them print `non-template: ` followed by its argument (with the `std::string` overload still printing its argument in quotes).

   Build and run your program. As the answer to this exercise, please show the output, and explain why each non-template overload was chosen over the function templates and their specializations. Which outputs from the previous exercises did these overloads fix?

6. Function templates cannot be partially specialized, but class templates can. A common technique is to put the type-specific behavior in a class template, and have the function template forward to it.

   First, remove the code you added to `printit.h` in exercises 3 and 4 and the non-template overloads you added to `studio16.cpp` in exercise 5 (your answers already record them). Then, in `printit.h`:

   1. Declare and define a class template `Printer` with a single type parameter `T`, and a static member function `print(std::ostream& os, const T& t)` that inserts `t` into `os` (without a newline).
   2. Declare and define a full specialization `Printer<std::string>` whose `print` inserts the string in double quotes.
   3. Declare and define a partial specialization `Printer<T*>` whose `print` inserts a left square bracket (`"["`), then the value the pointer points to (printed by calling `Printer<T>::print`), then a space, an `@`, and the pointer's address (cast to `const void*`), and then a right square bracket (`"]"`). For example, a pointer to the `int` value 42 might print as `[42 @0x7ffd8478a6e4]`.
   4. Declare and define a partial specialization `Printer<std::vector<T>>` whose `print` inserts a left curly brace (`"{"`) and a space, then each element (printed by calling `Printer<T>::print`) followed by a space, and then a right curly brace (`"}"`). (You will also need to include the `<vector>` header.)
   5. Change the body of the `printit` function template so that it calls `Printer<T>::print(os, t)` and then inserts a newline.

   In `main`, declare a `std::vector<std::string>` with a few elements and a `std::vector<int*>` containing `ip` at least twice, and pass each of them to `printit` after the existing calls.

   Build and run your program and look closely at the output for `cp`. Then add a full specialization `Printer<const char*>` that prints the C-style string itself, and build and run your program again.

   As the answer to this exercise, please show your `Printer` class template and its specializations, and the output from both runs. Explain which specialization of `Printer` was used for `cp` in each run, and which specializations were combined to print the `std::vector<int*>`.

7. As the answer to this exercise, please briefly explain when you would choose each of these approaches to customizing behavior for a specific type: (1) a full specialization of a function template, (2) a non-template overload, and (3) a full or partial specialization of a class template.

## Deliverables

- `ANSWERS.md` with your numbered answers to all of the required exercises above.
