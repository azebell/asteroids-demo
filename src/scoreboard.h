#ifndef SCOREBOARD_H
#define SCOREBOARD_H

void drawString(float x, float y, void *font, const char *text);
void processTextToScreen(float x, float y, float number, const char *textFormat);
void drawScoreboard(std::vector<int> values, int height, int width, float ratio);

#endif // SCOREBOARD_H
