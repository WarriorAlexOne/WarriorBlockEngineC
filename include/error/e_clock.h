#ifndef E_CLOCK_H
#define E_CLOCK_H

bool e_Clock_create (Clock* clock);
bool e_Clock_destroy (Clock** clockPtr);

bool e_Clock_init (Clock* clock);
bool e_Clock_update (Clock* clock);

bool e_Clock_cycleUpdate (Clock* clock, int i);
bool e_Clock_frameUpdate (Clock* clock, int i);
bool e_Clock_tickUpdate (Clock* clock, int i);
bool e_Clock_secUpdate (Clock* clock, int i);

bool e_Clock_addCycleFunction (Clock* clock, void (*function)());
bool e_Clock_addFrameFunction (Clock* clock, void (*function)());
bool e_Clock_addTickFunction (Clock* clock, void (*function)());
bool e_Clock_addSecFunction (Clock* clock, void (*function)());

#endif