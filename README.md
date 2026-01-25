# NOTE
Rewrite

Done / planned in rewrite: 
- [x] Cross-compatible
- [x] Using LuaJIT for better performance
- [x] Passing in the filename in the terminal as argument instead of calling the file "demo.lua"
- [ ] More readable code
- [ ] better organization
- [ ] not using macros for everything
  
# ImGui-Lua

<div align="center">
  <img src="https://raw.githubusercontent.com/penguin-cmyk/penguin-cmyk.github.io/refs/heads/main/output.gif" alt="ImGui-Lua Showcase" width="800">

  <p><em>A Lua binding for Dear ImGui with syntax as close as possible to the original C++ API</em></p>
</div>

## Overview

ImGui-Lua is a binding library that ports Dear ImGui functionality to Lua while maintaining syntax that closely mirrors the original C++ API. The lexer has been modified to support the `::` operator, allowing for nearly identical code structure between C++ and Lua implementations.

## Features

<table>
  <tr>
    <td><strong>Near-Identical Syntax</strong></td>
    <td>Use ImGui::Begin(), ImGui::Button() just like in C++</td>
  </tr>
  <tr>
    <td><strong>Modified Lexer</strong></td>
    <td>Custom Lua lexer supports :: operator for authentic ImGui feel</td>
  </tr>
  <tr>
    <td><strong>Complete API Coverage</strong></td>
    <td>Widgets, windows, tables, input handling, and more</td>
  </tr>
</table>



## Building from Source

### Prerequisites
- Visual Studio 2019 or later with C++ support
- CMake 3.15 or higher

### Build Instructions

1. **Clone the repository**
   ```bash
   git clone https://github.com/penguin-cmyk/imgui-lua.git
   cd imgui-lua
   ```

2. **Generate build files**
   ```bash
   mkdir build
   cd build
   cmake ..
   ```

3. **Compile the project**
   ```bash
   cmake --build . --config Release
   ```

<details>
<summary><strong>Visual Studio Integration</strong></summary>

You can also open the project directly in Visual Studio and use the integrated CMake support to build the project.

</details>

## Key Features

**Authentic ImGui Experience**: The modified Lua lexer allows you to write ImGui code that looks and feels exactly like C++ ImGui, making it easy to port existing ImGui applications or follow C++ ImGui tutorials.

**Complete Widget Support**: All major ImGui widgets are supported including buttons, text inputs, sliders, combo boxes, tables, tree views, and more.

**Demo Application**: Includes a comprehensive demo showcasing widgets, text input, tables, trees, color pickers, and theming capabilities.

## Documentation

The API matches Dear ImGui's C++ interface exactly:
- Same function names and parameters
- Identical return behavior
- Direct translation from C++ examples

## Contributing

Contributions are welcome! Feel free to submit pull requests or report issues.

## License

This project is licensed under the MIT License.
