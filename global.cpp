#include "global.h"
#include "Pen.h"
#include "Layer.h"

#define NO_PEN -1
#define NO_LAYER -1

Pen myPenArray[MAX_PEN];
Layer myLayerArray[MAX_LAYER];
int CurrentPenID=NO_PEN;
int CurrentLayerID=NO_LAYER;
