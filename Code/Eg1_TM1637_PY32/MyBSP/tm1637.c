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
}; // ���������0~9������
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
}; // ����ܲ���ʾ

/********************Start����*************************/
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
 * @brief ����I2Cֹͣ�źš�
 *
 * �ú���ͨ������SCL��SDA���ŵ�״̬�仯�����ɷ���I2CЭ���ֹͣ�źš�
 * ֹͣ�źŵ�ʱ��������²��裺
 * 1. ��SCL���͡�
 * 2. ��SDA���͡�
 * 3. ��SCL���ߡ�
 * 4. ��SDA���ߣ����ֹͣ�źŵķ��͡�
 *
 * @note �ú������������º궨�����ʵ�֣�
 *       - TM_SCL_LOW(): ��SCL��������Ϊ�͵�ƽ��
 *       - TM_SDA_LOW(): ��SDA��������Ϊ�͵�ƽ��
 *       - TM_SCL_HIGH(): ��SCL��������Ϊ�ߵ�ƽ��
 *       - TM_SDA_HIGH(): ��SDA��������Ϊ�ߵ�ƽ��
 *       - delay_us(us): ��ʱָ����΢������
 *       - TM_DELAY_TIME: ������ʱ��ʱ�䳤�ȣ���λ��΢�룩��
 *
 * @return �޷���ֵ��
 */
void I2CStop()
{
    // ����SCL���ţ�׼����ʼֹͣ�źŵ�ʱ��
    TM_SCL_LOW();
    delay_us(TM_DELAY_TIME);

    // ����SDA���ţ�ȷ�������ߴ��ڵ͵�ƽ״̬
    TM_SDA_LOW();
    delay_us(TM_DELAY_TIME);

    // ����SCL���ţ��ͷ�ʱ����
    TM_SCL_HIGH();
    delay_us(TM_DELAY_TIME);

    // ����SDA���ţ�����ֹͣ�źŵĹؼ�����
    TM_SDA_HIGH();
    delay_us(TM_DELAY_TIME);

    // ���ս�SCL��SDA�ָ�����ʼ״̬���͵�ƽ��
    TM_SCL_LOW();
    TM_SDA_LOW();
}

/**
 * @brief ͨ��I2CЭ�鷢��һ���ֽڵ����ݡ�
 *
 * �ú����������һ���ֽ�����ͨ��I2C������λ���ͣ����λ�ȷ��͡�
 * ������ɺ󣬵ȴ����豸��ACKӦ���źš�
 *
 * @param oneByte Ҫ���͵��ֽ����ݣ�8λ����
 * @return �޷���ֵ��
 */
void I2CWritebyte(uint8_t oneByte)
{
    uint8_t i;

    // ѭ������һ���ֽڵ�ÿһλ�������λ��ʼ��
    for (i = 0; i < 8; i++)
    {
        TM_SCL_LOW();       // ����SCLʱ���ߣ�׼����������
        if (oneByte & 0x01) // �жϵ�ǰλ�Ƿ�Ϊ1
            TM_SDA_HIGH();  // ���Ϊ1������SDAΪ�ߵ�ƽ
        else
            TM_SDA_LOW();        // ���Ϊ0������SDAΪ�͵�ƽ
        delay_us(TM_DELAY_TIME); // ��ʱ��ȷ���ź��ȶ�
        TM_SCL_HIGH();           // ����SCLʱ���ߣ����һλ���ݵķ���
        oneByte = oneByte >> 1;  // ���ֽ�����һλ��׼��������һλ
    }

    // 8λ���ݷ�����ɣ�����ACKӦ��׶�
    TM_SCL_LOW();            // ����SCLʱ���ߣ�׼������ACK�ź�
    delay_us(TM_DELAY_TIME); // ��ʱ��ȷ���ź��ȶ�

    // �ȴ����豸����SDA���Է���ACK�ź�
    while (TM_SDA_STA() == 1)
        ;

    delay_us(TM_DELAY_TIME); // ��ʱ��ȷ��ACK�źű���ȷ��ȡ
    TM_SCL_HIGH();           // ����SCLʱ���ߣ�����ACKӦ��׶�
    delay_us(TM_DELAY_TIME); // ��ʱ��ȷ���ź��ȶ�
}

/**
 * ��������: disp0
 * ��������: ͨ��I2CЭ������ʾ�豸�������ݣ������ʾ�Ĵ����ĳ�ʼ��������д�롣
 * ����˵��:
 *     p - ָ��Ҫ���͵����ݻ�������ָ�룬����Ϊunsigned char*��
 * ����ֵ: ��
 * ע������:
 *     1. �ú���������I2CStart��I2CWritebyte��I2CStop�ȵײ�I2Cͨ�ź�����
 *     2. ���ݻ�����p�������ٰ���6�ֽڵ���Ч���ݡ�
 */
void disp0(unsigned char *p)
{
    unsigned char i;

    // ����I2C��ʼ�źţ����������������ַ�Զ���1��д���ݵ���ʾ�Ĵ���
    I2CStart();
    I2CWritebyte(0x40);
    I2CStop();

    // ����I2C��ʼ�źţ������õ�ַ�����ʼ��ַΪ00H
    I2CStart();
    I2CWritebyte(0xc0);

    // ѭ������6�ֽ����ݵ��Դ�
    for (i = 0; i < 6; i++)
    {
        I2CWritebyte(*p);
        p++;
    }
    I2CStop();

    // ����I2C��ʼ�źţ���������ʾ�����������ʾ��������Ϊ11/16
    I2CStart();
    I2CWritebyte(0x8C);
    I2CStop();
}

/**
 * @brief ��ȡ����ֵ�ĺ�����
 *
 * �ú���ͨ��I2CЭ�����ⲿ�豸ͨ�ţ���ȡһ���ֽڵİ���ֵ��
 * �������̰�������I2Cͨ�š����Ͷ���ָ���λ��ȡ���ݡ�����ACKӦ���źţ������շ��ض�ȡ���İ���ֵ��
 *
 * @return unsigned char ���ض�ȡ���İ���ֵ��һ���ֽڣ���
 */
unsigned char read_key()
{
    unsigned char rekey, i;

    // ����I2Cͨ��
    I2CStart();

    // ���Ͷ���ָ��0x42
    I2CWritebyte(0x42);

    // �ͷ�SDA�ߣ�׼����������
    TM_SDA_HIGH();

    // ѭ����ȡ8λ���ݣ��ӵ�λ��ʼ
    for (i = 0; i < 8; i++)
    {
        TM_SCL_LOW();
        delay_us(TM_DELAY_TIME);

        // ���Ѷ�ȡ����������һλ��Ϊ�������ڳ��ռ�
        rekey = rekey >> 1;

        delay_us(TM_DELAY_TIME);
        TM_SCL_HIGH();

        // ����SDA��״̬�жϵ�ǰλ��ֵ��������rekey
        if (TM_SDA_STA())
            rekey = rekey | 0x80;
        else
            rekey = rekey | 0x00;

        delay_us(1);
    }

    // ����SCL�ߣ�׼������ACKӦ���ź�
    TM_SCL_LOW();
    delay_us(TM_DELAY_TIME);

    // �ȴ�SDA�߱�Ϊ�͵�ƽ����ʾ���յ�ACK�ź�
    while (TM_SDA_STA() == 1)
        ;

    delay_us(TM_DELAY_TIME);

    // ����SCL�ߣ����ACK�źŴ���
    TM_SCL_HIGH();
    delay_us(TM_DELAY_TIME);

    // ֹͣI2Cͨ��
    I2CStop();

    // ���ض�ȡ���İ���ֵ
    return rekey;
}
/************��ʾ�������̶���ַд����************/
/**
 * disp - ����ʾ�豸��ָ����ַд�����ݲ�������ʾ��
 *
 * ����:
 *   add   - Ŀ���ַ������ָ����ʾ�豸�ļĴ�����ַ��
 *   value - Ҫд�������ֵ��ͨ��CODE����ӳ��Ϊʵ�ʵ���ʾ���ݡ�
 *
 * ����ֵ:
 *   �޷���ֵ��
 *
 * ��������:
 *   �ú���ͨ��I2CЭ������ʾ�豸������������ݣ�������²�����
 *   1. ������ʾ�Ĵ����Ĺ̶���ַ��
 *   2. ��ָ����ַд��ӳ������ʾ���ݡ�
 *   3. ������ʾ���������Կ�����ʾ�����������ȡ�
 */
void disp(unsigned char add, unsigned char value)
{
    // ����I2Cͨ�Ų����͹̶���ַ���׼��д����ʾ�Ĵ���
    I2CStart();
    I2CWritebyte(0x44); // �����������ã��̶���ַ��д���ݵ���ʾ�Ĵ���
    I2CStop();

    // ����I2Cͨ�Ų�����Ŀ���ַ���׼��д��add��Ӧ��ַ
    I2CStart();
    I2CWritebyte(add); // ��ַ�������ã�д��add��Ӧ��ַ

    // ��Ŀ���ַд��ӳ������ʾ����
    I2CWritebyte(CODE[value]); // ��add��ַд����
    I2CStop();

    // ����I2Cͨ�Ų�������ʾ�������������ʾ������������
    I2CStart();
    I2CWritebyte(0x8C); // ��ʾ�����������ʾ��������Ϊ11/16.
    I2CStop();
}

/**
 * @brief ���������벢���ݰ���ִֵ����Ӧ����ʾ������
 *
 * �ú�����ȡ��������ֵ�������ݲ�ͬ�İ���ֵ������ʾ��������Ļ����ʾ��Ӧ�����ݡ�
 * �������ֵΪĬ��ֵ��0xff������ִ���κβ�����
 *
 * @param �޲���
 * @return �޷���ֵ
 */
void key_process(void)
{
    unsigned char temp;
    temp = read_key(); // ��ȡ��������ֵ

    // ��鰴��ֵ�Ƿ���Ч����0xff��
    if (temp != 0xff)
    {
        MY_PRINTF("key=%X", temp);   // ��ӡ����ֵ���ڵ���
        disp0((unsigned char *)TAB); // ������׼����ʾ������

        // ���ݰ���ִֵ�в�ͬ����ʾ����
        switch (temp)
        {
        case 0xf7:
            disp(0xc0, 1); // K1��SG1��Ӧ�������£���ʾ1
            break;
        case 0xf6:
            disp(0xc1, 2); // K1��SG2��Ӧ�������£���ʾ2
            break;
        case 0xf5:
            disp(0xc2, 3); // K1��SG3��Ӧ�������£���ʾ3
            break;
        case 0xf4:
            disp(0xc3, 4); // K1��SG4��Ӧ�������£���ʾ4
            break;
        case 0xef:
            disp(0xc4, 5); // K2��SG1��Ӧ�������£���ʾ5
            break;
        case 0xee:
            disp(0xc5, 6); // K2��SG2��Ӧ�������£���ʾ6
            break;
        case 0xed:
            disp(0xc0, 7); // K2��SG3��Ӧ�������£���ʾ7
            break;
        case 0xec:
            disp(0xc1, 8); // K2��SG4��Ӧ�������£���ʾ8
            break;
        case 0xeb:
            disp(0xc2, 9); // K3��SG1��Ӧ�������£���ʾ9
            break;
        case 0xea:
            disp(0xc4, 1);
            disp(0xc5, 0); // ������ϰ�������ʾ10
            break;
        case 0xe9:
            disp(0xc4, 1);
            disp(0xc5, 1); // ������ϰ�������ʾ11
            break;
        case 0xe8:
            disp(0xc4, 1);
            disp(0xc5, 2); // ������ϰ�������ʾ12
            break;
        case 0xf3:
            disp(0xc4, 1);
            disp(0xc5, 3); // ������ϰ�������ʾ13
            break;
        case 0xf2:
            disp(0xc4, 1);
            disp(0xc5, 4); // ������ϰ�������ʾ14
            break;
        case 0xf1:
            disp(0xc4, 1);
            disp(0xc5, 5); // ������ϰ�������ʾ15
            break;
        case 0xf0:
            disp(0xc4, 1);
            disp(0xc5, 6); // ������ϰ�������ʾ16
            break;
        default:
            break; // δ����İ���ֵ����������
        }
    }
}

/**
 * @brief ��ʼ��TM1637������GPIO���Ų���ʾĬ�����ݡ�
 *
 * �ú���������²�����
 * 1. ʹ��GPIOAʱ�ӣ�
 * 2. ����PA5��SCL����PA6��SDA��Ϊ��©���ģʽ���������ڲ��������裻
 * 3. �������ŵ��ٶȵȼ�Ϊ���٣�
 * 4. ����disp0������ʾĬ�����ݡ�
 *
 * @param ��
 * @return ��
 */
void tm1637_init(void)
{
    // ʹ��GPIOAʱ�ӣ�ȷ��GPIOA�������
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

    // ����PA5��SCL������
    LL_GPIO_SetPinMode(TM_SCL_PORT, TM_SCL_PIN, LL_GPIO_MODE_OUTPUT);            // ����Ϊ���ģʽ
    LL_GPIO_SetPinOutputType(TM_SCL_PORT, TM_SCL_PIN, LL_GPIO_OUTPUT_OPENDRAIN); // ����Ϊ��©���
    LL_GPIO_SetPinPull(TM_SCL_PORT, TM_SCL_PIN, LL_GPIO_PULL_UP);                // �����ڲ���������
    LL_GPIO_SetPinSpeed(TM_SCL_PORT, TM_SCL_PIN, LL_GPIO_SPEED_FREQ_MEDIUM);     // �����ٶȵȼ�Ϊ����

    // ����PA6��SDA������
    LL_GPIO_SetPinMode(TM_SDA_PORT, TM_SDA_PIN, LL_GPIO_MODE_OUTPUT);            // ����Ϊ���ģʽ
    LL_GPIO_SetPinOutputType(TM_SDA_PORT, TM_SDA_PIN, LL_GPIO_OUTPUT_OPENDRAIN); // ����Ϊ��©���
    LL_GPIO_SetPinPull(TM_SDA_PORT, TM_SDA_PIN, LL_GPIO_PULL_UP);                // �����ڲ���������
    LL_GPIO_SetPinSpeed(TM_SDA_PORT, TM_SDA_PIN, LL_GPIO_SPEED_FREQ_MEDIUM);     // �����ٶȵȼ�Ϊ����

    // ����disp0������ʾĬ������
    disp0((unsigned char *)CODE);
}
