#ifndef SCOREBOARD_H
#define SCOREBOARD_H

void drawString(float x, float y, void *font, const char *text);
void processTextToScreen(float x, float y, int number, const char *textFormat);
void drawScoreboard(int number);

#endif // SCOREBOARD_H

