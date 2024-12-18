#ifndef CLOCK_H
#define CLOCK_H

#define NANO_SEC 1000000000.0
#define DEFAULT_FRAMERATE 60
#define DEFAULT_TICKRATE 60
#define TICK_CATCHUP_LIMIT (DEFAULT_TICKRATE*4)-1   // The amount of ticks that can be lost before the program stops keeping track.


long long int getNanoTime ();
void initClocks ();
void updateClocks ();

void cycleUpdate ();
void frameUpdate ();
void tickUpdate ();
void secUpdate ();
void pauseFrameUpdate ();
void pauseTickUpdate ();

void addCycleFunction (void (*function) ());
void addFrameFunction (void (*function) ());
void addTickFunction (void (*function) ());
void addSecFunction (void (*function) ());
void addPauseFrameFunction (void (*function) ());
void addPauseTickFunction (void (*function) ());

#endif