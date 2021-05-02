# AXI-DAC Documentation

DAC 控制器，可用于 Analog Devices 的 AD9708 等型号的 DAC 芯片。

## 模式

* 单次转换模式
* 重复转换模式
	* 单次重复模式
	* 循环模式

## 寄存器列表

| Register Name | Address | Width | Type | Reset Value | Description |
| --- | --- | --- | --- | --- | --- |
| CTL | 0x00000000 | 32 | rw | 0x00000000 | DAC control register |
| DATA | 0x00000004 | 8 | rw | 0x00000000 | DAC 输出数据，```Repeated```=0: rw, ```Repeated```=1: ro |
| SRC_ADDRESS | 0x00000008 | 32| rw | 0x00000000 | 重复模式数据开始地址 |
| SRC_SIZE | 0x0000000C | 32 | rw | 0x00000000 | 重复模式数据数量 |
| CLK_DIV | 0x00000010 | 32 | rw | 0x00000000 | DAC 输出时钟分频系数 |

### Register *CTL*

| Field Name | Bits | Reset Value | Type | Description |
| --- | --- | --- | --- | --- |
| Repeat | 0 | 0x0 | rw | 0=单次转换模式, 1=重复模式 |
| Loop | 1 | 0x0 | rw | 0: 单次重复模式, 1: 循环模式. 仅在 ```Repeated```=1 时有效 |
| Busy | 2 | 0x0 | r | 0: 空闲, 1: 忙碌 |
| Start | 3 | 0x0 | w | r: 0, w: ```Repeated```=1 时写入 1 开始 DAC 输出 |
| Stop | 4 | 0x0 | w | r: 0, w: 写入 1 时结束循环模式 |
| ClkEdge | 5 | 0x0 | rw | 0=输出数据在输出时钟上升沿有效, 1=输出数据在输出时钟下降升沿有效 |


### 乱七八糟的说明和其他问题

* CTL 寄存器的 Busy 位表示 AXI_M 处于读取状态，或 output stage 的 dac_clk_en 有效
* Repeat 模式下 写入 Stop 位后 AXI_M 会完成最后一次 AXI transaction，output stage 会在清空
FIFO 后结束 DAC 转换，因此 Busy 位不会立即无效，DAC 的停止时间也是不可预测的。Stop 后 Busy 时执行 Start 可能无法让转换重新开始，必须要在 Busy=0 时 Start
* output stage 结束的时候一定是 fifo_empty 的，output stage 开始时也是（AXI_M 还没开始写入）
* Start 之后由于信号跨时钟域同步以及 FIFO 延迟的问题，output stage 不会马上启动
<!-- 时钟切换的时候亚稳态怎么办？ -->
<!-- pulse和state的sync延时不一样 -->
* AXI_M 的 transaction 的 burst 比较多，如果中间被 fifo_full 堵住的话会把整个 transaction
拉得特别长，占用总线时间，应该在 FIFO 半满的时候开始读 RAM
* 用 FIFO 的 almost_full 信号代替 full 信号可以解决丢数据的问题
* TODO: 接收到 Stop 信号后/非对齐的读取位置达到时不往 FIFO 中写数据 (AXI_M)
* SRC_SIZE 需要对齐到 4 字节，否则 output stage 读取时不能跳过 FIFO 中的数据
* 改成同步时钟或许也可以
* TODO: 增加 AXI Stream 接口的输入通道