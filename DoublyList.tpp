template <typename T>
DoublyList<T>::DoublyList()
: header(new Node), trailer(new Node) {
    header->next  = trailer;
    trailer->prev = header;
}

template <typename T>
DoublyList<T>::DoublyList(const DoublyList<T>& copyObj)
: header(new Node), trailer(new Node) {
    copy(copyObj);
}

template <typename T>
DoublyList<T>& DoublyList<T>::operator=(const DoublyList<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
DoublyList<T>::~DoublyList() {
    clear();
    delete header;
    delete trailer;
    header = trailer = nullptr;
}

template <typename T>
void DoublyList<T>::append(const T& elem) {
    Node* pred = trailer->prev;
    Node* succ = trailer;

    Node* n = new Node(elem, succ, pred);
    pred->next = n;
    succ->prev = n;

    ++this->length;
}

template <typename T>
void DoublyList<T>::clear() {
    for (Node* curr = nullptr; header->next != trailer; ) {
        curr = header->next->next;
        delete header->next;
        header->next = curr;
    }

    trailer->prev = header;
    this->length  = 0;
}

template <typename T>
void DoublyList<T>::copy(const DoublyList<T>& copyObj) {
    this->length   = copyObj.length;
    Node* myCurr   = header;
    Node* copyCurr = copyObj.header->next;

    while (copyCurr != copyObj.trailer) {
        Node* n      = new Node(copyCurr->value);
        myCurr->next = n;
        n->prev      = myCurr;
        myCurr       = n;
        copyCurr     = copyCurr->next;
    }

    myCurr->next  = trailer;
    trailer->prev = myCurr;
}

template <typename T>
T DoublyList<T>::getElement(int position) const {
    if (position < 0 || position >= this->length) {
        throw std::out_of_range("getElement: position out of range");
    }

    Node* curr;
    if (position < this->length / 2) {
        curr = header->next;
        for (int i = 0; i < position; ++i) {
            curr = curr->next;
        }
    } else {
        curr = trailer->prev;
        for (int i = this->length - 1; i > position; --i) {
            curr = curr->prev;
        }
    }

    return curr->value;
}

template <typename T>
int DoublyList<T>::getLength() const {
    return this->length;
}


template <typename T>
void DoublyList<T>::insert(int position, const T& elem) {
    if (position < 0 || position > this->length) {
        throw std::out_of_range("insert: position out of range");
    }

    Node* succ;
    if (position == this->length) {
        succ = trailer;
    } else if (position <= this->length / 2) {
        succ = header->next;
        for (int i = 0; i < position; ++i) succ = succ->next;
    } else {
        succ = trailer->prev;
        for (int i = this->length - 1; i >= position; --i) {
            if (i == position) break;
            succ = succ->prev;
        }
    }

    Node* pred = succ->prev;
    Node* n = new Node(elem, succ, pred);
    pred->next = n;
    succ->prev = n;

    ++this->length;
}

template <typename T>
bool DoublyList<T>::isEmpty() const {
    return this->length  == 0
        && header->next  == trailer
        && trailer->prev == header;
}

template <typename T>
void DoublyList<T>::remove(int position) {
    if (position < 0 || position >= this->length) {
        throw std::out_of_range("remove: position out of range");
    }

    Node* target;
    if (position < this->length / 2) {
        target = header->next;
        for (int i = 0; i < position; ++i) target = target->next;
    } else {
        target = trailer->prev;
        for (int i = this->length - 1; i > position; --i) target = target->prev;
    }

    Node* pred = target->prev;
    Node* succ = target->next;
    pred->next = succ;
    succ->prev = pred;

    delete target;
    --this->length;
}

template <typename T>
bool DoublyList<T>::search(const T& elem) const {
    for (Node* curr = header->next; curr != trailer; curr = curr->next) {
        if (curr->value == elem) return true;
    }
    return false;
}

template <typename T>
void DoublyList<T>::replace(int position, const T& elem) {
    if (position < 0 || position >= this->length) {
        throw std::out_of_range("replace: position out of range");
    }

    Node* curr;
    if (position < this->length / 2) {
        curr = header->next;
        for (int i = 0; i < position; ++i) curr = curr->next;
    } else {
        curr = trailer->prev;
        for (int i = this->length - 1; i > position; --i) curr = curr->prev;
    }
    curr->value = elem;
}

template <typename T>
ostream& operator<<(ostream& outStream, const DoublyList<T>& myObj) {
    if (myObj.isEmpty()) {
        outStream << "List is empty, no elements to display.\n";
    }
    else {
        typename DoublyList<T>::Node* curr = myObj.header->next;
        while (curr != myObj.trailer) {
            outStream << curr->value;
            if (curr->next != myObj.trailer) {
                outStream << " <--> ";
            }
            curr = curr->next;
        }
        outStream << endl;
    }

    return outStream;
}
