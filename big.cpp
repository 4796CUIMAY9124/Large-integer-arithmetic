
/*使用说明：本源代码利用VS2019实现，通过键盘输入读取大整数。
具体使用：运行代码，待出现提示输入第一个数（减法运算中为被减数），通过键盘输入，回车结束；
待出现提示输入第二个数，通过键盘输入，回车结束。同时，代码依次输出加减乘运算的结果
*/

#include<iostream>
#include<cmath>
using namespace std;

int op = 1;                                         //符号，一般为1，减法结果为负为0，输出‘-’.

class list;                                         //双向链表
class node {                                        //每个结点存储一个数、front、next
    int v;                                          //数值                                        
	node* next;
	node* front;
public:
    node();
	node(char a);                                   //将字符转为数值传进去
	node(int a);
	~node();
	friend class list;                              //使链表能使用node类
};

node::node() {                                      //数值为0，前后指针默认为空
	v = 0;
	next = front = NULL;
}

node::node(char a) {                                //将字符传进去，变成数值存储进node，使其前后指针都为空
	v = int(a) -48 ;
	next = front = NULL;	
}

node::node(int a) {                                //将字符传进去，变成数值存储进node，使其前后指针都为空
	v = a;
	next = front = NULL;
}

node::~node() {                                      //数值为0，前后指针设为空
	v = 0;
	next = front = NULL;
}

class list {
                                             //头尾指针，头指针只有NEXT，尾指针只有FRONT.头尾指针不存储有实际意义的数
	node* head;
	node* tail;
	int len;                                        //实际长度（不包括头尾指针）
public:
	list();
	list(char* a);                                  //将字符串传进去
	list(list* l);
	~list();
	list* operator+(list* list2);                   //加法
	list* operator-(list* list2);                   //减法
	list* operator*(list* list2);                   //乘法
	void print();                                   //链表输出
};

list::list() {
	head = new node();                               //生成头尾指针，都指向空
	tail = new node();
	len = 0;                                        //长度初始为0
}

list::list(char* a) {                               //将字符串传进去 
	len = 0;
	head = new node();
	tail = new node();
	node* temp0=tail;                               //temp0为当前创造结点的后一个,第一个结点为低位，按从低位到高位存储
	for(int i=0;a[i]!='\0';i++)
	{
		node* temp = new node(a[i]);
		head->next = temp;
		temp->front = head;
		temp->next = temp0;
		temp0->front = temp;
	    temp0 = temp;	len++;		
	}
}

list::list(list* l) {                               //将字符串传进去 
	len = l->len;
	head = new node();
	tail = new node();
	node* temp0 = l->head->next;                               //temp为当前创造结点,temp0 为对应l位置结点,temp1为当前结点前一个
	node* temp1 = head;
	while(temp0!=l->tail)
	{
		node* temp = new node(temp0->v);
		temp1->next = temp;
		temp->front = temp1;
		temp->next = tail;
		tail->front = temp;
		temp1 = temp;	
		temp0 = temp0->next;
	}
}

list::~list() {
	node* temp;
	while (head->next != tail) {
		temp = head->next;
		head->next = temp->next;
		delete temp;
	}
	delete head;
	delete tail;
	len = 0;                                        
}

list* list::operator+(list* list2) {                
	op = 1;
	if ((list2->tail->front->v == ('-' - 48)) && (tail->front->v == ('-' - 48))) {
		list* list3 = new list(this);             //深复制 3对1，4对2
		node* temp0 = list3->tail->front;
		temp0->front->next = list3->tail;
		list3->tail->front = temp0->front;
		list3->len--;

		list* list4 = new list(list2);             
		node* temp1 = list4->tail->front;
		temp1->front->next = list4->tail;
		list4->tail->front = temp1->front;
		list4->len--;

		list* list00 = list3->operator+(list4);  //取绝对值相加，符号为负
		op = 0;
		delete list3;
		delete list4;
		return  list00;
	}
	else if(list2->tail->front->v == ('-' - 48)){
		list* list3 = new list(list2);             //第二个数为负，用第一个数减第二个数绝对值
		node* temp=list3->tail->front;
		temp->front->next = list3->tail;
		list3->tail->front = temp->front;
		list3->len--;
		
		list* list00 = operator-(list3);
		delete list3;
		return  list00;
	}
	else if (tail->front->v == ('-' - 48)) {       //第一个数为负，转成第二个数加第一个数
		list* list00 = list2->operator+(this);
		return  list00;
	}
	else {                                         //两数皆正，正常加法
		node* temp1 = head;
		node* temp2 = list2->head;
		int newlen;
		int* p = new int[newlen = (len > list2->len ? (len + 1) : (list2->len + 1))];
		int num, i;                                    //记录每一位运算的当前值
		for (i = 0; i < newlen; i++) {                  //置最终值数组元素都为0
			p[i] = 0;
		}

		int* l3 = p;                                       //保存当前P指向位置

		while ((temp1->next != tail) || (temp2->next != list2->tail)) {
			num = (temp1->next->v) + (temp2->next->v) + *p;
			*p = num % 10;                                 // 运算，存储计算所得的低位，运算值的进值存在下一位上
			*(++p) = num / 10;
			if (temp1->next != tail) {                     //在下一位存在的情况下，移到下一位
				temp1 = temp1->next;
			}
			if (temp2->next != list2->tail) {
				temp2 = temp2->next;
			}
		}
		char* l = new char[newlen + 1];                      //构成字符串数组
		for (i = 0; i < newlen; i++) {
			l[i] = char(l3[newlen - 1 - i] + 48);
		}
		l[newlen] = '\0';                                //构成字符串数组
		list* list00 = new list(l);
		delete []l3;
		delete []l;
		return  list00;
	}	
}

list* list::operator-(list* list2) { 
	op = 1;
	if ((list2->tail->front->v == ('-' - 48)) && (tail->front->v == ('-' - 48))) {
		//两数皆负，把第二个转正，第一个保持,变成第二个数绝对值加第一个数
		list* list3 = new list(list2);             
		node* temp1 = list3->tail->front;
		temp1->front->next = list3->tail;
		list3->tail->front = temp1->front;
		list3->len--;

		list* list00 = list3->operator+(this);
		delete list3;
		return  list00;
	}
	else if (list2->tail->front->v == ('-' - 48)) {
		list* list3 = new list(list2);             //第二个数负的，转为绝对值相加
		node* temp = list3->tail->front;
		temp->front->next = list3->tail;
		list3->tail->front = temp->front;
		list3->len--;

		list* list00 = operator+(list3);	
		delete list3;
		return  list00;
	}
	else if (tail->front->v == ('-' - 48)) {
		list* list3 = new list(this);             //第一个数负的，转为绝对值相加取负号。
		node* temp = list3->tail->front;
		temp->front->next = list3->tail;
		list3->tail->front = temp->front;
		list3->len--;

		list* list00 = list2->operator+(list3);
		op = 0;
		delete list3;
		return  list00;
	}
	else {
		int newlen;                                      //两数皆正，正常减法
		int s = 0;                                       //用于判断符号，+（第一个数大）为1，-为-1。0表示没比较，或者目前为止各位值相等。

		if (len < list2->len) { s = -1; op = 0; }        //判断符号
		else if (len > list2->len) { s = 1; }
		else {
			node* t1 = tail;
			node* t2 = list2->tail;

			while (s == 0 && (t1->front != head) && (t2->front != list2->head)) {
				if (t1->front->v > t2->front->v) { s = 1; break; }
				else if (t1->front->v < t2->front->v) { s = -1; op = 0; break; }
				else {
					t1 = t1->front;
					t2 = t2->front;
				}
			}
			if (t1->front == head && t2->front == list2->head) {
				char* p = new char[newlen = 2];
				p[0] = '0'; p[1] = '\0';
				                            //两组数相等
				list* list00 = new list(p);
				delete []p;
				return  list00;
			}
		}                                                //符号判断完毕，且两组数不相等

		node* temp1;
		node* temp2;
		node* end1;
		node* end2;

		//将大的数赋给temp1，小的给temp2
		if (s == 1) {
			temp1 = head;
			end1 = tail;
			temp2 = list2->head;
			end2 = list2->tail;
		}
		else {
			temp2 = head;
			end2 = tail;
			temp1 = list2->head;
			end1 = list2->tail;
		}

		int* p = new int[newlen = (len > list2->len ? (len + 1) : (list2->len + 1))];
		int num, i;                                       //记录每一位运算的当前值
		for (i = 0; i < newlen; i++) {                    //置最终值数组元素都为0
			p[i] = 0;
		}

		int* l3 = p;                                       //保存当前P指向位置

		// 运算，存储计算所得的低位，运算值的退值存在下一位上,退值标为正
		while (temp1->next != end1 || temp2->next != end2)
		{
			if ((temp1->next->v) >= ((temp2->next->v) + *p)) {
				num = (temp1->next->v - temp2->next->v - *p);
			}
			else {
				num = 10 - temp2->next->v + temp1->next->v - *p;
				*(++p) = 1;                                //记录退值后，返回当前数位
				p--;
			}

			*p = num;
			p++;

			if (temp1->next != end1) {                     //在下一位存在的情况下，移到下一位
				temp1 = temp1->next;
			}
			if (temp2->next != end2) {
				temp2 = temp2->next;
			}

		}
		char* l = new char[newlen + 1];                    //构成字符串数组
		for (i = 0; i < newlen; i++) {
			l[i] = char(l3[newlen - 1 - i] + 48);
		}
		l[newlen] = '\0';
		list* list00 = new list(l);
		delete []l3;
		delete []l;
		return  list00;
	}
}

list* list::operator*(list* list2) {   
	op = 1;
	if ((list2->tail->front->v == ('-' - 48)) && (tail->front->v == ('-' - 48))) {
		list* list3 = new list(this);             // 3对1，4对2
		node* temp0 = list3->tail->front;         //两数皆负，转为绝对值相乘，结果为正
		temp0->front->next = list3->tail;
		list3->tail->front = temp0->front;
		list3->len--;

		list* list4 = new list(list2);             //深复制 3对1，4对2
		node* temp1 = list4->tail->front;
		temp1->front->next = list4->tail;
		list4->tail->front = temp1->front;
		list4->len--;

		list* list00 = list3->operator*(list4);
		delete list3;
		delete list4;
		return  list00;
	}
	else if (list2->tail->front->v == ('-' - 48)) {
		list* list3 = new list(list2);             //其中一个数为负，转为绝对值相乘，取负号
		node* temp = list3->tail->front;
		temp->front->next = list3->tail;
		list3->tail->front = temp->front;
		list3->len--;

		list* list00 = operator*(list3);
		op = 0;		
		delete list3;
		return  list00;
	}
	else if (tail->front->v == ('-' - 48)) {
		list* list3 = new list(this);             
		node* temp = list3->tail->front;
		temp->front->next = list3->tail;
		list3->tail->front = temp->front;
		list3->len--;

		list* list00 = list3->operator*(list2);
		op = 0;
		delete list3;
		return  list00;
	}
	else {
		node* temp1 = head;
		node* temp2 = list2->head;
		int newlen;
		int* p = new int[newlen = (len + list2->len)];
		int num, i;
		for (i = 0; i < newlen; i++) {                      //置最终值数组元素都为0
			p[i] = 0;
		}

		int* l3 = p;                                        //保存当前P指向位置
		int* l4 = p;                                        //保存当前P指向位置,且位置不变
		while (temp1->next != tail) {                       // 运算，存储计算所得的低位，运算值的进值存在下一位上,进位可以为两位数
			while (temp2->next != list2->tail) {            //算出第一个数与第二个数每一位对应的乘积结果
				num = (temp1->next->v) * (temp2->next->v) + *p;
				*p = num % 10;
				*(++p) += num / 10;
				temp2 = temp2->next;
			}
			p = ++l3;                                       //乘下一位时最低位要进一位		
			temp2 = list2->head;
			temp1 = temp1->next;
		}

		char* l = new char[newlen + 1];                    //构成字符串数组
		for (i = 0; i < newlen; i++) {
			l[i] = char(l4[newlen - 1 - i] + 48);
		}
		l[newlen] = '\0';                                  //构成字符串数组
		list* list00 = new list(l);
		delete []l4;
		delete []l;
		return  list00;
	}
}

void list::print() {
	node* temp = tail;
	int counter = 0;                                   //判断已经输出了多少数
	int s = 0;                                         //判断0为开头还是数中，开头跳过，数中保留。默认为开头，数中为1
	if (op == 0){ cout << '-'; op = 1;}                //判断正负号
	while (temp->front != head) {
		if (s == 0 && temp->front->v == 0 && len!=1) { temp = temp->front; len--;  continue; }     	
		else {                                         //若计算数据第一位为0，跳过，长度减1。若结果为0，不变化
			s = 1;
			cout << temp->front->v;
			counter++;
			temp = temp->front;
			if ((len - counter) % 4 == 0) cout << " ";  //判断是否输出空格
		}		
	}
	cout << endl;                                       //输出完毕，换行
}

int main()
{
	//list1为链表，list2为链表指针
	char a[200];
	cout << "输入第一位计算数" << endl; 
	cin.getline(a, pow(2, 24),'\n');                    //getline参数只能为数组
	char* p = a;
	list list1 = list(p);
	
	cout << "输入第二位计算数" << endl;
	cin.getline(a, pow(2, 24),'\n');
	char* q = a; 	
	list* list2 =new list(q);
	
	cout << "输出结果+" << endl;
	list1.operator+(list2)->print();

	cout << "输出结果-" << endl;
	list1.operator-(list2)->print();

	cout << "输出结果*" << endl;
	list1.operator*(list2)->print();

	delete list2;
	return 0;
}

