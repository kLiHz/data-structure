struct item
{
    char * _where;
    int size;
};

class pool {
    char * content_head;
    char * tail;
    int size;
public:
    pool(int _size) {
        content_head = new char[size];
        tail = content_head;
        size = _size;
    };
    ~pool() { delete content_head; } ;
    int size();
    int space();
    char * locate(int offset);
};

class table {
    pool * pools;
    item * items;
    int size;
public:
    void insert();
};
