/**
 * @file tm1637.c
 * @author e-play
 * @brief
 * @version 0.1
 * @date 2025-03-27
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "tm1637.h"

#define TM_DELAY_TIME 2

const uint8_t CODE[10] = {
    0x3F,
    0x06,
    0x5B,
    0x4F,
    0x66,
    0x6D,
    0x7D,
    0x07,
    0x7F,
    0x6F,
}; // 共阳数码管0~9字型码
const uint8_t TAB[10] = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
}; // 数码管不显示

/********************Start函数*************************/
/**
 * @brief Initiates the I2C communication by generating a start condition.
 *
 * This function generates the start condition for I2C communication by
 * manipulating the SDA and SCL lines according to the I2C protocol.
 * It sets up the initial state of the bus and prepares it for data transmission.
 *
 * @note This function assumes that TM_SDA_HIGH(), TM_SCL_HIGH(), TM_SDA_LOW(),
 *       TM_SCL_LOW(), and delay_us() are properly defined elsewhere in the code.
 *
 * @return None
 */
void I2CStart()
{
    TM_SDA_HIGH();
    TM_SCL_HIGH();
    delay_us(TM_DELAY_TIME);
    TM_SDA_HIGH();
    delay_us(TM_DELAY_TIME);
    TM_SDA_LOW();
    delay_us(TM_DELAY_TIME);
    TM_SCL_LOW();
}

/**
 * @brief 发送I2C停止信号。
 *
 * 该函数通过控制SCL和SDA引脚的状态变化，生成符合I2C协议的停止信号。
 * 停止信号的时序包括以下步骤：
 * 1. 将SCL拉低。
 * 2. 将SDA拉低。
 * 3. 将SCL拉高。
 * 4. 将SDA拉高，完成停止信号的发送。
 *
 * @note 该函数依赖于以下宏定义或函数实现：
 *       - TM_SCL_LOW(): 将SCL引脚设置为低电平。
 *       - TM_SDA_LOW(): 将SDA引脚设置为低电平。
 *       - TM_SCL_HIGH(): 将SCL引脚设置为高电平。
 *       - TM_SDA_HIGH(): 将SDA引脚设置为高电平。
 *       - delay_us(us): 延时指定的微秒数。
 *       - TM_DELAY_TIME: 定义延时的时间长度（单位：微秒）。
 *
 * @return 无返回值。
 */
void I2CStop()
{
    // 拉低SCL引脚，准备开始停止信号的时序
    TM_SCL_LOW();
    delay_us(TM_DELAY_TIME);

    // 拉低SDA引脚，确保数据线处于低电平状态
    TM_SDA_LOW();
    delay_us(TM_DELAY_TIME);

    // 拉高SCL引脚，释放时钟线
    TM_SCL_HIGH();
    delay_us(TM_DELAY_TIME);

    // 拉高SDA引脚，生成停止信号的关键步骤
    TM_SDA_HIGH();
    delay_us(TM_DELAY_TIME);

    // 最终将SCL和SDA恢复到初始状态（低电平）
    TM_SCL_LOW();
    TM_SDA_LOW();
}

/**
 * @brief 通过I2C协议发送一个字节的数据。
 *
 * 该函数将输入的一个字节数据通过I2C总线逐位发送，最低位先发送。
 * 发送完成后，等待从设备的ACK应答信号。
 *
 * @param oneByte 要发送的字节数据（8位）。
 * @return 无返回值。
 */
void I2CWritebyte(uint8_t oneByte)
{
    uint8_t i;

    // 循环发送一个字节的每一位（从最低位开始）
    for (i = 0; i < 8; i++)
    {
        TM_SCL_LOW();       // 拉低SCL时钟线，准备发送数据
        if (oneByte & 0x01) // 判断当前位是否为1
            TM_SDA_HIGH();  // 如果为1，设置SDA为高电平
        else
            TM_SDA_LOW();        // 如果为0，设置SDA为低电平
        delay_us(TM_DELAY_TIME); // 延时，确保信号稳定
        TM_SCL_HIGH();           // 拉高SCL时钟线，完成一位数据的发送
        oneByte = oneByte >> 1;  // 将字节右移一位，准备发送下一位
    }

    // 8位数据发送完成，进入ACK应答阶段
    TM_SCL_LOW();            // 拉低SCL时钟线，准备接收ACK信号
    delay_us(TM_DELAY_TIME); // 延时，确保信号稳定

    // 等待从设备拉低SDA线以发送ACK信号
    while (TM_SDA_STA() == 1)
        ;

    delay_us(TM_DELAY_TIME); // 延时，确保ACK信号被正确读取
    TM_SCL_HIGH();           // 拉高SCL时钟线，结束ACK应答阶段
    delay_us(TM_DELAY_TIME); // 延时，确保信号稳定
}

/**
 * 函数名称: disp0
 * 功能描述: 通过I2C协议向显示设备发送数据，完成显示寄存器的初始化和数据写入。
 * 参数说明:
 *     p - 指向要发送的数据缓冲区的指针，类型为unsigned char*。
 * 返回值: 无
 * 注意事项:
 *     1. 该函数依赖于I2CStart、I2CWritebyte和I2CStop等底层I2C通信函数。
 *     2. 数据缓冲区p必须至少包含6字节的有效数据。
 */
void disp0(unsigned char *p)
{
    unsigned char i;

    // 发送I2C起始信号，并设置数据命令：地址自动加1，写数据到显示寄存器
    I2CStart();
    I2CWritebyte(0x40);
    I2CStop();

    // 发送I2C起始信号，并设置地址命令：初始地址为00H
    I2CStart();
    I2CWritebyte(0xc0);

    // 循环发送6字节数据到显存
    for (i = 0; i < 6; i++)
    {
        I2CWritebyte(*p);
        p++;
    }
    I2CStop();

    // 发送I2C起始信号，并设置显示控制命令：开显示，脉冲宽度为11/16
    I2CStart();
    I2CWritebyte(0x8C);
    I2CStop();
}

/**
 * @brief 读取按键值的函数。
 *
 * 该函数通过I2C协议与外部设备通信，读取一个字节的按键值。
 * 具体流程包括启动I2C通信、发送读键指令、逐位读取数据、处理ACK应答信号，并最终返回读取到的按键值。
 *
 * @return unsigned char 返回读取到的按键值（一个字节）。
 */
unsigned char read_key()
{
    unsigned char rekey, i;

    // 启动I2C通信
    I2CStart();

    // 发送读键指令0x42
    I2CWritebyte(0x42);

    // 释放SDA线，准备接收数据
    TM_SDA_HIGH();

    // 循环读取8位数据，从低位开始
    for (i = 0; i < 8; i++)
    {
        TM_SCL_LOW();
        delay_us(TM_DELAY_TIME);

        // 将已读取的数据右移一位，为新数据腾出空间
        rekey = rekey >> 1;

        delay_us(TM_DELAY_TIME);
        TM_SCL_HIGH();

        // 根据SDA线状态判断当前位的值，并更新rekey
        if (TM_SDA_STA())
            rekey = rekey | 0x80;
        else
            rekey = rekey | 0x00;

        delay_us(1);
    }

    // 拉低SCL线，准备接收ACK应答信号
    TM_SCL_LOW();
    delay_us(TM_DELAY_TIME);

    // 等待SDA线变为低电平，表示接收到ACK信号
    while (TM_SDA_STA() == 1)
        ;

    delay_us(TM_DELAY_TIME);

    // 拉高SCL线，完成ACK信号处理
    TM_SCL_HIGH();
    delay_us(TM_DELAY_TIME);

    // 停止I2C通信
    I2CStop();

    // 返回读取到的按键值
    return rekey;
}
/************显示函数，固定地址写数据************/
/**
 * disp - 向显示设备的指定地址写入数据并控制显示。
 *
 * 参数:
 *   add   - 目标地址，用于指定显示设备的寄存器地址。
 *   value - 要写入的数据值，通过CODE数组映射为实际的显示数据。
 *
 * 返回值:
 *   无返回值。
 *
 * 功能描述:
 *   该函数通过I2C协议向显示设备发送命令和数据，完成以下操作：
 *   1. 设置显示寄存器的固定地址。
 *   2. 向指定地址写入映射后的显示数据。
 *   3. 发送显示控制命令以开启显示并设置脉冲宽度。
 */
void disp(unsigned char add, unsigned char value)
{
    // 启动I2C通信并发送固定地址命令，准备写入显示寄存器
    I2CStart();
    I2CWritebyte(0x44); // 数据命令设置：固定地址，写数据到显示寄存器
    I2CStop();

    // 启动I2C通信并发送目标地址命令，准备写入add对应地址
    I2CStart();
    I2CWritebyte(add); // 地址命令设置：写入add对应地址

    // 向目标地址写入映射后的显示数据
    I2CWritebyte(CODE[value]); // 给add地址写数据
    I2CStop();

    // 启动I2C通信并发送显示控制命令，开启显示并设置脉冲宽度
    I2CStart();
    I2CWritebyte(0x8C); // 显示控制命令：开显示，脉冲宽度为11/16.
    I2CStop();
}

/**
 * @brief 处理按键输入并根据按键值执行相应的显示操作。
 *
 * 该函数读取按键输入值，并根据不同的按键值调用显示函数在屏幕上显示对应的内容。
 * 如果按键值为默认值（0xff），则不执行任何操作。
 *
 * @param 无参数
 * @return 无返回值
 */
void key_process(void)
{
    unsigned char temp;
    temp = read_key(); // 读取按键返回值

    // 检查按键值是否有效（非0xff）
    if (temp != 0xff)
    {
        MY_PRINTF("key=%X", temp);   // 打印按键值用于调试
        disp0((unsigned char *)TAB); // 清屏，准备显示新内容

        // 根据按键值执行不同的显示操作
        switch (temp)
        {
        case 0xf7:
            disp(0xc0, 1); // K1与SG1对应按键按下，显示1
            break;
        case 0xf6:
            disp(0xc1, 2); // K1与SG2对应按键按下，显示2
            break;
        case 0xf5:
            disp(0xc2, 3); // K1与SG3对应按键按下，显示3
            break;
        case 0xf4:
            disp(0xc3, 4); // K1与SG4对应按键按下，显示4
            break;
        case 0xef:
            disp(0xc4, 5); // K2与SG1对应按键按下，显示5
            break;
        case 0xee:
            disp(0xc5, 6); // K2与SG2对应按键按下，显示6
            break;
        case 0xed:
            disp(0xc0, 7); // K2与SG3对应按键按下，显示7
            break;
        case 0xec:
            disp(0xc1, 8); // K2与SG4对应按键按下，显示8
            break;
        case 0xeb:
            disp(0xc2, 9); // K3与SG1对应按键按下，显示9
            break;
        case 0xea:
            disp(0xc4, 1);
            disp(0xc5, 0); // 特殊组合按键，显示10
            break;
        case 0xe9:
            disp(0xc4, 1);
            disp(0xc5, 1); // 特殊组合按键，显示11
            break;
        case 0xe8:
            disp(0xc4, 1);
            disp(0xc5, 2); // 特殊组合按键，显示12
            break;
        case 0xf3:
            disp(0xc4, 1);
            disp(0xc5, 3); // 特殊组合按键，显示13
            break;
        case 0xf2:
            disp(0xc4, 1);
            disp(0xc5, 4); // 特殊组合按键，显示14
            break;
        case 0xf1:
            disp(0xc4, 1);
            disp(0xc5, 5); // 特殊组合按键，显示15
            break;
        case 0xf0:
            disp(0xc4, 1);
            disp(0xc5, 6); // 特殊组合按键，显示16
            break;
        default:
            break; // 未定义的按键值，不做处理
        }
    }
}

/**
 * @brief 初始化TM1637驱动的GPIO引脚并显示默认内容。
 *
 * 该函数完成以下操作：
 * 1. 使能GPIOA时钟；
 * 2. 配置PA5（SCL）和PA6（SDA）为开漏输出模式，并启用内部上拉电阻；
 * 3. 设置引脚的速度等级为中速；
 * 4. 调用disp0函数显示默认内容。
 *
 * @param 无
 * @return 无
 */
void tm1637_init(void)
{
    // 使能GPIOA时钟，确保GPIOA外设可用
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

    // 配置PA5（SCL）引脚
    LL_GPIO_SetPinMode(TM_SCL_PORT, TM_SCL_PIN, LL_GPIO_MODE_OUTPUT);            // 设置为输出模式
    LL_GPIO_SetPinOutputType(TM_SCL_PORT, TM_SCL_PIN, LL_GPIO_OUTPUT_OPENDRAIN); // 设置为开漏输出
    LL_GPIO_SetPinPull(TM_SCL_PORT, TM_SCL_PIN, LL_GPIO_PULL_UP);                // 启用内部上拉电阻
    LL_GPIO_SetPinSpeed(TM_SCL_PORT, TM_SCL_PIN, LL_GPIO_SPEED_FREQ_MEDIUM);     // 设置速度等级为中速

    // 配置PA6（SDA）引脚
    LL_GPIO_SetPinMode(TM_SDA_PORT, TM_SDA_PIN, LL_GPIO_MODE_OUTPUT);            // 设置为输出模式
    LL_GPIO_SetPinOutputType(TM_SDA_PORT, TM_SDA_PIN, LL_GPIO_OUTPUT_OPENDRAIN); // 设置为开漏输出
    LL_GPIO_SetPinPull(TM_SDA_PORT, TM_SDA_PIN, LL_GPIO_PULL_UP);                // 启用内部上拉电阻
    LL_GPIO_SetPinSpeed(TM_SDA_PORT, TM_SDA_PIN, LL_GPIO_SPEED_FREQ_MEDIUM);     // 设置速度等级为中速

    // 调用disp0函数显示默认内容
    disp0((unsigned char *)CODE);
}
