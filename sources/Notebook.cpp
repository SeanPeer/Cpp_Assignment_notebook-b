
#include <string>
#include <iostream>
#include <vector>
#include "Notebook.hpp"
#include "Direction.hpp"
using ariel::Direction;
using namespace std;

const size_t MAX_CHARS_ROW = 100;
const int ASCII_HIGH = 125;
const int ASCII_LOW = 32;

namespace ariel
{
    std::vector<char> line(MAX_CHARS_ROW, '_');

    void Notebook::write(int page, int row, int column, Direction direction, string str)
    {
        int length = str.length();
        size_t new_column = (size_t) column;
        string curr_str = read(page, row, column, direction, length);
        if (curr_str != std::string(str.length(), '_'))
        {
            throw("You cannot write where its already written");
        }
        for (size_t i = 0; i < str.length(); i++)
        {
            char ch = str[i];
            if (ch < ASCII_LOW || ch > ASCII_HIGH)
            {
                throw("You cannot write an invalid char");
            }
        }
        if (direction == Direction::Horizontal)
        {
            string index = std::to_string(page) + "-" + std::to_string(row);
            
            for (size_t i = 0; i < length; i++)
            {
                if (str[(size_t)i] == '~')
                {
                    throw("can't write ~");
                }
                noteBook[index].at(new_column + i) = str[i];
            }
        }
        else
        {
            for (int i = 0; i < length; i++)
            {
                string index = std::to_string(page) + "-" + std::to_string(row + i);
                noteBook[index].at(new_column) = str[(size_t)i];
            }
        }
    };

    string Notebook::read(int page, int row, int column, Direction direction, int length)
    {
        validInputCheck(page, row, column, direction, length);
        size_t new_column = (size_t) column;
        string result;
        if (direction == Direction::Horizontal)
        {
            string index = std::to_string(page) + "-" + std::to_string(row);
            if (noteBook[index].empty())
            {
                noteBook[index] = line;
            }
            for (size_t i = 0; i < length; i++)
            {
                result += noteBook[index].at(new_column + i);
            }
        }
        else
        {
            for (int i = 0; i < length; i++)
            {
                string index = std::to_string(page) + "-" + std::to_string(row + i);
                if (noteBook[index].empty())
                {
                    noteBook[index] = line;
                }
                result += noteBook[index].at(new_column);
            }
        }
        return result;
    };

    void Notebook::erase(int page, int row, int column, Direction direction, int length)
    {
        validInputCheck(page, row, column, direction, length);
        size_t new_column = (size_t) column;
        size_t new_row = (size_t) row;
        string curr_str = read(page, row, column, direction, length);
        if (direction == Direction::Horizontal)
        {
            string index = std::to_string(page) + "-" + std::to_string(row);

            for (size_t i = 0; i < length; i++)
            {
                noteBook[index].at(new_column + i) = '~';
            }
        }
        else
        {
            for (size_t i = 0; i < length; i++)
            {
                string index = std::to_string(page) + "-" + std::to_string(new_row + i);
                noteBook[index].at(new_column) = '~';
            }
        }
    }

    string Notebook::show(int pageNumber)
    {
        if (pageNumber < 0)
        {
            throw("Invalid page !");
        }
        string result;
        for (int i = 0; i < MAX_CHARS_ROW; i++)
        {
            result += read(pageNumber, i, 0, Direction::Horizontal, MAX_CHARS_ROW);
        }
        return result;
    }

    void Notebook::validInputCheck(int page, int row, int column, Direction direction, int length)
    {
        if (column < 0 || length < 0 || page < 0 || row < 0 )
        {
            throw("Out of bound");
        }

        if (direction == Direction::Horizontal && column + length > MAX_CHARS_ROW)
        {
            throw("There are only 100 chars for each row");
        }
    }

};