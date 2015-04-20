//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

#define Pheight 15
#define Pwidth  100

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);


int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
   
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;


       add ( window , paddle );
        add ( window , ball );
        add ( window , label );
        
        waitForClick();
        
    // keep playing until game over
    while (lives > 0 && bricks > 0 && points!=50 )
    {
        // TODO
        
        
        double velocity = 3.5;
        double angel = drand48() + 1.5;
    
        
        
        
        while (true)
        {
        
        GEvent event = getNextEvent(MOUSE_EVENT);

            // moving the paddle 
            if (event != NULL)
            {
                
                if (getEventType(event) == MOUSE_MOVED)
                {
                   
                    double x = getX(event) - getWidth(paddle) / 2;
                    double y = HEIGHT-100;
                    setLocation(paddle, x, y);
                }
            }
            
                
            // move circle , velocity speed 
        move(ball, velocity, angel);
        
        //check collision between ball and bricks
        GObject obrick = detectCollision( window , ball );
        
        
        
        // bounce off right edge of window
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            velocity = -velocity;
        }

        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            velocity = -velocity;
        }
        
        
        // bounce off the upper edge of the window 
        else if (getY(ball) + getHeight(ball)  <= 20)
        {
            velocity = -velocity;
            angel = -angel ;
        }
        
         // if collision with the paddle 
        else if (detectCollision(window,ball) == paddle )
                {
                     angel = -angel ;
                   
                }
                
                
        // if the ball passed the paddle 
        else if (getY(ball)+ getWidth(ball) > getHeight(window))
        {
            --lives;
             setLocation(ball, (WIDTH-RADIUS*2)/2  , HEIGHT-400);           
                while (true)
                {
                    // check for mouse event
                    GEvent event = getNextEvent(MOUSE_EVENT);

                    // if we heard one
                    if (event != NULL)
                    {
                        // if the event was movement
                        if (getEventType(event) == MOUSE_CLICKED)
                        {
                             break;
                        }
                    }
                }
                
                break ;            
        }
        
        else if (detectCollision(window,  ball) == 0  ) ;
            
        
        // collision with brick 
        // collision between an object "obrick" and an object of type Grect
        else if ( strcmp(getType(obrick) , "GRect") == 0  ) 
        {
            ++points;
            --bricks;
            removeGWindow(window , obrick );
            updateScoreboard(window,label,points);
             angel = -angel ;
            //velocity = -velocity;
            
        }
        
            
        pause(7);
            
        }
        
        
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // TODO
    
    int xloc = 2 , yloc = 20 ; 
    string clr[ROWS] = {"RED" , "YELLOW" , "GREEN" , "BLUE"  , "ORANGE"};
    // cols = 10 , wdth = 400 
    GRect bricks[COLS] ; // = newGRect( xloc  , yloc  , 50  , 15);
    
        for ( int j = 0 ; j < ROWS ; ++j)
        {        
            for ( int i = 0 ; i < COLS ; ++i)
            {
                  bricks[i]  = newGRect( ( xloc + (i*40) )  , yloc  , 35  , 12.5);
                  setFilled(bricks[i], true);
                  setColor(bricks[i] , clr[j]);
                  add ( window , bricks[i]);   
            }
            
            yloc +=20 ;
            
         
        } 
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    
    GOval ball = newGOval ((WIDTH-RADIUS*2)/2  , HEIGHT-400  , RADIUS*2  , RADIUS*2);    
    setFilled(ball , true);
    setColor(ball , "MAGENTA");
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
       
    GRect rect = newGRect( Pwidth+55  , HEIGHT-100  , Pwidth  , Pheight);
    setFilled(rect , true);
    setColor(rect , "BLACK");
    
    
    return rect;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel score;
    double x , y ;
    
    
    
    score = newGLabel("0");
    setFont(score , "SansSerif-25");
    x= (getWidth(window) - getWidth(score))/2 ;
    y= (getHeight(window) + getFontAscent(score) + RADIUS ) /2;
    
    setLocation(score , x , y );
    
    return score;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
