#include "headers.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

const int PLAY_AREA_WIDTH = 450;
const int PLAY_AREA_HEIGHT = 350;
const int BORDER_SIZE = 10;
const int MARGIN_TOP  = 60;

const char *FONT_PATH = "./resources/fonts/nokiafc22.ttf";

using namespace std;

TTF_Font *gFont = nullptr;

int main() {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        cerr << "SDL Not Available " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }
    if (TTF_Init() == -1){
        cerr << "TTF Not Available " << TTF_GetError() << endl;
        return EXIT_FAILURE;
    }

    gFont = TTF_OpenFont(FONT_PATH, 14);
    if (gFont == nullptr){
        cerr << "TTF Not Available " << TTF_GetError() << endl;
        return EXIT_FAILURE;
    }


    int screen_w = PLAY_AREA_WIDTH + (BORDER_SIZE * 2);
    int screen_h = PLAY_AREA_HEIGHT + BORDER_SIZE + MARGIN_TOP;

    SDL_Window *window = SDL_CreateWindow("SDL2 Retro Snake",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          screen_w,
                                          screen_h,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {
        cerr << "Could not create a window" << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event event;



    snake::Fps fps(60);

    vector<SDL_Rect> border_points = vector<SDL_Rect>();
    border_points.push_back({0, MARGIN_TOP, BORDER_SIZE, screen_h});
    border_points.push_back({0, MARGIN_TOP, screen_w, BORDER_SIZE});
    border_points.push_back({screen_w - BORDER_SIZE, MARGIN_TOP, BORDER_SIZE, screen_h});
    border_points.push_back({0, screen_h - BORDER_SIZE, screen_w, BORDER_SIZE});

    int initial_x_pos = (PLAY_AREA_HEIGHT / 2);
    initial_x_pos -= initial_x_pos % 10;

    int initial_y_pos = (PLAY_AREA_WIDTH / 2);
    initial_y_pos -= initial_y_pos % 10;

    snake::Snake snake = snake::Snake(initial_x_pos,
                                      initial_y_pos,
                                      5,
                                      PLAY_AREA_WIDTH,
                                      PLAY_AREA_HEIGHT,
                                      BORDER_SIZE + MARGIN_TOP
    );
    snake.pauseToggle();

    snake::Texture scoreTexture = snake::Texture(renderer, gFont);
    snake::Texture highScoreTexture = snake::Texture(renderer, gFont);
    int highScore = 0;

    snake::Texture gameOverTexture = snake::Texture(renderer, gFont);
    bool gameOver = false;
    bool isRunning = true;

    while (isRunning){
        fps.update();
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
                break;
            }
            if (event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym){
                    case SDLK_UP:
                        snake.setDirection(snake::Direction::UP);
                        break;
                    case SDLK_DOWN:
                        snake.setDirection(snake::Direction::DOWN);
                        break;
                    case SDLK_RIGHT:
                        snake.setDirection(snake::Direction::RIGHT);
                        break;
                    case SDLK_LEFT:
                        snake.setDirection(snake::Direction::LEFT);
                        break;
                    case SDLK_p:
                    case SDLK_SPACE:
                        snake.pauseToggle();
                        if (gameOver)
                            gameOver = false;
                        break;
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        isRunning = false;
                        break;
                    default:break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 142, 191, 14, 0);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 47, 76, 10, 255);
        if (SDL_RenderFillRects(renderer, &border_points[0], (int)border_points.size()) != 0){
            cerr << SDL_GetError() << endl;
        }

        int currentScore = snake.getScore();
        if (currentScore > highScore)
            highScore = currentScore;

        ostringstream ss;
        ss << "Score: ";
        ss << setw(4) << std::setfill('0') << currentScore;
        scoreTexture.loadFromRenderedText(ss.str(), {47, 76, 10, 255});
        ss.str("");
        ss.clear();

        ss << "High Score: ";
        ss << setw(4) << std::setfill('0') << highScore;
        highScoreTexture.loadFromRenderedText(ss.str(), {47, 76, 10, 255});


        snake.render(renderer);
        scoreTexture.render(5, (MARGIN_TOP / 2) - scoreTexture.getHeight());
        highScoreTexture.render(5, (MARGIN_TOP / 2) - scoreTexture.getHeight() + highScoreTexture.getHeight());

        if (gameOver){
            gameOverTexture.loadFromRenderedText("G A M E  O V E R", {47, 76, 10, 255});
            gameOverTexture.render((screen_w / 2) - (gameOverTexture.getWidth() / 2), screen_h / 2);
        }

        SDL_RenderPresent(renderer);

        if (snake.isGameOver()){
            snake.reset();
            snake.pauseToggle();
            gameOver = true;
        }
        fps.apply();
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    scoreTexture.free();
    highScoreTexture.free();
    gameOverTexture.free();
    TTF_Quit();
    SDL_Quit();


    return EXIT_SUCCESS;
}