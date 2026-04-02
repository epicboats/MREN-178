void processRestock(int pid, int loc, int qty);
void processShip(int pid, int loc, int qty);
void processTransfer(int pid, int from, int to, int qty);
void logTransaction(const char* entry);
void saveTransactionLog(const char* filename);
