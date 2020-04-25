#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

class Node{
public:
    int inbound;
    char letter;
    vector <Node *> gt_nodes;
    
    Node(char letter){
        this->inbound = 0;
        this->letter = letter;
    }
    
    void virtualEraseNode(){
        for(int i = 0; i < gt_nodes.size(); i ++){
            gt_nodes[i]->inbound --;
        }
    }
    
    void recoverInbound(){
        for(int i = 0; i < gt_nodes.size(); i ++){
            gt_nodes[i]->inbound ++;
        }
    }
    
    bool pushBack(Node * node){
        for(int i = 0; i < this->gt_nodes.size(); i ++){
            if(this->gt_nodes[i] == node)
                return false;
        }
        this->gt_nodes.push_back(node);
        return true;
    }
};

void error_print(int n){
    printf("Inconsistency found after %d relations.\n", n + 1);
}

void undetermined_print(){
    printf("Sorted sequence cannot be determined.\n");
}

void detemined_print(int n, string seq){
    printf("Sorted sequence determined after %d relations: %s.\n", n + 1, seq.c_str());
}

int main(){
    int m, n, i;
    while(true){
        scanf("%d %d", &m, &n);
        if(m == 0 && n == 0)
            break;
        
        Node ** nodes = new Node * [m];
        for(i = 0; i < m; i ++){
            nodes[i] = new Node('A' + i);
        }
        
        bool end = false;
        
        for(i = 0; i < n; i ++){
            char x, y;
            scanf("\n%c<%c", &x, &y);
            if(end) continue;
            
            nodes[x - 'A']->pushBack(nodes[y - 'A']);
            
            int now_num, now = -1, zero_num = 0;;
            bool *checked = new bool[m];
            string ans = "";
            memset(checked, 0, sizeof(bool) * m);
            
            for(int k = 0; k < m; k ++)
                nodes[k]->inbound = 0;
            for(int k = 0; k < m; k ++)
                nodes[k]->recoverInbound();
            
            for(int j = 0; j < m; j ++){
                if(nodes[j]->inbound == 0)
                    zero_num ++;
            }
            
            if(zero_num == 0){
                error_print(i);
                end = true;
            }
            else if(zero_num > 1){
                for(int j = 0; j < m; j ++){
                    now_num = 0;
                    for(int k = 0; k < m; k ++){
                        if(checked[k])
                            continue;
                        if(nodes[k]->inbound == 0){
                            now_num ++;
                            now = k;
                        }
                    }
                    if(now_num == 0){
                        error_print(i);
                        end = true;
                        break;
                    }
                    else{
                        checked[now] = true;
                        nodes[now]->virtualEraseNode();
                    }
                }
                if(!end && i == n - 1){
                    undetermined_print();
                }
            }
            else{
                for(int j = 0; j < m; j ++){
                    /*
                    for(int k = 0; k < m; k ++)
                        printf("%d ", nodes[k]->inbound);
                    printf("\n");
                     */
                    now_num = 0;
                    for(int k = 0; k < m; k ++){
                        if(checked[k]){
                            continue;
                        }
                        if(nodes[k]->inbound == 0){
                            now_num ++;
                            now = k;
                        }
                    }
                    if(now_num == 1){
                        ans += nodes[now]->letter;
                        if(j == m - 1){
                            detemined_print(i, ans);
                            end = true;
                            break;
                        }
                        else{
                            checked[now] = true;
                            nodes[now]->virtualEraseNode();
                        }
                    }
                    else if(now_num == 0){
                        error_print(i);
                        end = true;
                        break;
                    }
                    else if(i == n - 1){
                        undetermined_print();
                        end = true;
                        break;
                    }
                    else{
                        break;
                    }
                }
            }
        }
    }
}

/*
test data:
4 6
D<B
D<A
D<C
C<A
C<B
A<B
10 40
C<I
E<G
A<J
F<B
D<E
F<D
C<B
E<H
G<I
D<B
C<H
A<B
J<I
D<G
A<E
C<G
E<B
H<G
C<A
F<J
B<G
D<J
E<J
D<H
C<F
B<J
G<J
B<H
D<A
F<I
A<H
C<E
F<H
A<G
B<I
F<A
H<J
F<G
F<E
C<J
15 60
B<M
M<H
N<G
N<E
I<D
B<D
A<J
O<D
D<J
F<E
I<L
F<B
I<C
C<E
I<K
I<J
A<E
B<L
G<J
A<G
N<H
H<J
K<N
K<E
F<J
C<D
K<M
G<L
F<H
M<L
A<K
B<K
E<L
B<H
F<D
M<E
M<G
N<L
O<J
D<H
B<O
B<C
A<L
I<B
F<L
C<L
A<C
N<O
A<B
F<C
K<J
C<G
O<E
I<O
D<E
I<N
F<N
M<J
H<L
N<D
15 60
B<M
M<H
N<G
N<E
I<D
B<D
A<J
O<D
D<J
F<E
I<L
F<B
I<C
C<E
I<K
I<J
A<E
B<L
G<J
A<G
N<H
H<J
K<N
K<E
F<J
C<D
K<M
G<L
F<H
M<L
A<K
B<K
E<L
B<H
F<D
M<E
M<G
N<L
O<J
D<H
O<B
B<C
A<L
I<B
F<L
C<L
A<C
N<O
A<B
F<C
K<J
C<G
O<E
I<O
D<E
I<N
F<N
M<J
H<L
N<D
26 325
J<I
L<P
K<S
M<X
K<E
H<W
Z<S
G<R
F<R
A<Y
V<D
P<X
P<W
M<S
R<A
G<V
C<H
O<R
A<S
N<C
V<Y
A<I
F<Z
V<Q
V<R
H<I
Q<T
M<Q
F<A
J<X
M<D
C<Q
D<E
V<F
B<T
X<U
D<U
G<Y
V<B
B<J
N<U
K<Z
P<S
E<U
O<Y
M<Z
C<I
F<S
G<P
O<J
C<S
W<U
Z<Y
D<L
H<T
B<Q
X<W
D<I
K<B
R<L
L<X
S<Q
K<F
B<R
C<L
O<B
Y<S
F<Y
X<T
S<U
C<W
O<P
B<Z
V<U
C<X
H<U
O<U
V<W
D<A
O<X
G<D
P<A
D<X
E<T
S<T
C<T
H<O
J<Q
K<H
Z<Q
Z<W
I<T
J<A
Z<E
F<L
Q<U
J<S
N<H
J<E
B<D
M<I
K<R
Z<X
B<Y
P<Y
R<E
F<O
R<P
C<A
D<Y
D<Z
B<X
M<A
I<Q
K<J
J<Z
O<W
H<R
L<Q
M<F
W<T
F<X
F<E
A<W
N<J
K<O
H<S
F<B
V<K
O<A
R<U
M<W
M<K
E<W
C<D
N<S
S<E
Y<I
G<N
F<P
N<P
G<W
M<B
J<W
M<J
X<Q
Y<Q
Y<E
P<Q
S<W
J<T
Z<U
I<U
M<Y
F<Q
V<Z
J<D
C<J
K<Q
A<Q
M<U
S<I
C<O
Z<I
H<B
G<A
P<T
G<F
X<E
B<U
O<I
C<F
O<L
N<V
F<T
J<L
D<T
R<S
N<E
L<T
M<N
O<D
K<X
V<L
G<B
O<E
R<Y
G<I
O<Z
G<U
Z<L
R<T
N<Q
C<Y
M<C
K<I
O<S
H<E
R<X
R<W
H<J
G<K
E<I
C<U
H<A
L<E
N<F
V<X
N<W
M<P
H<F
F<I
R<Z
K<T
N<Y
D<W
G<J
N<I
G<S
M<L
N<X
F<U
L<Y
G<H
G<E
D<S
C<B
V<P
V<A
V<I
G<L
B<L
W<Q
T<U
N<D
V<T
P<I
B<I
N<Z
P<E
K<C
E<Q
K<D
N<K
B<E
V<H
G<T
B<P
V<J
D<Q
L<S
M<T
M<R
K<A
P<U
N<A
Z<A
L<I
V<E
H<L
K<Y
A<T
J<P
C<R
K<W
M<H
B<W
N<T
C<P
G<Z
R<D
H<P
Z<T
X<S
H<D
G<O
N<R
L<W
F<D
H<Q
R<I
V<C
V<O
N<O
L<U
Z<P
N<L
C<E
O<Q
H<X
F<J
G<C
D<P
A<U
A<E
M<E
J<Y
I<W
G<X
L<A
B<S
N<B
H<Y
C<Z
B<A
Y<U
X<A
K<L
Y<T
R<J
H<Z
R<Q
Y<W
V<S
X<Y
G<Q
K<U
G<M
M<V
X<I
J<U
K<P
M<O
F<W
O<T
26 26
A<B
B<C
C<D
D<E
E<F
F<G
G<H
H<I
I<J
J<K
K<L
L<M
M<N
N<O
O<P
P<Q
Q<R
R<S
S<T
T<U
U<V
V<W
W<X
X<Y
Y<Z
Z<A
5 10
D<E
A<D
B<D
B<C
C<E
D<C
B<A
A<C
A<E
B<E
20 158
I<L
F<R
I<C
N<B
C<K
R<O
E<D
D<K
F<S
A<C
J<E
H<A
N<D
N<T
H<I
A<T
M<S
T<O
P<Q
G<J
B<L
N<I
A<R
T<S
M<J
B<J
G<P
N<E
B<D
N<F
K<Q
B<E
E<O
M<P
M<F
A<F
H<S
G<D
P<J
A<Q
T<F
G<F
T<R
L<Q
A<J
G<I
H<O
C<D
P<L
H<T
T<E
D<Q
J<O
A<M
F<E
E<K
E<Q
P<T
C<E
M<B
T<J
G<E
N<K
I<P
M<Q
H<M
G<L
I<J
P<S
A<K
F<L
T<L
G<T
I<Q
B<O
H<N
M<G
J<R
C<B
N<O
T<D
A<D
L<S
I<K
R<Q
M<E
B<R
O<Q
R<D
I<T
T<Q
I<D
O<D
N<Q
A<S
M<K
H<G
G<C
H<E
B<Q
H<B
G<S
I<S
I<R
J<Q
A<L
F<Q
J<D
C<J
H<L
A<P
F<K
L<E
I<O
N<P
E<S
A<I
C<R
N<L
T<B
H<K
R<K
A<G
C<Q
J<K
C<T
P<B
H<F
O<K
R<L
O<S
G<O
M<I
K<S
F<O
G<R
B<S
P<E
T<K
G<B
A<O
I<B
P<C
N<M
J<F
H<R
F<D
P<D
H<P
G<Q
P<R
L<K
H<Q
S<Q
H<D
C<O
N<S
N<A
10 40
E<J
C<A
G<J
C<H
G<I
A<I
D<I
D<A
G<E
F<I
A<J
D<H
E<B
A<B
D<E
E<I
D<C
C<G
F<A
F<H
D<B
I<J
I<B
F<C
J<B
D<F
G<H
A<H
I<H
A<E
E<H
F<J
H<B
G<A
G<F
D<G
F<E
F<B
C<B
C<I
20 70
K<Q
P<L
I<C
O<L
I<M
B<Q
G<R
J<E
O<E
J<C
J<N
H<T
A<D
G<B
I<O
S<K
H<F
J<L
Q<C
G<K
J<B
O<D
P<K
T<L
E<D
T<R
R<L
H<B
F<L
I<Q
E<R
P<M
S<R
T<C
G<Q
I<N
G<C
I<E
R<N
A<Q
Q<M
B<K
A<R
Q<R
P<B
E<N
D<Q
K<D
S<F
B<C
B<T
O<J
S<M
B<F
R<M
S<I
S<T
I<F
H<D
A<E
P<T
E<Q
C<R
K<C
S<H
B<L
H<P
E<F
A<N
O<B
5 10
D<C
B<E
B<D
E<C
A<E
D<E
A<B
A<D
A<C
B<C
10 20
D<J
C<A
A<I
J<G
F<H
F<J
E<G
F<D
E<H
C<J
C<H
E<J
C<B
D<G
E<D
F<G
F<E
A<H
A<D
J<H
6 11
A<B
C<F
B<F
D<B
B<E
C<D
A<F
C<E
F<E
D<E
A<C
9 23
I<A
C<D
B<D
G<B
F<D
C<G
I<F
H<A
C<E
I<H
B<A
C<B
I<E
G<D
H<C
I<C
D<E
I<G
B<F
I<D
H<G
H<D
C<F
20 34
J<C
L<A
S<D
P<I
R<I
T<E
L<O
T<C
O<C
D<O
S<I
I<D
B<G
F<M
T<M
B<C
H<M
F<P
Q<I
F<O
Q<J
R<M
E<M
S<N
B<N
P<C
L<E
H<I
D<C
R<S
Q<N
P<E
I<T
E<D
20 190
B<E
C<M
N<S
N<R
O<K
M<J
B<J
F<B
G<B
R<O
Q<T
Q<G
D<G
M<F
C<T
H<E
D<B
Q<F
S<K
A<P
H<O
H<S
H<I
P<S
F<E
F<T
M<O
A<O
A<J
R<K
D<K
H<N
M<K
Q<N
P<E
S<O
P<O
F<J
N<D
F<S
C<D
D<O
A<S
C<B
Q<J
F<P
M<G
R<J
N<O
L<I
I<K
B<O
J<E
C<J
H<T
Q<A
Q<S
L<B
K<T
O<T
A<G
H<G
C<R
P<B
H<Q
C<E
A<E
I<J
R<F
M<D
H<D
N<T
C<O
I<T
D<R
C<K
H<P
C<I
C<P
N<A
R<B
H<M
R<I
C<Q
I<E
Q<I
Q<D
C<S
D<L
N<B
Q<K
C<G
P<J
C<A
J<T
Q<L
D<P
R<G
S<T
H<K
I<O
D<E
I<B
P<K
K<E
N<G
C<F
M<T
S<B
A<K
S<E
A<F
A<T
P<G
R<E
D<I
F<K
I<S
G<J
H<F
G<S
L<F
P<I
M<L
G<I
N<P
B<T
L<P
J<K
C<H
B<K
A<I
G<E
G<T
N<M
M<B
H<R
D<J
M<E
F<G
Q<M
D<S
H<B
N<J
Q<E
G<O
C<N
H<A
P<T
Q<B
L<S
R<S
N<L
L<G
Q<R
F<O
A<R
L<E
Q<P
E<T
M<R
M<S
L<O
A<L
R<P
H<J
L<K
M<P
A<M
L<T
R<T
L<R
S<J
N<E
F<I
A<D
D<F
Q<O
J<O
O<E
C<L
A<B
N<K
N<F
G<K
D<T
N<I
H<L
M<I
L<J
0 0
---------------------answer-----------------------
Sorted sequence determined after 6 relations: DCAB.
Sorted sequence determined after 29 relations: CFDAEBHGJI.
Sorted sequence cannot be determined.
Inconsistency found after 48 relations.
Sorted sequence determined after 318 relations: GMNVKCHFOBRJDZLPXAYSEIWQTU. x
Sorted sequence determined after 25 relations: ABCDEFGHIJKLMNOPQRSTUVWXYZ.
Sorted sequence determined after 7 relations: BADCE.
Sorted sequence determined after 158 relations: HNAMGIPCTBJFRLEODKSQ.
Inconsistency found after 35 relations.
Sorted sequence cannot be determined.
Sorted sequence determined after 7 relations: ABDEC.
Sorted sequence cannot be determined.
Sorted sequence determined after 11 relations: ACDBFE.
Sorted sequence cannot be determined.
Sorted sequence cannot be determined.
Sorted sequence determined after 179 relations: CHQNAMDLRFPGISBJOKET.

*/
