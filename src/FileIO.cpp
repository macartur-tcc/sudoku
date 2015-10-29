// $Id: FileIO.cpp 297 2008-05-30 20:16:20Z wimleers $


// @TODO: Add more exceptions.


/**
 * FileIO class definition.
 *
 * @file FileIO.cpp
 * @author Wim Leers
 */


#include "FileIO.h"


// pointer implementation
class FileIOImpl
{
public:
  FileIOImpl(const string & fileName,Format f);
  FILEIO_ROW csvReadRow(ifstream & fs);
  void cvsWriteRow(ofstream & fs, FILEIO_ROW row);
  Format m_format;
  string m_fileName;
  FILEIO_TABLE m_table;
};

FileIOImpl::FileIOImpl(const string & fileName = "db",Format f = FORMAT_CSV)
  : m_fileName(fileName), m_format(f)
{
}

//----------------------------------------------------------------------------
// Public methods.

FileIO::FileIO(const string & fileName, Format f)
 : impl(new FileIOImpl(fileName,f))
{
}

FileIO::~FileIO(void)
{
  delete this->impl;
}

Format
FileIO::GetFormat(void) const
{
  return this->impl->m_format;
}

void
FileIO::SetFormat(Format f)
{
 this->impl->m_format = f;
}

const string&
FileIO::GetFileName(void) const
{
  return this->impl->m_fileName;
}

void
FileIO::SetFileName(const string & fileName)
{
  this->impl->m_fileName = fileName;
}

FILEIO_TABLE
FileIO::GetTable(void) const
{
  return this->impl->m_table;
}

void
FileIO::SetTable(FILEIO_TABLE table )
{
  this->impl->m_table = table;
}

/**
 * Open (and read from) a file.
 */
void FileIO::Open(void) {
    ifstream fs(this->impl->m_fileName.c_str(), ios::in);
    FILEIO_ROW row;

    // Make sure the table is empty.
    this->impl->m_table.erase(this->impl->m_table.begin(), this->impl->m_table.end());

    if (fs.is_open()) {
        while (!fs.eof()) {
            switch (this->impl->m_format) {
                case FORMAT_CSV:
                    row = this->impl->csvReadRow(fs);
                    if (row.size())
                        this->impl->m_table.push_back(row);
                    break;
            }
        }
        fs.close();
    }
}

/**
 * Save a file.
 */
bool FileIO::Save(void) {
    ofstream fs(this->impl->m_fileName.c_str(), ios::out);
    FILEIO_ROW row;
    FILEIO_TABLE::iterator it;

    if (fs.is_open()) {
        switch (this->impl->m_format) {
            case FORMAT_CSV:
                for (it = this->impl->m_table.begin(); it != this->impl->m_table.end(); it++)
                    this->impl->cvsWriteRow(fs, *it);
                break;
        }
        fs.close();
        return true;
    }
    else
        throw(FileIOException(
            "FileIO::Open()",
            "The file " + this->impl->m_fileName + " could not be opened for writing."
        ));


}

/**
 * Erase the file.
 */
void FileIO::Erase(void) {
    // Erase the tabular representation of the file in the memory.
    this->impl->m_table.erase(this->impl->m_table.begin(), this->impl->m_table.end());

    // Erase the file itself.
    ofstream f(this->impl->m_fileName.c_str(), ios::trunc);
    f.close();
}

//----------------------------------------------------------------------------
// Private methods.

/**
 * Reads a row of strings from a filestream.
 *
 * @param fs
 *   Filestream that is opened in reading mode.
 * @return
 *   A row of strings.
 */
FILEIO_ROW FileIOImpl::csvReadRow(ifstream & fs) {
    string line;
    unsigned int pos = 0, prevPos = 0;
    FILEIO_ROW row;

    // Read the next row (one line) of the file.
    getline(fs, line);

    // Put all fields in this row in a queue.
    while (line.length() > 0 && pos < line.npos) {
        // Ignore the comma.
        if (pos > 0)
            prevPos = pos + 1;

        pos = (unsigned int) line.find(',', prevPos);
        row.push_back(line.substr(prevPos, pos - prevPos));
    }
    return row;
}

/**
 * Writes a row of strings to a filestream.
 *
 * @param fs
 *   Filestream that is opened in writing mode.
 * @param row
 *   A row of strings.
 */
void FileIOImpl::cvsWriteRow(ofstream & fs, FILEIO_ROW row) {
    FILEIO_ROW::iterator it, test;

    for (it = row.begin(); it != row.end(); it++) {
        fs << *it;

        // Test if we haven't reached the last column yet, and if so, print a
        // comma.
        test = it;
        test++;
        if (test != row.end())
            fs << ',';
    }
    fs << endl;
}
