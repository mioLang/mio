# MIO 语言解释器

## 简介
MIO 是一种基于寄存器的简单编程语言，支持基本的算术运算、逻辑运算、控制流和函数定义。该解释器使用 C++ 实现，可以解释执行 .mio 格式的源代码文件。

## 运行方式
```bash
# 方式1：直接运行，然后输入文件名
./mio

# 方式2：命令行参数指定文件
./mio code.mio
```

## 语法规范

### 1. 注释和标签
- **注释**：以 `#` 开头的行
- **标签**：以 `:` 开头的行，可用于跳转
```mio
# 这是一行注释
:start  # 这是一个标签
```

### 2. 变量定义
```mio
var x y z    # 定义三个变量，会自动分配内存地址
```

### 3. 内存操作
```mio
fp 100       # 分配100个内存单元（必须在程序开始使用）

mov dest src      # 将src的值复制到dest
mio addr value    # 将value（立即数）存入addr
```

### 4. 算术运算
```mio
add dest a b    # dest = a + b
sub dest a b    # dest = a - b
tim dest a b    # dest = a * b
div dest a b    # dest = a / b
mod dest a b    # dest = a % b
```

### 5. 逻辑运算
```mio
and dest a b    # dest = a & b
or  dest a b    # dest = a | b
xor dest a b    # dest = a ^ b
compl dest      # dest = ~dest
rmv dest a b    # dest = a >> b
lmv dest a b    # dest = a << b
```

### 6. 比较运算
```mio
sam dest a b    # dest = (a == b)
gre dest a b    # dest = (a > b)
les dest a b    # dest = (a < b)
```

### 7. 输入输出
```mio
put a b c       # 输出a,b,c的值（连续输出，无分隔符）
putc a b c      # 输出a,b,c对应的字符
get a b c       # 从输入读取值存入a,b,c
getc a b c      # 从输入读取字符存入a,b,c
```

### 8. 控制流
```mio
jmp label       # 跳转到label标签
if cond         # 如果cond的最低位为0，跳过下一行

# for循环（变量版本）
for i start end    # i从start到end循环
    # 循环体
end

# forn循环（立即数版本）
forn i 1 end       # i从1到end循环
    # 循环体
end

# while循环
while cond         # 当cond非0时循环
    # 循环体
end
```

### 9. 函数定义和调用
```mio
# 定义函数
def add_two 2 a b    # 函数名add_two，2个参数a和b
    # 函数体
    add result a b
    # 返回值（可选）
    return
endf

# 调用函数
run add_two x y      # 调用add_two，参数为x和y
```

### 10. 工具函数
```mio
max dest a b    # dest = max(a, b)
min dest a b    # dest = min(a, b)
ext             # 退出程序
```

## 编程示例

### 示例1：Hello World
```mio
fp 10
var msg

# 设置字符
mio msg 72    # 'H'
putc msg
mio msg 101   # 'e'
putc msg
mio msg 108   # 'l'
putc msg
mio msg 108   # 'l'
putc msg
mio msg 111   # 'o'
putc msg
ext
```

### 示例2：计算阶乘
```mio
fp 20
var n result i

mio n 5        # 计算5的阶乘
mio result 1
forn i 1 n
    tim result result i
end
put result
ext
```

### 示例3：使用函数
```mio
fp 30
var x y z

# 定义加法函数
def add 2 a b
    add result a b
    return
endf

# 使用函数
mio x 10
mio y 20
run add x y    # 计算 x + y
ext
```

## 注意事项

1. **必须先使用 `fp` 分配内存**，否则后续操作会失败
2. 变量在使用前必须先通过 `var` 定义
3. 循环和函数必须正确配对 `end`/`endf`
4. 标签名不能与关键字重复
5. 函数参数按值传递
6. 所有数值类型为 64 位整数

## 错误处理

解释器会捕获以下错误：
- 未定义的指令
- 未定义的变量
- 内存访问越界
- 函数调用错误

错误信息会显示错误类型和行号：
```
Catch a error on line xx:xx 
```
