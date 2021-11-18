#ifndef MEDIAN_TREE_IMPL_H
#define MEDIAN_TREE_IMPL_H

#include <stddef.h>
#include <utility>
#include <array>


template <typename T, size_t Size>
struct GMedian_tree
{
    GMedian_tree (T value = T()) :
        root(&tree[0]),
        index(0)
    {
        for (size_t i = Size; i-- != 0; )
        {
            node * parent = (i > 0)? &tree[(i - 1) / 2] : nullptr;
            node * left = (2*i + 1 < Size)? &tree[2*i + 1] : nullptr;
            node * right = (2*i + 2 < Size)? &tree[2*i + 2] : nullptr;
            
            tree[i] = {parent, left, right, 1, value};
            tree[i].update_size();
            
            position[i] = &tree[i];
        }
    }

    T filtered (T value)
    {
        node * cur = position[index];
        if (++index == Size)
            index = 0;
        
        remove(cur);
        
        cur->key = std::move(value);
        cur->size = 1;
        cur->parent = nullptr;
        cur->left = nullptr;
        cur->right = nullptr;

        add(cur);

        if constexpr (Size % 2 == 1)
        {
            return find(Size / 2)->key;
        }
        else
        {
            return (find((Size / 2) - 1)->key +
                    find(Size / 2)->key) / 2;
        }
    }

private:
    struct node
    {
        void update_parent (node * value)
        {
            if (!parent)
                return;
            if (parent->left == this)
                parent->left = value;
            else
                parent->right = value;
        }

        void update_size ()
        {
            size = get_size(left) + get_size(right) + 1;
        }
    
        node * right_small ();
        node * left_small ();
        node * right_big ();
        node * left_big ();
    
        node * balance ()
        {
            if (get_size(left) > 2 * get_size(right) + 1)
            {
                if (get_size(left->left) >= get_size(left->right))
                    return right_small();
                else
                    return right_big();
            }
            else if (2 * get_size(left) + 1 < get_size(right))
            {
                if (get_size(right->right) >= get_size(right->left))
                    return left_small();
                else
                    return left_big();
            }
            else 
                return this;
        }
        
        static size_t get_size (node * value)
        {
            return (value)? value->size : 0; 
        }
    
        node * parent;
        node * left;
        node * right;
        size_t size;
        
        T key;
    };
    
    
    void add (node * value);
    
    void replace (node * a, node * b)
    {
        a->update_parent(b);
        b->parent = a->parent;
        b->left = a->left;
        b->right = a->right;
        b->size = a->size;
        if (b->left)
            b->left->parent = b;
        if (b->right)
            b->right->parent = b;
    }
    
    node * remove_left (node * value);
    node * remove_right (node * value);
    
    void remove (node * value);
    node * find (size_t pos);
    
    node * root;
    std::array <node, Size> tree;
    std::array <node *, Size> position;
    size_t index;
};



template <typename T, size_t Size>
typename GMedian_tree <T, Size> ::node * GMedian_tree <T, Size> ::node::right_small ()
{
    node * my_left = left;
    
    left = my_left->right;
    my_left->right = this;
    update_parent(my_left);
    
    my_left->parent = parent;
    parent = my_left;
    if (left)
        left->parent = this;
    
    update_size();
    my_left->update_size();

    return my_left;
}

template <typename T, size_t Size>
typename GMedian_tree <T, Size> ::node * GMedian_tree <T, Size> ::node::left_small ()
{
    node * my_right = right;
    
    right = my_right->left;
    my_right->left = this;
    update_parent(my_right);
    
    my_right->parent = parent;
    parent = my_right;
    if (right)
        right->parent = this;

    update_size();
    my_right->update_size();

    return my_right;
}

template <typename T, size_t Size>
typename GMedian_tree <T, Size> ::node * GMedian_tree <T, Size> ::node::right_big ()
{
    node * my_left = left;
    node * my_center = my_left->right;
    
    my_left->right = my_center->left;
    left = my_center->right;
    my_center->left = my_left;
    my_center->right = this;
    update_parent(my_center);
    
    my_center->parent = parent;
    my_left->parent = my_center;
    parent = my_center;
    if (left)
        left->parent = this;
    if (my_left->right)
        my_left->right->parent = my_left;
    
    update_size();
    my_left->update_size();
    my_center->size = my_left->size + size + 1;

    return my_center;
}

template <typename T, size_t Size>
typename GMedian_tree <T, Size> ::node * GMedian_tree <T, Size> ::node::left_big ()
{
    node * my_right = right;
    node * my_center = my_right->left;
    
    my_right->left = my_center->right;
    right = my_center->left;
    my_center->left = this;
    my_center->right = my_right;
    update_parent(my_center);
    
    my_center->parent = parent;
    my_right->parent = my_center;
    parent = my_center;
    if (right)
        right->parent = this;
    if (my_right->left)
        my_right->left->parent = my_right;
    
    update_size();
    my_right->update_size();
    my_center->size = size + my_right->size + 1;

    return my_center;
}


template <typename T, size_t Size>
void GMedian_tree <T, Size> ::add (node * value)
{
    if (root == nullptr)
    {
        root = value;
        return;
    }

    node * cur = root;
    node * prev = nullptr;
    
    while (cur != nullptr)
    {
        prev = cur;
        if (value->key < cur->key)
            cur = cur->left;
        else
            cur = cur->right;
    }

    value->parent = prev;
    if (value->key < prev->key)
        prev->left = value;
    else
        prev->right = value;
    
    cur = prev;
    while (cur != nullptr)
    {
        cur->size++;
        prev = cur->balance();
        cur = prev->parent;
    }
    root = prev;
}

template <typename T, size_t Size>
typename GMedian_tree <T, Size> ::node * GMedian_tree <T, Size> ::remove_left (node * value)
{
    node * cur = value->left;
    node * prev = cur;
    node * ans;
    
    while (cur->right)
    {
        prev = cur;
        cur = cur->right;
    }
    
    if (prev != cur)
    {
        ans = prev;
        prev->right = cur->left;
        if (cur->left)
            cur->left->parent = prev;
        replace(value, cur);
    }
    else
    {
        ans = value->parent;
        value->update_parent(cur);
        cur->parent = value->parent;
        cur->right = value->right;
        if (cur->right)
            cur->right->parent = cur;
        cur->size += node::get_size(cur->right);
    }

    if (value == root)
        root = cur;

    return ans;
}

template <typename T, size_t Size>
typename GMedian_tree <T, Size> ::node * GMedian_tree <T, Size> ::remove_right (node * value)
{
    node * cur = value->right;
    node * prev = cur;
    node * ans;
    
    while (cur->left)
    {
        prev = cur;
        cur = cur->left;
    }
    
    if (prev != cur)
    {
        ans = prev;
        prev->left = cur->right;
        if (cur->right)
            cur->right->parent = prev;
        replace(value, cur);
    }
    else
    {
        ans = value->parent;
        value->update_parent(cur);
        cur->parent = value->parent;
        cur->left = value->left;
        if (cur->left)
            cur->left->parent = cur;
        cur->size += node::get_size(cur->left);
    }

    if (value == root)
        root = cur;

    return ans;
}

template <typename T, size_t Size>
void GMedian_tree <T, Size> ::remove (node * value)
{
    node * from;
    if (!value->left && !value->right)
    {
        from = value->parent;
        value->update_parent(nullptr);
        if (value == root)
            root = nullptr;
    }
    else if (node::get_size(value->left) >= node::get_size(value->right))
        from = remove_left(value);
    else
        from = remove_right(value);
    
    while (from != nullptr)
    {
        from->size--;
        from = from->balance()->parent;
    }
}

template <typename T, size_t Size>
typename GMedian_tree <T, Size> ::node * GMedian_tree <T, Size> ::find (size_t pos)
{
    node * cur = root;
    size_t left_size = node::get_size(cur->left);
    
    while (left_size != pos)
    {
        if (left_size < pos)
        {
            pos = pos - left_size - 1;
            cur = cur->right;
        }
        else
        {
            cur = cur->left;
        }
        left_size = node::get_size(cur->left);
    }
    
    return cur;
}


#endif

