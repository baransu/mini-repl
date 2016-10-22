# mini-repl

Miniamal REPL written in C

## Building
Available Makefile with `make start` which build ussing `gcc` on macOS nad Linux

```bash
make start
```

## Basic usage
`mini-repl` uses inifx notation as well as functions
```
> 42
42.00
> 2 + 2
4.00
> 10 - 1
9.00
> 2 * 3
6.00
> 2/2
1.00
```

It also has support for floating point value

```
> 2.1 + 2.1
4.20
```

`mini-repl is not supporting `

### Functions

Functions are reprezented as `function(a,b)`. One argument function has to have trailing coma after argument. It's not forbidden with more than one argument. 

Available functions
* `add(a, b)`
* `subtract(a, b)`
* `multiply(a, b)`
* `divide(a, b)`
* `absolute(a)`
* `neg(a)`
* `factorial(a)`
* `sin(a)`
* `cos(x)`
* `tangent(x)`
* `cotangent(x)`
* `pi` - takes no arguments and returns PI

### Negative values
`mini-repl` do not understand negative values as for example `-1`. You have to use `neg(a)` function to negate given value


### Variables
`mini-repl` has basic support for variables. To define variable is `let variable = value`. Value can be any expresion. To use specified value use: `@variable`.

```
> let a = 1
> @a
1.00
> @a + 2
3.00
> let b = @a + 3
> @b
5.00
> let c = factorial(@b,)
> @c
120.00
```

## Licence

MIT License

Copyright (c) 2016 Tomasz Cichocinski

