/**
 * @file WAO_Clock.h
 * @brief Provides functionality for managing Clock instances.
 *
 * This module includes the definition of the Clock structure and
 * functions to create, initialize, and update clock instances, as
 * editing their various aspects, and creating timers.
 */

#ifndef WAO_CLOCK_H
#define WAO_CLOCK_H

#include <SDL3/SDL.h>

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
 * - Default: ((DEFAULT_TICKRATE * 4) - 1) --- *AKA 4 seconds*
 */
#define TICK_CATCHUP_LIMIT (DEFAULT_TICKRATE * 4) - 1

#define SEC_CATCHUP_LIMIT NANO_SEC * 4

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

#define DEFAULT_TIMER_MALLOC 8


typedef struct {
    long long int currentTime;
    long long int startTime;
    long long int endTime;
    long long int remainingTime;
    long long int remainingTime_Seconds;
} WAO_Timer;

/**
 * @brief Represents a Clock instance.
 * 
 * Used to track and update various timings, such as system time, frame rate, and tick rate.
 */
typedef struct {
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
     * The amount of frames the program will be limited to per second. Directly coordinates with the WAO_UpdateClock function to
     * determine the amount of times the functions are ran per second.
     */
    double frameRate;


    double frameTime;   // Frame Rate converted to a second-fraction.


    double frameTarget;   // Constantly updates to the next time when it runs a frame.


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


    long long int secTarget;   // Updates every time a second passes, to know when the next second should pass.


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


    // Error helper arrays
    bool e_cycleUpdateErrorPositions[CYCLE_FUNCTION_LIMIT];

    bool e_frameUpdateErrorPositions[FRAME_FUNCTION_LIMIT];

    bool e_tickUpdateErrorPositions[TICK_FUNCTION_LIMIT];

    bool e_secUpdateErrorPositions[SEC_FUNCTION_LIMIT];

    // Timer Variables
    int timerCount;
    WAO_Timer* timers;
} WAO_Clock;


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
WAO_Clock* WAO_CreateClock();
void WAO_DestroyClock (WAO_Clock** clockPtr);

void WAO_InitClock (WAO_Clock* clock);
void WAO_UpdateClock (WAO_Clock* clock);

static void WAO_CycleUpdate (WAO_Clock* clock);
static void WAO_FrameUpdate (WAO_Clock* clock);
static void WAO_TickUpdate (WAO_Clock* clock);
static void WAO_SecUpdate (WAO_Clock* clock);

bool WAO_AddCycleFunction (WAO_Clock* clock, void (*function)());
bool WAO_AddFrameFunction (WAO_Clock* clock, void (*function)());
bool WAO_AddTickFunction (WAO_Clock* clock, void (*function)());
bool WAO_AddSecFunction (WAO_Clock* clock, void (*function)());

long long int WAO_GetCPS (WAO_Clock* clock);
int WAO_GetFPS (WAO_Clock* clock);
int WAO_GetTPS (WAO_Clock* clock);
double WAO_GetDT (WAO_Clock* clock);

#endif