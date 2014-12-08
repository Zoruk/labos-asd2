/* 
 * File:   PriorityQueue.h
 * Author: zoruk
 *  
 * Created on 28. novembre 2014, 14:10
 */

#ifndef PRIORITYQUEUE_H
#define	PRIORITYQUEUE_H
#include <vector>
#include <cassert>

// Queue de priorité pour des int allent de 0 a N
template<typename KEY>
class PriorityQueueInt {
    private:
        struct Element {
            int data;
            KEY key;
        };
        typedef typename std::vector<Element>::size_type size_type;
        
        
        std::vector<size_type> keys;
        std::vector<Element> queue;
        
        
        void exchange(size_type a, size_type b) {
            assert(a < queue.size() && b < queue.size());
            std::swap(queue[a], queue[b]);
            keys[queue[a].data] = a;
            keys[queue[b].data] = b;
        }
        
        bool less(size_type a, size_type b) {
            assert(a < queue.size() && b < queue.size());
            return queue[b].key < queue[a].key;
        }

        void swim(size_type k) {
            while (k > 1 && less(k / 2, k))
            {
                exchange(k, k / 2);
                k = k / 2;
            }
        }

        void sink(size_type k)
        {
            size_type j;
            const size_type MAX = queue.size() - 1;
            while (2 * k <= MAX)
            {
                j = 2 * k;
                if (j < MAX && less(j, j + 1))
                    j++;
                if (!less(k, j))
                    break;
                exchange(k, j);
                k = j;
            }
        }
        
    public:
        PriorityQueueInt(size_type size = 0) {
            queue.reserve(size + 1);
            queue.resize(1);
            keys.assign(size + 1, -1);
        }
        
        void insert(int v, KEY k) {
            insert({v, k});
        }

        void insert(Element e) {
            queue.push_back(e);
            keys[e.data] = queue.size() - 1;
            swim(queue.size() - 1);
        }

        bool isEmpty() {
            return queue.size() == 1;
        }

        Element pop()
        {
            assert(!isEmpty());
            Element max = queue[1];
            exchange(1, queue.size() - 1);
        
            queue.pop_back();
            sink(1);
        
            keys[max.data] = -1;
            return max;
        }
        
        void decreaseKey(int t, KEY key) {
            const size_type POS = keys[t];
            queue[POS].key = key;
            swim(POS);
        }
};

// Spécialise pour les int (utilisation de vectaur et non map)
// ATTENTION les element vont de 0 a size - 1 passé au constructeur.
template<typename KEY>
class PriorityQueue<int, KEY> {
    private:
        struct Element {
            int data;
            KEY key;
        };
        typedef typename std::vector<Element>::size_type size_type;
        
        
        std::vector<size_type> qp;
        std::vector<Element> pq;
        
        
        void exchange(size_type a, size_type b) {
            assert(a < pq.size() && b < pq.size());
            std::swap(pq[a], pq[b]);
            qp[pq[a].data] = a;
            qp[pq[b].data] = b;
        }
        
        bool less(size_type a, size_type b) {
            assert(a < pq.size() && b < pq.size());
            return pq[b].key < pq[a].key;
        }

        void swim(size_type k) {
            while (k > 1 && less(k / 2, k))
            {
                exchange(k, k / 2);
                k = k / 2;
            }
        }

        void sink(size_type k)
        {
            size_type j;
            const size_type MAX = pq.size() - 1;
            while (2 * k <= MAX)
            {
                j = 2 * k;
                if (j < MAX && less(j, j + 1))
                    j++;
                if (!less(k, j))
                    break;
                exchange(k, j);
                k = j;
            }
        }
        
    public:
        PriorityQueue(size_type size) {
            pq.reserve(size + 1);
            pq.resize(1);
            qp.assign(size + 1, -1);
        }
        
        PriorityQueue(size_type size, KEY k) {
            pq.resize(size + 1);
            qp.resize(size + 1);
            for (int i = 0; i < size; ++i) {
                pq[i + 1].data = i;
                pq[i + 1].key = k;
                qp[i] = i + 1;
            }
        }
        
        void insert(int v, KEY k) {
            insert({v, k});
        }

        void insert(Element e) {
            pq.push_back(e);
            qp[e.data] = pq.size() - 1;
            swim(pq.size() - 1);
            //std::cout << "Insert " << e.data << " " << e.key << std::endl;
        }

        bool isEmpty() {
            return pq.size() == 1;
        }

        Element pop()
        {
            assert(!isEmpty());
            Element max = pq[1];
            exchange(1, pq.size() - 1);
        
            pq.pop_back();
            sink(1);
        
            qp.pop_back();// = -1;
            return max;
        }
        
        void decreaseKey(int t, KEY key) {
            //std::cout << "decreaseKey " << t << "  " << key << std::endl;
            const size_type POS = qp[t];
            pq[POS].key = key;
            swim(POS);
        }
};

#endif	/* PRIORITYQUEUE_H */
