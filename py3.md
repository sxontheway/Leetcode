# Pythonic 风格
如何写出高效的python程序？
* 多使用`join`和`list`
    ```python
    # 不要这样：每加一次python就会创建开辟一块新内存
    s = 'line1\n'
    s += 'line2\n'

    # 最好这样
    l = ['line1', 'line2']
    s = '\n'.join(l)
    ```
* 避免对字符串使用 + 运算：    

    因为字符串是不可变对象，每次有新元素加入不可变对象时，Python都要分配新的内存，创建一个新的字符串和新的地址  
    ```python
    s1 = "my"
    msg = 'hello' + s1 + 'world'    # 不要这样
    msd = 'hello %s world' % s1     # 最好这样
    ```
* 多使用向量、矩阵式的编程思想:
    ```python
    a,b  = list("123"), list("456")

    # 最好这样
    c = ['(%s)%s' %(x, y) for x in a for y in b]

    # 不要这样
    c = []
    for x in a:
        for y in b:
            c.append('(' + x + ')' + y) # 对字符串进行 + 操作，低效  
    ```
* 使用 Generators: 不用一次返回所有项目

<br><br><br>

# Python 中的位运算
* 按位判断奇偶：`n&1 == 1   # n为奇数`
* 判断两数是否同正负：`a^b > 0  # 同号`
    *  原码，反码，补码  
    `正数补码 = 原码；负数补码 = 反码 +1，计算机中数都用反码表示`。负数的反码是符号位为1不变，其它位按位取反，这么做的目的是减一个数也可等效于加这个数的反码，加减运算统一用加法器电路就可解决。
    * 因为正数的符号位为0，负数的符号位为1，同号的两数异或后为正，异号的两数异或后为负
    * 在python中，查看数字的二进制源码：正数`bin(3)`,因为前面全为0；负数需要用 `bin(3 & 0xffffffff)`
* 两数相加
    ```
    def add(a, b):
        if b == 0: return a
        sum = a^b
        carry = (a&&b)<<1   # (a&&b)代表每一位是否需要进位，进位等于左移一位
        return add(sum, carry)  # 直到不需要进位位置
    ```
* 两数相除
    ```python
        def divide(self, dividend: int, divisor: int) -> int:
            if dividend == 0: return 0
            sign = -1 if dividend ^ divisor < 0 else 1    
            dived， divor = abs(dividend), abs(divisor)
            i, count = 1, 0
            while dived >= divor:   
                tmp, i = divor, 1
                while dived >= tmp:     # 每次先减一次，再将除数乘以二
                    dived -= tmp
                    count += i
                    i <<= 1
                    tmp <<= 1

            return (count if sign > 0 else -count)
    ```


<br><br><br>

# Python 中的数据结构
python中四种自带的数据结构（容器）：列表、元组、字典、集合  
常见线性数据结构：栈、队列、双端队列(deque)、循环队列、链表（单向、双向）  
常见非线性数据结构：树、图、堆、哈希表

---
## Python列表(List), 元组(tuple), 集合(set)
* 可以把元组理解为不能修改的列表，用 `()`表示。要修改元组只能用 `+=` 这种，这相当于重新产生了一个新的拼接后的元组对象，再绑定到了原变量上。
* 集合是剔除了重复元素的列表，用 `{}`表示: a = {1,2,3}, b = {"x": 1, "y": 2}，a是个集合，b是个字典   
集合set是不能用index的，一般用`.add(), .update(), .remove()`等方法  
集合set的`x in s`操作复杂度和dict相同，一般为O(1)，最坏为O(N) 
* 元组是可哈希对象；列表、集合是不可哈希对象。
```python
# 初始化列表
list1 = [0]*3   # 初始一维列表正确的方式 

list2 = [ [] for _ in range(3)]     # 初始化二维列表正确的方式
list2[0].append(1)  # 得到[[1], [], []]

list3 = [[]]*3
list3[0].append(1)  # 由于shared memory机制，会到[[1], [1], [1]]，不是想要的


# 列表字符串转换
a = list("abc") # ['a', 'b', 'c']
b = "".join(a)  # "abc"

# 列表拼接
c = [1, 2, 3]       
a += c          # ['a', 'b', 'c', 1, 2, 3]
a = [*a, *c]    # ['a', 'b', 'c', 1, 2, 3]

# 元组
d = 1,      # c = (1, ), 是个元组
d[0] = 2    # 报错，元组内元素不可修改
d += 2,     # d变为(1, 2)
e = 1       # d 是 int
```            
 
---

## Python字典 (Dict)  
> Python 字典和列表操作的时间复杂度: https://wiki.python.org/moin/TimeComplexity  
实现原理: https://www.cnblogs.com/guyannanfei/p/10930516.html   

* 字典内部实现  
Python2 dict的底层是依靠Hash Table实现的，使用`开放地址法`解决冲突。  
    * 冲突解决方法
        * 开放地址  
        当发生地址冲突时，按照某种方法继续探测哈希表中的其他存储单元，直到找到空位置为止。常见的开放地址思想的方法有线性探测再散列，二次探测再散列。  
        `对于利用开放地址法处理冲突所产生的哈希表中删除一个元素时需要谨慎，不能直接地删除，因为这样将会截断其他具有相同哈希地址的元素的查找地址，所以，通常采用设定一个特殊的标志以示该元素已被删除。 `
        * 链地址法  
        将所有关键字哈希值相同的记录都存在同一线性链表中，这样不需要占用其他的哈希地址，相同的哈希值在一条链表上，按顺序遍历就可以找到。
        * 再哈希法  
        这个方法是按顺序规定多个哈希函数，每次查询的时候按顺序调用哈希函数，调用到第一个为空的时候返回不存在，调用到此键的时候返回其值。 

* 字典操作的时间复杂度  
字典中 set, get, delete, in (收否包含某个元素) 四个操作平均时间复杂度均为 O(1)，最坏情况为 O(N)。  
* 字典与列表
    *  字典的键值只能为：可哈希对象  
    可哈希对象：str, tuple, objects  
    不可哈希对象：dict, list, set 
        ```python
        a = dict(a = 1, b = 2)  # dict的初始化
        a[('c', 'd')] = 3   # 正确，元组可哈希， a = {('c', 'd'): 3, 'a': 1, 'b': 2}
        a[['c', 'd']] = 3   # 错误，列表不可哈希
        a[{'c', 'd'}] = 3   # 错误，集合不可哈希
        ```
    * List中元素可以相同，dict的Key值不能相同，所以想把 [1,2,2,3] 这个list转化为 '以元素值为key，以index为value' 的字典时，字典中只有三个键值对。

---

## Collection模块
> https://docs.python.org/2/library/collections.html

collections模块自Python 2.4版本开始被引入，包含了dict、set、list、tuple以外的一些特殊的容器类型，分别是: 

|容器数据类型|描述|引入版本|
|--|--|--|
|namedtuple()|是一个factory function，返回值是元组的子类，元组内的元素被加上了名称|2.6|
|deque()|双端队列，支持 O(1) 的前插和后插，其余同列表 (列表前插复杂度是 O(N) )|2.4|
|Counter()|是字典的子类，用来统计可哈希对象出现的次数。其中元素作为key，其计数作为value|2.7|
|OrderedDict()|是字典的子类，会记录键值对的添加顺序，顺序不同的两个词典是不同的对象|2.7|
|defaultdict()|是字典的子类，输入参数为factory function，为不存在的键赋一个默认值，一般用于初始化字典|2.5|

* defaultdict()
    ```python
    from collections import defaultdict

    s = [('red', 1), ('blue', 2), ('red', 3), ('blue', 4), ('red', 1), ('blue', 4)]
    d = defaultdict(set)    # set()是一个工场函数，表示键的默认值为一个set
    for k, v in s:
    d[k].add(v)
    print(d)    # 输出 defaultdict(<class 'set'>, {'blue': {2, 4}, 'red': {1, 3}})

    words = ['hello', 'world', 'nice', 'world']
    #使用lambda来定义简单的函数
    counter = defaultdict(lambda: 0)    # 表示键的默认值为一个 0
    for kw in words:
    counter[kw] += 1
    ```

* Counter  
Counter的使用见Leetcode Q30
    ```python
    from collections import defaultdict

    # Counter创建
    c = Counter("abbccc")          # 可迭代对象创建
    c = Counter(h=1, l=3, o=2)          # 关键字创建
    c = Counter({'h':1,'l':3,'o':2})    # 字典创建
    c = Counter()                       # 空Counter类

    # Counter更新
    c = Counter("abbccc")  
    c.update("aa")      # 变为 Counter({'a': 3, 'c': 3, 'b': 2})
    print(c["a"])       # 输出 3
    ```
* namedtuple  
https://zhuanlan.zhihu.com/p/46187444 

---

## 链表：
一般结构为`一个头节点+数据节点`，以简化某些极端情况，例如删除列表的第一个数据节点。
* 删除一个单向链表的倒数第n个节点 (Leetcode Q19)：
    * 两次遍历法：第一次遍历得到链表长度，第二次遍历删除倒数第N个节点
    * 一次遍历法：使用双指针
        * 移动 q，直到 p 与 q 之间相隔的元素个数为 n
        * 同时移动 p 与 q，直到 q 指向的为 NULL
        * 将 p 的下一个节点指向下下个节点
    > 本质上，一个是单指针遍历两遍，另一个是双指针各遍历一遍，其实计算量上差别不大
    ```python
    def removeNthFromEnd(self, head: ListNode, n: int) -> ListNode:
        i = j = 0
        head0 = ListNode(-1) # 防止把第一个节点删除了
        head0.next = head
        p1 = p2 = head0
        while p1 and p2:
            # print(p1.val, p2.val, i, j)
            if p2.next == None:
                if j-i == n:
                    p1.next = p1.next.next
                    p2 = None
            else:
                p2 = p2.next
                j += 1
                if j-i > n:
                    p1 = p1.next
                    i += 1         
        return head0.next
    ```

* 将两个有序链表合成一个新的链表 (Leetcode Q21):
    ```python
    def merge2(l1: ListNode, l2: ListNode) -> ListNode:
        l3 = ListNode(-1)   # head
        p3 = l3
        while l1 and l2:
            if l1.val > l2.val:
                p3.next = l2
                l2 = l2.next
            else:
                p3.next = l1
                l1 = l1.next
            p3 = p3.next            
        if l1:  # p1还没到l1末尾
            p3.next = l1
        if l2: 
            p3.next = l2
        return l3.next
    ```
* 将K个有序链表合成一个新的链表 (Leetcode Q23)  
用分治法两两合并：4->2->1

---
## 队列和栈
在python中，队列和栈都可以通过list来手动实现：https://blog.csdn.net/henni_719/article/details/69941860 



<br><br><br>

# Python的其他特性
## itertools模块
---

## zip 和 unpacking (\*, **)
> 解包：https://zhuanlan.zhihu.com/p/41968260  
> zip：https://www.runoob.com/python3/python3-func-zip.html  

* 解包  
    * 表达式解包  
    任何可迭代对象都支持解包，可迭代对象包括元组、字典、集合、字符串、生成器等实现了__next__方法的一切对象。  
        ```python
        # 多变量赋值的本质：python自动解包
        a,b,c = "123"   # 分别赋值 1,2,3
        a,b,c = {"a":1, "b":2, "c":3}   # 分别赋值 'a', 'b', 'c'
        a, *b, c = [1,2,3,4]    # 分别赋值 1, [2,3], 4

        # 用解包合并列表、字典
        a, b = {"a":1, "b":2}, {"c":3, "d":4}
        list1, list2 = [1,2,3], range(3,6)
        [*list1, *list2]    # 输出 [1, 2, 3, 3, 4, 5]
        {**a, **b}          # 输出 {'a': 1, 'b': 2, 'c': 3, 'd': 4}
        ```
    * 函数解包
        ```python
        # 可作用于所有的可迭代对象，用于字典时传 key；** 只能作用于字典对象，传 value
        def func(a,b,c):
            print(a,b,c)
        func(*[1,2,3])              # 输出 1 2 3
        func(*{"a":1,"b":2,"c":3})  # 输出 a b c
        func(**{"a":1,"b":2,"c":3}) # 输出 1 2 3
        ```
* zip  
`zip(可迭代对象1, 可迭代对象2, ...)` 函数的参数为一个或多个可迭代的对象，其将对象中对应的元素打包成一个个元组，然后返回由这些元组组成的对象。需要查看结果时，可用 list() 转换来输出列表。  
如果各个迭代器的元素个数不一致，则返回列表长度与最短的对象相同。
    ```python
    # zip()函数
    nums = ['flower','flow','fly']  # nums整体作为一个可迭代对象
    print( list(zip(nums)) )    # 输出 [('flower',), ('flow',), ('fly',)]
    print( *nums )              # *nums包含三个可迭代对象，输出 flower flow fly
    print( list(zip(*nums)) )   # 输出 [('f', 'f', 'f'), ('l', 'l', 'l'), ('o', 'o', 'y')]

    # 用两个列表创建字典，可用zip
    a, b = [2,3,4], "abc"
    c = dict(zip(a,b))          # {2: 'a', 3: 'b', 4: 'c'}

    # 列表的转置
    a = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    b = [list(x) for x in zip(*a)]
    ```

---

## 正则表达式
使用方法：https://www.cnblogs.com/xieshengsen/p/6727064.html  
常用操作：https://www.cnblogs.com/guyuyun/p/5839881.html

`re.findall(str1, str2)`: 第一个参数为正则表达式字符串，第二个为被搜索的字符串，具体见上面链接    

常见的一些正则项目:  
^：匹配开头  
$：匹配结尾  
.:匹配任意单个字符  
?：匹配前一个字符的0或1次（即可有可无）   
*：匹配前一个字符0到无限次  
+：匹配前一个字符1到无限次  
[ ]：匹配括号中的其中一个字符  
\d：一个数字  
\D：除了数字的字符  
\w：从小写a到z,大写A到Z，数字0到9  
\W：除了字母与数字以外的特殊符号  

```python
str = "  +4193 with words"
print( int(*re.findall(r'^[\+\-]?\d+', str.lstrip())) ) # 得到 4193
```

---
## Function Annotations  
冒号（：）后跟的expression是注释；等号（=）后跟的是默认值；箭头（->）后跟的是返回值形式，annotation可被保存为函数的attributes。
```python
def func(a: 'spam' = 4, b: 'this is b' = 5, c: float = 6) -> int:
    return a + b + c
func.__annotations__  

# 输出：{'a': 'spam', 'b': 'this is b', 'c': float, 'return': int} 
```  
    
---
## Python 的 Shared Memory 机制
* 直接赋值（=），会采用shared memory方式，也即只是创建了一个对象的引用
    ```python
    # 对于不可更改对象：int, float, str, tuple等
    # 改变之前指向相同内存块，值改变之后指向不同内存块
    a = 1
    b = a
    print(b is a)   # True
    b = a + 1
    print(b is a)   # False

    # 对于可变对象：list, set, dict等
    # 对子对象做更改，仍然指向相同内存块
    # 只有对父对象进行更改，例如 += 这种，才会分配新的内存
    a=[1,2,3]
    b=a;  print(b is a)   # 得到 True
    b=a;    b[1]=3;         print(b is a)   # 得到 True
    b=a;    b.append(a);    print(b is a)   # 得到 True
    b=a;    b+=[4];         print(b is a)   # 得到 False
    b=a;    b=[0,0,0];      print(b is a)   # 得到 False
    b=a;    b=[*a, 2];      print(b is a)   # 得到 False
    ```


* `.copy()` 创建浅拷贝：深拷贝父对象（一级目录），子对象（二级目录）还是引用  
`copy.deepcopy()` 创建深拷贝:完全拷贝了父对象及其子对象。 深拷贝需要import copy模块
    ```python
    # 可更改对象(dict)：dict1, dict2指向相同内存块
    dict1 = {'user':'a','num':[1,2,3]} 
    dict2 = dict1              # 对象的引用
    dict3 = dict1.copy()       # 浅拷贝：深拷贝父对象（一级目录），子对象（二级目录）不拷贝，还是引用
    dict4 = copy.deepcopy(dict1)   # 深拷贝，完全拷贝了父对象及其子对象

    # 修改 data 数据
    dict2['user']='b'
    dict2['num'].remove(1)

    # 输出结果
    print(dict1)         # {'user': 'b', 'num': [2, 3]}
    print(dict2)         # {'user': 'b', 'num': [2, 3]}
    print(dict3)         # {'user': 'a', 'num': [2, 3]}
    print(dict4)         # {'user': 'a', 'num': [1, 2, 3]}
    ```

* Python函数传参本质上是传引用，但是原参数是否会被修改取决于具体的操作，其遵循上述 Shared Memory机制
    ```python
    # 不可变对象被修改
    a = 2
    def foo(b):
        print(b is a)   # True
        b = b+1
        print(b is a)   # False
    foo(a)       
    print(a)  # 2

    # 可变对象的父对象被修改
    a = [1, 2, 3]
    def bar(c):
        print(c is a)   # True
        c = [0, 0, 0]
        print(c is a)   # False
    bar(a)    
    print(a)  # [1,2,3]

    # 可变对象的子对象被修改
    a = [1, 2, 3]
    def foo(b):
        print(b is a)   # True
        b.append(4)
        print(b is a)   # True
    foo(a)
    print(a)  # [1,2,3,4]
    ```
