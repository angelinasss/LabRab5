#include <iostream>
#include <memory>

using std::shared_ptr;

template <typename T>
class queue {
    struct Node {
        T data;
        shared_ptr<Node> next;
        shared_ptr<Node> prev;
        Node(T data = T(), shared_ptr<Node> next = nullptr, shared_ptr<Node> prev = nullptr)
        {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
        ~Node() = default;
    };
    shared_ptr<Node> head;
    shared_ptr<Node> tail;
    size_t _size;
public:
    queue(const queue& other);
    queue(queue&& other) noexcept;
    queue();
    ~queue();
    void push(const T& data);
    void pop();
    bool empty();
    size_t size() const;
    T& front();
    T& back();
    queue& operator=(const queue& other);
    queue& operator=(queue&& other) noexcept;
    bool operator!=(const queue& right);
    bool operator==(const queue& right);
    bool operator>(const queue& right);
    bool operator<(const queue& right);
    bool operator>=(const queue& right);
    bool operator<=(const queue& right);
    void swap(queue& other);
    void clear();
    template <typename... Args>
    void emplace(Args &&...args);
};

template<class T>
queue<T>::queue(const queue& other)
{
    ~queue();
    _size = other._size;
    shared_ptr<Node> temp = other.head;
    while (temp)
    {
        push(temp->data);
        temp = temp->next;
    }
}

template <class T> queue<T>::queue() {
    head = std::make_shared<Node>();
    tail = head;
    _size = 0;
}

template<class T>
queue<T>::queue(queue&& other) noexcept
{
    _size = other._size;
    head = other.head;
    tail = other.tail;
    other.head = nullptr;
    other.tail = nullptr;
    other._size = 0;
}

template<class T>
queue<T>::~queue()
{
    while (head)
    {
        std::shared_ptr<Node> current = this->head;
        head = current->next;
        current.reset();
        _size--;
    }
}

template <typename T>
size_t queue<T>::size() const{
    return _size;
}

template <typename T>
bool queue<T>::empty() {
    return _size == 0;
}

template <typename T>
void queue<T>::push(const T& data) {
    shared_ptr<Node> temp = std::make_shared<Node>(data);

    if (_size != 0)
    {
        temp->data = data;
        temp->prev = head;
        tail->next = temp;
        tail = temp;
    }
    else
    {
        tail = head = temp;
    }
    _size++;
}

template <typename T>
void queue<T>::pop() {
    if (head == tail)
    {
        head.reset();
        head = tail = NULL;
    }
    else
    {
    shared_ptr<Node> ptr = head;
    head = head->next;
    ptr.reset();
    }
    _size--;
}


template <typename T>
void queue<T>::swap(queue<T>& other) {
    auto tmp = head;
    head = other.head;
    other.head = tmp;
    auto tmp1 = tail;
    tail = other.tail;
    other.tail = tmp1;
    size_t tmpSize = _size;
    _size = other._size;
    other._size = tmpSize;
}

template <typename T>
template <typename... Args>
void queue<T>::emplace(Args &&...args) {
    push(T(args...));
}

template <typename T>
T& queue<T>::front() {
    return head->data;
}

template <typename T>
T& queue<T>::back() {
    return tail->data;
}

template <typename T>
queue<T>& queue<T>::operator=(const queue& other)
{
    ~queue();
    shared_ptr<Node> temp = other.head;
    while (temp)
    {
        push(temp->data);
        head = head->next;
    }
    return *this;
}

template <typename T>
queue<T>& queue<T>::operator=(queue&& other) noexcept {
    _size = other._size;
    head = other.head;
    tail = other.tail;
    other.head = nullptr;
    other.tail = nullptr;
    other._size = 0;
    return *this;
}

template <typename T>
bool queue<T>::operator!=(const queue& right) {
    return !(this == right);

}

template <typename T>
bool queue<T>::operator==(const queue& right) {
    shared_ptr<Node> current = right.head;
    shared_ptr<Node> current1 = this->head;
    if (this->size() < right.size()) return false;
    else if (this->size() > right.size()) return false;
    else {
        for (int i = 0; i < right.size(); i++) {
            if (current1->data != current->data) return false;
            current = current->next;
            current1 = current1->next;
        }
        return true;
    }
}

template <typename T>
bool queue<T>::operator>(const queue& right) {
    bool check = true;
    shared_ptr<Node> current = right.head;
    shared_ptr<Node> current1 = this->head;
    if (this->size() > right.size()) return check;
    else if (this->size() < right.size()) return false;
    else if (this->size() == right.size()) {
        int check = 0;
        for (int i = 0; i < right.size(); i++) {
            if (current1->data != current->data) check++;
            current = current->next;
            current1 = current1->next;
        }
        if (check == 0) return false;
        else {
            current = right.head;
            current1 = this->head;
            for (int i = 0; i < right.size(); i++) {
                if (current1->data < current->data) return false;
                current = current->next;
                current1 = current1->next;
            }
            return true;
        }
    }
}

template <typename T>
bool queue<T>::operator<(const queue& right) {
    bool check = true;
    shared_ptr<Node> current = right.head;
    shared_ptr<Node> current1 = this->head;
    if (this->size() < right.size()) return check;
    else if (this->size() > right.size()) return false;
    else if (this->size() == right.size()) {
        int check = 0;
        for (int i = 0; i < right.size(); i++) {
            if (current1->data != current->data) check++;
            current = current->next;
            current1 = current1->next;
        }
        if (check == 0) return false;
        else {
            current = right.head;
            current1 = this->head;
            for (int i = 0; i < right.size(); i++) {
                if (current1->data > current->data) return false;
                current = current->next;
                current1 = current1->next;
            }
            return true;
        }
    }
}

template <typename T>
bool queue<T>::operator>=(const queue& right) {
    return (this > right || this == right);
}

template <typename T>
bool queue<T>::operator<=(const queue& right) {
    return (this < right || this == right);
}

template <typename T>
void queue<T>::clear() {
    while (head)
    {
        std::shared_ptr<Node> current = this->head;
        head = current->next;
        current.reset();
        _size--;
    }
}
