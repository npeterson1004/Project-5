#ifndef RECFILE_TPP
#define RECFILE_TPP

template <class RecType>
int RecordFile<RecType>::Read(RecType& record, int recaddr) {
    int readAddr, result;
    readAddr = BufferFile::Read(recaddr);
    if (readAddr == -1) return -1;
    result = record.Unpack(Buffer);
    if (!result) return -1;
    return readAddr;
}

template <class RecType>
int RecordFile<RecType>::Write(const RecType& record, int recaddr) {
    int result;
    result = record.Pack(Buffer);
    if (!result) return -1;
    return BufferFile::Write(recaddr);
}

template <class RecType>
int RecordFile<RecType>::Append(const RecType& record, int recaddr) {
    int result;
    result = record.Pack(Buffer);
    if (!result) return -1;
    return BufferFile::Append();
}

template <class RecType>
RecordFile<RecType>::RecordFile(IOBuffer& buffer) : BufferFile(buffer) {}

#endif // RECFILE_TPP
