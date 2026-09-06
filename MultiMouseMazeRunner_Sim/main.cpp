#include <iostream>
#include <utility>
#include <stack>
#include <vector>
#include <raylib.h>
#include <memory>
#include <thread>
#include <chrono>

#define MazeSize 25
#define CellSize 25

int dx[4] = {0, 0, -1, 1};  //this follows up, right, down, left
int dy[4] = {-1, 1, 0, 0}; 

const int UNEXPLORED = 0, END = 9, WALL = 8, VISITED = 1, DEAD_END = 2;
const int MOUSE_A = 3, MOUSE_B = 4;

enum MOUSE {MOUSEA, MOUSEB};
MOUSE mouse = MOUSEA;

enum STATE {FORWARD, BT};
STATE state = FORWARD;

class RENDER
{
private: 
    std::vector<std::vector<int>>& maze;  
    std::shared_ptr<std::pair<int, int>> mouse_a_pos = std::make_shared<std::pair<int, int>>();
    std::shared_ptr<std::pair<int, int>> mouse_b_pos = std::make_shared<std::pair<int, int>>();
public: 
    RENDER(std::vector<std::vector<int>>& MAZE, std::shared_ptr<std::pair<int, int>>MouseA_pos, 
        std::shared_ptr<std::pair<int, int>>MouseB_pos) : maze(MAZE), mouse_a_pos(MouseA_pos), mouse_b_pos(MouseB_pos) {}

    void DrawMaze()
    {
        for(int i = 0; i <MazeSize; i++)
        {
            for(int j = 0; j < MazeSize; j++)
            {
                if(maze[j][i] == WALL) { DrawRectangle(i*CellSize, j*CellSize, CellSize, CellSize, GRAY); }
                if(maze[j][i] == END) { DrawRectangle(i*CellSize, j*CellSize, CellSize, CellSize, PINK); }
                if(maze[j][i] == VISITED) { DrawRectangle(i*CellSize, j*CellSize, CellSize, CellSize, GREEN); }
                if(maze[j][i] == DEAD_END) { DrawRectangle(i*CellSize, j*CellSize, CellSize, CellSize, RED); }
                DrawRectangleLines(i*CellSize, j*CellSize, CellSize, CellSize, BLACK);
            }
        DrawCircle((mouse_a_pos->second*CellSize) + CellSize/2, (mouse_a_pos->first*CellSize) + CellSize/2, 5, SKYBLUE);
        DrawCircle((mouse_b_pos->second*CellSize) + CellSize/2, (mouse_b_pos->first*CellSize) + CellSize/2, 5, GOLD);
        }
    }
};

class WORLD
{
private: 
    std::vector<std::vector<int>>& memory;
    int(*maze)[MazeSize];
    std::stack<std::pair<int, int>>& StackMem_A;
    std::stack<std::pair<int, int>>& StackMem_B;
    
    std::shared_ptr<std::pair<int, int>> MouseA_pos = std::make_shared<std::pair<int, int>>();
    std::shared_ptr<std::pair<int, int>> MouseB_pos = std::make_shared<std::pair<int, int>>();
    std::pair<int, int>& end_pos;

    bool IsValid(int x, int y)
    {
        if(x >= 0 && x < MazeSize && y >= 0 && y < MazeSize)
        {
            if(maze[x][y] == WALL) 
            {
                memory[x][y] = WALL;
                return false;
            }
            return true;
        }
        return false;
    }

    std::pair<int, int> BackTrack(int& x, int& y)
    {
        std::pair<int, int> toReturn = {0, 0};
        std::pair<int, int>pre_pos = {0, 0};
        switch(mouse)
        {
            case(MOUSEA):
                if(StackMem_A.size() > 1)
                {
                    StackMem_A.pop();      
                }
                pre_pos = StackMem_A.top();
                *MouseA_pos = pre_pos;
                memory[MouseA_pos->first][MouseA_pos->second] = MOUSE_A;
                toReturn = *MouseA_pos;
                break;
            case(MOUSEB):
                if(StackMem_B.size() > 1)
                {
                    StackMem_B.pop();      
                }
                pre_pos = StackMem_B.top();
                *MouseB_pos = pre_pos;
                memory[MouseB_pos->first][MouseB_pos->second] = MOUSE_B;
                toReturn = *MouseB_pos;
                break;
        }
        memory[x][y] = DEAD_END;
        return{toReturn};
    }

    std::pair<int, int> CheckNeighbour(int x, int y) // CurrentPosition of Mouse A and B  // shouldn't add reference 
    {
        for(int d = 0; d < 4; d++)
        {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if(IsValid(nx, ny) && memory[nx][ny] != VISITED && memory[nx][ny] != DEAD_END && memory[nx][ny] != MOUSE_A && memory[nx][ny] != MOUSE_B)
            {
                state = FORWARD;
                return {nx, ny};
            }
        }
        state = BT;
        std::pair<int, int> toReturn = BackTrack(x, y);
        return{toReturn};
    }

public:
    WORLD(std::vector<std::vector<int>>& Memory, int(*Maze)[MazeSize], std::shared_ptr<std::pair<int, int>> mouseA_pos, 
    std::shared_ptr<std::pair<int, int>> mouseB_pos, std::pair<int, int>& endPos, std::stack<std::pair<int,int>>& StackMemA, std::stack<std::pair<int,int>>& StackMemB) : 
    memory(Memory), maze(Maze), MouseA_pos(mouseA_pos), MouseB_pos(mouseB_pos), end_pos(endPos), StackMem_A(StackMemA), 
    StackMem_B(StackMemB) {}

    void CheckMouseA()
    {
        mouse = MOUSEA;
        std::pair<int, int>newPos = CheckNeighbour(MouseA_pos->first, MouseA_pos->second);
        if(state == FORWARD)
        {
            memory[MouseA_pos->first][MouseA_pos->second] = VISITED;
            *MouseA_pos = newPos;
            StackMem_A.push({*MouseA_pos});
            memory[MouseA_pos->first][MouseA_pos->second] = MOUSE_A;
        }
    }

    void CheckMouseB()
    {
        mouse = MOUSEB;
        std::pair<int, int>newPos = CheckNeighbour(MouseB_pos->first, MouseB_pos->second);
        if(state == FORWARD)
        {
            memory[MouseB_pos->first][MouseB_pos->second] = VISITED;
            *MouseB_pos = newPos;
            StackMem_B.push({*MouseB_pos});
            memory[MouseB_pos->first][MouseB_pos->second] = MOUSE_B;
        }
    }

    void printMaze()
    {
        for(auto row = memory.begin(); row!= memory.end(); row++)
        {
            for(auto col = row->begin(); col != row->end(); col++)
            {
                std::cout << *col;
            }
            std::cout << std::endl;
        }
    }
};

int main()
{
    const int ScreenWidth = 650, ScreenHeight = 650;
    SetTargetFPS(90);
    //SetTargetFPS(GetMonitorRefreshRate(0));
    InitWindow(ScreenWidth, ScreenHeight, "MMMR");

    std::shared_ptr<std::pair<int, int>> MouseA_pos, MouseB_pos;
    MouseA_pos = std::make_shared<std::pair<int, int>>();
    MouseB_pos = std::make_shared<std::pair<int, int>>();
    
    std::pair<int, int> end_pos;
    std::vector<std::vector<int>> memory(MazeSize, std::vector<int>(MazeSize, UNEXPLORED));
    std::stack<std::pair<int,int>> StackMem_A, StackMem_B;
    int maze[MazeSize][MazeSize] = 
    {
        {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8},
        {8,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
        {8,0,8,8,8,0,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0,8},
        {8,0,8,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,8,0,8},
        {8,0,8,0,8,8,8,8,8,0,8,0,8,8,8,8,8,8,8,8,8,0,8,0,8},
        {8,0,0,0,8,0,0,0,8,0,0,0,8,0,0,0,0,0,0,0,8,0,0,0,8},
        {8,8,8,0,8,0,8,0,8,8,8,0,8,0,8,8,8,8,8,0,8,8,8,0,8},
        {8,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,8},
        {8,0,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0,8,8,8,8,8,0,8},
        {8,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,8,0,0,0,0,0,0,0,8},
        {8,8,8,8,8,8,8,8,8,0,8,0,8,8,8,0,8,8,8,8,8,8,8,0,8},
        {8,0,0,0,0,0,0,0,8,0,0,0,8,0,0,0,0,0,0,0,0,0,8,0,8},
        {8,0,8,8,8,8,8,0,8,8,8,8,8,0,8,8,8,8,8,8,8,0,8,0,8},
        {8,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,8},
        {8,8,8,8,8,0,8,8,8,8,8,8,8,8,8,8,8,0,8,8,8,8,8,0,8},
        {8,0,0,0,8,0,0,0,0,0,8,0,0,0,0,0,8,0,0,0,0,0,8,0,8},
        {8,0,8,0,8,8,8,8,8,0,8,0,8,8,8,0,8,8,8,8,8,0,8,0,8},
        {8,0,8,0,0,0,0,0,8,0,0,0,8,0,0,0,0,0,0,0,8,0,0,0,8},
        {8,0,8,8,8,8,8,0,8,8,8,8,8,0,8,8,8,8,8,0,8,8,8,0,8}, 
        {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
        {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0,8},
        {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,8},
        {8,0,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0,8,0,8},
        {8,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,8},
        {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8}
    };
    for(int i = 0; i < MazeSize; i++)
    {
        for(int j = 0; j < MazeSize; j++)
        {
            if(maze[i][j] == END) { end_pos = {i, j}; }
            else if(maze[i][j] == MOUSE_A) 
            {
                *MouseA_pos = {i, j};
                memory[i][j] = MOUSE_A;
                StackMem_A.push({*MouseA_pos});
            }
            else if(maze[i][j] == MOUSE_B)
            {
                *MouseB_pos = {i, j};
                memory[i][j] = MOUSE_B;
                StackMem_B.push({*MouseB_pos});
            }
        }
    }
    WORLD world(memory, maze, MouseA_pos, MouseB_pos, end_pos, StackMem_A, StackMem_B);
    RENDER render(memory, MouseA_pos, MouseB_pos);
    while(!WindowShouldClose())
    {
        if(StackMem_A.size() != 0) world.CheckMouseA();
        if(StackMem_B.size() != 0 ) world.CheckMouseB();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        render.DrawMaze();
        EndDrawing();
        system("clear");
        world.printMaze();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    CloseWindow();
}