//simple block chain and linear congruence method number generation program

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <chrono>
#include <string.h>

#include "RNG.h"

class Block {
private:
    std::vector<unsigned char> cText; 
    Block* next;
    int n;

public:
    Block(std::string message, unsigned char* key) {

        n = message.length();
        int keySize = strlen((char*)key);
        cText.reserve(n);

        //pads the original message to a multiple of the key size
        if(n%keySize != 0)
            for(int i = 0; i < keySize - n%keySize; i++)
                message += ' ';

        n = message.length();

        //assigns current block with text 
        for(int i = 0; i < keySize; i++)
            cText.push_back(message[i]);

        message = message.substr(keySize, n-keySize);

        //pad out next block if needed
        if(n < keySize*2) 
            for(int i = keySize; i < n; i++) 
                message += ' ';

        //XORs key with current block's message
        for(int i = 0; i < keySize; i++)
            cText[i] = cText[i] ^ key[i];

        if(n > keySize) {

            //XORs next block of text with current cText
            int bound = std::min(keySize, (int)message.length());
            for(int i = 0; i < keySize; i++)
                message[i] = ((message[i]) ^ (cText[i]));

            next = new Block(message, key);

        } else 
            next = nullptr;

    }

    //returns a string with any ascii character
    std::string getCText() {
        std::string out;
        int bounds = cText.size();
        for(int i = 0; i < bounds; i++) 
            out += cText[i];

        if(!next) return out;
        return out + next->getCText();
    }

    std::string decode(unsigned char* key) {
        std::string out, nextBlock;
        int bounds = cText.size();

        for(int i = 0; i < bounds; i++)
            out += (key[i] ^ cText[i]);

        //undos the cText ^ message component of the cipher process
        if(next) {
            nextBlock = next->decode(key);
            int tempSize = nextBlock.length();
            bounds = std::min(tempSize, bounds);
            for(int i = 0; i < bounds; i++)
                nextBlock[i] = nextBlock[i] ^ cText[i];
        }
        
        if(!next) return out;
        return out + nextBlock;
    }
};

int main() {
    int n = 10;
    unsigned char* key = randomNumGen(n);

    Block firstBlock("Testing out the blockchain", key);
    Block secondBlock("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\nUt enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\nDuis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.\nExcepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum", key);
    
    std::cout << firstBlock.getCText() << std::endl << std::endl;
    std::cout << secondBlock.getCText() << std::endl << std::endl << std::endl;

    std::cout << firstBlock.decode(key) << std::endl << std::endl;
    std::cout << secondBlock.decode(key) << std::endl;

    //TODO: add CLI functionality
    //TODOL use hashing instead of pointers
    //TODO: attack key gen
        //brute force
        // reverse the linear congruence method

    return 0;
}
