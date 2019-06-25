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
    int l = 0;
    int r = 0;
    int p = 0;
    int rl = 0;
    int h = 0;
    Node()
    {

    }
};

template<class ValueType>
class Set
{
private:
    std::vector<Node<ValueType>> tree;
public:
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
    Set(const Set & news)
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
    int lson(int ind) const
    {
        return tree[ind].l;
    }
    int rson(int ind) const
    {
        return tree[ind].r;
    }
    int diff(int ind) const
    {
        if (ind == 0)
        {
            return 0;
        }
        if (rson(ind) == 0 && this->tree[rson(ind)].h != 0)
        {
            this->tree[rson(ind)].h = 0;
        }
        if (lson(ind) == 0 && this->tree[lson(ind)].h != 0)
        {
            this->tree[lson(ind)].h = 0;
        }
        return this->tree[lson(ind)].h - this->tree[rson(ind)].h;
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
        this->tree[ind].h = (this->tree[lson(ind)].h < this->tree[rson(ind)].h ? this->tree[rson(ind)].h : this->tree[lson(ind)].h) + 1;
    }
    void rot(int ind, int dir)
    {
        if (dir == 1)
        {
            int tind = lson(ind);
        }
        else
        {
            int tind = rson(ind);
        }
        if (tind == 0 || ind == 0)
        {
            return;
        }
        if (ind == this->root)
        {
            this->root = tind;
        }
        if (dir == 1)
        {
            this->tree[ind].l = rson(ind);
        }
        else
        {
            this->tree[ind].r = lson(ind);
        }
        if (this->tree[tind].r != 0)
        {
            this->tree[rson(tind)].rl = -dir;
            this->tree[rson(tind)].p = ind;
        }
        if (dir == 1)
        {
            this->tree[tind].r = ind;
        }
        else
        {
            this->tree[tind].l = ind;
        }
        this->tree[tind].p = this->tree[ind].p;
        this->tree[tind].rl = this->tree[ind].rl;
        this->tree[ind].rl = dir;
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
    }
    void brotl(int ind)
    {
        rot(this->tree[ind].r, 1);
        rot(ind, -1);
    }
    void brotr(int ind)
    {
        rot(this->tree[ind].l, -1);
        rot(ind, 1);
    }
    void backway(int ind)
    {
        if (ind == 0)
        {
            return;
        }
        updh(ind);
        if (this->diff(ind) == 0)
        {
            return;
        }
        if (abs(this->diff(ind)) == 1)
        {
                this->backway(this->tree[ind].p);
            return;
        }
        if (this->diff(ind) <= -2)
        {
            if (this->diff(this->tree[ind].r) < 1)
            {
                this->rot(ind, -1);
            }
            else
            {
                this->brotl(ind);
            }
                this->backway(this->tree[ind].p);
            return;
        }
        if (this->diff(ind) >= 2)
        {
            if (this->diff(this->tree[ind].l) > -1)
            {
                this->rot(ind, 1);
            }
            else
            {
                this->brotr(ind);
            }
            this->backway(this->tree[ind].p);
            return;
        }
        this->backway(this->tree[ind].p);
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
                    tmv = lson(tmv);
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
                    tmv = rson(tmv);
                }
            }
        }
    }
    void erase(ValueType newk)
    {
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
                tmv = lson(tmv);
            }
            else if (this->tree[tmv].key < newk)
            {
                tmv = rson(tmv);
            }
            else
            {
                break;
            }
        }
        if (rson(tmv) != 0)
        {
            int ttmv = rson(tmv);
            while (lson(ttmv) != 0)
            {
                ttmv = lson(ttmv);
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
            this->root = lson(tmv);
            this->tree[this->root].p = 0;
            this->tree[this->root].rl = 0;
            this->tree[lson(tmv)].p = 0;
            return;
        }
        if (this->tree[tmv].rl == -1)
            this->tree[this->tree[tmv].p].l = lson(tmv);
        if (this->tree[tmv].rl == 1)
            this->tree[this->tree[tmv].p].r = lson(tmv);
        if (tree[tmv].l == 0)
        {
            updh(this->tree[tmv].p);
            this->backway(this->tree[tmv].p);
            return;
        }
        this->tree[lson(tmv)].p = this->tree[tmv].p;
        this->tree[lson(tmv)].rl = this->tree[tmv].rl;

        int tmpm = lson(tmv);
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
            *this = myt->beginin(rson(ind));
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
            *this = myt->beginin(rson(ind));
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
            *this = myt->endin(lson(ind));
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
        while (lson(pl) != 0)
        {
            pl = lson(pl);
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
        while (rson(pl) != 0)
        {
            pl = rson(pl);
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
                tmv = lson(tmv);
            }
            else if (this->tree[tmv].key < newk)
            {
                tmv = rson(tmv);
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
                tmv = lson(tmv);
            }
            else if (this->tree[tmv].key < newk)
            {
                tmv = rson(tmv);
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

