

enum replacementPolicy {
    FIFO,
    LRU

};

enum writeHitPolicy {
    WRITEBACK,
    WRITETHROUGH
};

enum writeMissPolicy { 
    WRITEALLOCATE,
    NOWRITEALLOCATE
};

enum accessType {
    READ,
    WRITE
};

template<typename T>
class Block {

    // Block size (in Bytes)
    int _size;
    // Valid bit
    bool _valid;
    // Dirty bit (for write-back)
    bool _dirty;
    unsigned long _tag;
    bool _spaceAllocated;
    T * _data;

    public:
    Block() {};
    Block(T *&);
    Block(int);
    void allocateSpace();
    int getSize();
    void setSize(int);
    bool getValid();
    void setValid(bool); 
    bool getDirty();
    void setDirty(bool);
    void setTag(unsigned long);
    void getTag();
    T operator [](int) const;
    T& operator [](int);
    ~Block();        

};

template<typename T>
class Set {
    int _associativity;    
    Block<T> * _ways;
    bool _waysAllocated; 

    public:
    Set(int, int);
    Set() {};
    void setAssociativity(int);
    void allocateBlocks(int); 
    Block<T> & operator[](int);
    void insertBlock(T *&);
    int findBlock(unsigned long);
    ~Set();

};

template<typename T>
class Cache {
    
    // Cache size in KB
    size_t _size;
    int _associativity;

    // Cache block size in Bytes
    int _blockSize;
    size_t _numSets;

    enum replacementPolicy _replacementPolicy;
    enum writeHitPolicy _writeHitPolicy;
    enum writeMissPolicy _writeMissPolicy;

    Set<T> * _sets;

    public:
    Cache(size_t, int, int, replacementPolicy=FIFO, writeHitPolicy=WRITEBACK, writeMissPolicy=WRITEALLOCATE);
    Set<T> & operator[](int);
    //~Cache();
    
};

#include "cache_impl.h"
