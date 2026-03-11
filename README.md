# Bubble Bobble

Exam project for the course Programming 4
By Yenco Lammens

# Introduction
Bubble Bobble is a Retro arcade game, with a lot of bubbles, and bobbles.

# Controls (UNFINISHED)
D-Pad/Keyboard for movement

# System design
Designed mainly around a game object and component oriënted system, among other game programming patterns that we are taught this semester.
Currently including:
- GameObject/Component
- Update loop
- Scene graph (Inspired by Unity/Unreal)
- Dirty flag (Transform)
- Command (Controls)
- pImpl (Hiding dependencies, currently XInput and SDL for controls)