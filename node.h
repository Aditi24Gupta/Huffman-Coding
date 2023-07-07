class binarytree{
    public:
    char data;
    int freq;
    binarytree* left;
    binarytree* right;

    binarytree(char data,int freq){
        this->data=data;
        this->freq=freq;
        this->left=NULL;
        this->right=NULL;
    }
};

class compare{
    public:
    bool operator()(binarytree* left, binarytree* right)
 
    {
        return (left->freq > right->freq);
    }
};

