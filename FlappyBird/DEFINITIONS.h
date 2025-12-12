#pragma once

#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 1024
#define SPLASH_STATE_SHOW_TIME 3.0f
#define PIPE_MOVEMENT_SPEED 200.0f
#define PIPE_SPAWN_FREQUENCY 2.0f
#define BIRD_ANIMATION_DURATION 0.4f
#define BIRD_STATE_STILL 1
#define BIRD_STATE_FALLING 2
#define BIRD_STATE_FLYING 3
#define GRAVITY 350.0f
#define FLYING_SPEED 350.0f
#define FLYING_DURATION 0.35f
#define ROTATION_SPEED 200.0f

#define SPLASH_SCENE_BACKGROUND_FILEPATH "Splash Background.png"
#define MAIN_MENU_BACKGROUND_FILEPATH "sky.png"
#define GAME_TITLE_FILEPATH "title.png"
#define PLAY_BUTTON_FILEPATH "PlayButton.png"
#define GAME_BACKGROUND_FILEPATH "sky.png"
#define GAME_OVER_BACKGROUND_FILEPATH "sky.png"
#define PIPE_UP_FILEPATH "PipeDown.png"
#define PIPE_DOWN_FILEPATH "PipeUp.png"
#define LAND_FILEPATH "Land.png"
#define BIRD_FRAME_1_FILEPATH "bird-01.png"
#define BIRD_FRAME_2_FILEPATH "bird-02.png"
#define BIRD_FRAME_3_FILEPATH "bird-03.png"
#define BIRD_FRAME_4_FILEPATH "bird-04.png"

enum GameStates {
    eReady,
    ePlaying,
    eGameOver,
};
