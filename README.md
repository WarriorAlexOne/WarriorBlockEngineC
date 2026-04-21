# WarriorBlockEngineC
A program creation engine that can be used to create a variety of software, including games, general software, and multi-window projects. BlockEngine is made in C using the latest SDL3 (and possibly Raylib in the future, to handle 3D things). Currently, there are plans for there to be a multitude of tools for creating menus, text, game physics, image animations, program loops, shader effects (maybe...), save formats, and many more things. BlockEngine is a passion project, and is expected to be in development for years to come, and to change in many ways to strive for user simplicity and accessibility while in these early days. The goal is to keep things as simple-to-use as possible, while also being powerful enough for advanced users to do whatever they please with little worry.

# Implemented Features
-A Clock Module that automatically limits the program's framerate to whatever the user chooses.

-An Input Module that automatically handles all keyboard inputs (mouse inputs coming soon), and gives various options for easy input detection (similar to Raylib).

-An Engine-Wide Update system that automatically keeps things running through 1 simple-to-use function.

-An Instance and Pointer System that gives the user full control of all data that they create (can also be almost-entirely ignored, for users who want more ease-of-use).

-The user still has full control of the program loop (along with the rest of the program), and can choose to activate BlockEngine wherever they please.

-Modular Code "Blocks" that can be activated or deactivated with ease. (Want to activate a WBE Clock instance for a moment, then disable it? Go for it!)

# The Purpose
The goal for BlockEngine is to strive for the freedom of SDL, while making things simple to use like Raylib. This no-compromise, easy-of-use paradigm, is what motivates the development of this engine, as well as the inspiration behind every new feature added. In particular, this is what motivates the use of C as the base, as C can be ported to nearly any language, allowing more people to use the engine in whatever way they find convenient. Ultimately, everyone should be able to use the engine, whether they are a professional, or a novice who doesn't know how to write code.

# How Things Are Currently Going
BlockEngine is in it's early days. The old engine had many game features implemented, but was a personal project that wasn't very expandable or practical, but it was an excellent learning experience. BlockEngine has gone through many interations since, to try to find what works as an API, and to further improve automation of more tedious tasks.

Right now, BlockEngine is a framework. As development continues, BlockEngine will have true engine features, such as an editor that'd allow the creation of programs and games with no code needing to be written by the user, but the user will also have full access to the code, and will be able to write their own with full control. (Being able to use BlockEngine as just a framework is planned to always be possible, and is 1 of the main goals of the project).

3D features are planned, but has no planned timeframe to be worked on. Raylib may or may not be used for 3D rendering; the details will be decided in time.

AI is not, and will not be used in the creation of this engine. Everything is written by hand, and all logic is created by humans. The old version of BlockEngine may have used some AI code snippets for learning, but all current code, and all future code, will be written by humans exclusively.