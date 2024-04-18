// File-IO-text-file.cpp                 2024
//
// Basic Text File IO - write and read
// Demonstrates:
//    Writing to a text file using an output file stream (ofstream)
//    Reading from a text file line-by-line, input file stream (ifstream)
//    Parsing a comma-delimited line of text using a stringstream object
//    Using <string> functions:  getline(), stoi() and stod()

// Note that the sample data file "students.txt" is in the project folder.
// You will have to set this folder to be the "Working Directory" so that CLion can find it.
// Set the Working Directory by selecting: // Run>Edit Configurations, and set
// "Working Directory" to be the project folder (click on the small folder icon in the edit label)

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

    // turn the line of text into a stringstream for tokenizing
    stringstream strStream( strLine );

    // set the delimeter character that is used in teh file (i.e. what separates the tokens in the string)
    // This could be a semicolon, or any character that we choose
    const  char DELIMETER = ',';
    string name;
    // extract the first token (the name) into the name variable
    // - a comma delimits the strings  -
    getline(strStream, name, DELIMETER);

    int age = 0;
    double height = 0.0;

    try
    {
        string strTemp;
        getline(strStream, strTemp, DELIMETER);  // read next field (age) as a string
        age = stoi(strTemp);    // convert string to int conversion (may throw exceptions)
        
        getline(strStream, strTemp, DELIMETER);   // extract the height as a string
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