#include "Playlist.h"

PlayListNode::PlayListNode():uniqueID("none"), songName("none"), artistName("none"), 
        songLength(0), nextNodePtr(0){}

PlayListNode::PlayListNode(string uniqueID, string songName, string artistName, int songLength, PlayListNode* nextNodePtr):uniqueID(uniqueID), songName(songName), artistName(artistName), 
        songLength(songLength), nextNodePtr(nextNodePtr){cout << "created newNODE" << endl;}

PlayListNode* PlayListNode::InsertAfter(PlayListNode* node){

}

void PlayListNode::SetNext(PlayListNode* &nextNode){
    nextNodePtr =  nextNode;
}

void PlayListNode::PrintPlaylistNode()const{
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}
    