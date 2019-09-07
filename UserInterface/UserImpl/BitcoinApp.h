/*Declaration of the functions used by the UX source file*/
void Initialize(void); //initialize the hashes for bitcoin-trees,user wallets and form-to users transactions
void CreateUser(char* UserID); //Create an empty wallet and add it to the wallet hash
void CreateBitcoin(char* BitcoinID,char* UserID,int Amount); //Create an empty BitcoinTree and then add it to the Bitcoin Trees hash
Boolean Transfer(char * fromUserID, char* toUserID, int Amount);//Creates a transaction struct and returns it accordingly to the given data(return True is the transaction is succesful,else return false)
int GetUserAmount(char* UserID);//return the current amount of money of the given UserId
void PrintSent(char* UserID);//Print all the transactions that the "UserID" is the sender with the sent amount for each such transaction
void PrintReceived(char* UserID);//Same as above so that
void PrintBitcoinOwners(char* BitcoinID); //Prints all the non-zero-amount owners of the given bitcoin
void PrintBitcoinHistory(char* BitcoinID);//Prints all the internal nodes of the tree that represent the change of hands in the bitcoin's parts
void Terminate(void); //Frees all the memory