# XylarBedrock

A lightweight DLL mod for Minecraft Bedrock Edition that patches trial restrictions.

## What Does It Do?

XylarBedrock automatically patches the `xgameruntime.dll` library to remove trial limitations in Minecraft Bedrock Edition. It works by:

1. Loading when Minecraft starts
2. Locating the `xgameruntime.dll` in memory
3. Finding and replacing the "isTrial" string with "xzNope"
4. This effectively bypasses trial version checks

## Installation

### Building From Source

```powershell
# Navigate to project directory
cd XylarBedrock_project

# Create build folder
mkdir build -Force

# Enter build folder
cd build

# Generate project files with CMake
cmake ..

# Compile the project
cmake --build . --config Release
 end
