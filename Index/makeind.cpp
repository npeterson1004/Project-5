#include "textind.h"
#include "delim.h"
#include "buffile.h"
#include "recordng.h"
#include "tindbuff.h"
#include <iostream>
#include <fstream>

int RetrieveRecording (Recording & recording, char * key, 
			TextIndex & RecordingIndex, BufferFile & RecordingFile)
// read and unpack the recording, return TRUE if succeeds
{	
    int result;
    cout <<"Retrieve "<<key<<" at recaddr "<<RecordingIndex.Search(key)<<endl;
    result = RecordingFile.Read(RecordingIndex.Search(key));
    cout <<"read result: "<<result<<endl;
    if (result == -1) return FALSE;
    result = recording.Unpack(RecordingFile.GetBuffer());
    return result;
}

// make an index from a recording file
int IndexRecordingFile (char * myfile, TextIndex & RecordingIndex)
{
    Recording rec; 
    int recaddr, result;
    DelimFieldBuffer Buffer; // create a buffer
    BufferFile RecordingFile(Buffer); 
    result = RecordingFile.Open(myfile, ios::in);
    if (!result)
    {
        cout << "Unable to open file!!! "<<myfile<<endl;
        return 0;
    }
    while (1) // loop until the read fails
    {
        recaddr = RecordingFile.Read(); // read next record
        if (recaddr < 0) break;
        rec.Unpack(Buffer);
        RecordingIndex.Insert(rec.Key(), recaddr);
        cout << recaddr <<'\t'<<rec<<endl;
    }
    RecordingIndex.Print(cout);
    char ky[11] = "96737Ocean";
    result = RetrieveRecording(rec, ky, RecordingIndex, RecordingFile);
    if(result == FALSE){
        cout << "Failed to retrieve record with key " << ky << endl;
    } else {
        cout <<"Found record: "<<rec;
    }
    return 1;
}

int main ()
{
    // first argument is the file name for the data file
    TextIndex RecordingIndex (10);
    char dfile[9] = "data.csv";
    int result = IndexRecordingFile(dfile, RecordingIndex);
    if(result == 0){
        cout << "Indexing failed. Exiting program." << endl;
        return 1;
    }
    // store the index in a file
    TextIndexBuffer IndexBuffer (12, 10);// 12 byte key, 10 keys
    BufferFile IndexFile (IndexBuffer);
    IndexBuffer.Pack(RecordingIndex);
    char ifile[13] = "recindex.dat";
    IndexFile.Create(ifile, ios::out);
    IndexFile.Write();
    cout << "Indexing successful. Index file created: " << ifile << endl;
    return 0;
}
