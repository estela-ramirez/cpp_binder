#include "Playlist.h"

PlayListNode::PlayListNode():uniqueID("none"), songName("none"), artistName("none"), 
        songLength(0), nextNodePtr(0){}


//FIX set default ptr to 0
PlayListNode::PlayListNode(string uniqueID, string songName, string artistName, int songLength, PlayListNode* nextNodePtr):uniqueID(uniqueID), songName(songName), artistName(artistName), 
        songLength(songLength), nextNodePtr(nextNodePtr){}



void PlayListNode::InsertAfter(PlayListNode* &node){
    if (nextNodePtr == 0){
        this->SetNext(node);
    }else{
        PlayListNode* nextNode = this->GetNext();
        node->SetNext(nextNode);
        this->SetNext(node);

    }
}

// parameter is reference to a (pointer to a PlayListNode) in order to update the list 
void PlayListNode::SetNext(PlayListNode* &nextNode){
    nextNodePtr =  nextNode;
}

void PlayListNode::SetNext(){
    nextNodePtr =  0;
   
}

void PlayListNode::PrintPlaylistNode()const{
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}
    