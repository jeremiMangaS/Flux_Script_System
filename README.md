# FLUX SCRIPT ENGINE

Flux Script System is a simple system that combines the architecture of the C++ language with Lua in building a system that can be run and changed directly without the need to shut down or 
restart the program first. Where C++ will be the main engine and Lua will be the logic that will manage the system through the C++ engine, so there is no need to rerun the program to 
immediately see light results. (For heavy things like changing the engine logic, it still has to be done through the C++ program directly so it still needs to be rerun the program).


## Project Structure :
<img width="289" height="674" alt="image" src="https://github.com/user-attachments/assets/c52e2a80-2ac3-4064-a18b-d2d83f62f6e6" />

## Installation and Setup
 Require :
 - C++ Compiler ( GCC, Clang, MSVC ) that supporting C++17 version
 - OpenCV 4.x configured in System Path
 - Lua Library and Header for linking
Setup :
 - Clone Repository
   ```bash
   git clone https://github.com/YourUsername/Flux_Script_System.git](https://github.com/jeremiMangaS/Flux_Script_System.git
   cd Flux_Script_System
 - Generae build files
   ``` bash
   mkdir build && cd build
   cmake ..

## How to use
- Make sure the required .xml models from OpenCV are placed in the resources/ folder
  <img width="257" height="128" alt="image" src="https://github.com/user-attachments/assets/f8240a95-1386-49ba-aea0-ad3756af65b6" />
- Running the engine
  Make sure to compile the engine first and then run the .exe file in the build/bin/ folder, the system will open your default camera
  <img width="207" height="299" alt="image" src="https://github.com/user-attachments/assets/675de129-f8d5-4318-89a8-53a597d408ea" />
  Note : Ignore the .jpg files

## Contributing
Contributions are welcome !!! So if you have ideas for better AI models or new Lua wrappers, feel free to fork this repo and submit a pull request.\


