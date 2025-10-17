#include <iostream>
#include <vector>

#define SHUFFLE_NBR (1000)

struct Cell
{
    bool flag;
    bool bomb;
    bool discover;
    int number;

    Cell() : flag(0), bomb(0), discover(0), number(0) {}

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
        if (bomb_nbr >= width * height || bomb_nbr <= 0)
            exit(1);

        // Fill bomb number needed
        for (int i = 0; i < bomb_nbr; i++)
        {
            array.at(i / height).at(i % height).bomb = true;
        }
        this->shuffle();
        this->assign_number();
    }

    std::vector<std::vector<Cell>> get_grid()
    {
        return array;
    }

    void discover(int col, int row)
    {
        if ((col < 0) || (col >= width) || (row < 0) || (row >= height))
            return;

        Cell *c = &array.at(col).at(row);
        c->discover = true;
        if (c->bomb)
            return;

        if (!(row - 1 < 0))
        {
            if (!(array.at(col).at(row - 1).discover || array.at(col).at(row - 1).number))
            {
                discover(col, row - 1);
            }
        }
        if (!(col - 1 < 0))
        {
            if (!(array.at(col - 1).at(row).discover || array.at(col - 1).at(row).number))
            {
                discover(col - 1, row);
            }
        }
        if (!(col + 1 >= width))
        {
            if (!(array.at(col + 1).at(row).discover || array.at(col + 1).at(row).number))
            {
                discover(col + 1, row);
            }
        }
        if (!(row + 1 >= height))
        {
            if (!(array.at(col).at(row + 1).discover || array.at(col).at(row + 1).number))
            {
                discover(col, row + 1);
            }
        }
        return;
    }

    void toggle_flag();
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

    void assign_number()
    {
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                Cell *c = &array.at(i).at(j); // Current cell
                if (c->bomb)                  // Don't count for bomb cells
                    continue;

                if (!(j - 1 < 0))
                {
                    if (array.at(i).at(j - 1).bomb)
                        c->number++;

                    if (!(i - 1 < 0))
                    {
                        if (array.at(i - 1).at(j - 1).bomb)
                            c->number++;
                    }
                    if (!(i + 1 >= width))
                    {
                        if (array.at(i + 1).at(j - 1).bomb)
                            c->number++;
                    }
                }
                if (!(j + 1 >= height))
                {
                    if (array.at(i).at(j + 1).bomb)
                        c->number++;

                    if (!(i + 1 >= width))
                    {
                        if (array.at(i + 1).at(j + 1).bomb)
                            c->number++;
                    }
                    if (!(i - 1 < 0))
                    {
                        if (array.at(i - 1).at(j + 1).bomb)
                            c->number++;
                    }
                }
                if (!(i - 1 < 0))
                {
                    if (array.at(i - 1).at(j).bomb)
                        c->number++;
                }
                if (!(i + 1 >= width))
                {
                    if (array.at(i + 1).at(j).bomb)
                        c->number++;
                }
            }
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
        for (int i = 0; i < grid.width; i++)
        {
            std::cout << " ── ";
        }
        std::cout << std::endl;

        std::vector<std::vector<Cell>> array = grid.get_grid();
        for (int i = 0; i < grid.height; i++)
        {
            for (int j = 0; j < grid.width; j++)
            {
                std::cout << "|";

                Cell cell = array.at(j).at(i);
                if (cell.discover)
                {
                    if (cell.bomb)
                    {
                        std::cout << " b ";
                    }
                    else
                    {
                        std::cout << " " << cell.number << " ";
                    }
                }
                else
                {
                    if (cell.flag)
                    {
                        std::cout << " f ";
                    }
                    else
                    {
                        std::cout << "   ";
                    }
                }
            }
            std::cout << "|" << std::endl;
            for (int i = 0; i < grid.width; i++)
            {
                std::cout << " ── ";
            }
            std::cout << std::endl;
        }
    }
};

int main()
{
    int width = 20;
    int height = 5;
    int bomb_nbr = 2;

    Game game;
    std::cout << "Welcome to minesweeper" << std::endl;

    Grid grid(width, height);
    UI ui;

    grid.init(bomb_nbr);
    ui.display_grid(grid);

    grid.discover(19, 4);
    ui.display_grid(grid);

    return 0;
}