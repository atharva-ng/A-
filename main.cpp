#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class ind_cordi
{
public:
        int x{}, y{};
        ind_cordi(int x, int y)
            : x(x), y(y)
        {
        }
};

class coordinates
{
public:
        vector<int> x;
        vector<int> y;
        int length{};
        void setCoordinates(int x1, int y1)
        {
                x.push_back(x1);
                y.push_back(y1);
                length++;
        }
};

void setGrid(vector<vector<int>> &grid)
{
        grid.at(1).at(1) = 1;
        grid.at(1).at(2) = 1;
        grid.at(1).at(3) = 0;
        grid.at(1).at(4) = 1;
        grid.at(1).at(5) = 1;
        grid.at(1).at(6) = 1;
        grid.at(1).at(7) = 1;
        grid.at(1).at(8) = 1;
        grid.at(2).at(1) = 1;
        grid.at(2).at(2) = 1;
        grid.at(2).at(3) = 0;
        grid.at(2).at(4) = 1;
        grid.at(2).at(5) = 0;
        grid.at(2).at(6) = 0;
        grid.at(2).at(7) = 0;
        grid.at(2).at(8) = 1;
        grid.at(3).at(1) = 1;
        grid.at(3).at(2) = 1;
        grid.at(3).at(3) = 1;
        grid.at(3).at(4) = 1;
        grid.at(3).at(5) = 1;
        grid.at(3).at(6) = 1;
        grid.at(3).at(7) = 1;
        grid.at(3).at(8) = 1;
        grid.at(4).at(1) = 1;
        grid.at(4).at(2) = 0;
        grid.at(4).at(3) = 0;
        grid.at(4).at(4) = 0;
        grid.at(4).at(5) = 0;
        grid.at(4).at(6) = 1;
        grid.at(4).at(7) = 0;
        grid.at(4).at(8) = 1;
        grid.at(5).at(1) = 1;
        grid.at(5).at(2) = 1;
        grid.at(5).at(3) = 1;
        grid.at(5).at(4) = 1;
        grid.at(5).at(5) = 1;
        grid.at(5).at(6) = 1;
        grid.at(5).at(7) = 1;
        grid.at(5).at(8) = 1;
}

float findG(ind_cordi curr, ind_cordi next)
{
        return sqrt(pow((curr.x - next.x), 2) + pow((curr.y - next.y), 2));
}

float findH(ind_cordi curr, ind_cordi last)
{
        return sqrt(pow((curr.x - last.x), 2) + pow((curr.y - last.y), 2));
}

int Neighbour(coordinates &emptyBlocks, vector<vector<int>> &grid, int x, int y)
{
        if (grid.at(x).at(y) == 1)
        {
                for (int a = -1; a <= 1; a++)
                {

                        for (int b = -1; b <= 1; b++)
                        {
                                if (x + a > 0 && x + a < 6 && y + b > 0 && y + b < 9)
                                {
                                        if (a == 0 && b == 0)
                                        {
                                                continue;
                                        }
                                        else if (grid.at(x + a).at(y + b) == 1)
                                        {
                                                if (a == 0 && b == 0)
                                                {

                                                        continue;
                                                }
                                                else
                                                {
                                                        emptyBlocks.setCoordinates(x + a, y + b);
                                                }
                                        }
                                }
                        }
                }
        }
        else
        {

                cout << "Try a feasible position" << endl;
        }
        return 0;
}

int main()
{
        vector<vector<int>> grid{
            {10, 10, 10, 10, 10, 10, 10, 10, 10},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
        };

        setGrid(grid);

        // cout << grid.at(2).at(4) << endl;

        ind_cordi start(1, 8);
        ind_cordi end(1, 1);

        ind_cordi curr(1, 8);
        ind_cordi next(1, 2);

        coordinates emptyBlocks;
        emptyBlocks.setCoordinates(curr.x, curr.y);

        Neighbour(emptyBlocks, grid, curr.x, curr.y);

        for (int i{}; i < emptyBlocks.length; i++)
        {
                cout << emptyBlocks.x.at(i) << " " << emptyBlocks.y.at(i) << endl;
        }

        // // int h{}; // next block to last block
        // // int g{}; // this block to next block
        // int f{};

        // f = findG(curr, next) + findH(curr, end);

        return 0;
}