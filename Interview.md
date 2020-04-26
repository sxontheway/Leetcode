## 用加减乘除计算开方、开立方等问题：
牛顿法迭代：f(x_n+1) = f(x_n) - f(x_n)/f'(x_n)
  
* 牛顿法和梯度下降的关系：https://zhuanlan.zhihu.com/p/38186912  
  * 牛顿法是求零点问题：`f(x)=0 求 x`
  * 梯度下降是求极值点问题：`argmin_x f(x) 求 x`
  * 用牛顿法求极值点的思路：极值点=梯度的零点。对于求极值问题，用梯度下降是一阶收敛，用牛顿法是二阶收敛
  
<br>
    
## 检索数组中满足某种条件的子集：
### 双指针
找出数组中所有的两两组合，其和为k，O(n)
  
### 前缀和+哈希表：
> https://zhuanlan.zhihu.com/p/107778275   

* 前缀和、差分是什么？  
  前缀和：是一个数组的某项下标之前（包括此项元素）的所有数组元素的和。   
  差分：将数列中的每一项分别与前一项数做差。差分序列最后比原序列多一个数（相当于0减前缀和的最后一个数）  
  ```
  原数列：1,3,-2,4  
  前缀和：1,4,2,6  
  差分：1,3,-2,4,-6  
  ```

* 求`和为k的连续的子数组`的个数？   
  先存好前缀和，并用哈希表记录该前缀和出现的次数，O(n)，见 https://zhuanlan.zhihu.com/p/107778275 

* 求数组中连续一段数的和，绝对值最大？  
  对前缀和排序，最大和最小的做差

* 求数组中连续一段数的和，绝对值最小？  
  对前缀和排序，两两做差，再排序，取最小值。把该最小值和最小前缀和比较。
  
### 多维前缀和：
> 二维前缀和： 
https://cloud.tencent.com/developer/article/1457488  
> 多维前缀和： 
https://blog.nowcoder.net/n/f547adfd75e24650a89663aceaf3f6c2  
https://oi-wiki.org/basic/prefix-sum/
  
* 二维前缀和矩阵的生成：  
  容赤原理：时间复杂度为 O(n*(2^d))，d为维数
  ```c
  for(int i = 1; i <= n; i++)
      for(int j = 1; j <= m; j++)
          a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1]
  ```
  另一种方法：时间复杂度为 O(n*d)，d为维数
  ```c
  for(int i = 1; i <= n; i++)
      for(int j = 1; j <= m; j++) a[i][j] += a[i][j - 1];
  for(int i = 1; i <= n; i++)
      for(int j = 1; j <= m; j++) a[i][j] += a[i - 1][j];
  ```
 
* ***题目***：
  输入一正整数数组`A = (a_1,...,a_n)`，对于任意`i`，求出是否存在`j`，使得`ai`和`aj`的二进制按位与结果为0？若有，返回1，若无，返回0。例如，输入`A=(1,3,10)`，返回 `(1,0,1)`。
  > 类似题目：  
  https://www.cnblogs.com/SovietPower/p/10073986.html  
  https://www.cnblogs.com/barrier/p/6670514.html  
    1. 长度对齐，高位补0：`(1,3,10)`->`(0001,0011,1010)`，假设长度统一为 d (A中最大的数为转换为二进制有多少位)
    1. 构建哈希表，使得`A中某个数 x 出现次数的操作（或是否包含 x ）`能在 O(1) 时间内完成
    1. 构建高位前缀和矩阵  
        1. 高位前缀和矩阵的维度为`2*2*...*2*2`，一共d个2；index为某数二进制补码；value为A中与该数按位与为0的个数。
        1. 例如：和3按位与结果为0的数，可能是`0000, 0100, 1000, 1100`，`3->0011（二进制）->1100（补码）`。对于3，将高位前缀和矩阵所提供的映射记为`f(1,1,0,0)=n`，**n为数组A中满足`高两位为0或1，低两位能为0`的数的个数，也即A中与3按位与结果为0的个数**。
        1. 从`f(0,0,0,0)`开始，直到`f(1,1,1,1)`，迭代地计算`f(i_1, ..., i_n)`的值，例如：`f(1,1,0,0) = f(0,1,0,0)+f(1,0,0,0)-f(0,0,0,0)+A中3(补码为1100)的个数`，其中`A中1100的个数`由哈希表在 O(1) 内得到
        1. 高位前缀和矩阵的建立：用上文的第二种方法，时间复杂度`O(n*d)`
    1. 高位前缀和矩阵建立后，`n=f(a_i的二进制补码)`，可以通过索引直接得到，复杂度为`O(1)`

### 字典树：
> https://leetcode-cn.com/problems/maximum-xor-of-two-numbers-in-an-array/solution/shu-zu-zhong-liang-ge-shu-de-zui-da-yi-huo-zhi-by-/
* 数组中两个数的最大异或值，O(n):

  <p align="center" >
  <img src="https://pic.leetcode-cn.com/Figures/421/trie.png" height = "300">
  </p>

  ```python
  nums = [3, 10, 5, 25, 2]
  L = len(bin(max(nums))) - 2   # 10->'0b1010'，去除'0b'
  nums = [[(x >> i) & 1 for i in range(L)][::-1] for x in nums]   # 长度不够，高位补0
  trie = {}
  max_xor = 0

  for num in nums:  # num是已经转化为二进制的数
      curr_xor = 0  # curr_xor 是对于num最大的异或值
      xor_node = trie
      node = trie   # node是指向trie某个节点的指针

      for bit in num:


          # 将二进制数插入字典树
          if not bit in node:
              node[bit] = {}  
          node = node[bit]  # 进入key为bit的子节点 

          # 计算已有的数和新插入的数的最大异或值
          toggled_bit = 1 - bit
          if toggled_bit in xor_node:   # 与num的异或值在此位为1的数存在
              curr_xor = (curr_xor << 1) | 1
              xor_node = xor_node[toggled_bit]
          else:
              curr_xor = curr_xor << 1  # 与num的异或值在此位为1的数不存在
              xor_node = xor_node[bit]

      max_xor = max(max_xor, curr_xor)

  return max_xor
  ```
 
<br>
  
