
/*ʹ��˵������Դ��������VS2019ʵ�֣�ͨ�����������ȡ��������
����ʹ�ã����д��룬��������ʾ�����һ����������������Ϊ����������ͨ���������룬�س�������
��������ʾ����ڶ�������ͨ���������룬�س�������ͬʱ��������������Ӽ�������Ľ��
*/

#include<iostream>
#include<cmath>
using namespace std;

int op = 1;                                         //���ţ�һ��Ϊ1���������Ϊ��Ϊ0�������-��.

class list;                                         //˫������
class node {                                        //ÿ�����洢һ������front��next
    int v;                                          //��ֵ                                        
	node* next;
	node* front;
public:
    node();
	node(char a);                                   //���ַ�תΪ��ֵ����ȥ
	node(int a);
	~node();
	friend class list;                              //ʹ������ʹ��node��
};

node::node() {                                      //��ֵΪ0��ǰ��ָ��Ĭ��Ϊ��
	v = 0;
	next = front = NULL;
}

node::node(char a) {                                //���ַ�����ȥ�������ֵ�洢��node��ʹ��ǰ��ָ�붼Ϊ��
	v = int(a) -48 ;
	next = front = NULL;	
}

node::node(int a) {                                //���ַ�����ȥ�������ֵ�洢��node��ʹ��ǰ��ָ�붼Ϊ��
	v = a;
	next = front = NULL;
}

node::~node() {                                      //��ֵΪ0��ǰ��ָ����Ϊ��
	v = 0;
	next = front = NULL;
}

class list {
                                             //ͷβָ�룬ͷָ��ֻ��NEXT��βָ��ֻ��FRONT.ͷβָ�벻�洢��ʵ���������
	node* head;
	node* tail;
	int len;                                        //ʵ�ʳ��ȣ�������ͷβָ�룩
public:
	list();
	list(char* a);                                  //���ַ�������ȥ
	list(list* l);
	~list();
	list* operator+(list* list2);                   //�ӷ�
	list* operator-(list* list2);                   //����
	list* operator*(list* list2);                   //�˷�
	void print();                                   //�������
};

list::list() {
	head = new node();                               //����ͷβָ�룬��ָ���
	tail = new node();
	len = 0;                                        //���ȳ�ʼΪ0
}

list::list(char* a) {                               //���ַ�������ȥ 
	len = 0;
	head = new node();
	tail = new node();
	node* temp0=tail;                               //temp0Ϊ��ǰ������ĺ�һ��,��һ�����Ϊ��λ�����ӵ�λ����λ�洢
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

list::list(list* l) {                               //���ַ�������ȥ 
	len = l->len;
	head = new node();
	tail = new node();
	node* temp0 = l->head->next;                               //tempΪ��ǰ������,temp0 Ϊ��Ӧlλ�ý��,temp1Ϊ��ǰ���ǰһ��
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
		list* list3 = new list(this);             //��� 3��1��4��2
		node* temp0 = list3->tail->front;
		temp0->front->next = list3->tail;
		list3->tail->front = temp0->front;
		list3->len--;

		list* list4 = new list(list2);             
		node* temp1 = list4->tail->front;
		temp1->front->next = list4->tail;
		list4->tail->front = temp1->front;
		list4->len--;

		list* list00 = list3->operator+(list4);  //ȡ����ֵ��ӣ�����Ϊ��
		op = 0;
		delete list3;
		delete list4;
		return  list00;
	}
	else if(list2->tail->front->v == ('-' - 48)){
		list* list3 = new list(list2);             //�ڶ�����Ϊ�����õ�һ�������ڶ���������ֵ
		node* temp=list3->tail->front;
		temp->front->next = list3->tail;
		list3->tail->front = temp->front;
		list3->len--;
		
		list* list00 = operator-(list3);
		delete list3;
		return  list00;
	}
	else if (tail->front->v == ('-' - 48)) {       //��һ����Ϊ����ת�ɵڶ������ӵ�һ����
		list* list00 = list2->operator+(this);
		return  list00;
	}
	else {                                         //���������������ӷ�
		node* temp1 = head;
		node* temp2 = list2->head;
		int newlen;
		int* p = new int[newlen = (len > list2->len ? (len + 1) : (list2->len + 1))];
		int num, i;                                    //��¼ÿһλ����ĵ�ǰֵ
		for (i = 0; i < newlen; i++) {                  //������ֵ����Ԫ�ض�Ϊ0
			p[i] = 0;
		}

		int* l3 = p;                                       //���浱ǰPָ��λ��

		while ((temp1->next != tail) || (temp2->next != list2->tail)) {
			num = (temp1->next->v) + (temp2->next->v) + *p;
			*p = num % 10;                                 // ���㣬�洢�������õĵ�λ������ֵ�Ľ�ֵ������һλ��
			*(++p) = num / 10;
			if (temp1->next != tail) {                     //����һλ���ڵ�����£��Ƶ���һλ
				temp1 = temp1->next;
			}
			if (temp2->next != list2->tail) {
				temp2 = temp2->next;
			}
		}
		char* l = new char[newlen + 1];                      //�����ַ�������
		for (i = 0; i < newlen; i++) {
			l[i] = char(l3[newlen - 1 - i] + 48);
		}
		l[newlen] = '\0';                                //�����ַ�������
		list* list00 = new list(l);
		delete []l3;
		delete []l;
		return  list00;
	}	
}

list* list::operator-(list* list2) { 
	op = 1;
	if ((list2->tail->front->v == ('-' - 48)) && (tail->front->v == ('-' - 48))) {
		//�����Ը����ѵڶ���ת������һ������,��ɵڶ���������ֵ�ӵ�һ����
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
		list* list3 = new list(list2);             //�ڶ��������ģ�תΪ����ֵ���
		node* temp = list3->tail->front;
		temp->front->next = list3->tail;
		list3->tail->front = temp->front;
		list3->len--;

		list* list00 = operator+(list3);	
		delete list3;
		return  list00;
	}
	else if (tail->front->v == ('-' - 48)) {
		list* list3 = new list(this);             //��һ�������ģ�תΪ����ֵ���ȡ���š�
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
		int newlen;                                      //������������������
		int s = 0;                                       //�����жϷ��ţ�+����һ������Ϊ1��-Ϊ-1��0��ʾû�Ƚϣ�����ĿǰΪֹ��λֵ��ȡ�

		if (len < list2->len) { s = -1; op = 0; }        //�жϷ���
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
				                            //���������
				list* list00 = new list(p);
				delete []p;
				return  list00;
			}
		}                                                //�����ж���ϣ��������������

		node* temp1;
		node* temp2;
		node* end1;
		node* end2;

		//�����������temp1��С�ĸ�temp2
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
		int num, i;                                       //��¼ÿһλ����ĵ�ǰֵ
		for (i = 0; i < newlen; i++) {                    //������ֵ����Ԫ�ض�Ϊ0
			p[i] = 0;
		}

		int* l3 = p;                                       //���浱ǰPָ��λ��

		// ���㣬�洢�������õĵ�λ������ֵ����ֵ������һλ��,��ֵ��Ϊ��
		while (temp1->next != end1 || temp2->next != end2)
		{
			if ((temp1->next->v) >= ((temp2->next->v) + *p)) {
				num = (temp1->next->v - temp2->next->v - *p);
			}
			else {
				num = 10 - temp2->next->v + temp1->next->v - *p;
				*(++p) = 1;                                //��¼��ֵ�󣬷��ص�ǰ��λ
				p--;
			}

			*p = num;
			p++;

			if (temp1->next != end1) {                     //����һλ���ڵ�����£��Ƶ���һλ
				temp1 = temp1->next;
			}
			if (temp2->next != end2) {
				temp2 = temp2->next;
			}

		}
		char* l = new char[newlen + 1];                    //�����ַ�������
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
		list* list3 = new list(this);             // 3��1��4��2
		node* temp0 = list3->tail->front;         //�����Ը���תΪ����ֵ��ˣ����Ϊ��
		temp0->front->next = list3->tail;
		list3->tail->front = temp0->front;
		list3->len--;

		list* list4 = new list(list2);             //��� 3��1��4��2
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
		list* list3 = new list(list2);             //����һ����Ϊ����תΪ����ֵ��ˣ�ȡ����
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
		for (i = 0; i < newlen; i++) {                      //������ֵ����Ԫ�ض�Ϊ0
			p[i] = 0;
		}

		int* l3 = p;                                        //���浱ǰPָ��λ��
		int* l4 = p;                                        //���浱ǰPָ��λ��,��λ�ò���
		while (temp1->next != tail) {                       // ���㣬�洢�������õĵ�λ������ֵ�Ľ�ֵ������һλ��,��λ����Ϊ��λ��
			while (temp2->next != list2->tail) {            //�����һ������ڶ�����ÿһλ��Ӧ�ĳ˻����
				num = (temp1->next->v) * (temp2->next->v) + *p;
				*p = num % 10;
				*(++p) += num / 10;
				temp2 = temp2->next;
			}
			p = ++l3;                                       //����һλʱ���λҪ��һλ		
			temp2 = list2->head;
			temp1 = temp1->next;
		}

		char* l = new char[newlen + 1];                    //�����ַ�������
		for (i = 0; i < newlen; i++) {
			l[i] = char(l4[newlen - 1 - i] + 48);
		}
		l[newlen] = '\0';                                  //�����ַ�������
		list* list00 = new list(l);
		delete []l4;
		delete []l;
		return  list00;
	}
}

void list::print() {
	node* temp = tail;
	int counter = 0;                                   //�ж��Ѿ�����˶�����
	int s = 0;                                         //�ж�0Ϊ��ͷ�������У���ͷ���������б�����Ĭ��Ϊ��ͷ������Ϊ1
	if (op == 0){ cout << '-'; op = 1;}                //�ж�������
	while (temp->front != head) {
		if (s == 0 && temp->front->v == 0 && len!=1) { temp = temp->front; len--;  continue; }     	
		else {                                         //���������ݵ�һλΪ0�����������ȼ�1�������Ϊ0�����仯
			s = 1;
			cout << temp->front->v;
			counter++;
			temp = temp->front;
			if ((len - counter) % 4 == 0) cout << " ";  //�ж��Ƿ�����ո�
		}		
	}
	cout << endl;                                       //�����ϣ�����
}

int main()
{
	//list1Ϊ����list2Ϊ����ָ��
	char a[200];
	cout << "�����һλ������" << endl; 
	cin.getline(a, pow(2, 24),'\n');                    //getline����ֻ��Ϊ����
	char* p = a;
	list list1 = list(p);
	
	cout << "����ڶ�λ������" << endl;
	cin.getline(a, pow(2, 24),'\n');
	char* q = a; 	
	list* list2 =new list(q);
	
	cout << "������+" << endl;
	list1.operator+(list2)->print();

	cout << "������-" << endl;
	list1.operator-(list2)->print();

	cout << "������*" << endl;
	list1.operator*(list2)->print();

	delete list2;
	return 0;
}

