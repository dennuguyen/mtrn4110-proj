#!python
#cython: language_level=3

import cython
from functools import wraps
import cv2
import itertools as it
import numpy as np

ORIGIN_CORNER_COLOUR = (255, 0, 255)
OTHER_CORNER_COLOUR = (0, 255, 255)
WALL_COLOUR = (120, 50, 255)
EPUCK_COLOUR = (150, 20, 20)
LADYBUG_COLOUR = (0, 255, 0)


cdef public void print_hello():
    '''
    Sanity checking stdout.
    '''
    print("Hello!")


cdef public list runCVLocaliser(char* mazeFileName, char* robotFileName):
    '''
    CVLocaliser reads the maze file name for a bird's eye image of the maze, and detects and returns
    the current position and current heading of the robot.
    '''
    # CONSIDER IF WE NEED THE ROBOT IMAGE TO GET THE EPUCK HEADING. WE COULD GET THIS INFO FROM HC_LOCALISER

    # IMPLEMENT THIS FUNCTION
    epuck_position = 42
    epuck_direction = 42
    return epuck_position, epuck_direction


cdef public list runCVWaypointer(char* mazeFileName, char* destinationFileName):
    '''
    CVWaypointer reads the maze file name for a bird's eye image of the maze, and detects and
    returns the intended destination as deliberated by the user using openCV.
    '''
    # CONSIDER IF WE NEED THE LADYBUG IMAGE TO GET THE DESTINATION.
    
    # IMPLEMENT THIS FUNCTION
    destination = 42
    return destination


cdef public char* runCVMapper(char* mazeFileName):
    '''
    CVMapper reads in the maze file name for a bird's eye image of the maze and returns the map of
    it in string format.
    '''
    # IMPLEMENT THIS FUNCTION
    maze_map = '42'
    return maze_map.decode('utf-8')

### ADD FUNCTIONS BELOW HERE