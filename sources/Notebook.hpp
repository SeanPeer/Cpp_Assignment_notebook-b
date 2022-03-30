
#include <vector>
#include <string>
#include <map>
#include "Direction.hpp"

using namespace std;
namespace ariel {
    class Notebook {
         private:
            std::map<std::string, std::vector<char>> noteBook;

        public:
            void write (int page, int row , int column , Direction direction, string str);
            string read (int page, int row , int column , Direction direction, int length);
            void erase (int page, int row , int column , Direction direction, int length);
            string show (int pageNumber);
            static void validInputCheck(int page, int row, int column, Direction direction, int length);
    };
};