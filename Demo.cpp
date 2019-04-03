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
	*S.top = *S.base = 0; //保持
	return 1;
}
template <typename T> int push(Stack<T>& S, T ele) {
	if (S.top - S.base == SIZE)
		return 0; //栈满
	*S.top++ = ele;
	return 1;
}
template <typename T> int pop(Stack<T> & S) {
	if (S.top == S.base)
		return 0; //栈空
	--S.top;
	return 1;
}
template <typename T> int pop(Stack<T> & S, T & ele) {
	if (S.top == S.base)
		return 0;     //栈空
	ele = *--S.top; //返回删除的值
	return 1;
}
int inPrior(char ele) //在栈内的运算符优先级
{
	switch (ele) {
	case '+':
	case '-':
		return 2;
	case '*':
	case '/':
		return 3;
	case '(':
		return 1; //栈内不保存），在运算完（）内的公式是删除掉
	default:
		return 0;
	}
}
int outPrior(char ele) //在栈外的运算符优先级
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
		if (*Te.top == '(' || *Te.top == ')') //错误的将）入栈
			return true;
	return false;
}
int main() {
	OperaList opera; //操作栈
	NumList num;     //数字栈
	initList(opera);
	initList(num); //初始化栈
	char formula[SIZE] = { '\0' };
	cout << "请输入公式：";
	cin >> formula;
	int length = strlen(formula); //输入公式的长度
	int fli = 0, tmj = 0;         //指向数组的个数，从零开始
	double Num, newNum;           //运算符前后数字
	char ope;                     //操作符
	bool hasNum = false;          //在运算前不存在数字
	while (1) {
		if (isdigit(formula[fli])) //是否为数字
		{
			hasNum = true;
			char* temp = new char[MAXNUM]; //存储数字的临时数组
			while (isdigit(formula[fli]))  //得到数字
				temp[tmj++] = formula[fli++];
			Num = atof(temp); //将char数组转换为double数字
			delete[] temp;
			tmj = 0;
			if (!push(num, Num))
				cout << "栈满" << endl, exit(0);
			if (fli == length)
				break;
			if (formula[fli] == '(') {
				cout << "表达式错误！数字后无运算符";
				return 0;
			} //排除3（4+5）等情况
		}
		else {
			char charNum = formula[fli];
			if (charNum == '+' || charNum == '-' || charNum == '*' ||
				charNum == '/' || charNum == '(' || charNum == ')') //判断是否为运算符
			{
				if (fli == length - 1 && charNum != ')') {
					cout << "错误的公式，不能以运算符结尾。";
					return 0;
				}
				if (!hasNum) {
					if (charNum == '-' || charNum == '+') {
						push(num, 0.0);
						push(opera, charNum);
					} //负号运算
					if (charNum == '*' || charNum == '/' || charNum == ')') {
						cout << "公式错误";
						return 0;
					} //排除（）、（*、（/这样的公式
					if (charNum == '(')
						push(opera, charNum);
					fli++; //移动为下一符号
				}        //以上为数字后没运算符和（-9)等的解决办法
				else {
					hasNum = false;
					if (inPrior(*(opera.top - 1)) <
						outPrior(charNum))         //栈内优先级低于栈外
						push(opera, formula[fli++]); //将运算符进入操作栈
					else {
						if (charNum == ')' && *(opera.top - 1) == '(') {
							pop(opera);
							hasNum = true; //若为)则删掉自己和上一个括号
							if (fli == length - 1)
								break;
							else
								fli++;
						}
						else {
							newNum = calcu(*(num.top - 2), *(opera.top - 1),
								*(num.top - 1)); //计算
							pop(opera);                     //清除运算符
							pop(num);
							pop(num);          //清除数字两个
							push(num, newNum); //将新的数字压入栈
							hasNum = true;     // push(opera, formula[fli++]);
						}
					}
					if (fli > length - 1)
						break;
				}
			}
			else {
				cout << "表达式出现未知符号";
				return 0;
			}
		}
	} //最后有剩余计算(当最后不是以括号结尾时，会进入这里，或者是没有括号的四则运算
	while (opera.top != opera.base) {
		if (hasLeft(opera)) {
			cout << "表达式有多余括号";
			return 0;
		}
		pop(num, Num);                    //取出后一个数
		pop(num, newNum);                 //取出前一个数
		pop(opera, ope);                  //取出操作符
		newNum = calcu(newNum, ope, Num); //计算
		push(num, newNum);                //将新的数字压入栈
	}
	cout << *num.base << endl;
	system("pause>nul");
	return 0;
}