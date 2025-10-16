#include <iostream>
#include <vector>

struct Cell
{
    Cell() : flag(0), bomb(0), discover(1), number(2) {}
    bool flag;
    bool bomb;
    bool discover;
    int number;
};
/*
      0 1 2 3 4 5 6 (i, width)
    0 . . . . . . .
    1 . . . . . . .
    2 . . . . . . .
    (j,
    height)
*/
class Grid
{
    std::vector<std::vector<Cell>> array;

public:
    int width;
    int height;

    Grid(int width, int height) : width(width), height(height)
    {
        for (int i = 0; i < width; i++)
        {
            std::vector<Cell> row;
            for (int j = 0; j < height; j++)
            {
                Cell cell;
                row.push_back(cell);
            }
            array.push_back(row);
        }
    }

    // Add bomb randomly and give number to cells
    void init(int bomb_nbr)
    {
        return;
    }
    void toggle_flag();
    void discover();
    std::vector<std::vector<Cell>> get_grid()
    {
        return array;
    }
    bool bomb_is_discover();
};

struct Game
{
    std::string get_state();
    std::string get_time();
    void run();
};

struct UI
{
    void discover_cells();
    void add_flag();
    void display_grid(Grid grid)
    {
        std::vector<std::vector<Cell>> array = grid.get_grid();
        for (int i = 0; i < grid.width; i++)
        {
            for (int j = 0; j < grid.height; j++)
            {
                Cell cell = array.at(i).at(j);
                if (cell.discover)
                {
                    if (cell.bomb)
                    {
                        std::cout << "b ";
                    }
                    else if (cell.number)
                    {
                        std::cout << cell.number << " ";
                    }
                }
                else
                {
                    if (cell.flag)
                    {
                        std::cout << "f ";
                    }
                    else
                    {
                        std::cout << "  ";
                    }
                }
            }
            std::cout << std::endl;
        }
    }
};

int main()
{
    Game game;
    int width = 8;
    int height = 5;
    int bomb_nbr = 4;
    std::cout << "Welcome to minesweeper" << std::endl;

    Grid grid(height, width); // Width, height, bomb
    UI ui;
    ui.display_grid(grid);
    std::cout << std::endl;
    grid.init(bomb_nbr);
    ui.display_grid(grid);
    return 0;
}