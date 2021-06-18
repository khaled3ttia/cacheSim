template<typename T>
Block<T>::Block(T*& src){
    int numElems = _size / sizeof(T);
    if (!_spaceAllocated){
        _data = new T[numElems];
        _spaceAllocated = true;
    }
    for (int i = 0 ; i < numElems; i++){
        _data[i] = src[i];
    }
}

template<typename T>
void Block<T>::allocateSpace(){
    _data = new T[_size / sizeof(T)];
    _spaceAllocated = true;

}

template<typename T>
void Block<T>::setSize(int val){
    _size = val;
}

template<typename T>
int Block<T>::getSize(){
    return _size;
}

template<typename T>
void Block<T>::setDirty(bool val){
    _dirty = val;

}

template<typename T>
bool Block<T>::getDirty(){
    return _dirty;
}

template<typename T>
void Block<T>::setValid(bool val){
    _valid = val;
}

template<typename T>
bool Block<T>::getValid(){
    return _valid;
}

template<typename T>
T Block<T>::operator [] (int index) const{

    assert(index < _size/sizeof(T));
    return _data[index]; 

}

template<typename T>
T& Block<T>::operator [] (int index){
    assert(index < _size/sizeof(T));
    return _data[index]; 

}

template<typename T>
Block<T>::~Block(){
    /*
    if (_spaceAllocated){

        delete [] _data;
    }

    */
}

template<typename T>
void Set<T>::setAssociativity(int associativity){
    _associativity = associativity;
}

template<typename T>
void Set<T>::allocateBlocks(int blockSize){
    _ways = new Block<T>[_associativity];
    _waysAllocated = true; 
    for (int i = 0 ; i < _associativity; i++){
        _ways[i].setSize(blockSize);

    }

}

template<typename T>
Block<T>& Set<T>::operator [](int blockIndex){
    assert(blockIndex < _associativity);
    return _ways[blockIndex];
}

template<typename T>
void Set<T>::insertBlock(T *& src){
    bool blockInserted = false;
    if (_waysAllocated){
        for (int i = 0; i < _associativity; i++){
            if (!_ways[i].getValid()){
                _ways[i] = Block<T>(src);
                _ways[i].setValid(true);
                blockInserted = true;
                //TODO set the tag
                //_ways[i].setTag();
                break;
            }
        }
    }

    if (!blockInserted){

        //TODO Need to replace one of the blocks in the set
        std::cout << "Couldn't insert block :( " << std::endl;
    }
}

template<typename T>
int  Set<T>::findBlock(unsigned long tag){
    
    for (int i = 0 ; i < _associativity; i++){
        
        if (_ways[i].getValid()){
            
            if (_ways[i].getTag() == tag){
                
                return i;
            
            }

        }

    }
    return -1;

}

template<typename T>
Set<T>::~Set(){
    if (_waysAllocated) {
        delete [] _ways;
    }
}

template<typename T>
Cache<T>::Cache(size_t size, int associativity, int blockSize, replacementPolicy repPolicy, writeHitPolicy writeHPolicy, writeMissPolicy writeMPolicy): _size(size), _associativity(associativity), _blockSize(blockSize), _replacementPolicy(repPolicy), _writeMissPolicy(writeMPolicy){

    std::cout << "Size is : " << size  << " KB" << std::endl;
    std::cout << "Assoc is : " << associativity << std::endl;
    _numSets = _size * 1024/ _blockSize / _associativity;

    std::cout << "Block size is : " << blockSize << std::endl;
    
    std::cout << "Number of sets is : " << _numSets << std::endl;

    _sets = new Set<T>[_numSets];
    for (int i = 0 ; i < _numSets; i++){
        _sets[i].setAssociativity(_associativity);
        _sets[i].allocateBlocks(_blockSize);
    }
}


template<typename T>
Set<T>& Cache<T>::operator [](int setIndex){

    assert(setIndex < _associativity);

    return _sets[setIndex];
}
