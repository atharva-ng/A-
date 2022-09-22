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
        coordinates()
        {
        }

        coordinates(int x, int y)
            : x(x), y(y)
        {
        }

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
        return sqrt(static_cast<float>(pow((curr.x - next.x), 2) + pow((curr.y - next.y), 2)));
}

float findH(ind_cordi curr, ind_cordi last)
{
        return sqrt(static_cast<float>(pow((curr.x - last.x), 2) + pow((curr.y - last.y), 2)));
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

class person
{
public:
        ind_cordi start;
        ind_cordi end;
        ind_cordi curr;

        coordinates route;

        person(ind_cordi starti, ind_cordi endi)
            : start(starti), end(endi), curr(starti)
        {
                route.setCoordinates(start.x, start.y);
        }
};

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

        ind_cordi start(2, 4);
        ind_cordi end(1, 1);

        person p1(start, end);

        while ((p1.curr.x != end.x) && (p1.curr.y != end.y))
        {
                coordinates emptyBlocks;
                ind_cordi next(0, 0);
                Neighbour(emptyBlocks, grid, p1.curr.x, p1.curr.y);
                for (int i{}; i < emptyBlocks.length; i++)
                {
                        cout << emptyBlocks.x.at(i) << " " << emptyBlocks.y.at(i) << endl;
                }
                cout << "=============================================" << endl;
                vector<float> f;
                for (int i{}; i < emptyBlocks.length; i++)
                {
                        // int h{}; // next block to last block
                        // int g{}; // this block to next block

                        next.x = emptyBlocks.x.at(i);
                        next.y = emptyBlocks.y.at(i);
                        f.push_back((findG(p1.curr, next) + findH(next, end)));
                }
                for (auto k : f)
                {
                        cout << k << endl;
                }
                cout << "=============================================" << endl;
                int minElementIndex = min_element(f.begin(), f.end()) - f.begin();

                p1.curr.x = emptyBlocks.x.at(minElementIndex);
                p1.curr.y = emptyBlocks.y.at(minElementIndex);
                p1.route.setCoordinates(emptyBlocks.x.at(minElementIndex), emptyBlocks.y.at(minElementIndex));
        }
        cout << "=============================================" << endl;
        cout << "=============================================" << endl;
        cout << "=============================================" << endl;
        for (int i{}; i < p1.route.length; i++)
        {
                cout << p1.route.x.at(i) << " " << p1.route.y.at(i) << endl;
        }

        return 0;
}