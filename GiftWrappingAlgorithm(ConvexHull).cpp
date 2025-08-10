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
    int32_t mIndex{};
    int32_t mNextIndex{};
    glm::vec2 mLeftMost;
    glm::vec2 mCurrentVertex;
    glm::vec2 mNextVertex;

    std::vector<glm::vec2> mPoints;
    std::vector<glm::vec2> mHull;
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
            return pPoint1.x < pPoint2.x;
        };
    std::sort(sPoints.mPoints.begin(), sPoints.mPoints.end(), sortPred);
    sPoints.mLeftMost = sPoints.mPoints[0];

    sPoints.mCurrentVertex = sPoints.mLeftMost;
    sPoints.mHull.push_back(sPoints.mCurrentVertex);
    sPoints.mNextVertex = sPoints.mPoints[1];
    sPoints.mIndex = 2;
}

void drawPoints(SDL_Renderer* pRenderer, const std::vector<glm::vec2>& pPoints)
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

    createPoints(100);

    bool isFillingHull = true;

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
                for (auto& i : sPoints.mHull)
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

        if (isFillingHull)
        {
            //glm::vec2 checking = { 12.0f, 23.0f };
            //if (!sPoints.mPoints.empty())
            //    checking = sPoints.mPoints[sPoints.mIndex];
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            for (auto& i : sPoints.mHull)
            {
                SDL_RenderPoint(renderer, i.x, i.y);
            }

            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderPoint(renderer, sPoints.mLeftMost.x, sPoints.mLeftMost.y);
            SDL_SetRenderDrawColor(renderer, 200, 0, 255, 255);
            SDL_RenderPoint(renderer, sPoints.mCurrentVertex.x, sPoints.mCurrentVertex.y);
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderLine(renderer, sPoints.mCurrentVertex.x, sPoints.mCurrentVertex.y, sPoints.mNextVertex.x, sPoints.mNextVertex.y);

            glm::vec2 checking = { 12.0f, 23.0f };
            if (!sPoints.mPoints.empty())
            {
                checking = sPoints.mPoints[sPoints.mIndex];
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderLine(renderer, sPoints.mCurrentVertex.x, sPoints.mCurrentVertex.y, checking.x, checking.y);
            }

            SDL_SetRenderDrawColor(renderer, 0, 23, 255, 255);
            const glm::vec2 firstVector = sPoints.mNextVertex - sPoints.mCurrentVertex;
            const glm::vec2 secondVector = checking - sPoints.mCurrentVertex;
            const glm::vec3 cross = glm::cross(glm::vec3(firstVector.x, firstVector.y, 0.0f), glm::vec3(secondVector.x, secondVector.y, 0.0f));
            if (cross.z < 0.0f)
                sPoints.mNextVertex = checking;
            if (sPoints.mIndex < sPoints.mPoints.size() - 1)
                sPoints.mIndex = sPoints.mIndex + 1;
            else
            {
                if (!sPoints.mPoints.empty())
                {
                    sPoints.mHull.push_back(sPoints.mNextVertex);
                    sPoints.mCurrentVertex = sPoints.mNextVertex;
                    sPoints.mIndex = 0;
                    sPoints.mPoints.erase(sPoints.mPoints.begin() + sPoints.mIndex);
                    sPoints.mNextVertex = sPoints.mLeftMost;
                    if (sPoints.mHull[0] == *(sPoints.mHull.end() - 1))
                        isFillingHull = false;
                }
            }
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            for (size_t i = 0; i < sPoints.mHull.size() - 1; ++i)
            {
                SDL_RenderLine(renderer, sPoints.mHull[i].x, sPoints.mHull[i].y, sPoints.mHull[i + 1].x, sPoints.mHull[i + 1].y);
            }
        }
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}


//SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
//for (auto& i : sPoints.mHull)
//{
//    SDL_RenderPoint(renderer, i.x, i.y);
//}
//
//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
//SDL_RenderPoint(renderer, sPoints.mLeftMost.x, sPoints.mLeftMost.y);
//SDL_SetRenderDrawColor(renderer, 200, 0, 255, 255);
//SDL_RenderPoint(renderer, sPoints.mCurrentVertex.x, sPoints.mCurrentVertex.y);
//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
//SDL_RenderLine(renderer, sPoints.mCurrentVertex.x, sPoints.mCurrentVertex.y, sPoints.mNextVertex.x, sPoints.mNextVertex.y);
//
//glm::vec2 checking = { 12.0f, 23.0f };
//if (!sPoints.mPoints.empty())
//{
//    checking = sPoints.mPoints[sPoints.mIndex];
//    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//    SDL_RenderLine(renderer, sPoints.mCurrentVertex.x, sPoints.mCurrentVertex.y, checking.x, checking.y);
//}
//
//SDL_SetRenderDrawColor(renderer, 0, 23, 255, 255);
//const glm::vec2 firstVector = sPoints.mNextVertex - sPoints.mCurrentVertex;
//const glm::vec2 secondVector = checking - sPoints.mCurrentVertex;
//const glm::vec3 cross = glm::cross(glm::vec3(firstVector.x, firstVector.y, 0.0f), glm::vec3(secondVector.x, secondVector.y, 0.0f));
//if (cross.z < 0.0f)
//    sPoints.mNextVertex = checking;
//if (sPoints.mIndex < sPoints.mPoints.size() - 1)
//    sPoints.mIndex = sPoints.mIndex + 1;
//else
//{
//    if (!sPoints.mPoints.empty())
//    {
//        sPoints.mHull.push_back(sPoints.mNextVertex);
//        sPoints.mCurrentVertex = sPoints.mNextVertex;
//        sPoints.mIndex = 0;
//        sPoints.mNextVertex = sPoints.mLeftMost;
//    }
//}
