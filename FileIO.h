# include <iostream>
# include <fstream>

using namespace std;

class FileIO {
    public:
        FileIO();
        FileIO(string name);
        ~FileIO();

        void setName(string name);
        int getSumLines();

        double getLine();
        void check();

        int currLine;
        int sumLine;
        string fileName;
};
