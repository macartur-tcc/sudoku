// $Id: FileIO.h 297 2008-05-30 20:16:20Z wimleers $


/**
 * FileIO template class definition.
 *
 * @file FileIO.h
 * @author Wim Leers
 */


#ifndef FILEIO_H
#define FILEIO_H

#include <fstream>
#include <string>
#include <queue>
using namespace std;
#include "FileIOException.h"

enum Format { FORMAT_CSV };

#define FILEIO_ROW deque<string>
#define FILEIO_TABLE deque< FILEIO_ROW >

class FileIOImpl;

class FileIO {
    public:
        FileIO(const string & fileName = "db", Format f = FORMAT_CSV);
        ~FileIO(void);
        Format GetFormat(void) const;
        void SetFormat(Format f);
        const string & GetFileName(void) const;
        void SetFileName(const string & fileName);
        FILEIO_TABLE GetTable(void) const ;
        void SetTable(FILEIO_TABLE table );
        void Open(void);
        bool Save(void);
        void Erase(void);

    private:
      FileIOImpl* impl;
};

#endif
