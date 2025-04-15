# CSE Student Study Room

## Project Overview
The "CSE Student Study Room" project is an OpenGL-based simulation of a computer science student's study room. It aims to create a virtual environment that mimics a student's workspace, including various interactive objects such as a rotating ceiling fan, a desk with a computer, a clock, a lamp, and other furnishings. The project showcases 2D graphics, animations, and basic interactions using OpenGL and the GLUT library.

## Features and Functionality

### 1. **Room Layout**
   - **Floor and Wall**: A basic floor and wall structure to represent the room’s boundaries.
   - **Furniture**: Includes a desk, bookshelf, chair, coffee mug, and calendar. All objects are created using simple 2D shapes such as rectangles, circles, and lines.

### 2. **Interactive Objects**
   - **Ceiling Fan**: The fan rotates continuously at a constant speed. The speed and direction are controlled by OpenGL transformations.
   - **Lamp**: The lamp moves back and forth on the desk, and its state (on/off) can be toggled using the 'L' key.
   - **Clock**: A wall clock with working hour and minute hands. The clock hands rotate every frame, updating the time dynamically.
   - **Window with Curtains**: A window that changes color based on the time of day (Day/Night). The curtains are drawn on the window.
   - **Keyboard and Mouse**: A computer keyboard and mouse are displayed on the desk, enhancing the study room simulation.

### 3. **Day and Night Cycle**
   - The room’s background changes dynamically based on the time of day. Pressing the 'D' or 'd' key toggles between day and night modes. 
     - **Day Mode**: The background turns light, simulating daytime.
     - **Night Mode**: The background turns dark, simulating nighttime.

### 4. **Animations**
   - **Fan Animation**: The ceiling fan rotates continuously, with the blades spinning.
   - **Lamp Movement**: The lamp on the desk moves horizontally between two points to simulate a swinging motion.
   - **Clock Hands**: The second and minute hands of the clock continuously update their positions based on time.

### 5. **Sound**
   - A background sound (`ss.wav`) is played asynchronously during the runtime of the application to provide an ambient effect.

## Key Libraries and Dependencies
- **OpenGL**: For rendering 2D objects and transformations.
- **GLUT (OpenGL Utility Toolkit)**: For window management and handling user input.
- **Windows API**: Used for background sound (`PlaySound`).
- **C++ Standard Library**: For general-purpose programming tasks such as math functions.

## How to Run the Project

### Prerequisites
- OpenGL and GLUT libraries installed on your system.
- A C++ compiler (e.g., GCC, MSVC).

### Steps to Run
1. **Install OpenGL and GLUT**:
   - On Linux: You can install OpenGL and GLUT using your package manager (e.g., `sudo apt-get install freeglut3 freeglut3-dev`).
   - On Windows: Download and install the necessary libraries from [here](http://freeglut.sourceforge.net/).
   
2. **Compile the Code**:
   - Use the following command to compile the C++ source code:
     ```bash
     g++ -o studyroom studyroom.cpp -lGL -lGLU -lglut
     ```
   
3. **Run the Executable**:
   - After compilation, you can run the program by executing:
     ```bash
     ./studyroom
     ```

4. **Interact**:
   - Use the 'D' or 'd' key to toggle between Day and Night modes.
   - Use the 'L' or 'l' key to turn the lamp on and off.

## Project Structure

```plaintext
CSE-Student-Study-Room/
│
├── studyroom.cpp            # Main source file with OpenGL code
├── ss.wav                   # Background sound file
└── README.md                # This file
