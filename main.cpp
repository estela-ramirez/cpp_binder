#include "Playlist.cpp"
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

//FIX
// asks user for length of song in (sec)
int askForLength(){
    int length;

    cout << "Enter song's length (in seconds):" << endl;
    try{                                                // not catching exception
        cin >> length;
    }catch(int length){
        cout << "Default length set to 180 seconds" << endl;   
        length = 100;
    }

    bufferIsClear = false;
    return length;
}

// creates new PlaylistNode and adds it to the end of the list
void addSong(PlayListNode* &head, PlayListNode* &tail){
    PlayListNode* newNode;

    newNode = new PlayListNode(askForID(), askForSongName(), 
            askForArtistName(), askForLength(), 0);
    if (head == 0){
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
    PlayListNode* next = 0;
    PlayListNode* delNode = 0;
    cout << "REMOVE SONG" << endl;

    if (curr == 0) {
        cout << "NO SONGS TO DELETE " << endl;
        return;
    }else if (uniqueID.compare(curr->GetID()) == 0){        //HEAD
        next = curr->GetNext();                             // the next node

        if (next == 0){                               //deleted only one in list
            head = 0;
            tail = 0;
        }else{
            head = next;                                     
            curr->SetNext();                        
        }
        cout << curr->GetSongName() << " removed\n" << endl;
        delete curr;

    }else{
        while (curr!= tail){
            if (uniqueID.compare(curr->GetNext()->GetID()) == 0){
                
                delNode = curr->GetNext();
  
                if (delNode->GetNext() != 0){           //MIDDLE
                    next = delNode->GetNext();
                    curr->SetNext(next);                    //??? why can't I put delNode->GetNext() directly
                    delNode->SetNext();
                }else{
                    curr->SetNext();                       //TAIL
                    tail = curr;
                }
                cout << delNode->GetSongName() << " removed\n" << endl;
                delete delNode;
                break;                                      // only if you don't allow overlapping id's
            }
            curr = curr->GetNext(); 
        }
    }
}

// return the total number of nodes in the Playlist
int getNumberOfNodes(PlayListNode* &head){
    PlayListNode* curr = head;
    int counter = 0;
    while (curr!= 0){
        counter++;
        curr = curr->GetNext();
    }

    return counter;
}

/*asks user for the currPos (position of node you want to move)
and nextPos (position to move node to) **/
void askForPositions(int &currPos, int &nextPos){
    cout << "CHANGE POSITION OF SONG" << endl;
    cout << "Enter song's current position:" << endl;
    checkBuffer();
    cin >> currPos;
    cout << "Enter new position for song:" << endl;
    cin >> nextPos;
    bufferIsClear = false;
}

//if pos less than 1 (move) to head, greater than n (move) to tail 
void checkPositions(int &currPos, int &nextPos, const int n){
    if (nextPos < 1){nextPos = 1;}
    if (nextPos > n){nextPos = n;}
    if ((currPos > n) || (currPos < 1)){currPos = -1;}
    cout << "check positions  currPos: " << currPos << " nextPos: " << nextPos << endl;
}

// returns the node at position pos
PlayListNode* getNode(PlayListNode* &head, int pos){
    PlayListNode* curr = head;

    for (int i = 0; i < pos; i++){
        curr = curr->GetNext();
    }

    return curr;
}

// will return the node accoding to it's position in the list 
PlayListNode* getMoveToNode(PlayListNode* &head, PlayListNode* &tail, const int n, const int nextPos){
    PlayListNode* moveTo = 0;
    if (nextPos == 1){
        moveTo = head;
    }else if (nextPos == n){
        moveTo = tail;
    }else {
        moveTo = getNode(head, nextPos-1);   
    }

    return moveTo;
}

    //"Canned Heat" moved to position 2
    // Moving the head node (1 pt)
    // Moving the tail node (1 pt)
    // Moving a node to the head (1 pt)
    // Moving a node to the tail (1 pt)
    // Moving a node up the list (1 pt)
    // Moving a node down the list (1 pt)
void changePosition(PlayListNode* &head, PlayListNode* &tail){
    PlayListNode* moveNode = head;
    PlayListNode* moveTo = head;
    PlayListNode* prev = head;
    int currPos = -1;
    int nextPos = -1;
    cout << "getting number of noedes"  << endl;
    int n = getNumberOfNodes(head);

    cout << "n == " << n << endl;
    askForPositions(currPos, nextPos);
    checkPositions(currPos, nextPos, n);
    cout << "2. current and nextPos === " << currPos << ", " << nextPos << endl;

    // if no nodes, positons same, no node in that pos return
    if (head == 0 || (currPos == -1) || (currPos == nextPos)){return;}  

    if (currPos == 1){                      // MOVE HEAD
        moveNode = head;
        moveTo = getNode(head, nextPos-1);
        
        head = head->GetNext();
        moveNode->SetNext();                
        moveTo->InsertAfter(moveNode);

        if (nextPos == n){tail = moveNode;}

    }else if (currPos == n){               // MOVE TAIL   
        PlayListNode* newTail = moveTo;

        moveNode = tail;
        newTail = getNode(head, n-2);

        // update tail
        newTail->SetNext();
        tail = newTail;

        if (nextPos == 1){                              // move tail to head
            moveNode->SetNext(head);            
            head = moveNode;
        }else{                                          // move tail in between nodes
            prev = getNode(head, nextPos -2);          // previous of node positions to move to 
            prev->InsertAfter(moveNode);              // move old tail to nextPos
        }
    }else{                                              // MOVE MIDDLE NODE 
        PlayListNode* next = 0;

        prev = getNode(head, currPos-2);                // prev of moveNode node
        moveNode = prev->GetNext();

        moveTo = getMoveToNode(head, tail, n, nextPos);

        cout << "prev = " << prev->GetID() << endl;
        cout << "moveNode = " << moveNode->GetID() << endl;
        cout << "moveTo = " << moveTo->GetID() << endl;

        next = moveNode->GetNext();
        cout << "next = " << next->GetID() << endl;

        prev->SetNext(next);
        moveNode->SetNext();
        cout << "prev->next = " << (prev->GetNext())->GetID() << endl;   

        if (nextPos == 1){                              // move to head
            moveNode->SetNext(head);
            cout << "moveNode next = " << (moveNode->GetNext())->GetID() << endl;
            head = moveNode;
            cout << "head = " << head->GetID() << endl;
            cout << "tail = " << tail->GetID() << endl;
            }

        if (nextPos == n){                              // move to tail
            tail->InsertAfter(moveNode);
            tail = moveNode;}

        if (nextPos > currPos){                         // move down list
            moveTo->InsertAfter(moveNode);} 

        if (nextPos < currPos){                         //move up list
            prev = getNode(head, nextPos -2);          // prev of moveTo node
            prev->InsertAfter(moveNode);}
    }
    cout << "\"" << moveNode->GetSongName() << "\"" << " moved to position " << nextPos << endl;
}


// finds every PlayListNode that has matching artistName, prints out its data
void outputSongs(PlayListNode* &head, const string artistName){
    PlayListNode* curr = head;
    int counter = 1;
    bool found = false;
    if (head == 0){
        cout << "No songs by: " << artistName << endl;
    }else{
        while (curr != 0){
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
    }
}

// adds up all PlayListNode's lengths (Playlist's total time) and prints it out
void outputTime(PlayListNode* &head){
    cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
    PlayListNode* curr = head;
    int total = 0;
    while (curr!= 0){
        total += curr->GetSongLength();
        curr = curr->GetNext();
    }

    cout << "Total time: " << total << " seconds" << endl << endl;

}

// outputs every playListNode in the list
void outputPlaylist(PlayListNode* &head, const string playlistTitle){
    PlayListNode* curr = head;
    int counter = 1;
    if (head == 0){
        cout << "Playlist is empty" << endl << endl;
    }else{
        cout << playlistTitle<<" - OUTPUT FULL PLAYLIST" << endl;
        
        while (curr != 0){
            if (counter > 1){
                cout << endl;
            }
            cout << counter << "." << endl;
            curr->PrintPlaylistNode();
            counter++;
            curr = curr->GetNext();
        }
        cout << endl;
    }
}

// calls method corresponding to user choice
void executeChoice(const char choice, PlayListNode* &head, PlayListNode* &tail, const string playlistTitle){
    cout << "choice = " << choice << endl;
    if (choice == 'a'){
        addSong(head, tail);
    }else if (choice == 'd'){
        removeSong(head, tail, askForID());
        
    }else if (choice == 's'){
        cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
        outputSongs(head, askForArtistName());
    }else if (choice == 't'){
        outputTime(head);
    }else if (choice == 'c'){
        changePosition(head, tail);
    }else{
        outputPlaylist(head, playlistTitle);
    }
}

int main(void){


    PlayListNode* head = 0;
    PlayListNode* tail = 0;

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