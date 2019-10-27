// Cameron Kwan
// V00910702
// Last Edit Fri Sept. 20 2019
// Vigenere Cipher:
// Input: Alphabet, Message, Key
// Output: Alphabet, Message, Key, Encryption, Decryption


#include <iostream>
#include <string>

//Compare Key to Alphabet and return numeric key Val
int NumKey(std::string Key, std::string alpha, int i){
    int index{0};
    for(unsigned int j = 0; j < alpha.size(); j++){
                    
        if(Key.at(i) == alpha.at(j)){
            index = j;
        }
    }
    return index;
}




int main(){
    std::string alpha{};
    std::string Key{};
    std::string msg{};
    std::string Encrypt{};
    std::string Decrypt{};


    std::getline(std::cin, alpha);
    std::getline(std::cin, msg);
    std::getline(std::cin, Key);

    std::string OKey{Key};
    

    while(Key.size() <= msg.size()){
        Key += Key;
    }

    for(unsigned int i = 0; i < msg.size(); i++){
        //cycle through msg chars
        for(unsigned int j = 0; j < alpha.size(); j++){
            //cycle through alphabet chars
            if(msg.at(i) == alpha.at(j)){
                //compare to msg chars
                // Encrypt += alpha.at(j + NumKey(Key, alpha, i));
                if((j + NumKey(Key, alpha, i)) < alpha.size()){
                    //Encryption
                    Encrypt += alpha.at(j + NumKey(Key, alpha, i));
                } else {
                    Encrypt += alpha.at(j + NumKey(Key, alpha, i) - alpha.size());
                }
                int k = j;
                if(( k - NumKey(Key, alpha, i)) >= 0){
                    //Decryption
                    Decrypt += alpha.at(k - NumKey(Key, alpha, i));
                } else {
                    Decrypt += alpha.at(k - NumKey(Key, alpha, i) + alpha.size());
                }

            }
        }

    }

    std::cout << "Alphabet: ["<< alpha << "]" << std::endl;
    std::cout << "Message: ["<< msg << "]" << std::endl;
    std::cout << "Key: ["<< OKey << "]" << std::endl;
    std::cout << "Encrypted: ["<< Encrypt << "]" << std::endl;
    std::cout << "Decrypted: ["<< Decrypt << "]" << std::endl;

    return 0;
}