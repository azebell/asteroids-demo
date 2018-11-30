#ifndef SCOREBOARD_H
#define SCOREBOARD_H

void drawString(float x, float y, void *font, const char *text);
void processTextToScreen(float x, float y, float number, const char *textFormat);
void drawScoreboard(float number);

#endif // SCOREBOARD_H

