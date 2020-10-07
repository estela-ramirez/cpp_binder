else if (uniqueID.compare(curr->GetID())){  //FRONT
//         delNode = curr;
//         head->SetNext(curr->GetNext()); 
//         curr->SetNext(nullptr); //
//         cout << delNode->GetSongName() << " removed" << endl;
//         delete delNode;
//         if (head == nullptr){ //deleted last one in list
//             tail = nullptr;
//         }

//     }else{
//         while (curr!= tail){
//             if (uniqueID.compare(curr->GetNext()->GetID())){
                
//                 delNode = curr->GetNext();
  
//                 if (delNode->GetNext() != nullptr){
//                     curr = delNode->GetNext();
//                     curr->SetNext(curr);  //??? why can't I put delNode->GetNext() directly
//                     delNode->SetNext(nullptr);
//                 }else{
//                     curr->SetNext(nullptr);
//                     tail = curr;
//                 }
//                 cout << delNode->GetSongName() << " removed" << endl;
//                 delete delNode;
//             }
//             curr = curr->GetNext(); 
//         }
//     }
// }