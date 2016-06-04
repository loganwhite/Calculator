
// 我真诚地保证：

// 我自己独立地完成了整个程序从分析、设计到编码的所有工作。
// 如果在上述过程中，我遇到了什么困难而求教于人，那么，我将在程序实习报告中
// 详细地列举我所遇到的问题，以及别人给我的提示。

// 在此，我感谢蔡老师对我的启发和帮助。下面的报告中，我还会具体地提到
// 他们在各个方法对我的帮助。

// 我的程序里中凡是引用到其他程序或文档之处，
// 例如教材、课堂笔记、网上的源代码以及其他参考书上的代码段,
// 我都已经在程序的注释里很清楚地注明了引用的出处。

// 我从未没抄袭过别人的程序，也没有盗用别人的程序，
// 不管是修改式的抄袭还是原封不动的抄袭。

// 我编写这个程序，从来没有想过要去破坏或妨碍其他计算机系统的正常运转。

// 冯温迪

//in this header file, I've written two form of data structure, that is continuous and linked structure.
//the DataSturcture contains two sub-namespace, each one represent one form. But unfortunately, on testing the
//linkedstructrue, I found some errors, so I simply use the linearStructure to implement my simple calculator.
#include<limits>//for INT_MAX

namespace DataStructure
{
	enum Error_code
	{
		success,
		overflow,
		underflow,
		range_error,
		fail
	};

	namespace LinkedSturcture
	{
		template<class T>
		struct Node
		{
			T entry;
			Node<T> * next;

			Node(){next = NULL}
			Node(const T &x, Node<T> * link = NULL)
			{
				entry = x;
				next = link;
			}
		};

		template<class T>
		class List
		{
		public:
			List();
			~List();
			List(const List<T> &copy);
			void clear();
			Error_code replace(int position,const T&x);
			Error_code remove(int position, T&x);
			Error_code remove(int position);
			Error_code insert(int position, const T&x);
			Error_code insertRear(const T &x);
			Error_code getValue(int position, T& x)const;
			void operator=(const T&copy);
		protected:
			int count;
			Node<T> *head;
			Node<T> *set_position(int position)const;
		};

		template<class T>
		class Stack : public List<T>
		{
		public:
			Stack();
			Stack(const Stack<T> &s);
			bool empty() const;
			Error_code pop();
			Error_code top(T &item) const;
			Error_code push(const T &item);
			int stackLen()const;
			~Stack();
		private:
			int stack_count;
			List<T> stack_entry;
		};

		template<class T>
		class Queue : public List<T>
		{
		public:
			Queue();
			Queue(const Queue<T> &s);
			bool empty() const;
			Error_code serve();
			Error_code append(const T &item);
			Error_code retrieve(T &item) const;
			int queueLen()const;
			~Queue();
		protected:
			int queue_count;
			int front, rear;
			List<T> queue_entry;
		};


		////////////////////////////////////////////////////////////////////////////
		template<class T>
		List<T>::List()
		{
			count = 0;
			head = NULL;
		}

		template<class T>
		List<T>::List(const List<T> &copy)
		{
			Node<T> *new_node, *copy_node = copy.head;
			count = copy.count;
			if (copy_node == NULL) head = NULL;
			else 
			{
				head = new_node =	 new Node<T>(copy_node->entry);
				while (copy_node->next!=NULL) 
				{
					copy_node = copy_node->next;
					new_node->next =	new Node<T>(copy_node->entry);
					new_node = new_node->next;
				}
			}
		}

		template <class T>
		void List<T>::clear( )
		{
			Node<T> *previous, *current = head;
			while (current!=NULL) 
			{
				previous = current;
				current = current->next;
				delete previous;
			}
			count = 0;
			head = NULL;
		}

		template <class T>
		Node<T> *List<T>::set_position(int position) const
		{
			Node<T> *temp = head;
			for (int i = 0; i < position; i++ )
				temp = temp->next;
			return temp;
		}

		template <class T>
		Error_code List<T> :: replace(int position,	const T &x)
		{
			Node<T> *current;
			if (position < 0 || position >= count)
				return range_error;
			current = set_position(position);
			current->entry = x;
			return success;
		}

		template <class T>
		Error_code List<T> :: remove(int position, T &x)
		{
			Node<T> *prior, *current;
			if (count == 0) return fail;
			if (position < 0 || position >= count) return range_error;
			if (position > 0) 
			{
				prior = set_position(position - 1);
				current = prior->next;
				prior->next = current->next;
			}
			else 
			{
				current = head;
				head = head->next;
			}
			x = current->entry;
			delete current;
			count--;
			return success;
		}

		template <class T>
		Error_code List<T> :: remove(int position)//don't have to get the value
		{
			Node<T> *prior, *current;
			if (count == 0) return fail;
			if (position < 0 || position >= count) return range_error;
			if (position > 0) 
			{
				prior = set_position(position - 1);
				current = prior->next;
				prior->next = current->next;
			}
			else 
			{
				current = head;
				head = head->next;
			}
			delete current;
			count--;
			return success;
		}

		template <class T>
		Error_code List<T>::insert(int position, const T &x)
		{
			if (position < 0 || position > count) return range_error;
			Node<T> *new_node, *previous, *following;
			if (position > 0) {
				previous = set_position(position - 1);
				following = previous->next;
			}
			else following = head;
			new_node = new Node<T>(x, following);
			if (new_node == NULL) 
				return overflow;
			if (position == 0) head = new_node;
			else previous->next = new_node;
			count++ ;
			return success;
		}


		template <class T>
		Error_code List<T>::insertRear(const T &x)
		{
			Node<T> *new_node, *end;
			end = set_position(count-1);

			new_node = new Node<T>(x,NULL);
			if (new_node == NULL) 
				return overflow;
			if (count == 0) head = new_node;
			else end->next = new_node;
			count++ ;
			return success;
		}

		template<class T>
		void List<T>::operator=(const T&copy)
		{
			List<T> new_list(copy);
			clear();
			head = new_list.head;
			count = new_list.count;
		}

		template<class T>
		Error_code List<T>::getValue(int position, T& x)const
		{
			Node<T> *current;
			if (position < 0 || position >= count)
				return range_error;
			current = set_position(position);
			x = current->entry;
			return success;
		}

		template<class T>
		List<T>::~List()
		{
			clear();
		}
		////////////////////////////////////////////////////////////////////////////
		/////Stack declaration
		///////////////////////////////////////////////////////////////////////////
		template<class T>
		Stack<T>::Stack()
		{
			stack_count = 0;
		}

		template<class T>
		Stack<T>::Stack(const Stack<T> &s)
		{
			stack_entry = s.stack_entry;
			stack_count = s.stack_count;
		}

		template<class T>
		Error_code Stack<T>::top(T& item)const
		{
			if (stack_count <= 0) return underflow;
			stack_entry.getValue(stack_count,item);
			return success;
		}

		template<class T>
		Error_code Stack<T>::pop()
		{
			if (stack_count <= 0) return underflow;
			else
			{
				stack_entry.remove(stack_count);
				stack_count--;
				return success;
			}
		}

		template<class T>
		Error_code Stack<T>::push(const T &item)
		{
			stack_count++;
			stack_entry.insertRear(item);
			return success;
		}

		template<class T>
		bool Stack<T>::empty()const
		{
			return stack_count == 0;
		}

		template<class T>
		int Stack<T>::stackLen()const
		{
			return stack_count;
		}

		template<class T>
		Stack<T>::~Stack()
		{
			stack_entry.clear();
			stack_count = 0;
		}
		/////////////////////////////////////////////////////////////////////////////////
		////Queue Declaration
		////////////////////////////////////////////////////////////////////////////////

		template<class T>
		Queue<T>::Queue()
		{
			queue_count = 0;
			rear = queue_count;
			front = 0;
		}

		template<class T>
		Queue<T>::Queue(const Queue<T> &s)
		{
			queue_entry = s.queue_entry;
			front = s.front;
			rear = s.rear;
			queue_count = s.queue_count;
		}

		template<class T>
		Error_code Queue<T>::append(const T &item)
		{
			queue_entry.insertRear(item);
			queue_count++;
			return success;
		}

		template<class T>
		Error_code Queue<T>::serve()
		{
			if (queue_count == 0)
				return underflow;
			queue_entry.remove(1);
			queue_count--;
			return success;
		}

		template<class T>
		Error_code Queue<T>::retrieve(T &item)const
		{
			if (queue_count == 0)
				return underflow;
			queue_entry.getValue(1,item);
			return success;
		}

		template<class T>
		Queue<T>::~Queue()
		{
			queue_entry.clear();
			queue_count = 0;
			front = 0;
			rear = queue_count;
		}

		template<class T>
		int Queue<T>::queueLen()const
		{
			return queue_count;
		}

		template<class T>
		bool Queue<T>::empty()const
		{
			return queue_count == 0;
		}
	}

	namespace LinearSturcture
	{
		const int Max_Size = 20;

		template<class T>
		class stack
		{
		public:
			stack();
			bool empty()const;
			Error_code push(const T& x);
			Error_code pop();
			Error_code getValue(int position,T& item)const;
			Error_code top(T& item)const;
			int stackLen()const;
			~stack();
		private:
			int count;
			T stack_entry[Max_Size];
		};

		template<class T>
		stack<T>::stack()
		{
			count = 0;
		}

		template<class T>
		bool stack<T>::empty()const
		{
			if (count > 0) return false;
			else	 return true;
		}

		template<class T>
		Error_code stack<T>::pop()
		{
			if (count == 0) return underflow;
			else 
			{
				--count;
				return success;
			}
		}

		template<class T>
		Error_code stack<T>::top(T& item)const
		{
			if (count == 0) return underflow;
			else 
			{
				item = stack_entry[count - 1];
			    return success;
			}
		}

		template<class T>
		Error_code stack<T>::push(const T& item)
		{
			if (count >= Max_Size) return overflow;
			else 
			{
				stack_entry[count++] = item;
				return success;
			}
		}

		template<class T>
		int stack<T>::stackLen()const
		{
			return count;
		}

		template<class T>
		stack<T>::~stack()
		{
			count = 0;
		}
	}
}

