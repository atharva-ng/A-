#include <iostream>
#include <vector>
#include <algorithm>
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
        void print()
        {
                for (int i{}; i < length; i++)
                {
                        cout << x.at(i) << " " << y.at(i) << endl;
                }
                cout << "=============================================" << endl;
        }
};

void setGrid(vector<vector<int>> &grid)
{
        grid.at(1).at(1) = 1;
        grid.at(1).at(2) = 1;
        grid.at(1).at(3) = 1;
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

float findF(ind_cordi curr, ind_cordi next, ind_cordi end)
{
        return (findG(curr, next) + findH(next, end));
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

        ind_cordi start(5, 8);
        ind_cordi end(1, 1);

        person p1(start, end);
        while (((p1.curr.x == end.x) && (p1.curr.y == end.y)) == 0)
        {

                coordinates emptyBlocks;
                ind_cordi next(0, 0);

                // Finding empty blocks

                Neighbour(emptyBlocks, grid, p1.curr.x, p1.curr.y);

                // Analysing Empty blocks

                vector<float> f;
                for (int i{}; i < emptyBlocks.length; i++)
                {
                        next.x = emptyBlocks.x.at(i);
                        next.y = emptyBlocks.y.at(i);
                        f.push_back(findF(p1.curr, next, end)); // H: next block to last block|| G:this block to next block
                }

                // Finding the next element

                int minElementIndex = min_element(f.begin(), f.end()) - f.begin();
                vector<int>::iterator itX;
                vector<int>::iterator itY;
                itX = find(p1.route.x.begin(), p1.route.x.end(), emptyBlocks.x.at(minElementIndex));
                itY = find(p1.route.y.begin(), p1.route.y.end(), emptyBlocks.y.at(minElementIndex));
                if (*itX == 0)
                {
                        *itX = 9999;
                }
                if (*itY == 0)
                {
                        *itY = 9999;
                }
                if (((*itX == *p1.route.x.end()) && (*itY == *p1.route.y.end())))
                {
                        p1.curr.x = emptyBlocks.x.at(minElementIndex);
                        p1.curr.y = emptyBlocks.y.at(minElementIndex);
                        p1.route.setCoordinates(emptyBlocks.x.at(minElementIndex), emptyBlocks.y.at(minElementIndex));
                }
                else
                {
                        cout << "Present  " << ((itX == p1.route.x.end()) && (itY == p1.route.y.end())) << endl;
                }
        }

        cout << "=============================================" << endl;
        p1.route.print();

        return 0;
}