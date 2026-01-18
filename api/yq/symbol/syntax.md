#! Symbol Library `*.sym` Syntax

## Comments

Comments lines begin with `#` and all will be ignored on said line.

    #   This is a comment
    
## Blank lines

Blank lines are ignored.

## Multiline Continuation

Any line may be continued with the `\` and it'll be concatenated into a single line before parsing

## Blocks

Blocks start with `{` and end with `}`, and may start as the FINAL character to a line

    circle {
    }

Note, same line won't work, so this is illegal

    circle { something }   #< Staring brace won't be recognized, be lumped into the command/arguments


## Symbol

Symbols start with a key as the first argument.  A second string will become its name.  

    green.blob "Green Blob" {
        # definitions....
    }

## Pins

Pins are spots for lines to attach to.

    green.blob "Green Blob" {
        # definitions....
        pin 1 {
            flow in
            pos 1,1
        }
    }
    
## Coordinates

Coordinates... screen coordinates.  So +X goes left and +Y goes down.

    allow               Allows attributes
    dead/nc             A dead/nonconnected pin
    fill                fill options
    input/in            input pin
    inputs/ins          input pins (line)
    output/out          output pin
    outputs/outs        output pins (line)
    pin                 pin
    pins                pins (line)
    rectangle/rect/box  axially aligned box
    stroke              stroke options

    
# Commands

## Allow

    allow X         # Allows the symbol to be mirrored in X
    allow Y         # Allows the symbol to be mirrored in Y
    allow XY        # Allows the symbol to have its X/Y coordinates flipped
    allow ROT       # Allows for rotation of the symbol
    allow AR        # Allows for aspect ratio to be flexed (ie for text, user, etc)
    

Flags for permissible actions on the symbol.  Note, these can be combined to a single line

    allow X Y XY ROT AR




 



    
