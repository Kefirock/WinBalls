#include <iostream>

struct Node
{
    int value;
    Node* next;
};

struct List
{
    Node* head = 0;

    private:

        Node* addNewNode(int value)
        {
            Node* newNode = new Node;
            newNode -> value = value;
            newNode -> next = 0;
            return newNode;
        }

        int length()
        {
            int len = 0;
            Node* last = head;
            while (last)
            {
                last = last -> next;
                len = len + 1;
            }
            return len;
        }

    public:

        // Вставка в конец
        void pushBack(int value)
        {            
            Node* newNode = addNewNode(value);
            
            if(!head)
            {
                head = newNode;
                return;
             }
            Node* last = head;

            while (last -> next)
                last = last -> next;
            
            last -> next = newNode;
        }

        // Вставка в начало
        void pushFront(int value)
        {
            Node* newNode = addNewNode(value);

            if(!head)
            {
                head = newNode;
                return;
            }

            Node* First = newNode;
            First -> next = head;
            head = First;
        }

        // Вставка по индексу
        void insert(int index, int value)
        {
            Node* newNode = addNewNode(value);
            Node* indx = head;

            int len = length();

            if (index > 0 and index <= len)
            {
                for (int i = 0; i < index - 1; i++)
                {
                    indx = indx -> next;
                }          

                Node* nxt = indx -> next;
                Node* indexed = newNode;
                indx -> next = indexed;
                indexed -> next = nxt;
            }

            if (index == 0)
            {
                Node* indexed = newNode;
                indexed -> next = head;
                head = indexed;
            }

            else if (index > len)
            {
                std::cout << "WARNING: Index is out of range, index: " << index << ", value: " << value << std::endl;
            }
            
            else if (index < 0)
            {
                std::cout << "WARNING: Index < 0, index: " << index << ", value: " << value << std::endl;
            }
        }

        // Удаление по индексу
        void remove(int value)
        {
            Node* last = head;

            while (last)
            {      
                if (head == last and last -> value == value)
                {
                    head = head -> next;                   
                    delete last;
                    last = head;
                }

                if (last -> next != 0 and last -> next -> value == value)
                {
                    Node* prev = last;
                    last = last -> next;
                    Node* nxt = last -> next;

                    delete last;
                    
                    last = prev;
                    prev -> next = nxt;
                }

                last = last -> next;    
            }
            
            return;
        }

        // Длина списка
        int size()
        {
            int len = length();
            std::cout << "|SIZE: " << len << std::endl;
            return len;
        }

        // Очистка списка
        void clear()
        {
            Node* last = head;
            while(last)
            {
                Node* prev = last;
                last = last -> next;
                delete prev;
            }
            head = 0;
            
            return;
        }

        // Вывод списка
        void printAll()
        {
            std::cout << "\nList:" << std::endl;
            if (head)
            {
                std::cout << "|HEAD: " << head->value << ", " << head << std::endl;
                Node* last = head;

                while (last and last->next != 0)
                {
                    last = last -> next;
                    std::cout << "VALUE: " << last->value << ", " << last << std::endl;
                }
            }  
        }

        // Вытащить начало
        int popFront()
        {
            std::cout << "FRONT: " << head -> value << std::endl;
            return head -> value;
        }

        // Вытащить концовку
        int popBack()
        {
            Node* last = head;
            while(last)
            {
                last = last -> next;
                if (last -> next == 0)
                {
                    std::cout << " BACK: " << last -> value << std::endl;
                    return last -> value;
                }
            } 
            return 0;
        }

        // Элемент списка
        int& operator[](int index)
        {
            std::cout << "INDEX : " << index << std::endl;
            Node* indx = head;
            Node* prev;
            int len = length();

            if (index >= 0 and index < len)
            {
                for (int i = 0; i < index; i++)
                {
                    std::cout << "INDX: " << indx -> value << std::endl;
                    
                    if (index > 1)
                    {
                        indx = indx -> next;
                    }
                }
                std::cout << "[Value]: " << indx -> value << std::endl;
                return indx -> value;  
            }


            else if (index >= len)
            {
                std::cout << "WARNING: Index is out of range, index: " << index << std::endl;
            }
            
            else if (index < 0)
            {
                std::cout << "WARNING: Index < 0, index: " << index << std::endl;
            }
        }
};

int main()
{
    List MyList;

    MyList.pushFront(1);
    MyList.pushBack(12);
    MyList.pushBack(21);
    MyList.pushFront(2);
    MyList.pushBack(5);
    MyList.insert(0, 55);
    MyList.insert(-5, 13);
    MyList.insert(8, 55);
    MyList.printAll();
    MyList.size();

    MyList.popBack();
    MyList.popFront();
    
    MyList.clear();
    MyList.printAll();
    MyList.size();

    MyList.pushBack(1);
    MyList.pushFront(1);
    MyList.insert(1, 2);
    MyList.printAll();
    MyList.size();

    MyList.remove(1);
    MyList.printAll();
    MyList.size();
    MyList[-1];
    std::cout << MyList[0] << std::endl;
    MyList[0];
    MyList[2];
    MyList[0] = 55;
    MyList[0];

    return 0;
}