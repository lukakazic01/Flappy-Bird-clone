#pragma once

#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 1024
#define SPLASH_STATE_SHOW_TIME 3.0f
#define PIPE_MOVEMENT_SPEED 200.0f
#define PIPE_SPAWN_FREQUENCY 1.0f
#define BIRD_ANIMATION_DURATION 0.4f
#define BIRD_STATE_STILL 1
#define BIRD_STATE_FALLING 2
#define BIRD_STATE_FLYING 3
#define GRAVITY 350.0f
#define FLYING_SPEED 350.0f
#define FLYING_DURATION 0.35f
#define ROTATION_SPEED 200.0f
#define FLASH_SPEED 1500.0f
#define BACKGROUND_MUSIC_FADE_SPEED 100.0f
#define TIME_BEFORE_GAME_OVER_APPEARS 1.5f
#define BRONZE_MEDAL_SCORE 0
#define SILVER_MEDAL_SCORE 5
#define GOLD_MEDAL_SCORE 25
#define PLATINUM_MEDAL_SCORE 100
#define BLUE_BIRD_UNLOCK_QUOTA 50
#define ORANGE_BIRD_UNLOCK_QUOTA 150
#define RED_BIRD_UNLOCK_QUOTA 500

#define SPLASH_SCENE_BACKGROUND_FILEPATH "Splash Background.png"
#define MAIN_MENU_BACKGROUND_FILEPATH "sky.png"
#define GAME_TITLE_FILEPATH "title.png"
#define PLAY_BUTTON_FILEPATH "PlayButton.png"
#define GAME_BACKGROUND_FILEPATH "sky.png"
#define GAME_OVER_BACKGROUND_FILEPATH "sky.png"
#define PIPE_UP_FILEPATH "PipeDown.png"
#define PIPE_DOWN_FILEPATH "PipeUp.png"
#define LAND_FILEPATH "Land.png"
#define FLAPPY_FONT_FILEPATH "FlappyFont.ttf"
#define GAME_OVER_TITLE_FILEPATH "Game-Over-Title.png"
#define GAME_OVER_BODY_FILEPATH "Game-Over-Body.png"
#define HIGHSCORE_FILEPATH "Highscore.txt"
#define BRONZE_MEDAL_FILEPATH "Bronze-Medal.png"
#define SILVER_MEDAL_FILEPATH "Silver-Medal.png"
#define GOLD_MEDAL_FILEPATH "Gold-Medal.png"
#define PLATINUM_MEDAL_FILEPATH "Platinum-Medal.png"
#define HIT_SOUND_FILEPATH "Hit.wav"
#define POINT_SOUND_FILEPATH "Point.wav"
#define WING_SOUND_FILEPATH "Wing.wav"
#define BACKGROND_MUSIC_FILEPATH "Flying me softly.mp3"
#define PAUSE_BUTTON_FILEPATH "Pause-button.png"
#define RESUME_BUTTON_FILEPATH "Resume-button.png"
#define SKIN_TABLE_FILEPATH "skin-table.png"
#define SKIN_TABLE_CONTAINER_FILEPATH "skin-table-container.png"
#define COSMETICS_BUTTON_FILEPATH "CosmeticsButton.png"
#define HOME_BUTTON_FILEPATH "Home-button.png"
#define LOCK_FILEPATH "lock.jpg"

#define BIRD_FRAME_1_FILEPATH "bird-01.png"
#define BIRD_FRAME_2_FILEPATH "bird-02.png"
#define BIRD_FRAME_3_FILEPATH "bird-03.png"
#define BIRD_FRAME_4_FILEPATH "bird-04.png"

#define BLUE_BIRD_FRAME_1_FILEPATH "bird-blue-01.png"
#define BLUE_BIRD_FRAME_2_FILEPATH "bird-blue-02.png"
#define BLUE_BIRD_FRAME_3_FILEPATH "bird-blue-03.png"
#define BLUE_BIRD_FRAME_4_FILEPATH "bird-blue-04.png"

#define ORANGE_BIRD_FRAME_1_FILEPATH "bird-orange-01.png"
#define ORANGE_BIRD_FRAME_2_FILEPATH "bird-orange-02.png"
#define ORANGE_BIRD_FRAME_3_FILEPATH "bird-orange-03.png"
#define ORANGE_BIRD_FRAME_4_FILEPATH "bird-orange-04.png"

#define RED_BIRD_FRAME_1_FILEPATH "bird-red-01.png"
#define RED_BIRD_FRAME_2_FILEPATH "bird-red-02.png"
#define RED_BIRD_FRAME_3_FILEPATH "bird-red-03.png"
#define RED_BIRD_FRAME_4_FILEPATH "bird-red-04.png"

enum GameStates {
    eReady,
    ePlaying,
    eGameOver,
    ePaused,
};
