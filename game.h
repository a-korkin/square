#ifndef GAME_H
#define GAME_H

#define SCREEN_WIDTH 640
#define SCREEN_HEIGTH 480
#define STEP 32
#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

void init(void);
void handle_event(void);
void update(void);
void render(void);
void loop(void);
void quit(void);

#endif // GAME_H

