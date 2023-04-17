// buffile.cc

#include "buffile.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

BufferFile::BufferFile (IOBuffer & from)
 // create with a buffer
	: Buffer (from)
{
}

int BufferFile::Open(const char* filename, int mode)
{
    // These modes are not allowed when opening an existing file
    if (mode & std::ios::app || mode & std::ios::trunc)
        return FALSE;

    File.open(filename, static_cast<std::ios_base::openmode>(mode) | std::ios_base::in | std::ios_base::binary);
    if (!File.good())
        return FALSE;

    File.seekg(0, std::ios_base::beg);
    File.seekp(0, std::ios_base::beg);

    HeaderSize = ReadHeader();
    if (!HeaderSize) // no header and file opened for output
        return FALSE;

    File.seekp(HeaderSize, std::ios_base::beg);
    File.seekg(HeaderSize, std::ios_base::beg);

    return File.good();
}

int BufferFile::Create(const char* filename, int mode)
// create a new file and write a header on it.
// use ios::trunc to ensure that the file is created and truncated if it already exists.
{
    if (!(mode & std::ios::out))
        return FALSE; // must include ios::out
    File.open(filename, static_cast<std::ios_base::openmode>(mode) | std::ios_base::in | std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
    if (!File.good()) {
        File.close();
        return FALSE;
    }
    HeaderSize = WriteHeader();
    return HeaderSize != 0;
}



int BufferFile::Close ()
{
	File . close();
	return TRUE;
}

int BufferFile::Rewind ()
{
	File . seekg (HeaderSize, ios::beg);
	File . seekp (HeaderSize, ios::beg);
	return 1;
}

// Input and Output operations
int BufferFile::Read (int recaddr)
// read a record into the buffer
// return the record address
// return <0 if read failed
// if recaddr == -1, read the next record in the File
// if recaddr != -1, read the record at that address
{
	if (recaddr == -1)
		return Buffer . Read (File);
	else
		return Buffer . DRead (File, recaddr);
}
 
int BufferFile::Write (int recaddr)
 // write the current buffer contents
{
	if (recaddr == -1)
		return Buffer . Write (File);
	else
		return Buffer . DWrite (File, recaddr);
}

int BufferFile::Append ()
// write the current buffer at the end of File
{
	File . seekp (0, ios::end);
	return Buffer . Write (File);
}

// Access to IOBuffer
IOBuffer & BufferFile::GetBuffer ()
{ return Buffer;}

// protected methods
int BufferFile::ReadHeader ()
{
	return Buffer . ReadHeader (File);	
}

int BufferFile::WriteHeader ()
{
	return Buffer . WriteHeader (File);
}

