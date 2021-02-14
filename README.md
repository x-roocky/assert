## 背景

简单而完备的C99断言。既兼容标准断言(assert)，又提供扩展的格式化输出。

## 示例

1. 扩展格式化输出

```c
#include "assert.h"

int main() {
    int a = 0, b = 1;
    assert(a == b, "%d == %d", a, b);
}
```

2. 兼容标准C

```c
#include "assert.h"

int main() {
    int a = 0, b = 1;
    assert(a == b);
}
```

3. 重定向断言输出

```c
#include <stdio.h>

/* 通过重定义ASSERT_CONFIG_PRINTF，重定向断言输出 */
#define ASSERT_CONFIG_PRINTF(...)   printf(__VA_ARGS__)
#include "assert.h"
```

4. 重定义异常中止动作

```c
/* 通过重定义ASSERT_CONFIG_ABORT，变更异常终止动作，这里以屏蔽中止为例 */
#define ASSERT_CONFIG_ABORT()       ((void)0)
#include "assert.h"
```

5. 配置打开或关闭断言

```c
/* 关闭：编译器全局定义ASSERT_CONFIG_ENABLE=0或NDEBUG=1，亦可头文件assert.h包含前定义
 * 打开：编译器全局定义ASSERT_CONFIG_ENABLE=1，亦可头文件assert.h包含前定义
 */
#define ASSERT_CONFIG_ENABLE        0
#include "assert.h"
```
