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

// for lines

//struct Lines
//{
//	int32_t mNextIndex{};
//	int32_t mIndex{};
//
//	glm::vec2 mCurrentVertex{};
//	glm::vec2 mNextVertex{};
//	glm::vec2 mCheckedVertex{};
//	glm::vec2 mTheMostLeftVertex{};
//
//	std::vector<glm::vec2> mHull;
//    std::vector<glm::vec2> mEndLines;
//	std::vector<glm::vec4> mLines;
//} gLines;
//
//void createLines(int32_t pNumber)
//{
//    std::default_random_engine gen(std::random_device{}());
//    std::uniform_int_distribution<int32_t> randX(10, WIN_WIDTH - 10);
//    std::uniform_int_distribution<int32_t> randY(10, WIN_HEIGHT - 10);
//    
//    for (int32_t i = 0; i < pNumber; ++i)
//    {
//        gLines.mLines.push_back({ (float)randX(gen), (float)randY(gen), WIN_WIDTH / 2, WIN_HEIGHT / 2 });
//        gLines.mEndLines.push_back({ gLines.mLines[i].x, gLines.mLines[i].y });
//    }
//
//    auto sortPred = [](const auto& pFirst, const auto& pSecond)
//        {
//            return pFirst.x < pSecond.x;
//        };
//    std::sort(gLines.mLines.begin(), gLines.mLines.end(), sortPred);
//    std::sort(gLines.mEndLines.begin(), gLines.mEndLines.end(), sortPred);
//    gLines.mTheMostLeftVertex = gLines.mEndLines[0];
//
//    gLines.mCurrentVertex = gLines.mTheMostLeftVertex;
//    gLines.mHull.push_back(gLines.mCurrentVertex);
//    gLines.mNextVertex = gLines.mEndLines[1];
//    gLines.mIndex = 2;
//}
//
//void renderLines(SDL_Renderer* pRenderer)
//{
//    for (auto& i : gLines.mLines)
//    {
//        SDL_RenderLine(pRenderer, i.x, i.y, i.z, i.w);
//    }
//}
//
//int main(int argc, char* argv[])
//{
//    SDL_Window* window = SDL_CreateWindow("Window", WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_RESIZABLE);
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
//
//    createLines(10);
//
//    bool isChecking{ true };
//    bool active{ true };
//    while (active)
//    {
//        SDL_Event event;
//        while (SDL_PollEvent(&event))
//        {
//            if (event.type == SDL_EVENT_QUIT ||
//                event.key.key == SDLK_ESCAPE)
//            {
//                active = false;
//                break;
//            }
//            if (event.key.key == SDLK_W)
//            {
//                for (auto& i : gLines.mLines)
//                {
//                    i.y -= 10.0f;
//                }
//            }
//            if (event.key.key == SDLK_S)
//            {
//                for (auto& i : gLines.mLines)
//                {
//                    i.y += 10.0f;
//                }
//            }
//            if (event.key.key == SDLK_D)
//            {
//                for (auto& i : gLines.mLines)
//                {
//                    i.x += 10.0f;
//                }
//            }
//            if (event.key.key == SDLK_A)
//            {
//                for (auto& i : gLines.mLines)
//                {
//                    i.x -= 10.0f;
//                }
//            }
//        }
//        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//        SDL_RenderClear(renderer);
//        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//
//        renderLines(renderer);
//
//        if (isChecking)
//        {
//            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
//            SDL_RenderPoint(renderer, gLines.mTheMostLeftVertex.x, gLines.mTheMostLeftVertex.y);
//            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//            SDL_RenderPoint(renderer, gLines.mCurrentVertex.x, gLines.mCurrentVertex.y);
//            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
//            SDL_RenderLine(renderer, gLines.mCurrentVertex.x, gLines.mCurrentVertex.y,
//                                     gLines.mNextVertex.x, gLines.mNextVertex.y);
//
//            if (gLines.mIndex < gLines.mEndLines.size())
//            {
//                gLines.mCheckedVertex = gLines.mEndLines[gLines.mIndex];
//                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
//                SDL_RenderLine(renderer, gLines.mCurrentVertex.x, gLines.mCurrentVertex.y, gLines.mCheckedVertex.x, gLines.mCheckedVertex.y);
//            }
//
//            glm::vec2 firstVector = gLines.mNextVertex - gLines.mCurrentVertex;
//            glm::vec2 secondVector = gLines.mCheckedVertex - gLines.mCurrentVertex;
//            glm::vec3 cross = glm::cross(glm::vec3(firstVector.x, firstVector.y, 0.0f), glm::vec3(secondVector.x, secondVector.y, 0.0f));
//            if (cross.z < 0.0f)
//                gLines.mNextVertex = gLines.mCheckedVertex;
//            if (gLines.mIndex < gLines.mLines.size())
//                gLines.mIndex++;
//            else
//            {
//                gLines.mHull.push_back(gLines.mNextVertex);
//                gLines.mCurrentVertex = gLines.mNextVertex;
//                gLines.mIndex = 0;
//                gLines.mNextVertex = gLines.mTheMostLeftVertex;
//                if (gLines.mHull[0] == *(gLines.mHull.end() - 1))
//                    isChecking = false;
//            }
//        }
//        else
//        {
//            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
//            for (int32_t i = 0; i < std::ssize(gLines.mHull) - 1; ++i)
//            {
//                SDL_RenderLine(renderer, gLines.mHull[i].x, gLines.mHull[i].y, gLines.mHull[i + 1].x, gLines.mHull[i + 1].y);
//            }
//            for (int32_t i = 0; i < std::ssize(gLines.mEndLines); ++i)
//            {
//                gLines.mLines[i].z = gLines.mEndLines[i].x;
//                gLines.mLines[i].w = gLines.mEndLines[i].y;
//            }
//        }
//        SDL_RenderPresent(renderer);
//    }
//
//    SDL_DestroyWindow(window);
//    SDL_DestroyRenderer(renderer);
//    SDL_Quit();
//    return 0;
//}
