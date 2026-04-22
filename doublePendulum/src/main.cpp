#include "raylib.h"
#include <cmath>

#define WIDTH 800
#define HEIGHT 600
#define LINELEN 60
#define RADIUS 10
#define GRAVITY 1000
#define FPS 60
#define DAMPING 0.98

float g, l1, l2, m1, m2, theta1, theta2, omega1, omega2, v1, v2, dt;
Vector2 startPos = {WIDTH / 2, 100};

void init()
{
    g = GRAVITY;
    l1 = LINELEN;
    l2 = LINELEN;
    m1 = 10;
    m2 = 20;
    theta1 = 80 * DEG2RAD;  // 角度
    theta2 = 80 * DEG2RAD;
    omega1 = omega2 = 0.0; // 角速度
    dt = 1.0f / FPS;
    v1 = v2 =0.0; // 角加速度
    
}

void calculate()
{
    v1 = (-g * (2 * m1 + m2)* std::sin(theta1) - m2 * g * std::sin(theta1 - 2 * theta2) - 2 * m2 * std::sin(theta1 - theta2) * (l2 * theta2 * theta2 + l1 * theta1 * theta1 * std::cos(theta1 - theta2))) / (l1 * (2 * m1 + m2 - m2 * std::cos(2 * (theta1 - theta2))));
    v2 = (2 * std::sin(theta1 - theta2) * (l1 * (m1 + m2) * theta1 * theta1 + g * (m1 + m2) * std::cos(theta1) + l2 * m2 * theta2 * theta2 * std::cos(theta1 - theta2))) / (l2 * (2 * m1 + m2 - m2 * std::cos(2 * (theta1 - theta2))));
    omega1 += v1 * dt;
    omega2 += v2 * dt;
    theta1 += omega1 * dt;
    theta2 += omega2 * dt;
    
    omega1 *= DAMPING;
    omega2 *= DAMPING;
}

void pendulum()
{
    Vector2 pos1 = {startPos.x + l1 * std::sin(theta1), startPos.y + l1 * std::cos(theta1)};
    Vector2 pos2 = {pos1.x + l2 * std::sin(theta2), pos1.y + l2 * std::cos(theta2)};
    DrawLineEx(startPos, pos1, 3, WHITE);
    DrawLineEx(pos1, pos2, 3, WHITE);
    DrawCircleV(pos1, RADIUS, RED);
    DrawCircleV(pos2, RADIUS, RED);
}

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "双摆实验");

    SetTargetFPS(FPS);
    
    init();
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            calculate();
            pendulum();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
