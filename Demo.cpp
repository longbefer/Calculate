#include <iostream>
#define SIZE 30
#define MAXNUM 9
using namespace std;
template <typename T> struct Stack {
	T* top;
	T* base;
};
typedef Stack<double> NumList;
typedef Stack<char> OperaList;
template <typename T> int initList(Stack<T>& S) {
	S.base = new T[SIZE];
	if (!S.base)
		exit(0);
	S.top = S.base;
	*S.top = *S.base = 0; //����
	return 1;
}
template <typename T> int push(Stack<T>& S, T ele) {
	if (S.top - S.base == SIZE)
		return 0; //ջ��
	*S.top++ = ele;
	return 1;
}
template <typename T> int pop(Stack<T> & S) {
	if (S.top == S.base)
		return 0; //ջ��
	--S.top;
	return 1;
}
template <typename T> int pop(Stack<T> & S, T & ele) {
	if (S.top == S.base)
		return 0;     //ջ��
	ele = *--S.top; //����ɾ����ֵ
	return 1;
}
int inPrior(char ele) //��ջ�ڵ���������ȼ�
{
	switch (ele) {
	case '+':
	case '-':
		return 2;
	case '*':
	case '/':
		return 3;
	case '(':
		return 1; //ջ�ڲ����棩���������꣨���ڵĹ�ʽ��ɾ����
	default:
		return 0;
	}
}
int outPrior(char ele) //��ջ�����������ȼ�
{
	switch (ele) {
	case '(':
		return 4;
	case '*':
	case '/':
		return 3;
	case '+':
	case '-':
		return 2;
	case ')':
		return 1;
	}
}
double calcu(double a, char opera, double b) {
	switch (opera) {
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	}
}
template <typename T> void show(Stack<T> S) {
	Stack<T> Te = S;
	while (Te.base != Te.top)
		cout << *--Te.top << " ";
	cout << endl;
}
bool hasLeft(OperaList S) {
	OperaList Te = S;
	while (Te.base != Te.top--)
		if (*Te.top == '(' || *Te.top == ')') //����Ľ�����ջ
			return true;
	return false;
}
int main() {
	OperaList opera; //����ջ
	NumList num;     //����ջ
	initList(opera);
	initList(num); //��ʼ��ջ
	char formula[SIZE] = { '\0' };
	cout << "�����빫ʽ��";
	cin >> formula;
	int length = strlen(formula); //���빫ʽ�ĳ���
	int fli = 0, tmj = 0;         //ָ������ĸ��������㿪ʼ
	double Num, newNum;           //�����ǰ������
	char ope;                     //������
	bool hasNum = false;          //������ǰ����������
	while (1) {
		if (isdigit(formula[fli])) //�Ƿ�Ϊ����
		{
			hasNum = true;
			char* temp = new char[MAXNUM]; //�洢���ֵ���ʱ����
			while (isdigit(formula[fli]))  //�õ�����
				temp[tmj++] = formula[fli++];
			Num = atof(temp); //��char����ת��Ϊdouble����
			delete[] temp;
			tmj = 0;
			if (!push(num, Num))
				cout << "ջ��" << endl, exit(0);
			if (fli == length)
				break;
			if (formula[fli] == '(') {
				cout << "���ʽ�������ֺ��������";
				return 0;
			} //�ų�3��4+5�������
		}
		else {
			char charNum = formula[fli];
			if (charNum == '+' || charNum == '-' || charNum == '*' ||
				charNum == '/' || charNum == '(' || charNum == ')') //�ж��Ƿ�Ϊ�����
			{
				if (fli == length - 1 && charNum != ')') {
					cout << "����Ĺ�ʽ���������������β��";
					return 0;
				}
				if (!hasNum) {
					if (charNum == '-' || charNum == '+') {
						push(num, 0.0);
						push(opera, charNum);
					} //��������
					if (charNum == '*' || charNum == '/' || charNum == ')') {
						cout << "��ʽ����";
						return 0;
					} //�ų���������*����/�����Ĺ�ʽ
					if (charNum == '(')
						push(opera, charNum);
					fli++; //�ƶ�Ϊ��һ����
				}        //����Ϊ���ֺ�û������ͣ�-9)�ȵĽ���취
				else {
					hasNum = false;
					if (inPrior(*(opera.top - 1)) <
						outPrior(charNum))         //ջ�����ȼ�����ջ��
						push(opera, formula[fli++]); //��������������ջ
					else {
						if (charNum == ')' && *(opera.top - 1) == '(') {
							pop(opera);
							hasNum = true; //��Ϊ)��ɾ���Լ�����һ������
							if (fli == length - 1)
								break;
							else
								fli++;
						}
						else {
							newNum = calcu(*(num.top - 2), *(opera.top - 1),
								*(num.top - 1)); //����
							pop(opera);                     //��������
							pop(num);
							pop(num);          //�����������
							push(num, newNum); //���µ�����ѹ��ջ
							hasNum = true;     // push(opera, formula[fli++]);
						}
					}
					if (fli > length - 1)
						break;
				}
			}
			else {
				cout << "���ʽ����δ֪����";
				return 0;
			}
		}
	} //�����ʣ�����(������������Ž�βʱ����������������û�����ŵ���������
	while (opera.top != opera.base) {
		if (hasLeft(opera)) {
			cout << "���ʽ�ж�������";
			return 0;
		}
		pop(num, Num);                    //ȡ����һ����
		pop(num, newNum);                 //ȡ��ǰһ����
		pop(opera, ope);                  //ȡ��������
		newNum = calcu(newNum, ope, Num); //����
		push(num, newNum);                //���µ�����ѹ��ջ
	}
	cout << *num.base << endl;
	system("pause>nul");
	return 0;
}