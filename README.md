# Studio 16: Template Specializations

Today's lecture and studio focus on how template specializations can be used to customize program behavior involving templates, with respect to specific types. Issues of ambiguity, overloading, recursion, and template parameter deduction are all relevant for today's material, as they have been for previous lectures and studios.

**Record your answers to each exercise in [`ANSWERS.md`](ANSWERS.md).** Number each response so it is easy to match with its exercise.

You are encouraged to work in groups of 2 or 3 people on each studio (groups may change from studio to studio), though you may also complete any studio by yourself.

## Required Exercises

1. As the answer to the first exercise, list the names of the people who worked together on this studio.

2. First, ssh into `shell.cec.wustl.edu` using your WUSTL Key id and password, then use `qlogin` to log into one of the Linux Lab machines, and confirm that the version of `g++` there is correct (as you did in [Studio 0](https://github.com/cse4208-wustl/studio0)). Then work inside your clone of this repository.

   This repository already contains a `Makefile` for this studio, with the executable named `studio16` and `studio16.cpp` listed as the main source file. Copy the source and header files from your solution for [Studio 15](https://github.com/cse4208-wustl/studio15) into this repository. Rename any source and header files as appropriate (e.g., `studio15.h` to `studio16.h` and `studio15.cpp` to `studio16.cpp`, etc.), and update the `CMPL_SRCS`, `TMPL_SRCS`, and `HEADER_FILES` entries in the `Makefile` to list your files.

   In your template header and source files, declare and define specializations for `std::string` of:

   1. the non-variadic template that has a single type parameter and inserts the passed const reference to that type into the `ostream` that it was passed, and
   2. the variadic template that has a type parameter followed by a template parameter pack, inserts the passed const reference to the first parameterized type into the `ostream` that it was passed, and then passes the function parameter pack it was passed into a recursive call to itself.

   **Hint:** the declarations of those specializations should look something like:

   ```cpp
   template <> void printit (std::ostream&, const std::string&);
   ```

   and

   ```cpp
   template <typename... Args>
   void printit (std::ostream&, const std::string&, const Args&...);
   ```

   The definition of each of those specializations should insert quotes (`"\""`) into the `ostream` before and after it inserts a `std::string` into the `ostream`, but otherwise should behave the same as the more general template it is specializing.

   Modify your main function so that it declares another variable of type `std::string` and initializes it with a different C-style string than is used to initialize any of the other variables, and then adds that variable at the end of the list of variables that is passed into the call to the variadic template that wraps the call to the variadic template you are specializing in this exercise (as was done in the previous studio).

   Try to compile your program, and as the answer to this exercise, please explain (1) the kinds of errors that were reported by the compiler, and (2) why you think those errors occurred.

3. Add a non-template header and source file to this repository (and to your `Makefile`), and include the non-template header file in the non-template source file, in your template header file, and in the source file for your main program. These new non-template header and source files will store declarations and definitions of non-template overloads of some of your function templates, to remove ambiguity and allow the code to compile and the program to run successfully.

   Move the declaration and definition of the non-variadic template specialization out of your template header and source files and into the new non-template header and source files you just added. Modify the declaration and definition so that rather than being a template specialization it is a non-template overload, e.g., the signature of the declaration should look something like:

   ```cpp
   void printit (std::ostream&, const std::string&);
   ```

   Try to compile your program. Depending on how you implemented your solution to the previous studio and to the previous exercise in this studio, you may also need to declare and define an additional overload that only takes in a reference to an `ostream` and does nothing, in order to fully terminate the recursion, as in:

   ```cpp
   void printit (std::ostream&);
   ```

   If your code compiled without that additional overload, please continue without adding it.

   Run your program, and as the answer to this exercise, please show (1) the declaration and the definition of the remaining template specialization that you added in the previous exercise, (2) the declaration and the definition of the non-template overload you added in this exercise, and (3) the output that your program produced.

4. In your template header and source files, declare and define a specialization of the variadic template that takes `const char * const` and a parameter pack. In your non-template header and source files for overloads, declare and define an overload for `const char * const`. Both of those should print out:

   - a left square bracket (`"["`),
   - the `const char * const` variable,
   - a space,
   - a `reinterpret_cast` of the `const char * const` variable to `const void *`,
   - a right square bracket (`"]"`), and
   - a space.

   The specialization of the variadic template should then pass its function parameter pack into a call to the variadic template it is specializing.

   In your main function, declare a pointer to another C-style string, and add it as the last argument to the call to the variadic function template that wraps the variadic template you specialized in this exercise. Compile and run your code, and as the answer to this exercise please show the output that it produced.

5. In your template header and source files, declare and define a specialization of the variadic template for your class type, and in your non-template header and source files for overloads, declare and define an overload for it as well. Both of those should print out:

   - a left curly brace (`"{"`),
   - the object itself,
   - the object's address,
   - a right curly brace (`"}"`), and
   - a space.

   The specialization of the variadic template should then pass its function parameter pack into a call to the variadic template it is specializing.

   In your main function, declare another object of your class type that is initialized with a pointer to another C-style string that differs from any other one the main function uses, and add that object as the last argument to the call to the variadic function template that wraps the variadic template you specialized in this exercise. Compile and run your code, and as the answer to this exercise please show the output that it produced.

6. In your template source file, declare two more global static unsigned integer variables, both initialized to 0: one to count the number of bytes that were passed in `int` variables, and one to count the number of bytes that were passed in `float` variables.

   In your template header and source files, declare and define two specializations of the non-variadic template that counts how many bytes there are in each variable that was passed in. Each of those specializations should add the size of the passed variable (in bytes) to both the global counter that was declared in the previous studio, and to the newly added global counter for bytes of variables of that specific type, before returning the variable that was passed into it.

   In your template source file, modify the variadic template that applies the counting function template to its function parameter pack expansion, so that it prints out not only the total bytes that were in any type that was passed in, but also how many bytes were in `int` variables, how many bytes were in `float` variables, and how many bytes were in all variables of other types.

   Compile and run your program, and as the answer to this exercise please show the output that it produced.

## Deliverables

- `ANSWERS.md` with your numbered answers to all of the required exercises above.
