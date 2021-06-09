# Paint
Application Paint uses Abstract Factory Design Patterns

User Interface of Paint Application
                            Designed by Nguyen Tran Tien
_______________________________________________________________________________________
|                           | Add |  Remove  |  Undo  |  Redo  | Print  |  3D  |  2D  |
|                           |_________________________________________________________|                 MAIN MENU
|Circle( )                  |                                                         |       ______________________________
| Position  | Radius        |                                                         |       |          |                 |
|           |               |                                                         |       |___KEY____|____Function_____|
|           |               |                                                         |       |   A      |     ADD         |
|           |               |                                                         |       |   R      |    Remove       |
|           |               |                                                         |       |   U      |     Undo        |
|                           |                                                         |       |___B______|_____Redo________|
|                           |                                                         |
|                           |                                                         |               TUTORIAL
|                           |                                                         |     Create a circle:    A + C
|Rectangle( )               |                                                         |     Create a rectangle: A + Any keys
|Position | Width  | Height |                                                         |     Remove a circle:    R + C
|         |        |        |                                                         |     Remove a rectangle: R + Any keys
|         |        |        |                                                         |     Undo:               U
|         |        |        |                                                         |     Redo:               B
|         |        |        |                                                         |     Modify:             M
|         |        |        |                                                         |     (1) move the cursor to the place to be edited
|___________________________|_________________________________________________________|     (2) press Tab to enable edit function
                                                                                            (3) Modify and press enter
                                                                                            (4) Press E to exit edit function.
