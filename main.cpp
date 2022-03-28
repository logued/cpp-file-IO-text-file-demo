// File-IO-text-file.cpp                          March 2022
//
// Basic Text File IO - write and read
// Demonstrates:
//    Writing to a text file using an output file stream (ofstream)
//    Reading from a text file line-by-line, input file stream (ifstream)
//    Parsing a comma-delimited line of text using a stringstream object
//    Using <string> functions:  getline(), stoi() and stod()

// Note that the file "students.txt" will have to be copied into
// the folder:  "cmake-build-debug" as that is the default location where
// CLion it will search for files.

#include <iostream>
#include <fstream>      // file stream
#include <string>       // getline(), stoi(), stod()
#include <sstream>      // string stream

using namespace std;

void DemoOutputFileStream() 
{
    cout << "Creating and writing to file: out.txt" << endl;

    // create an output file stream object associated to the file out.txt
    ofstream outFileStream("out.txt");  // default write mode (overwrites existing data)

    if ( outFileStream.good() )
    {
        outFileStream << "Write one line of text to file.\n";
        outFileStream << "Write a second line of text to the same file\n";
        int age = 19;
        double height = 1.85;
        outFileStream << "John" << "," << age << "," << height << endl;
        
        outFileStream.close(); //  close file
        cout << "File has been written. Open it in a text error to check it.\n" << endl;
    }
    else
        cout << "Unable to open file";
}

/* 
* Parse a comma-delimited string and output each field.
* We know the string format is: "name,age,height"
*/
void parseLine(const string& strLine) {

    stringstream strStream( strLine ); //create a string-stream from the string

    string name;
    getline(strStream, name, ','); // get first string - which we expect to be the name

    int age = 0;
    double height = 0.0;

    try
    {
        string strTemp;
        getline(strStream, strTemp, ',');  // read next field (age) as a string
        age = stoi(strTemp);    // sconvert tring to int conversion (may throw exceptions)
        
        getline(strStream, strTemp, ',');   // extract the height as a string
        height = stod(strTemp); // convert string to double (may throw exceptions)
    }
    catch (std::invalid_argument const& e)
    {
        cout << "Bad input: std::invalid_argument thrown" << '\n';
    }
    catch (std::out_of_range const& e)
    {
        cout << "Integer overflow: std::out_of_range thrown" << '\n';
    }
    cout << "Name: " << name << " age: " << age << " height: " << height << endl;
}

/*
* Open text file as an input file stream (ifstream)
* Read text line-by-line from the file 
* Parse each line of text.
*/
void DemoInputFileStream() {
    cout << "Attempting to read from a comma-delimited text file." << endl;

    ifstream inFileStream("students.txt"); // open file as input file stream

    if ( inFileStream.good() )  // if file opened successfully, and not empty
    {
        string line;            // create a string object to store a line of text

        while ( getline(inFileStream, line) )   // read a line until false returned , getline() from <string> library
        {
            parseLine( line );  // pass the line of text to have it parsed
        }
        inFileStream.close();
    }
    else 
        cout << "Unable to open file, or file is empty.";
}

int main() {
    DemoOutputFileStream();
    DemoInputFileStream(); // read and parse lines 
    return 0;
}