#define TABLE_SIZE 100003
#define MAX_NAME 50

#define MAX_PRODUCTS 100000
#define MAX_LOCATIONS 1000

extern int productExists[MAX_PRODUCTS];
extern int locationExists[MAX_LOCATIONS];

void createProductType(int pid, char* name, int max_capacity);
void createLocation(int loc);
void stockProduct(int pid, int loc, int qty, int max_capacity, char* name);

typedef struct Product {
    int product_id;
    int location_id;
    char name[MAX_NAME];
    int quantity;
    int max_capacity;
    struct Product* next;
} Product;

extern Product* hashTable[TABLE_SIZE];

void insertProduct(int pid, char* name, int loc, int qty, int max);
Product* findProduct(int pid, int loc);
void printInventory();
