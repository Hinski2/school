function Tree(val, left, right){
    this.left = left;
    this.right = right;
    this.val = val;
}

/*
    array.splice(start, deleteNo, item1, item2, .. itemn)
    start := indeks początkowy
    deleteNo (opcjonalny) :=
        * 0 - nic nie zostanie usunięte
        * n - n elementów zostanie usuniętych
        * pominiętny paramter - zostaną usunięte wszystkie elementy od start do końca
    itemx (opcjonalny) := elementy do dodania 

*/
Tree.prototype[Symbol.iterator] = function*(){
    let queue = [this];
    while(queue.length){
        // let begin = queue.splice(0, 1)[0] opcja z splice 
        let begin = queue.shift()

        if(begin.left) queue.push(begin.left)
        if(begin.right) queue.push(begin.right)

        yield begin.val
    }
}

var root = new Tree( 1, new Tree( 2, new Tree( 3 ) ), new Tree( 4 ));
for(var e of root)
    console.log(e)

// implementacja queue
class Node{
    constructor(val){
        this.val = val;
        this.next = null;
    }
}

class Queue{
    constructor(){
        this.begin = null;
        this.end = null;
        this.size = 0
    }

    empty(){
        return this.size == 0
    }

    push(val){
        if(this.empty()){
            this.begin = new Node(val);
            this.end = this.begin;
        }
        else{
            this.end.next = new Node(val);
            this.end = this.end.next
        }
        this.size++;
    }

    pop(){
        if(this.empty()) return null;
        else if(this.size == 1){
            let front = this.begin;
            this.begin = null;
            this.end = null;

            this.size--;
            return front.val;
        }
        else{
            let front = this.begin;
            this.begin = this.begin.next;

            this.size--;
            return front.val
        }
    }
}
