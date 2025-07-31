Chip 8 emulator that run anny .ch8 rom.

Libraries: SDL2 , SDL2_ttf
Compiler used is g++ (note can use another one but in the run.sh script this one is used so you will have to compile it with your own script)

- to run you can use the ./run.sh script I made
- to change the rom in main inside the load_rom() function you can input the file path as a string to the rom you want to run
- there are a few games / demo roms to test on in the arrays in main
- Keys depend on the game being played
- Keypad (these are all the keys involved in the games)
  1 2 3 4
  q w e r
  a s d f
  z x c v

- you can toggle the debugg gui to render when the rom is running by change the boolean in main 

Demo Example:
  ![image](https://github.com/user-attachments/assets/20fb9b2e-bee3-47db-928d-20870fc03706)


Game Example:
  ![image](https://github.com/user-attachments/assets/9ef8f2c7-e0d3-4628-939a-03089ab518ff)

Debugger Gui:
  ![image](https://github.com/user-attachments/assets/ff3b048c-519c-493e-9b39-c33314fb708f)
