#include <iostream>
using namespace std;
#define MAXSIZE 30
#define NUMSIZE 9
#define ERROR -1
template <typename T>
struct Stack {
	T* base;
	T* top;
	int size;
};
typedef Stack<char> OperaStack;
typedef Stack<double> NumStack;

template <typename T>
void initStack(Stack<T>& S)
{
	S.base = S.top = new T[MAXSIZE];
	if (!S.base) exit(OVERFLOW);
	S.size = MAXSIZE;
}

template <typename T>
bool push(Stack<T>& S, T var)//入栈
{
	if ((S.top - S.base) == S.size) return false;
	*S.top++ = var;
	return true;
}

template <typename T>
bool pop(Stack<T>& S, T& var)//出栈
{
	if (S.base == S.top) return false;
	var = *--S.top;
	return true;
}

template <typename T>
bool pop(Stack<T>& S)//出栈
{
	if (S.base == S.top) return false;
	--S.top;
	return true;
}

template <typename T>
bool getTop(Stack<T> S, T& var)
{
	if (S.base == S.top) return false;
	var = *S.top - 1;
	return true;
}

template <typename T>
T getTop(Stack<T> S)//直接取得返回值
{
	if (S.base == S.top) return '#';
	return *(S.top - 1);
}

char popr(Stack<char> inS, char outOpera)//判断优先级
{
	char inTop = getTop(inS);
	switch (outOpera)
	{
	case '+':
	case '-':
		if (inTop == '+' || inTop == '-' ||
			inTop == '*' || inTop == '/') return '>';
		else if (inTop == '#' || inTop == '(') return '<';
		else return ERROR;
	case '*':
	case '/':
		if (inTop == '+' || inTop == '-' || inTop == '(' || inTop == '#')
			return '<';
		else if (inTop == '*' || inTop == '/') return '>';
		else return ERROR;
	case '(':
		if (inTop == '+' || inTop == '-' || inTop == '*' || 
			inTop == '/' || inTop == '(' || inTop == '#') return '<';
	case ')':
		if (inTop == '+' || inTop == '-' ||
			inTop == '*' || inTop == '/') return '>';
		else if (inTop == '(') return '=';
		else return ERROR;
	case '#':
		if (inTop == '+' || inTop == '-' || inTop == '*' ||
			inTop == '/' || inTop == '#') return '>';
		else if (inTop == '(') return ERROR;//表明多余（
		else return ERROR;
	}
}

double cal(Stack<double>& S1, Stack<char>& Ca)
{
	char opera = getTop(Ca);
	double nextNum = getTop(S1);
	double prorNum = *(S1.top - 2);//Attation
	switch (opera)
	{
	case '+':return prorNum + nextNum;
	case '-':return prorNum - nextNum;
	case '*':return prorNum * nextNum;
	case '/':return prorNum / nextNum;
	}
	return ERROR;
}

double cal(double num1, char opera, double num2)
{
	switch (opera)
	{
	case '+':return num1 + num2;
	case '-':return num1 + num2;
	case '*':return num1 + num2;
	case '/':return num1 + num2;
	}
	return ERROR;
}

bool isNum(char Num)
{
	if ((Num - '0' >= 0 && Num - '0' <= 9) || Num == '.')
		return true;
	else return false;
}

double toNum(const char* Num)
{
	int realNum;
	int length = strlen(Num);
	double integer = 0;//整数
	double decimal = 0;//小数
	double decTimes;//小数倍数
	int decTime = 1;//小数次数
	bool hasDec = false;//是否有小数点
	int i = 0;
	while (1)
	{
		if (Num[i] == '.')
		{
			hasDec = true;
			i++;
		}
		realNum = Num[i] - '0';
		if (!hasDec && realNum >= 0 && realNum <= 9)
		{
			integer = 10 * integer + realNum;
			i++;
		}
		else
		{
			decTimes = pow(0.1, decTime++);
			decimal = decimal + decTimes * realNum;
			i++;
		}
		if (i == length) break;
	}
	return integer + decimal;
}

int poprCal(Stack<double>& num, Stack<char>& in, char out, bool& hasNum)//in为栈内的操作符，out为栈外的操作符(hasNum不参与运算)
{
	double newNum;
	char prio = popr(in, out);
	switch (prio)
	{
	case '>'://栈内大于栈外
	{
		newNum = cal(num, in);
		pop(in);//清除运算符
		pop(num); pop(num);//清除数字两个
		push(num, newNum); //将新的数字压入栈
		hasNum = true;//运算完后，保留数字
		return false;//不后移一位
	}
	case '<'://栈内小于栈外，将栈外操作符入栈
	{
		push(in, out);
		hasNum = false;//没运算，前面位操作符
		return true;//向后移一位
	}
	case '=':
	{
		pop(in);
		hasNum = true;//括号代表者数字
		return true;//是否向后移一位
	}
	default:
	case ERROR:return ERROR;
	}
}

double Running(const char* formula)
{
	OperaStack opera;
	NumStack num;
	initStack(opera); 
	initStack(num);
	int fli = 0;
	int length = strlen(formula);
	double Num;
	bool hasNum = false;
	while (1)
	{	
		if (isNum(formula[fli]) && formula[fli] != '.')
		{
			hasNum = true;
			char* temp = new char[NUMSIZE];
			int temj = 0;
			int dec = 0;//小数点个数
			while (isNum(formula[fli]))
			{
				if (formula[fli] == '.')
					dec++;
				if (dec > 1)
				{
					cout << "只能拥有一个小数点" << endl;
					return ERROR;
				}
				temp[temj++] = formula[fli++];
			}
			temp[temj] = '\0';
			Num = toNum(temp);
			push(num, Num);
			delete[] temp;
			if (formula[fli] == '(') {
				cout << "表达式错误！数字后没有运算符";
				return ERROR;
			}
		}
		else
		{
			char charNum = formula[fli];
			if (charNum == '+' || charNum == '-' || charNum == '*' ||
				charNum == '/' || charNum == '(' || charNum == ')')
			{
				if (fli == length - 1 && charNum != ')') {
					cout << "错误的公式，不能以运算符结尾。";
					return ERROR;
				}
				if (!hasNum) {
					if (charNum == '-' || charNum == '+') {
						push(num, 0.0);
						push(opera, charNum);
					} //负号运算
					if (charNum == '*' || charNum == '/' || charNum == ')') {
						cout << "公式错误";
						return ERROR;
					} //排除（）、（*、（/这样的公式
					if (charNum == '(')
						push(opera, charNum);
					fli++; //移动为下一符号
				}        //以上为数字后没运算符和（-9)等的解决办法
				else {
					hasNum = false;
					int cal = poprCal(num, opera, charNum, hasNum);
					if (cal == ERROR)
					{
						cout << "不可预知的错误";
						return ERROR;
					}
					else if (cal) fli++;
				}
			}
			else
			{
				if (charNum == '.')
				{
					cout << "小数点前必须有数字";
					return ERROR;
				}
				else
				{
					cout << "出现未知字符";
					return ERROR;
				}
			}
		}
		if (fli == length)
		{
			while (opera.base != opera.top)
				if (poprCal(num, opera, '#', hasNum) == ERROR)//结束
				{
					cout << "不可预知的错误";
					return ERROR;
				}
			return *num.base;
		}
	}
}

int main(void)
{
	char formula[MAXSIZE];
	cin >> formula;
	//cout << toNum(formula);
	double reslut = Running(formula);
	cout << reslut;
	return 0;
}