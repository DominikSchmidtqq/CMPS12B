public class MyQueue implements QueueInterface {
	/* 
	* TODO 2: Implement "MyQueue"
	*/
	private MyLinkedList list = new MyLinkedList();

	//constructor, creates a new instance of MyQueue
	public MyQueue() {
	    list = new MyLinkedList();
    }

    //checks if the queue contains anything, is the list is empty returns true, otherwise return false
    public boolean isEmpty() {
        if (list.size == 0) {
            return true;
        } else {
            return false;
        }
    }

    //adds an object at the last index of the internal list of the queue
    public void enqueue(Object item) {
        list.add(list.size, item);
    }

    //returns and removes the object at the first index of the internal list of the queue, if the queue is empty, throws an exception
    public Object dequeue() {
        if (this.isEmpty()) {
            throw new QueueException("Queue is empty");
        } else {
            Object o = list.get(0);
            list.remove(0);
            return o;
        }
    }

    //removes all items from the internal list of the queue by creating a new internal list
    public void dequeueAll() {
	    list = new MyLinkedList();
    }

    //return the item at the first index of the internal list if it exists, other throws an exception
    public Object peek() {
	    if (this.isEmpty()) {
            throw new StackException("Queue is empty");
	    }
        else {
	        return list.get(0);
        }
    }

    //toString, used for printing out Queue objects
    public String toString() {
        String queue = new String("(");
        for (int i = 0; i < list.size - 1; i++) {
            queue += list.get(i) + ", ";
        }

        if (this.isEmpty()) {
            queue += ")";
        } else {
            queue += list.get(list.size - 1) + ")";
        }

        return queue;
    }
	/* 
	* TODO 2: Implement "MyQueue"
	*/

} 