# UE5 GridTool

Grid tool is an actor, that contains editable slots every 1 meter in X, Y and Z axis. In editor user can set which class should be spawned at any given slot upon game start.

## Classes

Project contains several C++ classes which include

- LevelChunk (Base class for grid tool actor)
- LevelGridSlot (Base for a single slot)
- SpawnableElement (Base for any object that can be spawned in slot)

**Only classes that inherit from SpawnableElement can be picked as an object in Slot component**

Some of those classes have their base Blueprint implementations in /Content/Blueprints/ directory

## Optimizations

- Slots hold **TSoftClassPtr** pointers instead of a **UClass**.
  Classes get loaded when previewing, and/or on BeginPlay. One can add implementation to manually decide when to load classes.
  Currently classes are loaded **synchronously**, but async implementation can be added.
- All LevelChunk components (slots and previews) get destroyed upon game start.

## Settings

User can define grid size in every dimension (X, Y, Z).

## Previewing

- To preview all slots in currently selected **BP_LevelChunk**, press the **"PreviewElements"** button located in **ActorMethods** category in the Details panel.
- To hide previews hit the **"HidePreview"** button located in the same panel.

## Selecting

To select a single slot when the whole actor is selected **double click** chosen slot in the viewport.
