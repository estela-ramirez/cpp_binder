#include "Playlist.cpp"
// ?? do we need to check that id is unique?

// how to set netNodePtr as nullptr in setNext(), Playlist.cpp , template?
// ?? removeSong() can I have an additional method in the class declaration to set 
// the nextNodeptr to nullptr else use template?


// FIX
// ?? ask for length -> handle it being a char?  // ?? not handling exception
// changePosition()


bool bufferIsClear = true;

// if cin >> has been used, the buffer will be cleared of the \n
void checkBuffer(){
    if (!bufferIsClear){
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        bufferIsClear = true;
    }
}

// returns true if choice is within the valid choices
bool validateChoice(const char choice, const string validChoices){
    for (int i = 0; i < validChoices.length(); i++){
        if (choice == validChoices[i]){
            return true;
        }       
    }
    return false;
}

//prints menu with options
void printMenu(const string playlistTitle){
    cout << playlistTitle << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl;
    cout << "\nChoose an option:" << endl;
}

// asks user for unique ID
string askForID(){
    string id;
    cout << "Enter song's unique ID:" << endl;
    checkBuffer();;
    getline(cin, id);
    return id;
}

// asks user for song name
string askForSongName(){
    string songName;
    cout << "Enter song's name:" << endl;
    checkBuffer();
    getline(cin, songName);
    return songName;
}

// asks user for an artist name
string askForArtistName(){
    string artistName;
    cout << "Enter artist's name:" << endl;
    checkBuffer();
    getline(cin, artistName);
    return artistName;
}

// asks user for length of song in (sec)
int askForLength(){
    int length;

    cout << "Enter song's length (in seconds):" << endl;
    try{                                                // not catching exception
        cin >> length;
    }catch(exception length){
        cout << "Default length set to 180 seconds" << endl;   
    }

    length = 180;
    bufferIsClear = false;
    return length;
}

// creates new PlaylistNode and adds it to the end of the list
void addSong(PlayListNode* &head, PlayListNode* &tail){
    PlayListNode* newNode;

    newNode = new PlayListNode(askForID(), askForSongName(), 
            askForArtistName(), askForLength(), nullptr);
    cout << "adding this node " << newNode << endl;

    if (head == nullptr){
        head = newNode;
        tail = newNode;
    }else{
        tail->SetNext(newNode); 
        tail = newNode;
    }
}

//TO DO: COMMENT
void removeSong(PlayListNode* &head, PlayListNode* &tail, const string uniqueID){
    PlayListNode* curr = head;
    PlayListNode* next = nullptr;
    PlayListNode* delNode = nullptr;
    cout << "REMOVE SONG" << endl;

    if (curr == nullptr) {
        cout << "NO SONGS TO DELETE " << endl;
        return;
    }else if (uniqueID.compare(curr->GetID()) == 0){        //HEAD
        next = curr->GetNext();                             // the next node

        if (next == nullptr){                               //deleted only one in list
            head = nullptr;
            tail = nullptr;
        }else{
            head = next;                                    
            curr->SetNextAsNull();                          
        }
        cout << curr->GetSongName() << " removed" << endl;
        delete curr;

    }else{
        while (curr!= tail){
            if (uniqueID.compare(curr->GetNext()->GetID()) == 0){
                
                delNode = curr->GetNext();
  
                if (delNode->GetNext() != nullptr){         //MIDDLE
                    next = delNode->GetNext();
                    curr->SetNext(next);                    //??? why can't I put delNode->GetNext() directly
                                                            // initial value of reference to non-const must be an lvalue
                    delNode->SetNextAsNull();
                }else{
                    curr->SetNextAsNull();                  //TAIL
                    tail = curr;
                }
                cout << delNode->GetSongName() << " removed" << endl;
                delete delNode;
                break;                                      // only if you don't allow overlapping id's
            }
            curr = curr->GetNext(); 
        }
    }
}


//COMMENT
// void changePosition(PlayListNode* head, PlayListNode* tail){
//     cout << "CHANGE POSITION OF SONG" << endl;
//     PlayListNode* curr = head;
//     int currPos, nextPos = -1;
//     int counter = 1;
//     //pos less than 1 (move) to head, greater than n (move) to tail

//     cout << "Enter song's current position:" << endl;
//     cin >> currPos;
//     cout << "Enter new position for song:" << endl;
//     cin >> nextPos;
//     bufferIsClear = false;
   

//     //"Canned Heat" moved to position 2

//     if (curr == nullptr){return;}
//     //FRONT
//     if (currPos == 1){

//     }

//     //MIDDLE

//     //END
// }


// finds every PlayListNode that has matching artistName, prints out its data
void outputSongs(PlayListNode* &head, const string artistName){
    PlayListNode* curr = head;
    int counter = 1;
    bool found = false;
    if (head == nullptr){
        cout << "No songs by: " << artistName << endl << endl;
    }else{
        while (curr != nullptr){
            if (artistName.compare(curr->GetArtistName()) == 0){
                found = true;
    
                cout << endl << counter << "." << endl;
                curr->PrintPlaylistNode();
            }
            counter++;
            curr = curr->GetNext();
        }
        cout << endl;

        if(!found){
            cout << "No songs by: " << artistName << endl;
        }
        cout << endl;
    }
}

// adds up all PlayListNode's lengths (Playlist's total time) and prints it out
void outputTime(PlayListNode* &head){
    cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl << endl;
    PlayListNode* curr = head;
    int total = 0;
    while (curr!= nullptr){
        total += curr->GetSongLength();
        curr = curr->GetNext();
    }

    cout << "Total time: " << total << " seconds" << endl << endl;

}

// outputs every playListNode in the list
void outputPlaylist(PlayListNode* &head, const string playlistTitle){
    PlayListNode* curr = head;
    int counter = 1;
    if (head == NULL){
        cout << "Playlist is empty" << endl << endl;
    }else{
        cout << playlistTitle<<" - OUTPUT FULL PLAYLIST" << endl;
        
        while (curr != nullptr){
            if (counter > 1){
                cout << endl;
            }
            cout << counter << "." << endl;
            cout << "----- " << curr << endl;
            curr->PrintPlaylistNode();
            counter++;
            curr = curr->GetNext();
        }
        cout << endl;
    }
}

// calls method corresponding to user choice
void executeChoice(const char choice, PlayListNode* &head, PlayListNode* &tail, const string playlistTitle){
    if (choice == 'a'){
        addSong(head, tail);
    }else if (choice == 'd'){
        removeSong(head, tail, askForID());
        
    }else if (choice == 's'){
        cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
        outputSongs(head, askForArtistName());
    }else if (choice == 't'){
        outputTime(head);
    }else{
        outputPlaylist(head, playlistTitle);
    }

    // else if (choice == 'c'){
    //     changePosition(head, tail);
    // }
}

int main(void){


    PlayListNode* head = nullptr;
    PlayListNode* tail = nullptr;

    string playlistTitle;
    string validChoices = "adcstoq";
    char choice;
    cout << "Enter playlist's title:" << endl;
    getline(cin, playlistTitle);
    printMenu(playlistTitle);
    cin >> choice;

    // will ask user for choice until valid, executes the choice, printsMenu
    while (choice != 'q'){
        if (validateChoice(choice, validChoices)){
            bufferIsClear = false;
            executeChoice(choice, head, tail, playlistTitle);
            printMenu(playlistTitle);
            cin >> choice;
        }else{
            cout << "Enter valid choice" << endl;
            cin >> choice;
        }
    }
    return 0;
}