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
| DATA | 0x00000004 | 32 | rw | 0x00000000 | DAC 输出数据，```Repeated```=0: rw, ```Repeated```=1: ro |
| SRC_ADDRESS | 0x00000008 | 32| rw | 0x00000000 | 重复模式数据开始地址 |
| SRC_SIZE | 0x0000000C | 32 | rw | 0x00000000 | 重复模式数据数量 |
| CLK_DIV | 0x00000010 | 32 | rw | 0x00000000 | DAC 输出时钟分频系数 |

### Register *CTL*

| Field Name | Bits | Reset Value | Type | Description |
| --- | --- | --- | --- | --- |
| Repeated | 0 | 0x0 | rw | 0=单次转换模式, 1=重复模式 |
| Loop | 1 | 0x0 | rw | 0: 单次重复模式, 1: 循环模式. 仅在 ```Repeated```=1 时有效 |
| Busy | 2 | 0x0 | r | 0: 空闲, 1: 忙碌 |
| Stop | 3 | 0x0 | w | r: 0, w: 写入 1 时结束循环模式 |