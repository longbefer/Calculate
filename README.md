# 计算器
这是关于数据结构的课程设计，利用栈实现四则运算功能，普通的计算器而已。。。
本应用程序经过Visual Studio 2019运行通过，其中参考了百度某回答（改了改，感觉我的比那个差。。。而且可能有没考虑到的地方（汗））应该一般没问题，但是1--1被认为是1-（-1）这个我不想改了，感觉这个还好吧。。。只能进行简单的四则运算，不能代入变量求值或者三角函数什么的。。。等之后有了想法之后再改吧。。。
程序仅在windows 10 运行通过，应该在Linux等平台也可以通过吧。。。

本程序基于栈，利用模板创建了两个栈：操作栈和数字栈，经过对程序的修改，可以较为准确的得出答案（在小数部分可能有丢失，这个我不想改了）。
其中，去除栈所定义的函数外，其他函数主要包括：1，判断是否为数字（这里把小数点也判断进去了）；2，将char数组转换成数字（没做太多处理，可能会有问题，但是在本程序中应该没有）；3，优先级的定义（老师讲的，但这样看起来好麻烦，不改了）；4，对数据的操作（这里面的hasNum真麻烦，希望可以改改。。。）；5，主要运算函数（大部分用来纠正可能出现的问题）

本程序经过了第二次较大更改，将main函数中的函数进行了大部分的分解，当然冗余肯定不少，但我不知道啊。。。

# Calculator
This is a calculate by using stack.
This file is only running in visual studio 2019 prview,maybe cannot running in visual studio 2010,please noted.And i found these answer in internet,but change some,it only doing "normal arithmetic".(smile) maybe something bad...

This application is base on stack,include operatoar stack and number stack.I modify most of codes,you can see the different between the last one and the first one.
