# 14种解决问题的模式
https://zhuanlan.zhihu.com/p/90664857?utm_source=wechat_session&utm_medium=social&utm_oi=37607459258368  
滑动窗口  
双指针  
快慢指针  
区间合并  
循环排序  
原地反转链表  
树BFS  
树DFS  
双堆  
子集  
变种二分  
最大前K的元素  
K-路归并  
拓扑排序

<br><br><br>

# 四大算法思想：回溯、动态规划、贪心、分治
> https://blog.csdn.net/qq_25800311/article/details/90635979   

* 回溯 (由递归实现，自顶向下)  
回溯算法是个“万金油”。基本上能用的动态规划、贪心解决的问题，我们都可以用回溯算法解决。回溯算法相当于穷举搜索。穷举所有的情况，然后对比得到最优解。不过，回溯算法的时间复杂度高，是指数级别的，只能用来解决小规模数据的问题。可用 `回溯+备忘录` 或 `回溯+剪枝` 来降低复杂度

* 动态规划（自底向上）      
动态规划的基本策略是将原问题分解为相似的子问题，先求解并保存重复子问题的解，再逐步合并成为原问题的解。`动态规划之所以高效，就是因为回溯算法实现中存在大量的重复子问题。`能用动态规划解决的问题，需要满足三个特征，`最优子结构、无后效性和重复子问题`。

* 贪心算法  
贪心算法实际上是动态规划算法的一种特殊情况。它解决问题起来更加高效，代码实现也更加简洁，但它可以解决的问题也更加有限。它能解决的问题需要满足三个条件，`最优子结构、无后效性和贪心选择性`，这里不要求`重复子问题`。其中，最优子结构、无后效性跟动态规划中的无异。`“贪心选择性”的意思是，通过局部最优的选择，能产生全局的最优选择`。每一个阶段，我们都选择当前看起来最优的决策，所有阶段的决策完成之后，最终由这些局部最优解构成全局最优解。

* 分治  
分治算法也就是分块处理，一个按顺序处理`O(N)`的算法，经过分治处理，复杂度可以减少为`O(logN)`：例如快速排序、N个数组合并（分别两两合并：4->2->1，比按顺序依次合并复杂度低）  
二分法是分治算法的特例，对于有序的数组等进行操作，可考虑二分法降低时间复杂度

* 一些讨论
    * `动态规划`和`回溯+备忘录`的区别：https://www.cnblogs.com/liweiwei1419/p/8616113.html    

        `回溯+备忘录`是自顶向下实现。动态规划是自顶向下思考，但自底向上实现，是先解决了数据规模较小的问题，然后一步一步地解决了数据规模较大的问题。  

        例如求斐波拉契数列，既可以用递归也可以用循环。递归自顶向下进行，暴力递归会导致子问题的重复计算，可用 `备忘录` 避免；用循环做的话，是自底向上，是一种可称之为“动态规划”的解法。  

    * 递归/迭代 是算法结构； 回溯/动态规划：算法思想


<br><br><br>

# 经典问题
## 求数组中位数
设数组为nums，数组长度为n，
Python3中：`中位数 = (nums[n//2] + nums[(n-1)//2])/2`   
Python2中：`中位数 = (nums[n/2] + nums[(n-1)/2])/2` 

---
<br>

## Ksum问题 (Leetcode Q18)
> https://leetcode-cn.com/problems/4sum/

4sum: 给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。

2sum: 暴力枚举: O(N^2)； 排序+双指针首尾夹闭: O(NlogN)； Python字典(哈希表): O(N)  
3sum: 最优O(N^2)：单元素遍历 + 字典/（排序+双指针首尾夹闭）  
4sum: 最优O(N^2)：两元素和遍历 + 字典/（排序+双指针首尾夹闭）

* 用双指针首尾夹闭：是一个普适的方法，可以避免最后的统一去重

* 用Dict：无可避免地需要在最后一步统一去重（计算量可能很大s）
    * dic =｛两数之和：[两个数的下标组合1], [两个数的下标组合2], [两个数的下标组合3], ... ]｝
    * 用字典的一个问题是Key值不能重复，所以"去重"这步将会非常麻烦。  
最坏情况会达到`C(4,N) = O(N^4)`的复杂度，例如：nums = [1,1,1,1,1,1], target = 4

---
<br>

## 就地移除数组元素（Leetcode Q26, Q27）
不要使用额外的数组空间，你必须在原地修改输入数组并在使用 O(1) 额外空间的条件下完成。  
* 给定一个排序数组，你需要在原地删除重复出现的元素，使得每个元素只出现一次，返回移除后数组的新长度
* 给定一个数组 nums 和一个值 val，你需要原地移除所有数值等于 val 的元素，返回移除后数组的新长度
```python
def removeElement(self, nums: List[int], val: int) -> int:
    i = 0
    for j in range(len(nums)):
        if nums[j] != val:
            nums[i] = nums[j]
            i += 1
    return i
```

`那些需要先遍历再进行某些操作的，可以考虑双指针: 慢指针指向处理后的数组的末端（被赋值），快指针指向原数组的末端（检测是否需要删除）`

---
<br>

## 第K大（小）问题 (Leetcode Q4)
* 问题描述 
    * 初阶：有两个数组A和B，假设A和B已经有序（从大到小），求A和B数组中所有数的第k大，要求时间复杂度`O(log k)`
    * 进阶：有N台机器，每台机器上有一个有序的大数组，需要求得所有机器上所有数中的第K大。注意，需要考虑N台机器的并行计算能力。

* 思路：
    * 取两个数组中的第k/2个元素进行比较，如果来自数组1的元素小于来自数组2的元素，则说明数组1中的前k/2个元素不可能成为第k个元素的候选，所以将数组1中的前k/2个元素去掉，组成新数组和数组2求第k-k/2小的元素。因为我们把前k/2个元素去掉了，所以相应的k值也应该减小

```python
def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        def findKthElement(arr1,arr2,k):
            len1,len2 = len(arr1),len(arr2)
            if len1 > len2:
                return findKthElement(arr2,arr1,k)
            if not arr1:
                return arr2[k-1]
            if k == 1:
                return min(arr1[0],arr2[0])
            i,j = min(k//2,len1)-1,min(k//2,len2)-1
            if arr1[i] > arr2[j]:
                return findKthElement(arr1,arr2[j+1:],k-j-1)
            else:
                return findKthElement(arr1[i+1:],arr2,k-i-1)
        l1,l2 = len(nums1),len(nums2)
        left,right = (l1+l2+1)//2,(l1+l2+2)//2
        return (findKthElement(nums1,nums2,left)+findKthElement(nums1,nums2,right))/2
```

---
<br>

## 字符串匹配：KMP算法 (Leetcode Q28):
> KMP算法讲解：http://www.sohu.com/a/336648975_453160 

> KMP算法复杂度：https://segmentfault.com/q/1010000014560162   
> * 计算模板串的最长公共前缀后缀长度列表时的比较次数介于 [m,2m]，m为模板串的长度.  
> * 比较模板串和子串时比较次数介于[n,2n]，最坏情形形如 `T="aaaabaaaab",P="aaaaa"`
> * 总时间复杂度为 O(M+N), M, N 分别为主串和模板串长度

简而言之，暴力匹配用双指针，一个指针指向主串，另外一个指针指向模板串。每匹配一位，两个指针都向后移动一位，当在某一位匹配失败时，模板串指针退回到串首，主串指针也回退到上一次匹配开始位置的下一位。

KMP算法中，有一个数组记录最长公共前后缀长度。每次匹配失败时，主串指针不动，模板串指针退回到之前某个位置，这个位置是最长公共前后缀的前缀的尾部。可以用一个`next数组`记录应该退回到的位置。`next`数组之和模板串有关，其生成运用了动态规划的思想：https://segmentfault.com/a/1190000008575379 

例如：模板串 `ABABAAABABAA`，对应的 next 数组为`[-1, 0, 0, 1, 2, 3, 1, 1, 2, 3, 4, 5]`

|模板串|A|B|A|B|A|A|A|B|A|B|A|A|
|--|--|--|--|--|--|--|--|--|--|--|--|--|
|值|-1|0|0|1|2|3|1|1|2|3|4|5|
|下标|0|1|2|3|4|5|6|7|8|9|10|11|

* 给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从0开始)。如果不存在，则返回 -1；当 needle 是空字符串时我们应当返回 0。
    ```python
        def strStr(self, haystack, needle):
            def gen_next(s2):
                n = len(s2)
                k, j = -1, 0
                next_list = [0 for i in range(n)]
                next_list[0] = -1 # 用-1标识next[0]，代表最大公共前后缀长度为0。因为要区别next[0]和值为0的next[i]
                while j < n-1:
                    if k == -1 or s2[k] == s2[j]:           # j是两个串失配的地方，k是最长相同前缀最后的位置
                        k += 1
                        j += 1
                        next_list[j] = k                    # 如果相等 则next[j+1] = k
                    else:
                        k = next_list[k]                    # 如果不等，则将next[k]的值给k
                return next_list


            len1, len2 = len(haystack), len(needle)
            if len2 == 0: return 0
            if len1 < len2: return -1
            next_ = gen_next(needle)
            i = j = 0
            while i < len1:
                if haystack[i] == needle[j] or j == -1:
                    if  j == len2-1: return i-len2+1
                    i += 1
                    j += 1
                else:
                    j = next_[j]
            return -1
    ```

---
<br>

## 括号生成 (Leetcode Q22):
* 给出 n 代表生成括号的对数，请你写出一个函数，使其能够生成所有可能的并且有效的括号组合。
例如，给出 n = 3，生成结果为：["((()))", "(()())", "(())()", "()(())", "()()()"]
    * 思路一：回溯 (自顶向下)
        > 构造了一棵树，根节点为("", 0 ,0)，也就是顶。自顶向下进行DFS遍历，满足条件就跳出，也即叶结点。

        ```python
        def generateParenthesis(self, n):
            ans = []
            def back(s, l, r):  
                if len(s) == 2*n:   # 满足条件
                    ans.append(s)
                    return
                if l<n:
                    back(s+'(', l+1, r)
                if r<l:
                    back(s+')', l, r+1)

            back("", 0, 0)
            return ans
        ```

    * 思路二：动态规划（自底向上)
        > 原理："(" + [n=p时所有括号的排列组] + ")" + [n=q时所有括号的排列组合]  
        其中 p + q = n-1，且 p q 均为非负整数。可用反证法证明这样生成出来的字符串不重复。

        ```python
        def generateParenthesis(self, n: int) -> List[str]:
        dict_ = {}
        dict_[0] = [""]
        dict_[1] = ["()"]

        if n<2: return dict_[n]
        for m in range(2, n+1):
            dict_[m] = []
            for i in range(0, m):
                dict_[m] += ['(%s)%s' %(x, y) for x in dict_[i] for y in dict_[m-1-i]] 
        return dict_[n]
        ```

---
<br>

## 下一个更大的排列、全排列 (Leetcode Q31)
https://blog.csdn.net/ggdhs/article/details/90285794 
