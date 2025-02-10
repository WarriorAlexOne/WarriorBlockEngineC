/**
 * @file clock.h
 * @brief Provides functionality for managing and manipulating clock instances.
 *
 * This module includes the definition of the Clock structure and
 * functions to create, initialize, and update clock instances.
 */

#ifndef CLOCK_H
#define CLOCK_H

/**
 * @brief Number of nanoseconds in one second.
 */
#define NANO_SEC 1000000000.0

/**
 * @brief Default rate that frames will be limited to.
 * 
 * - Default: 60
 */
#define DEFAULT_FRAMERATE 60

/**
 * @brief Default rate that ticks will always run.
 * 
 * - Default: 60
 */
#define DEFAULT_TICKRATE 60

/**
 * @brief The limit at which the program stops ticking.
 * 
 * This is amount of ticks the program will continue accounting for before it stops ticking. Prevents the 'fastforward' effect from being absurdly long.
 * 1 tick is subtracted to account for stop delay when no longer counting ticks.
 * 
 * - Default: ((DEFAULT_TICKRATE * 4) - 1) (aka, 4 seconds)
 */
#define TICK_CATCHUP_LIMIT (DEFAULT_TICKRATE*4)-1

/**
 * @brief Internal function limit.
 *
 * Purely determines how much memory is allocated to functions that are updated, thus dictating how many functions can be updated at a time.
 * It is safe to edit these values to any number that is required by the program, up to the integer limit.
 */
#define CYCLE_FUNCTION_LIMIT 1024

/**
 * @brief Internal function limit.
 *
 * Purely determines how much memory is allocated to functions that are updated, thus dictating how many functions can be updated at a time.
 * It is safe to edit these values to any number that is required by the program, up to the integer limit.
 */
#define FRAME_FUNCTION_LIMIT 1024

/**
 * @brief Internal function limit.
 *
 * Purely determines how much memory is allocated to functions that are updated, thus dictating how many functions can be updated at a time.
 * It is safe to edit these values to any number that is required by the program, up to the integer limit.
 */
#define TICK_FUNCTION_LIMIT 1024

/**
 * @brief Internal function limit.
 *
 * Purely determines how much memory is allocated to functions that are updated, thus dictating how many functions can be updated at a time.
 * It is safe to edit these values to any number that is required by the program, up to the integer limit.
 */
#define SEC_FUNCTION_LIMIT 1024


/**
 * @brief Represents a Clock instance.
 * 
 * Used to track and update various timings, such as system time, frame rate, and tick rate.
 */
typedef struct Clock {
    /**
     * @brief The variable that makes the clock run.
     * 
     * - THIS SHOULD NEVER BE CHANGED!
     */
    long long int currentCycleTime;

    /**
     * @brief Used to calculate timing limits.
     * 
     * Primarily used to calculate the cycle delta and tick delta, to check how much time has passed, and how much time was lost.
     */
    long long int lastCycleTime;

    /**
     * @brief Used to get the time between 'cycles'.
     * 
     * Useful for making variables account for slowdown and speedup, allowing them to be more consistent.
     */
    double cycleDelta;

    /**
     * @brief Tracks the cycles per second.
     */
    long long int cps;

    /**
     * @brief Stores the last amount of cycles.
     * 
     * Keeps track of the amount of cycles that were counted during the last second. Updates every second.
     * 
     * Useful for getting the CPS of a program for that thread.
     */
    long long int getCPS;

    /**
     * @brief The frame limit.
     * 
     * The amount of frames the program will be limited to per second. Directly coordinates with the Clock_update function to
     * determine the amount of times the functions are ran per second.
     */
    double frameRate;


    double frameTime;   // Frame Rate converted to a second-fraction.


    double frameTarget;   // Constantly updates to the next time 'til it runs a frame.


    long long int lastFrameTime;   // Used to calculate the frameDelta, to check how much time has passed/was lost between frames.


    double frameDelta;   // Used to get the time between frames. Useful for making values run consistently with a varying framerate.


    int fps;   // Frames per second.


    int getFPS;

    double tickRate;


    double tickTime;   // Tick Rate converted to a second-fraction.


    double tickTarget;   // Constantly updates to the next time 'til it runs a tick.


    double tickDelta;   // Different from other delta times. Keeps track of current tick progression, and whether ticks were lost or not.


    int tps;   // Ticks per second.


    int getTPS;


    double secTime;   // Updates every time a second passes, to know when the next second should pass.


    // Function arrays used for updating specified functions at different points.
    void (*cycleUpdateFunctions[CYCLE_FUNCTION_LIMIT])();


    void (*frameUpdateFunctions[FRAME_FUNCTION_LIMIT])();


    void (*tickUpdateFunctions[TICK_FUNCTION_LIMIT])();


    void (*secUpdateFunctions[SEC_FUNCTION_LIMIT])();


    // Keeps track of how many functions each array contains during runtime. Used to loop through each populated element in the array.
    int cycleUpdateCount;


    int frameUpdateCount;


    int tickUpdateCount;


    int secUpdateCount;


    // Error helper variables
    bool e_cycleUpdateErrorPositions[CYCLE_FUNCTION_LIMIT];

    bool e_frameUpdateErrorPositions[FRAME_FUNCTION_LIMIT];

    bool e_tickUpdateErrorPositions[TICK_FUNCTION_LIMIT];

    bool e_secUpdateErrorPositions[SEC_FUNCTION_LIMIT];
} Clock;


// long long int Clock_nanoTime();

/**
 * @brief Creates a Clock instance to update functions.
 *
 * A Clock instance that contains all the necessary clock functions needed to run outside functions at various timings.
 * To use the new Clock instance properly, it is recommended to put the Clock_update function in a while loop, with
 * the Clock instance as the argument; this allows the clock to update it's various timings accurately.
 * 
 * @return A Clock pointer to create a new instance.
 */
Clock* Clock_create();
void Clock_destroy (Clock** clockPtr);

void Clock_init (Clock* clock);
void Clock_update (Clock* clock);

void Clock_cycleUpdate (Clock* clock);
void Clock_frameUpdate (Clock* clock);
void Clock_tickUpdate (Clock* clock);
void Clock_secUpdate (Clock* clock);

void Clock_addCycleFunction (Clock* clock, void (*function)());
void Clock_addFrameFunction (Clock* clock, void (*function)());
void Clock_addTickFunction (Clock* clock, void (*function)());
void Clock_addSecFunction (Clock* clock, void (*function)());

#endif