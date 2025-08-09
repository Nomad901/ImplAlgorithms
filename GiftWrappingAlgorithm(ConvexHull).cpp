#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#include "SDL3/SDL.h"
#include "glm/glm.hpp"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

struct Points
{
    std::vector<SDL_Point> mPoints;
    std::vector<SDL_Point> mHull;

    SDL_Point mLeftMost;
    SDL_Point mCurrentVertex;
    int32_t mIndex{};
    SDL_Point mNextVertex;
} sPoints;

void createPoints(int32_t pNumber)
{
    sPoints.mPoints.reserve(pNumber);

    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int32_t> randX(10, WIN_WIDTH);
    std::uniform_int_distribution<int32_t> randY(10, WIN_HEIGHT);

    for (int32_t i = 0; i < pNumber; ++i)
    {
        sPoints.mPoints.push_back({ randX(gen), randY(gen) });
    }

    auto sortPred = [](const auto& pPoint1, const auto& pPoint2)
        {
            return pPoint1.x <= pPoint2.x;
        };
    std::sort(sPoints.mPoints.begin(), sPoints.mPoints.end(), sortPred);
    sPoints.mLeftMost = sPoints.mPoints[0];
    sPoints.mPoints.erase(sPoints.mPoints.begin());

    sPoints.mCurrentVertex = sPoints.mLeftMost;
    sPoints.mNextVertex = sPoints.mPoints[0];
    sPoints.mIndex = 1;
}

void drawPoints(SDL_Renderer* pRenderer, const std::vector<SDL_Point>& pPoints)
{
    for (auto& i : pPoints)
    {
        SDL_RenderPoint(pRenderer, i.x, i.y);
    }
}

int main(int argc, char* argv[])
{
    SDL_Window* window = SDL_CreateWindow("Window", WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    createPoints(15);

    SDL_FPoint mMousePoint{};
    bool active{ true };
    while (active)
    {
        SDL_GetMouseState(&mMousePoint.x, &mMousePoint.y);
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT ||
                event.key.key == SDLK_ESCAPE)
            {
                active = false;
                break;
            }
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                for (auto& i : sPoints.mPoints)
                {
                    std::cout << std::format("Pos of the point: {}-{}\n", i.x, i.y);
                }
                std::cout << std::format("Mouse pos: {}-{}\n", mMousePoint.x, mMousePoint.y);
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        
        drawPoints(renderer, sPoints.mPoints);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderPoint(renderer, sPoints.mLeftMost.x, sPoints.mLeftMost.y);
        SDL_SetRenderDrawColor(renderer, 200, 0, 255, 255);
        SDL_RenderPoint(renderer, sPoints.mCurrentVertex.x, sPoints.mCurrentVertex.y);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderLine(renderer, sPoints.mCurrentVertex.x, sPoints.mCurrentVertex.y, sPoints.mNextVertex.x, sPoints.mNextVertex.y);
        
        auto checking = sPoints.mPoints[sPoints.mIndex];
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderLine(renderer, sPoints.mCurrentVertex.x, sPoints.mCurrentVertex.y, checking.x, checking.y);

        const glm::vec2 

    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
