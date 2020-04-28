// write the generic functions for insert and search

template <class T>
class Node
{
    T data; // generic data
    int index; // index of data stored in "conceptual array"
    Node *right; // ptr to the next class object
    Node *left; // ptr to the prev class object
}

class Header
{
    int size; // current size of DLL
    Node *header; // pointer to the first obj of Node class
    Node *tail; // pointer to the last obj of Node class
    Header()
    {
        tail = NULL;
        header = NULL;
        size = 0;
    }
}

// creates new obj of class Node and initialises it
template <typename T>
Node* createNew(T ele, int index)
{
    Node *obj;
    obj->data = ele;
    obj->index = index;
    obj->left = NULL;
    obj->right = NULL;

    return obj;
}

// insert : takes the ele to be inserted. 
// adds to DLL
template <typename T>
void insert(T ele, int index, Header *hobj)
{
    // create a new object of class Node 
    Node *temp = createNew(ele, index); // returns ptr to struct node
    if(hobj->size == 0)
    {
        hobj->header = temp;
    }
    // insert at the end 
    temp->right = NULL;
    temp->left = tail;
    tail = temp;
    // update size of DLL
    ++(hobj->size);
}

// search for an element and returns it
// searching from end as most recently element is more likely to be searched
// thereby increaseing speed
template <typename T>
T search(Node *hobj, T ele)
{
    Node *it = hobj->tail;
    while(it != NULL)
    {
        if(it->data == ele)
        {
            return it->data;
        }
        else
        {
            it = it->left;
        }
    }
    return nullptr; // not found 
}

template<typename