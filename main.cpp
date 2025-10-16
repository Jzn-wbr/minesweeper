#include <iostream>
#include <vector>

#define SHUFFLE_NBR (1000)

struct Cell
{
    bool flag;
    bool bomb;
    bool discover;
    int number;

    Cell() : flag(0), bomb(0), discover(1), number(2) {}

    void swap_with(Cell *cell)
    {
        Cell tmp = *this;
        *this = *cell;
        *cell = tmp;
    }
};

/*
                   col
                    |
                    v
              0 1 2 3 4 5 6 (width)
            0 . . . . . . .
    row --> 1 . . . . . . .     grid[col][row]
            2 . . . . . . .
        (height)
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
            std::vector<Cell> col;
            for (int j = 0; j < height; j++)
            {
                Cell cell;
                col.push_back(cell);
            }
            array.push_back(col);
        }
    }

    // Add bomb randomly and give number to cells
    void init(int bomb_nbr)
    {
        if (bomb_nbr >= width * height)
            exit(1);

        // Fill bomb number needed
        for (int i = 0; i < bomb_nbr; i++)
        {
            array.at(i / height).at(i % height).bomb = true;
        }
        this->shuffle();
    }

    std::vector<std::vector<Cell>> get_grid()
    {
        return array;
    }

    void toggle_flag();
    void discover();
    bool bomb_is_discover();

private:
    void shuffle()
    {
        srand((unsigned int)time(0));
        for (int i = 0; i < SHUFFLE_NBR; i++)
        {
            int col1 = rand() % width;
            int row1 = rand() % height;
            int col2 = rand() % width;
            int row2 = rand() % height;
            array[col1][row1].swap_with(&array[col2][row2]);
        }
    }
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
        for (int i = 0; i < grid.height; i++)
        {
            for (int j = 0; j < grid.width; j++)
            {
                Cell cell = array.at(j).at(i);
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
    int width = 20;
    int height = 10;
    int bomb_nbr = 20;

    Game game;
    std::cout << "Welcome to minesweeper" << std::endl;

    Grid grid(width, height);
    UI ui;

    ui.display_grid(grid);
    std::cout << std::endl;
    grid.init(bomb_nbr);
    ui.display_grid(grid);

    return 0;
}