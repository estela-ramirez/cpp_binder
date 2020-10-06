#include "Playlist.cpp"

bool validateChoice(const char choice, const string validChoices){
    for (int i = 0; i < validChoices.length(); i++){
        if (choice == validChoices[i]){
            return true;
        }       
    }
    return false;
}

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

string askForID(){
    string id;
    cout << "Enter song's unique ID:" << endl;
    getline(cin, id);
    return id;
}

string askForSongName(){
    string songName;
    cout << "Enter song's name:" << endl;
    getline(cin, songName);
    return songName;
}

string askForArtistName(){
    string artistName;
    cout << "Enter artist's name:" << endl;
    getline(cin, artistName);
    return artistName;
}

int askForLength(){
    int length;
    cout << "Enter song's length (in seconds):" << endl;
    cin >> length;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return length;
}

void addSong(PlayListNode* &head, PlayListNode* &tail){
    PlayListNode* newNode;

    cout << "ADD SONG" << endl;

    newNode = new PlayListNode(askForID(), askForSongName(), 
            askForArtistName(), askForLength(), nullptr);
    
    if (head == nullptr){
        head = newNode;
        tail = newNode;
    }else{
        tail->SetNext(newNode); 
        tail = newNode;
    }
    

}


// void removeSong(PlayListNode* &head, PlayListNode* &tail, const string uniqueID){
//     PlayListNode* curr = head;
//     PlayListNode* delNode = nullptr;
//     cout << "REMOVE SONG" << endl;

//     if (curr == nullptr) {
//         return;
//     }else if (uniqueID.compare(curr->GetID())){  //FRONT
//         delNode = curr;
//         head->SetNext(curr->GetNext()); 
//         curr->SetNext(nullptr); //
//         delete delNode;
//         if (head == nullptr){ //deleted last one in list
//             tail = nullptr;
//         }

//     }else{
//         while (curr!= tail){
//             if (uniqueID.compare(curr->GetNext()->GetID())){
                
//                 delNode = curr->GetNext();// delete this node
  
//                 if (delNode->GetNext() != nullptr){
//                     curr->SetNext(delNode->GetNext());
//                     delNode->SetNext(nullptr);
//                 }else{
//                     curr->SetNext(nullptr);
//                     tail = curr;
//                 }
//                 delete delNode;
//             }
//             curr = curr->GetNext(); 
//         }
//     }
// }

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
//     cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   

//     //"Canned Heat" moved to position 2

//     if (curr == nullptr){return;}
//     //FRONT
//     if (currPos == 1){

//     }

//     //MIDDLE

//     //END
// }


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
            curr->PrintPlaylistNode();
            counter++;
            curr = curr->GetNext();
        }
        cout << endl;
    }
}

void executeChoice(const char choice, PlayListNode* &head, PlayListNode* &tail, const string playlistTitle){
    if (choice == 'a'){
        addSong(head, tail);
    // }else if (choice == 'r'){
    //     removeSong(head, tail, askForID());
        
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

    //TEST
    // addSong(head, tail);
    // addSong(head, tail);
    // addSong(head, tail);

    // outputPlaylist(head, "h");
    // //removeSong(head, tail, askForID());
    // outputPlaylist(head, "h");

    string playlistTitle;
    string validChoices = "adcstoq";
    char choice;
    cout << "Enter playlist's title:" << endl;
    getline(cin, playlistTitle);
    printMenu(playlistTitle);
    cin >> choice;

    while (choice != 'q'){
        if (validateChoice(choice, validChoices)){
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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