# AXI-ADC Documentation

ADC 控制器，可用于 Analog Devices 的 AD9280 等型号的 ADC 芯片。

## 模式

* 单次采样模式
* 重复采样模式
	* 触发采样 (TODO) 中断/开始

## 寄存器列表

| Register Name | Address | Width | Type | Reset Value | Description |
| --- | --- | --- | --- | --- | --- |
| CTL | 0x00000000 | 32 | rw | 0x00000000 | ADC control register |
| DATA | 0x00000004 | 8 | r | 0x00000000 | ADC 采样数据 |
| DST_ADDR | 0x00000008 | 32| rw | 0x00000000 | 重复采样数据保存地址 |
| DST_SIZE | 0x0000000C | 16 | rw | 0x00000000 | 重复采样数据数量 |
| CLK_DIV | 0x00000010 | 16 | rw | 0x00000000 | 采样时钟分频系数 |
| TRIG_CTL | 0x00000014 | 32 | rw | 0x00000000 | 触发控制寄存器 |
| CMPR_H | 0x00000018 | 8 | rw | 0x00000000 | 比较寄存器 H |
| CMPR_L | 0x0000001C | 8 | rw | 0x00000000 | 比较寄存器 L |

### Register *CTL*

| Field Name | Bits | Reset Value | Type | Description |
| --- | --- | --- | --- | --- |
| Repeat | 0 | 0x0 | rw | 0=单次采样模式, 1=重复采样模式 |
| NoOut | 1 | 0x0 | rw | 0=采样后将数据输出, 1=采样后不输出，允许该模块仅作为比较器使用 |
| TrigStart | 2 | 0x0 | rw | 0=直接开始采样, 1=触发后开始采样 |
| Busy | 3 | 0x0 | r | 0: 空闲, 1: 忙碌 |
| Start | 4 | 0x0 | w | r: 0, w: 写入 1 时开始 ADC 采样 |
| Stop | 5 | 0x0 | w | r: 0, w: 打断 ADC 触发或重复采样 |
| StopTrig | 6 | 0x0 | w | r: 0, w: 仅在等待 ADC 触发时打断 |

### Register *TRIG_CTL*

| Field Name | Bits | Reset Value | Type | Description |
| --- | --- | --- | --- | --- |
| MODE | 2-0 | 0x0 | rw | 0=禁用触发, 1=范围触发, 2=跨越触发，3=外部高电平触发，4=外部低电平触发 |
| HCMP_EN | 3 | 0x0 | rw | 比较寄存器 H enabled |
| LCMP_EN | 4 | 0x0 | rw | 比较寄存器 L enabled |
| IEN | 5 | 0x0 | rw | 中断 enabled，IRQ 发出后 IEN 置为 0 |