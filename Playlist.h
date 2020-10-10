#pragma once
#include <iostream>
#include <string>
using namespace std;

//--------------------------------------------------------------//

class PlayListNode{
    public:
        PlayListNode();
    
        //FIX set default ptr to 0
        PlayListNode(string uniqueID, string songName, string artistName, int songLength, PlayListNode* nextNodePtr);
    
        inline string GetID()const {return uniqueID;}
        inline string GetSongName()const {return songName;}
        inline string GetArtistName()const {return artistName;}
        inline int GetSongLength()const {return songLength;}
        inline PlayListNode* GetNext()const {return nextNodePtr;}

        void InsertAfter(PlayListNode* &node);

        void SetNext(PlayListNode* &nextNode);  // can set to 0
        
        void SetNext();

        void PrintPlaylistNode()const;
    
    private:
        string uniqueID;
        string songName;
        string artistName;
        int songLength;
        PlayListNode* nextNodePtr;
    
};
