#include "ktypes.h"
#include "config.h"
#include "gui.h"

#ifndef APP_H_
#define APP_H_

typedef struct {
	Config conf;
	GuiInstance gui;

	u8 flags;

} App;

void AppInit(App *app);
void AppUpate(App *app, float dt);

#endif
