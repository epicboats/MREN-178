#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

void processRestock(int pid, int loc, int qty);
void processShip(int pid, int loc, int qty);
void processTransfer(int pid, int from, int to, int qty);

#endif