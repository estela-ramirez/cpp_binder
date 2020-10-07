#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>
#include <string>
using namespace std;

//--------------------------------------------------------------//

class PlayListNode{
    public:
        PlayListNode();
    
        PlayListNode(string uniqueID, string songName, string artistName, int songLength, PlayListNode* nextNodePtr);
    
        inline string GetID()const {return uniqueID;}
        inline string GetSongName()const {return songName;}
        inline string GetArtistName()const {return artistName;}
        inline int GetSongLength()const {return songLength;}
        inline PlayListNode* GetNext()const {return nextNodePtr;}

        void SetNextAsNull(){nextNodePtr = nullptr;}  // ??? is helper allowed? or need template

        void InsertAfter(PlayListNode* node);

        // how to set netNodePtr as nullptr
        void SetNext(PlayListNode* &nextNode);
        

        void PrintPlaylistNode()const;
    
    private:
        string uniqueID;
        string songName;
        string artistName;
        int songLength;
        PlayListNode* nextNodePtr;
    
};

#endif