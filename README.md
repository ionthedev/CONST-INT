# CONST-INT
A GDExtension planning to make game development easier. If you clone this project, please do not hesitate to watch or star the repo to stay up to data with it's changes.

CURRENT CLASSES MAY BE A WORK IN PROGRESS.

## CURRENT STATE: LANGUAGE PORTING
Check the [Projects](https://github.com/users/ionthedev/projects/2) page to view the currently active aspects being ported.

External contributions are locked until the language port is complete.

Converting the project from C# to C++. The C# version has been made legacy.
https://ionthedev.itch.io/constint

If you would like to support the project as it develops, feel free to click the sponsor button on the top or visit https://ko-fi.com/ionthedev

The current features of the legecy version (0.5.2 on [Itch.io]([url](https://ionthedev.itch.io/constint))) https://ionthedev.itch.io/constint


- [FPS Controller (Sprinting, Crouching, Stair Handling Jumping and Walking)](https://github.com/ionthedev/CONST-INT/issues/4)
- Inventory Component
- Enemy with simple EXTREMELY simple follow AI
- Custom State Machine - used for FPS controller
- Doors - Rotational and Translational
- Display Box Message System
- Event System (resource based)
- Custom PSX Shader
- Custom Post Processing Shader
- Health System
- Custom GDpsx with helper functions for people wanting to expand the system with their own code.

# Why //CONST //INT
Godot leverages Entity-Component Patterns, Flyweight Patterns and Observer Patterns masterfully. This probably makes NO sense if you are not a programmer, which is why YOU are the type of person I am making this for.

//CONST //INT is aimed to act as your technical artist and systems engineer, allowing you to just hop in and make 3D games.

If you are a programmer, //CONST //INT aims to fill in the gaps of systems you don't want to keep writing time and time again; allowing you to just make the tings that are fun for you.

//CONST //INT is inspired greatly by the way Valve and Source engine games feel, and a huge aspect of that is strong toolset that they've unleashed onto their audience allowing them to make amazing games and experiences.
That is what I aim for this project to be for Godot.

# How can I help //CONST //INT
Look [Projects](https://github.com/users/ionthedev/projects/2) page and pick and issue a task that isn't already an active issue. Once you feel it's ready, make it a PR and it will go through the process. The project should follow the [Contributing Guidelines set by Godot](https://docs.godotengine.org/en/stable/contributing/ways_to_contribute.html) as close as possible and the project will be built upon to further reflect those guidelines for a solid foundation of mutual understanding.

Also join the discord and hop in the chat if you are interested in joining in on the project.


# Community
We currently only have a discord, so [feel free to join! ](https://discord.com/servers/friendly-studios-745380942167670785)
# gdextension

GDExtension template that automatically builds into a self-contained addon for the Godot Asset Library.

### Getting started:
1. Clone this repository (or a new repository with this template) with submodules.
    - `git clone --recurse-submodules https://github.com/nathanfranke/gdextension.git`
    - `cd gdextension`
2. Update to the latest `godot-cpp`.
    - `git submodule update --remote`
2. Build a debug binary for the current platform.
    - `scons`
3. Import, edit, and play `project/` using Godot Engine 4+.
    - `godot --path project/`
4. Check the output:
   ```
   Hello GDScript!
   Hello GDExtension Node!
   Hello GDExtension Singleton!
   ```

### Repository structure:
- `project/` - Godot project boilerplate.
  - `addons/example/` - Files to be distributed to other projects.¹
  - `demo/` - Scenes and scripts for internal testing. Not strictly necessary.
- `src/` - Source code of this extension.
- `godot-cpp/` - Submodule needed for GDExtension compilation.

¹ Before distributing as an addon, all binaries for all platforms must be built and copied to the `bin/` directory. This is done automatically by GitHub Actions.

### Make it your own:
1. Rename `project/addons/example/` and `project/addons/example/example.gdextension`.
2. Replace `LICENSE`, `README.md`, and your code in `src/`.
3. Not required, but consider leaving a note about this template if you found it helpful!

### Distributing your extension on the Godot Asset Library with GitHub Actions:
1. Go to Repository→Actions and download the latest artifact.
2. Test the artifact by extracting the addon into a project.
3. Create a new release on GitHub, uploading the artifact as an asset.
4. On the asset, Right Click→Copy Link to get a direct file URL. Don't use the artifacts directly from GitHub Actions, as they expire.
5. When submitting/updating on the Godot Asset Library, Change "Repository host" to `Custom` and "Download URL" to the one you copied.
