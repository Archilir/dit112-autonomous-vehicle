import pygame
import numpy as np
import cv2 as cv
import serial
import RPi.GPIO as GPIO
import time
import threading
import logging

BLACK    = (   0,   0,   0)
WHITE    = ( 255, 255, 255)

#Class for printing to the raspberry pi for testing purposes
class TextPrint:
    def __init__(self):
        self.reset()
        self.font = pygame.font.Font(None, 20)

    def print(self, screen, textString):
        textBitmap = self.font.render(textString, True, BLACK)
        screen.blit(textBitmap, [self.x, self.y])
        self.y += self.line_height
        
    def reset(self):
        self.x = 10
        self.y = 10
        self.line_height = 15
        
    def indent(self):
        self.x += 10
        
    def unindent(self):
        self.x -= 10

class Joystick:
    logging.basicConfig(level=logging.DEBUG,
                    format='[%(levelname)s] (%(threadName)-10s) %(message)s',
                    )
    AXIS_LEFT_X = 0
    AXIS_LEFT_Y = 1
    AXIS_RIGHT_X = 2
    AXIS_RIGHT_Y = 5
    AXIS_L2 = 3
    AXIS_R2 = 4
    AXIS_MOTION_ROLL = 6
    AXIS_MOTION_PITCH1 = 7
    AXIS_MOTION_PITCH2 = 8

    BUTTON_SQUARE = 0
    BUTTON_CROSS = 1
    BUTTON_CIRCLE = 2
    BUTTON_TRIANGLE = 3
    BUTTON_L1 = 4
    BUTTON_R1 = 5
    BUTTON_L2 = 6
    BUTTON_R2 = 7
    BUTTON_SHARE = 8
    BUTTON_OPTIONS = 9
    BUTTON_L3 = 10
    BUTTON_R3 = 11
    BUTTON_PLAYSTATION = 12
    BUTTON_TOUCHPAD = 13

    HAT_X = 0
    HAT_Y = 1

    

    def __init__(self, serial):
        self.serial = serial
        pygame.init()
        pygame.display.set_caption("Joystick output")
        pygame.joystick.init()
        self.clock = pygame.time.Clock()
        self.size = [500, 700]
        self.screen = pygame.display.set_mode(self.size)
        self.textPrint = TextPrint()
        self.done = False

    def buttonInput(self, button):
        if(button == Joystick.BUTTON_SQUARE):
            self.serial.write('X'.encode())
            
        elif(button == Joystick.BUTTON_CROSS):
            self.serial.write('X'.encode())
            
        elif(button == Joystick.BUTTON_CIRCLE):
            self.serial.write('X'.encode())

        elif(button == Joystick.BUTTON_TRIANGLE):
            self.serial.write('X'.encode())

        elif(button == Joystick.BUTTON_L1):
            self.serial.write('X'.encode())

        elif(button == Joystick.BUTTON_R1):
            self.serial.write('X'.encode())

        elif(button == Joystick.BUTTON_L2):
            self.serial.write('X'.encode())

        elif(button == Joystick.BUTTON_R2):
            self.serial.write('X'.encode())

        elif(button == Joystick.BUTTON_SHARE):
            self.serial.write('X'.encode())

        elif(button == Joystick.BUTTON_OPTIONS):
            self.serial.write('X'.encode())

        elif(button == Joystick.BUTTON_L3):
            self.serial.write('X'.encode())

        elif(button == Joystick.BUTTON_R3):
            self.serial.write('X'.encode())

        elif(button == Joystick.BUTTON_PLAYSTATION):
            self.serial.write('X'.encode())

        elif(button == Joystick.BUTTON_TOUCHPAD):
            self.serial.write('X'.encode())

        else:
            print("Undefined button pressed: This should not happen")

    def hatInput(self, hat, value):
        if(hat == 0):
            if(value[0] > 0):
                self.serial.write('X'.encode())
            elif(value[0] < 0):
                self.serial.write('X'.encode())

            if(value[1] > 0):
                self.serial.write('X'.encode())
            elif(value[1] < 0):
                self.serial.write('X'.encode())
        else:
            print("Undefined hat pressed. This should not happen.")
            
    def processJoystick(self):
        logging.debug('Starting')
        done = False
        while done==False:
            # EVENT PROCESSING STEP
            for event in pygame.event.get(): # User did something
                if event.type == pygame.QUIT: # If user clicked close
                    done=True # Flag that we are done so we exit this loop
                
                # Possible joystick actions: JOYAXISMOTION JOYBALLMOTION JOYBUTTONDOWN JOYBUTTONUP JOYHATMOTION
                if event.type == pygame.JOYBUTTONDOWN:
                    print("Joystick button pressed.")
                if event.type == pygame.JOYBUTTONUP:
                    print("Joystick button released.")
                    
         
            # DRAWING STEP
            # First, clear the screen to white. Don't put other drawing commands
            # above this, or they will be erased with this command.
            self.screen.fill(WHITE)
            self.textPrint.reset()

            # Get count of joysticks
            joystick_count = pygame.joystick.get_count()

            self.textPrint.print(self.screen, "Number of joysticks: {}".format(joystick_count) )
            self.textPrint.indent()
            
            # For each joystick:
            for i in range(joystick_count):
                joystick = pygame.joystick.Joystick(i)
                joystick.init()
            
                self.textPrint.print(self.screen, "Joystick {}".format(i) )
                self.textPrint.indent()
            
                # Get the name from the OS for the controller/joystick
                name = joystick.get_name()
                self.textPrint.print(self.screen, "Joystick name: {}".format(name) )
                
                # Usually axis run in pairs, up/down for one, and left/right for
                # the other.
                axes = joystick.get_numaxes()
                self.textPrint.print(self.screen, "Number of axes: {}".format(axes) )
                self.textPrint.indent()
                
                for i in range( axes ):
                    axis = joystick.get_axis( i )
                    self.textPrint.print(self.screen, "Axis {} value: {:>6.3f}".format(i, axis) )
                self.textPrint.unindent()
                    
                buttons = joystick.get_numbuttons()
                self.textPrint.print(self.screen, "Number of buttons: {}".format(buttons) )
                self.textPrint.indent()

                for i in range( buttons ):
                    button = joystick.get_button( i )
                    self.textPrint.print(self.screen, "Button {:>2} value: {}".format(i,button) )
                    if(button == 1):
                        self.buttonInput(i);
                self.textPrint.unindent()
                    
                # Hat switch. All or nothing for direction, not like joysticks.
                # Value comes back in an array.
                hats = joystick.get_numhats()
                self.textPrint.print(self.screen, "Number of hats: {}".format(hats) )
                self.textPrint.indent()

                for i in range( hats ):
                    hat = joystick.get_hat( i )
                    self.textPrint.print(self.screen, "Hat {} value: {}".format(i, str(hat)))
                    self.hatInput(i, hat)
                self.textPrint.unindent()
                
                self.textPrint.unindent()

            
            # ALL CODE TO DRAW SHOULD GO ABOVE THIS COMMENT
            
            # Go ahead and update the screen with what we've drawn.
            pygame.display.flip()

            # Limit to 20 frames per second
            self.clock.tick(20)
            
        # Close the window and quit.
        # If you forget this line, the program will 'hang'
        # on exit if running from IDLE.
        pygame.quit ()
        
    def start(self):
        joystickThread = threading.Thread(target=self.processJoystick)
        joystickThread.start()
        print("Thread Started")

    
