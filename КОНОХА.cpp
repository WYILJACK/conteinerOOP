#include <iostream>
#include <string>
#include<concepts>
#include"sh1nob1.h"
#include<typeinfo>

using namespace std;

template <typename T>
struct Node {
    T name;
    Node* next;

};
template <typename T>
class MyShinobiList {
public:

    struct Iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        Iterator(pointer ptr) : m_ptr(ptr) {}
        Iterator(const Iterator& other) : m_ptr(other.m_ptr) {}

        reference operator*() const { if (m_ptr != nullptr) return m_ptr->name->getName() + " " + m_ptr->name->getClan() + " " + m_ptr->name->getRang() + "\n"; }
        pointer operator->() { if (m_ptr != nullptr) return m_ptr->next; }
        Iterator& operator++() { if (m_ptr != nullptr) { m_ptr = m_ptr->next; } return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr->name == b.m_ptr->name; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr->name != b.m_ptr->name; };
         
    private:
        pointer m_ptr;
    };

    struct const_Iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = const T*;
        using reference = const T&;
        using const_reference = const value_type&;

        const_Iterator(pointer ptr) : m_ptr(ptr) {}
        const_Iterator(const const_Iterator& other) : m_ptr(other.m_ptr) {}

        const_reference operator*() const { if (m_ptr != nullptr) return m_ptr->name->getName() + " " + m_ptr->name->getClan() + " " + m_ptr->name->getRang() + "\n"; }
        const pointer operator->() { if (m_ptr != nullptr) return m_ptr->next; }
        const const_Iterator& operator++() { if (m_ptr != nullptr) { m_ptr = m_ptr->next; } return *this; }
        const const_Iterator operator++(int) { const_Iterator tmp = *this; ++(*this); return tmp; }
        friend bool operator== (const const_Iterator& a, const const_Iterator& b) { return a.m_ptr->name == b.m_ptr->name; };
        friend bool operator!= (const const_Iterator& a, const const_Iterator& b) { return a.m_ptr->name != b.m_ptr->name; };


    private:
        pointer m_ptr;
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
    const_Iterator cbegin() { return const_Iterator(head); }
    const_Iterator cend() { return const_Iterator(nullptr); }

    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using const_reference = const T&;
    using iterator = Iterator;
    using const_iterator = const Iterator;
    using size_type = int;

    
    MyShinobiList(){ 
        head = nullptr;
        size = 0; 
    }
    MyShinobiList(const MyShinobiList& other){ 
        head = other.head;
        size = other.size; 
    }
    MyShinobiList(MyShinobiList&& other) noexcept { 
        head = other.head;
        size = other.size;
        other.head = nullptr;
        other.size = 0;
    }

    ~MyShinobiList() {clear();}

    MyShinobiList& operator=(MyShinobiList& spis) {
       std::swap(this->head,spis.head );
       return *this;
    }
    MyShinobiList& operator=(MyShinobiList&& spis) noexcept{
        if (this != &spis) {
            this->~MyShinobiList();
            this->head = spis.head;
            this->size = spis.size;
            spis.head = nullptr;
            spis.size = 0;
        }
    }
    bool operator==(const MyShinobiList& spis) {
        auto tmp = this;
        if (this->size != spis.size) {
            return false;
        }
        else {
            int k = 0;
            Node<T>* cur1 = tmp->head;
            Node<T>* cur2 = spis.head;
            while (cur1 != nullptr) {
                if (cur1->name != cur2->name) {
                    k += 1;
                }
                cur1 = cur1->next;
                cur2 = cur2->next;
            }
            if (k > 0) return false;
            else return true;
        }
    }

    void swap(MyShinobiList& spis) {
        auto tmp = this;
        Node<T>* cur1 = tmp->head;
        Node<T>* cur2 = spis.head;
        while (cur1 != nullptr) {
            Shinobi* temp = cur1->name;
            cur1->name = cur2->name;
            cur2->name = temp;
            cur1 = cur1->next;
        }
    }
    bool isEmpty(MyShinobiList& spis) {
        if (spis.head == nullptr) {
            return true;
        }
        else return false;
    }
    size_type listSize(MyShinobiList& spis) {
        Node<T>* cur = spis.head;
        int size = 1;
        do {
            size += 1;
        } while (cur != nullptr);
    }
    void push(T infounit) {
        Node<T>* e = new Node<T>;
        e->name = infounit;
        e->next = nullptr;
        if (this->head == nullptr) {
            this->head = e;
            this->head->next = nullptr;
            this->size += 1;
        }
        else {
            Node<T>* cur = this->head;
            do {
                if (cur->next == nullptr) {
                    cur->next = e;
                    e->next = nullptr;
                    cur = cur->next;
                    this->size += 1;
                }
                else {
                    cur = cur->next;
                }

            } while (cur != nullptr);

        }
    }
    void pull(T info) {
        if (this->head == nullptr) {
            std::cout << "No elements\n";
        }
        else {
            if (this->head->name->getClan() == info->getClan() && this->head->name->getName() == info->getName() && this->head->name->getRang() == info->getRang()) {
                free(this->head);
                this->size = 0;
            }
            else {
                Node<T>* cur = this->head;
                do {
                    if (cur->name->getClan() == info->getClan() && cur->name->getName() == info->getName() && cur->name->getRang() == info->getRang()) {
                        Node<T>* tmp = cur->next;
                        cur->next = cur->next->next;
                        free(tmp);
                        this->size -= 1;
                    }
                    cur = cur->next;
                } while (cur != nullptr);
            }
        }
    }
    void print() {
        if (this->head == nullptr) {
            std::cout << "No elements1\n";
        }
        else {
            Node<T>* cur = this->head;
            do {
                cout << cur->name->getClan() << " " << cur->name->getName() << "   ";
                cur = cur->next;
            } while (cur != nullptr);

            printf("\b\b  \n");
        }
    }
    void find(T info) {
        if (this->head == nullptr) {
            std::cout << "No elements";
        }
        else {
            Node<T>* cur = this->head;
            do {
                if (cur->name->getClan() == info->getClan() && cur->name->getName() == info->getName() && cur->name->getRang() == info->getRang()) {
                    std::cout << cur << '\n';
                }
                cur = cur->next;
            } while (cur != nullptr);
        }
    }
    void clear() {
        if (this->head == nullptr) {
            std::cout << "";
        }
        else {
            while (this->head->next != nullptr) {
                Node<T>* cur = this->head;
                while (cur->next->next != nullptr) {
                    cur = cur->next;
                }
                delete cur->next;
                cur->next = nullptr;
            }
           this->size = 0;
           delete this->head;
           this->head = nullptr;
        }
    }
private:
    Node<T>* head;
    int size;
};
int main()
{
    jutsu_Style* fire = new fire_Jutsu();
    jutsu_Style* water = new water_Jutsu();
    jutsu_Style* wind = new wind_Jutsu();
    MyShinobiList list = MyShinobiList<Shinobi*>();
    Shinobi* unit = new Uchiha("Sasuke",fire);
	list.push(unit);
	Shinobi* unit2 = new  Hugo("Nedji", wind);
    list.push(unit2);
	Shinobi* unit3 = new Udzumaki("Naruto", wind);
    list.push(unit3);
	Shinobi* unit4 = new Uchiha("Shisui", fire);
    list.push(unit4);
	Shinobi* unit5 = new Hugo("Hinata", water);
    list.push(unit5);
    list.print();
    cout << unit3->getName() << " " << unit3->getClan() << " Technique: ";
    cout << "Rang: " << unit3->getRang() << endl;
    unit3->RootSpell();
    cout << "\n";
    cout << unit5->getName() << " " << unit5->getClan() << " Technique: ";
    unit5->RootSpell();
    cout << "Rang: " << unit5->getRang() << endl;
    unit5->operator+(unit3->getClan());
    cout << unit5->getName() << " " << unit5->getClan();
    cout << "\n";
    cout << "\n";
    teams* team7 = new teams(unit, unit2, unit3);
    //cout << team7;
    unit->jutsu();
    //unit2->UseByakugan(unit2->getEyes());
    /*list->~MyShinobiList();
    list->print();*/
    //MyShinobiList list2 = MyShinobiList();
    /*list2.operator=(list);
    list2.print();*/
    /*MyShinobiList list3(move(list));
    list3.print();*/
	
}

