Personal work done for Western Cyber Society's Cryptography Project. To be showcased at the 2024 Toronto Tech Expo.

Includes:
  1. A simple block chain
Takes in a message and a key, encrypting a portion of equal size to the key. Then XORs another portion of the remaining message with the encrypted text and that passes down along with the same key to a new block. This process repeats until the message has been fully encrypted

  2. A pseudo random number generator
generates a key of n length using the linear congruence method, with the current time since epoch as the seed
