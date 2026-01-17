#! Symbology

#  General

## Why?

Chicken & Egg problem, trying to define these to make a drawing program, so I've got a good palette of symbols to have tools to draw the symbols... 

## Solution

Micro language to describe the symbol. To be kept SIMPLE


## Coordinates

Coordinates will be normalized on load to be +- 1, centered at 0.  Degenerate axis (variations < 0.01) will simply be shifted to zero center.

# Grammar

    "name" flags
        instruction...

And repeat per symbol

## Pins

Pins are points of attachment

# Reference

## Commands

### In

An input pin, see "pin" for full detail

### isym

An input symbol

    isymbol [type]

### osym

An output symbol

    osymbol [type]


### Pin

    pin 1,0

Creates a point of attachment. 

### Pins

Creates an array of pins along the final two points.  

    pins [N]
    pins 0..N

Arguments
+ No N implies unlimited
+ N makes N pins
+ a..b makes a to b pins here



### psym

Defines the pin symbol

    psym [none]             // no pin marker
    psym circle             // circle
    psym diamond            // diamond
    psym square             // square
    psym triangle[.dir]     // triangle
    psym arrow[.dir]           // arrow
    
For input/output pins, the dir will be implied unless overriden

### vertex

    vertex 4,5
    




