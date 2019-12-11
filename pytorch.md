pickle: 将python对象二进制序列化和反序列化

.evla() 执行一个字符串表达式，并返回表达式的值
eval("2+2") 得到 4

a = torch.randn(1,2,3,4)    # 张量各维度维数 1, 2, 3, 4
torch.numel(a)      # 输出 24，为张量的长度


a = dict(a=1, b=2)  
for k in a:     
    print(k, end = ' ')    # 输出 b a

a = dict(a=1, b=2)
for k,  v in a.items():
    print(k,v, end = ' ')  # b 2 a 1