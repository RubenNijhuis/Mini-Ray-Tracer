# Mini Ray Tracer
🌈 A small ray tracing project for the exercise "MiniRT"

[ Display a really cool img or gif here 🤤 ]

## Quick Start 
```
$ git clone --recursive git@github.com:RubenNijhuis/Mini-Ray-Tracer.git
$ make run
```

## Project structure
```
Mini-Ray-Tracer -/
	- assets -/		# All types of assets, output img
	- bin -/		# Mini-Ray-Tracer output
	- include -/		# The .h files of the project
	- libs -/		# Our custom and vendor libraries

	- src -/			# Source files
		- file_parse -/		# File parsing module
		- mlx_utils -/		# Utilities for MLX
		- utils -/		# Regular utils
		main.c			# Starting points

	- test -/		# Testing directory
	- .gitignore		# To ignore files
	- .gitmodules		# Describes what submodules are installed
	- LICENSE		# Regular MIT license
	- Makefile		# Compiling && linking magic happens here
	- README.md		# Our point of setup, notes and API
```

## Command list
```
$ make norm
Outputs the norminette across the src and include folder of every project

$ make test
Test the functions of MiniRT using Criterion

$ make run
Run the program with a default file from the assets folder

$ make submodules
Pulls the most recent versions of the submodules !! BEWARE !! this could import breaking !!
```

## Testing
Dependent on Criterion lib, install via brew and run make with the `CODAM=1` variable.


## Notes
[Scratchapixel](https://www.scratchapixel.com/)

## Todo
[ ] - Setup a vector math lib  
[ ] - Incorrect file formatting checker
[ ] - Program close on [ x ] button click
[ ] - Render image based on input file