/*
 THE COMPUTER CODE CONTAINED HEREIN IS THE SOLE PROPERTY OF OUTRAGE
 ENTERTAINMENT, INC. ("OUTRAGE").  OUTRAGE, IN DISTRIBUTING THE CODE TO
 END-USERS, AND SUBJECT TO ALL OF THE TERMS AND CONDITIONS HEREIN, GRANTS A
 ROYALTY-FREE, PERPETUAL LICENSE TO SUCH END-USERS FOR USE BY SUCH END-USERS
 IN USING, DISPLAYING,  AND CREATING DERIVATIVE WORKS THEREOF, SO LONG AS
 SUCH USE, DISPLAY OR CREATION IS FOR NON-COMMERCIAL, ROYALTY OR REVENUE
 FREE PURPOSES.  IN NO EVENT SHALL THE END-USER USE THE COMPUTER CODE
 CONTAINED HEREIN FOR REVENUE-BEARING PURPOSES.  THE END-USER UNDERSTANDS
 AND AGREES TO THE TERMS HEREIN AND ACCEPTS THE SAME BY USE OF THIS FILE.
 COPYRIGHT 1996-2000 OUTRAGE ENTERTAINMENT, INC.  ALL RIGHTS RESERVED.
 */
 

#ifndef PSCLASS_H
#define PSCLASS_H

//	a universal list node to use with the list type
template<class T> struct tListNode
{
	T t;
	tListNode<T> *next;
};


//	LIST CLASSES
//

//	tList
//		this is a VERY BASIC list class that encapsulates a lot
//		of list operations into one class.  this class handles list NODES ONLY.
//		a more advanced form is to come, but this is for those hardcode programmers.

//	to declare say, a list that will contain integers, do this:
//		tList<int> list;
//		tListNode<int> *node;
//		node = new tListNode<int>;
//		node->data = 1;
//		list.Link(node);
//		it is the programmers responsibility to create the nodes DYNAMICALLY

//	universal single-linked-list type
template <class T> class tList
{
	tListNode<T> *m_link, *m_mark;
	int m_length;

public:
	tList() { m_link = m_mark = NULL; m_length = 0; };
	~tList() { tList::free(); };

//	moves to start of list. used for iteration
	tListNode<T> *start() { m_mark = m_link; return m_mark; }

//	gets next list item in iteration.  if at end of list, last item will be returned.
	tListNode<T> *next() { m_mark = (m_mark->next) ? m_mark->next : m_mark; return get(); };

//	returns the node at the current link location in iteration.
	tListNode<T> *get() const { return m_mark ? m_mark : NULL; };

//	length
	int length() const { return m_length; };

//	frees list
	void free() {
		m_link = m_mark = NULL;
		m_length = 0;
	};

//	make a link at the current mark location.
	void link(tListNode<T> *node) {
		if (m_link) {
			node->next = m_mark->next;
			m_mark->next = node;
		}
		else {
			m_link = node;
			node->next = NULL;
		}
		m_mark = node;
		m_length++;
	};

//	unlink a node on the list at the current mark, returning the unlinked node.
	tListNode<T> *unlink() {
		tListNode<T> *freenode, *node;
		if (!m_link) return NULL;
		if (m_link == m_mark) {
			freenode = m_mark;
			m_mark = m_link = m_link->next;
		}
		else {
			node = m_link;
			while (node->next != m_mark) 
				node = node->next;
			freenode = m_mark;
			node->next = m_mark->next;
		}
		freenode->next = NULL;
		return freenode;
	};
};

//	tQueue 
//		a circular queue implementation

template <class T, int t_LEN> class tQueue
{
	T m_items[t_LEN];
	short m_head, m_tail;

public:
	tQueue() {  m_head = m_tail = 0; };
	~tQueue() { };

	void send(T& item) {						// sends an item onto the queue
		short temp = m_tail+1;
		if (temp == t_LEN) 
			temp = 0;
		if (temp != m_head) {
			m_items[m_tail] = item;
			m_tail = temp;
		}
	};
	bool recv(T* item) {						// returns an item from the queue, false if no item.
		if (m_head == m_tail) 
			return false;
		*item = m_items[m_head++];
		if (m_head == t_LEN) 
			m_head = 0;
		return true;
	};

	void flush() {								// flush queue entries.
		m_head = m_tail = 0;
	};
};

#endif