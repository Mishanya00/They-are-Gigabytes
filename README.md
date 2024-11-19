# They-are-Gigabytes

They are Gigabytes [TAG] - is a future RTS 3D videogame. Virus attacked computer curcuit: all CPUs are captured and only Kernel is still under player's control. Build your base and liberate all CPUs to delete virus from the system!

*// All game names are not final*

**Technologies and libraries:**

* C++

* OpenGL.  (GLUT for "multiplatformness" and GLEW for Modern OpenGL features)

* Assimp (For loading models of various formats) 

* stb_image for loading textures

* Miniaudio (C lib for audio that is implemented through miniaudio.cpp and miniaudio.h files)

* Others (that I maybe forget or will add in future)

This game is being created for educational purposes and I do my best to follow OOP and Architecture recommendatioins to make the game easy to develop and modify.

**What's done?**

* Fundamental things such as 3D graphics Rendering (and all math behind it), loading models and textures, shaders, transformation matrices, camera, input events, etc...

* Very basic support of audio

* BasicModel class that any visible object in game will aggregate. BasicModel aggregates BasicMesh class which is created by Etai Meiri (https://github.com/emeiri), kudos to him for amazing OpenGL tutorials

* Simplest light shader and its support.

**What's should be done?**

* Models manager that handles all model and mesh loadings by itself

* Interface subsystem

* Gameplay mechanics

* More difficult shader techniques (Because models I use support shining, normal mapping, etc...)



![2024-11-05-11-31-30-image](https://github.com/user-attachments/assets/da3516b9-263f-4c9f-b46f-420c94cfea5a)


      *Picture 1 - current state of graphics in game*

![2024-11-05-11-41-10-image](https://github.com/user-attachments/assets/057e3bdf-3497-4b1c-ae67-94f1ec724ef5)


*Picture 2 - Example of log during compilation (loaded textures and models)*
