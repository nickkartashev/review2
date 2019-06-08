#include<vector>
#include<iostream>
#include<stdlib.h>
#include<set>
#include<time.h>
template<class ValueType>
class Node
{
public:
    ValueType key;
    int l=0;
    int r=0;
    int p=0;
    int rl = 0;
    int h = 0;
    Node()
    {
        l = 0;
        r = 0;
        p = 0;
        h = 0;
        rl = 0;
    }
};

template<class ValueType>
class Set
{
public:
    std::vector<Node<ValueType>> tree;
    size_t sz = 0;
    int root = 0;
    Set()
    {
        this->tree.resize(1);
    }
    Set(std::initializer_list<ValueType> stin)
    {
        this->tree.resize(1);
        for (auto it = stin.begin(); it != stin.end(); it++)
        {
            this->insert(*it);
        }
    }
    Set(Set & news)
    {
        this->tree.resize(1);
        this->tree = news.tree;
        sz = news.sz;
        this->root = news.root;
    }
    template<class InputIter>
    Set(InputIter start, InputIter finish)
    {
        this->tree.resize(1);
        for (InputIter i = start; i != finish; i++)
        {
            this->insert(*i);
        }
    }
    ~Set()
    {
        this->tree.clear();
        sz = 0;
        this->root = 0;
    }
    const int diff(int ind)
    {
        if (ind == 0)
        {
            return 0;
        }
        if (this->tree[ind].r == 0 && this->tree[this->tree[ind].r].h != 0)
        {
            this->tree[this->tree[ind].r].h = 0;
            //std::cout << "WHATTJOITIOGHOIRHHGOGOGHHIOR" <<  std::endl;
        }
        if (this->tree[ind].l == 0 && this->tree[this->tree[ind].l].h != 0)
        {
            this->tree[this->tree[ind].l].h = 0;
            //std::cout << "WHATTJOITIOGHOIRHHGOGOGHHIOR" <<  std::endl;
        }
        //std::cout << "HIGH " << this->tree[this->tree[ind].l].h - this->tree[this->tree[ind].r].h << " " << ind << " " << this->tree[this->tree[ind].l].h << " " << this->tree[this->tree[ind].r].h << std::endl;
        return this->tree[this->tree[ind].l].h - this->tree[this->tree[ind].r].h;
    }
    const size_t size() const
    {
        return sz;
    }
    const bool empty() const
    {
        return (sz == 0);
    }
    void updh(int ind)
    {
        if (ind == 0)
        {
            this->tree[ind].h = 0;
            return;
        }
        this->tree[ind].h = (this->tree[this->tree[ind].l].h < this->tree[this->tree[ind].r].h ? this->tree[this->tree[ind].r].h : this->tree[this->tree[ind].l].h) + 1;
    }
    void rotl(int ind)
    {
        int tind = this->tree[ind].r;
        if (tind == 0 || ind == 0)
        {
            return;
        }
        if (ind == this->root)
        {
            this->root = tind;
        }
        this->tree[ind].r = this->tree[tind].l;
        if (this->tree[tind].l != 0)
        {
            this->tree[this->tree[tind].l].rl = 1;
            this->tree[this->tree[tind].l].p = ind;
        }
        this->tree[tind].l = ind;
        this->tree[tind].p = this->tree[ind].p;
        this->tree[tind].rl = this->tree[ind].rl;
        this->tree[ind].rl = -1;
        this->tree[ind].p = tind;
        if (this->tree[tind].rl == -1 && this->tree[tind].p != 0)
        {
            this->tree[this->tree[tind].p].l = tind;
        }
        else if (this->tree[tind].rl == 1 && this->tree[tind].p != 0)
        {
            this->tree[this->tree[tind].p].r = tind;
        }
        this->updh(ind);
        this->updh(tind);
    }
    void rotr(int ind)
    {
        int tind = this->tree[ind].l;
        if (tind == 0 || ind == 0)
        {
            return;
        }
        if (ind == this->root)
        {
            this->root = tind;
        }
        this->tree[ind].l = this->tree[tind].r;
        if (this->tree[tind].r != 0)
        {
            this->tree[this->tree[tind].r].rl = -1;
            this->tree[this->tree[tind].r].p = ind;
        }
        this->tree[tind].r = ind;
        this->tree[tind].p = this->tree[ind].p;
        this->tree[tind].rl = this->tree[ind].rl;
        this->tree[ind].rl = 1;
        this->tree[ind].p = tind;
        if (this->tree[tind].rl == -1 && this->tree[tind].p)
        {
            this->tree[this->tree[tind].p].l = tind;
        }
        else if (this->tree[tind].rl == 1 && this->tree[tind].p)
        {
            this->tree[this->tree[tind].p].r = tind;
        }
        this->updh(ind);
        this->updh(tind);
        //std::cout << this->tree[tind].r << std::endl;
    }
    void brotl(int ind)
    {
        rotr(this->tree[ind].r);
        rotl(ind);
    }
    void brotr(int ind)
    {
        rotl(this->tree[ind].l);
        rotr(ind);
    }
    void backway(int ind)
    {
        //std::cout << ind << "IND" << std::endl;
        if (ind == 0)
        {
            return;
        }
        //int tmp = this->tree[ind].h;
        updh(ind);
        //if (tmp.h != )
        if (this->diff(ind) == 0)
        {
            //this->backway(this->tree[ind].p);
            return;
        }
        if (abs(this->diff(ind)) == 1)
        {
            //if (this->tree[ind].h != tmp)
            //{
                this->backway(this->tree[ind].p);
            //}
            return;
        }
        if (this->diff(ind) <= -2)
        {
            //std::cout << "BAL1" << this->tree[ind].key << std::endl;
            if (this->diff(this->tree[ind].r) < 1)
            {
                this->rotl(ind);
            }
            else
            {
                this->brotl(ind);
            }
            //if (this->tree[ind].h != tmp)
            //{
                this->backway(this->tree[ind].p);
            //}
            return;
        }
        if (this->diff(ind) >= 2)
        {
            //std::cout << "BAL2" << this->tree[ind].key << std::endl;
            if (this->diff(this->tree[ind].l) > -1)
            {
                //std::cout << "THIS" << std::endl;
                this->rotr(ind);
            }
            else
            {
                this->brotr(ind);
            }
            //if (this->tree[ind].h != tmp)
            //{
                this->backway(this->tree[ind].p);
            //}
            return;
        }
        //if (this->tree[ind].h != tmp)
        //{
            this->backway(this->tree[ind].p);
        //}
    }
    void insert(ValueType newk)
    {
        if (this->find(newk) != this->end())
        {
            return;
        }
        sz++;
        if (this->root == 0)
        {
            this->tree.resize(2);
            this->tree[1].key = newk;
            this->tree[1].h = 1;
            this->tree[1].p = 0;
            this->tree[1].l = 0;
            this->tree[1].r = 0;
            this->tree[1].rl = 0;
            this->root = 1;
            return;
        }
        int tmv = this->root;
        while (true)
        {
            if (newk < this->tree[tmv].key)
            {
                if (this->tree[tmv].l == 0)
                {

                    this->tree[tmv].l = this->tree.size();
                    this->tree.push_back(Node<ValueType>());
                    this->tree[this->tree.size() - 1].p = tmv;
                    this->tree[this->tree.size() - 1].key = newk;
                    this->tree[this->tree.size() - 1].rl = -1;
                    this->tree[this->tree.size() - 1].h = 1;
                    this->tree[this->tree.size() - 1].l = 0;
                    this->tree[this->tree.size() - 1].r = 0;
                    this->backway(tmv);
                    return;
                }
                else
                {
                    tmv = this->tree[tmv].l;
                }
            }
            if (this->tree[tmv].key < newk)
            {
                if (this->tree[tmv].r == 0)
                {
                    this->tree[tmv].r = this->tree.size();
                    this->tree.push_back(Node<ValueType>());
                    this->tree[this->tree.size() - 1].p = tmv;
                    this->tree[this->tree.size() - 1].key = newk;
                    this->tree[this->tree.size() - 1].rl = 1;
                    this->tree[this->tree.size() - 1].h = 1;
                    this->tree[this->tree.size() - 1].l = 0;
                    this->tree[this->tree.size() - 1].r = 0;
                    this -> backway(tmv);
                    return;
                }
                else
                {
                    tmv = this->tree[tmv].r;
                }
            }
        }
    }
    void erase(ValueType newk)
    {
        //std::cout << "AAAAA1" << std::endl;
        if (this->find(newk) == this->end())
        {
            return;
        }
        sz--;
        int tmv = this->root;
        while (true)
        {
            if (newk < this->tree[tmv].key)
            {
                tmv = this->tree[tmv].l;
            }
            else if (this->tree[tmv].key < newk)
            {
                tmv = this->tree[tmv].r;
            }
            else
            {
                break;
            }
        }
        //std::cout << tree[tmv].key << " " << tree[tmv].r << " " << tmv << " " << tree[tree[tmv].r].l << std::endl;
        if (this->tree[tmv].r != 0)
        {
            int ttmv = this->tree[tmv].r;
            while (this->tree[ttmv].l != 0)
            {
                ttmv = this->tree[ttmv].l;
            }
            ValueType tmtm = this->tree[ttmv].key;
            sz++;
            this->erase(this->tree[ttmv].key);
            this->tree[tmv].key = tmtm;
            this->updh(tmv);
            this->backway(tmv);
            return;
        }
        if (this->tree[tmv].p == 0)
        {
            this->root = this->tree[tmv].l;
            this->tree[this->root].p = 0;
            this->tree[this->root].rl = 0;
            this->tree[this->tree[tmv].l].p = 0;
            return;
        }
        if (this->tree[tmv].rl == -1)
            this->tree[this->tree[tmv].p].l = this->tree[tmv].l;
        if (this->tree[tmv].rl == 1)
            this->tree[this->tree[tmv].p].r = this->tree[tmv].l;
        if (tree[tmv].l == 0)
        {
            updh(this->tree[tmv].p);
            this->backway(this->tree[tmv].p);
            return;
        }
        this->tree[this->tree[tmv].l].p = this->tree[tmv].p;
        this->tree[this->tree[tmv].l].rl = this->tree[tmv].rl;

        int tmpm = tree[tmv].l;
        this->backway(tmpm);
    }
    class iterator
    {
    public:
        int ind = 0;
        const Set* myt;
        iterator ()
        {

        }
        iterator (int in, const Set* my)
        {
            ind=in;
            myt = my;
        }
        iterator operator++()
        {
            if (myt->tree[ind].r == 0)
            {
                if (myt->tree[ind].rl != 1)
                {
                    *this = iterator(myt->tree[ind].p, myt);
                    return *this;
                }
                else
                {
                    int tmv = ind;
                    while (myt->tree[tmv].rl == 1)
                    {
                        tmv = myt->tree[tmv].p;
                    }
                    *this = iterator(myt->tree[tmv].p, myt);
                    return *this;
                }
            }
            *this = myt->beginin(myt->tree[ind].r);
            return *this;
        }
        iterator operator++(int)
        {
            int tmp = ind;
            if (myt->tree[ind].r == 0)
            {
                if (myt->tree[ind].rl != 1)
                {
                    *this = iterator(myt->tree[ind].p, myt);
                    return iterator(tmp, myt);
                }
                else
                {
                    int tmv = ind;
                    while (myt->tree[tmv].rl == 1)
                    {
                        tmv = myt->tree[tmv].p;
                    }
                    *this = iterator(myt->tree[tmv].p, myt);
                    return iterator(tmp, myt);
                }
            }
            *this = myt->beginin(myt->tree[ind].r);
            return iterator(tmp, myt);
        }
        const ValueType operator*()
        {
            return myt->tree[ind].key;
        }
        const ValueType* operator->()
        {
            return &(myt->tree[ind].key);
        }
        iterator operator--()
        {
            if (ind == 0)
            {
                *this = myt->endin(myt->root);
                return *this;
            }
            if (myt->tree[ind].l == 0)
            {
                if (myt->tree[ind].rl != -1)
                {
                    *this = iterator(myt->tree[ind].p, myt);
                    return *this;
                }
                else
                {
                    int tmv = ind;
                    while (myt->tree[tmv].rl == -1)
                    {
                        tmv = myt->tree[tmv].p;
                    }
                    *this = iterator(myt->tree[tmv].p, myt);
                    return *this;
                }
            }
            *this = myt->endin(myt->tree[ind].l);
            return *this;
        }
        iterator operator--(int)
        {
            int tmp = ind;
            if (ind == 0)
            {
                *this = myt->endin(myt->root);
                return iterator(tmp, myt);
            }
            if (myt->tree[ind].l == 0)
            {
                if (myt->tree[ind].rl != -1)
                {
                    *this = iterator(myt->tree[ind].p, myt);
                    return iterator(tmp, myt);
                }
                else
                {
                    int tmv = ind;
                    while (myt->tree[tmv].rl == -1)
                    {
                        tmv = myt->tree[tmv].p;
                    }
                    *this = iterator(myt->tree[tmv].p, myt);
                    return iterator(tmp, myt);
                }
            }
            *this = myt->endin(myt->tree[ind].l);
            return iterator(tmp, myt);
        }
        bool operator==(const iterator& oth) const
        {
            return (oth.ind == ind);
        }
        bool operator!=(const iterator& oth) const
        {
            return (oth.ind != ind);
        }
    };
    iterator beginin(int pl) const
    {
        while (this->tree[pl].l != 0)
        {
            pl = this->tree[pl].l;
        }
        return iterator(pl, this);
    }
    iterator begin() const
    {
        return this->beginin(this->root);
    }
    iterator end() const
    {
        return iterator(0, this);
    }
    iterator endin(int pl) const
    {
        while (this->tree[pl].r != 0)
        {
            pl = this->tree[pl].r;
        }
        return iterator(pl, this);
    }
    iterator find(ValueType newk) const
    {
        int tmv = this->root;
        while (tmv != 0)
        {
            if (newk < this->tree[tmv].key)
            {
                tmv = this->tree[tmv].l;
            }
            else if (this->tree[tmv].key < newk)
            {
                tmv = this->tree[tmv].r;
            }
            else
            {
                break;
            }
        }
        return iterator(tmv, this);
    }
    iterator lower_bound(ValueType newk) const
    {
        int tmv = this->root;
        int lastb = 0;
        while (tmv != 0)
        {
            if (newk < this->tree[tmv].key)
            {
                lastb = tmv;
                tmv = this->tree[tmv].l;
            }
            else if (this->tree[tmv].key < newk)
            {
                tmv = this->tree[tmv].r;
            }
            else
            {
                lastb = tmv;
                break;
            }
        }
        return iterator(lastb, this);
    }

};

