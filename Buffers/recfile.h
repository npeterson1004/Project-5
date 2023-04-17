#ifndef RECFILE_H
#define RECFILE_H

#include "buffile.h"
#include "iobuffer.h"

template <class RecType>
class RecordFile : public BufferFile {
public:
    int Read(RecType& record, int recaddr = -1);
    int Write(const RecType& record, int recaddr = -1);
    int Append(const RecType& record, int recaddr = -1);
    RecordFile(IOBuffer& buffer);
};

#include "recfile.cpp"

#endif // RECFILE_H
