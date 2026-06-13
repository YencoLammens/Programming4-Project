# Bubble Bobble

Exam project for the course Programming 4
By Yenco Lammens

# Introduction
For this project I attempted to recreate Bubble Bobble, it currently contains 3 levels, and it would be very scalable to add more

#Github repo
https://github.com/YencoLammens/Programming4-Project

# Controls
WASD/DPAD for movement and selection in menu's
SPACE/X to fire bubble
Score entry screen: SPACE/ENTER/A(dpad) to confirm 

# Features
- Singleplayer implemented
- Multiplayer implemented
- Versus not implemented
- 3 first levels in an infinite loop until lives of player(s) run out
- Bubble mechanic closely matching original, same with popping of enemies and their pick up drops
- Animations
- Physics
- Double jumping when colliding with bubble
- Zen chan and Maita mostly correctly implemented, Maita with boulders


# System design
Designed mainly around a game object and component oriënted system, among other game programming patterns that we are taught this semester.
Levels are loaded via JSON files that are created by the application from itch.io called "Tiled", which will be listed in sources.
Patterns that are included but not exclusive:
- GameObject/Component
- Update loop
- Scene graph (Inspired by Unity/Unreal)
- Dirty flag (Transform)
- Command (Controls in game and menu)
- pImpl (Hiding dependencies, currently XInput and SDL for controls)
- Observer (PlayerHitObserver, EnemyBubbledObserver, Displays)
- Threading (Sound system)
- Object pool (Melon + fries pickups, bubbles and boulders)
- Service locator (CollisionManager and SoundSystem)
- States (Game states, player states, enemy states for Maita and Zenchan)
- SDBM hash for events

# Sources
https://thorbjorn.itch.io/tiled
Took inspiration and got help from some friends (Rani Nagels, Nils Hammond, Georgi Georgiev)

