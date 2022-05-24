# Mini Ray Tracer
🌈 A small ray tracing project for the exercise "MiniRT"

[ Display a really cool img or gif here 🤤 ]

## Quick Start 
```sh
$ git clone --recursive git@github.com:RubenNijhuis/Mini-Ray-Tracer.git
$ make run
```

If you're on Linux(Debian-like), you have to install the prerequisites for [MLX42](https://github.com/codam-coding-college/MLX42/) first:
```sh
sudo apt install build-essential libx11-dev libglfw3-dev libglfw3 xorg-dev
```

## Project structure
```
Mini-Ray-Tracer -/
  - 🖼 assets -/    # All types of assets, output img
  - 📦 bin -/       # Mini-Ray-Tracer output
  - 👀 include -/   # The .h files of the project
  - 📚 libs -/      # Our custom and vendor libraries
  - ⛲️ src -/       # Source files
  - 🧪 test -/      # Testing directory
  - .gitmodules    # Describes what submodules are installed
  - Makefile        # Compiling && linking magic happens here
  ...
```

## Module folder structure

In this project we tried to adhere to a more modular structure of our project. Creating components that have one entry point and abstract the inner-workings.

Each module has a folder and file that match name-wise. Every other file can be seen as a part of that bigger module. In some cases some functions might be exposed to the larger project as it follows the DRY principle more.

```
📁 Folder name
  - File with that same folder name (this is the module entry point)
  - ...supporting files
  - Potential README explaining the setup and usage
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
[Rotation Matrix](https://en.wikipedia.org/wiki/Rotation_matrix)

## Todo
[ ] - Setup a vector math lib  
[ ] - Incorrect file formatting checker  
[ ] - Program close on [ x ] button click  
[ ] - Render image based on input file (linearly)  
  [ ] - Shoot rays from camera  
  [ ] - Calculate if ray intersects with any objects  
  [ ] - Calculate light/color value of ray  
  [ ] - Add to img object  
