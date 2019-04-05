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
bool push(Stack<T>& S, T var)//��ջ
{
	if ((S.top - S.base) == S.size) return false;
	*S.top++ = var;
	return true;
}

template <typename T>
bool pop(Stack<T>& S, T& var)//��ջ
{
	if (S.base == S.top) return false;
	var = *--S.top;
	return true;
}

template <typename T>
bool pop(Stack<T>& S)//��ջ
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
T getTop(Stack<T> S)//ֱ��ȡ�÷���ֵ
{
	if (S.base == S.top) return '#';
	return *(S.top - 1);
}

char popr(Stack<char> inS, char outOpera)//�ж����ȼ�
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
		else if (inTop == '(') return ERROR;//�������ࣨ
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
	double integer = 0;//����
	double decimal = 0;//С��
	double decTimes;//С������
	int decTime = 1;//С������
	bool hasDec = false;//�Ƿ���С����
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

int poprCal(Stack<double>& num, Stack<char>& in, char out, bool& hasNum)//inΪջ�ڵĲ�������outΪջ��Ĳ�����(hasNum����������)
{
	double newNum;
	char prio = popr(in, out);
	switch (prio)
	{
	case '>'://ջ�ڴ���ջ��
	{
		newNum = cal(num, in);
		pop(in);//��������
		pop(num); pop(num);//�����������
		push(num, newNum); //���µ�����ѹ��ջ
		hasNum = true;//������󣬱�������
		return false;//������һλ
	}
	case '<'://ջ��С��ջ�⣬��ջ���������ջ
	{
		push(in, out);
		hasNum = false;//û���㣬ǰ��λ������
		return true;//�����һλ
	}
	case '=':
	{
		pop(in);
		hasNum = true;//���Ŵ���������
		return true;//�Ƿ������һλ
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
			int dec = 0;//С�������
			while (isNum(formula[fli]))
			{
				if (formula[fli] == '.')
					dec++;
				if (dec > 1)
				{
					cout << "ֻ��ӵ��һ��С����" << endl;
					return ERROR;
				}
				temp[temj++] = formula[fli++];
			}
			temp[temj] = '\0';
			Num = toNum(temp);
			push(num, Num);
			delete[] temp;
			if (formula[fli] == '(') {
				cout << "���ʽ�������ֺ�û�������";
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
					cout << "����Ĺ�ʽ���������������β��";
					return ERROR;
				}
				if (!hasNum) {
					if (charNum == '-' || charNum == '+') {
						push(num, 0.0);
						push(opera, charNum);
					} //��������
					if (charNum == '*' || charNum == '/' || charNum == ')') {
						cout << "��ʽ����";
						return ERROR;
					} //�ų���������*����/�����Ĺ�ʽ
					if (charNum == '(')
						push(opera, charNum);
					fli++; //�ƶ�Ϊ��һ����
				}        //����Ϊ���ֺ�û������ͣ�-9)�ȵĽ���취
				else {
					hasNum = false;
					int cal = poprCal(num, opera, charNum, hasNum);
					if (cal == ERROR)
					{
						cout << "����Ԥ֪�Ĵ���";
						return ERROR;
					}
					else if (cal) fli++;
				}
			}
			else
			{
				if (charNum == '.')
				{
					cout << "С����ǰ����������";
					return ERROR;
				}
				else
				{
					cout << "����δ֪�ַ�";
					return ERROR;
				}
			}
		}
		if (fli == length)
		{
			while (opera.base != opera.top)
				if (poprCal(num, opera, '#', hasNum) == ERROR)//����
				{
					cout << "����Ԥ֪�Ĵ���";
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