/*****************************************************************************
*��Ȩ��Ϣ��������΢�������޹�˾
*�� �� ����TM1637-V1.0
*��ǰ�汾��V1.0
*MCU �ͺţ�STC12C5608AD
*����Ƶ�ʣ�11.0592MHZ
*������ڣ�2013-07-19
*�����ܣ�����������Ͱ���������8��6λLED�����������ʾ,����Ӧ��������ʱ��ʾ1~7,ԭ��ͼ��ο�TM1637����飻
*����������1.�˳���ΪTM1637��������LED����ܺͰ�����ʾ���򣬽����ο�֮�á�
		   2.����ֱ��ʹ�ñ����̳�����ɾ�����ʧ�ģ�����˾���е��κ�����
********************************************************************************/
#include <reg52.h>	 //ͷ�ļ�
#include "intrins.h" //����_nop_()ָ��ͷ�ļ�

#define nop  \
	_nop_(); \
	_nop_(); \
	_nop_(); \
	_nop_(); \
	_nop_(); // �궨��

/********************������ƶ˿�**********************/
sbit CLK = P2 ^ 2; // ����CLK
sbit DIO = P2 ^ 3; // ����DIO

/********************��������*************************/
unsigned char code CODE[10] = {
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
unsigned char code TAB[10] = {
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

/********************��ʱ��������ʱnms******************/
void delay_nms(unsigned int n)
{
	unsigned int i;
	while (n--)
		for (i = 0; i < 550; i++)
			;
}

/********************Start����*************************/
void I2CStart()
{
	DIO = 1;
	CLK = 1;
	nop;
	DIO = 1;
	nop;
	DIO = 0;
	nop;
	CLK = 0;
}

/********************Stop����*************************/
void I2CStop()
{
	CLK = 0;
	nop;
	nop;
	DIO = 0;
	nop;
	nop;
	CLK = 1;
	nop;
	nop;
	nop;
	DIO = 1;
	nop;
	CLK = 0;
	DIO = 0;
}

/***************����8bit���ݣ��ӵ�λ��ʼ**************/
void I2CWritebyte(unsigned char oneByte)
{
	unsigned char i;
	for (i = 0; i < 8; i++)
	{
		CLK = 0;
		if (oneByte & 0x01)
			DIO = 1;
		else
			DIO = 0;
		nop;
		CLK = 1;
		oneByte = oneByte >> 1;
	}
	// 8λ���ݴ�����
	CLK = 0; // �ж�оƬ��������ACKӦ���ź�
	nop;
	while (DIO == 1)
		;
	nop;
	CLK = 1;
	nop;
}

/***************����������**************/
unsigned char read_key()
{
	unsigned char rekey, i;
	I2CStart();
	I2CWritebyte(0x42); // д����ָ��0x42
	DIO = 1;			// �ͷ�DIO
	for (i = 0; i < 8; i++)
	{
		CLK = 0;
		nop;
		nop;
		rekey = rekey >> 1; // �ȶ���λ
		nop;
		nop;
		CLK = 1;
		if (DIO)
			rekey = rekey | 0x80;
		else
			rekey = rekey | 0x00;
		nop;
	}
	CLK = 0; // �ж�оƬ��������ACKӦ���ź�
	nop;
	nop;
	while (DIO == 1)
		;
	nop;
	nop;
	CLK = 1;
	nop;
	nop;
	I2CStop();

	return rekey;
}

/************��ʾ��������ַ�Լ�һ************/
void disp0(unsigned char *p)
{
	unsigned char i;
	I2CStart();
	I2CWritebyte(0x40); // �����������ã���ַ�Զ���1��д���ݵ���ʾ�Ĵ���
	I2CStop();

	I2CStart();
	I2CWritebyte(0xc0);		// ��ַ�������ã���ʼ��ַΪ00H
	for (i = 0; i < 6; i++) // ����4�ֽ����ݵ��Դ�
	{
		I2CWritebyte(*p);
		p++;
	}
	I2CStop();

	I2CStart();
	I2CWritebyte(0x8C); // ��ʾ�����������ʾ��������Ϊ11/16.
	I2CStop();
}

/************��ʾ�������̶���ַд����************/
void disp(unsigned char add, unsigned char value)
{
	I2CStart();
	I2CWritebyte(0x44); // �����������ã��̶���ַ��д���ݵ���ʾ�Ĵ���
	I2CStop();

	I2CStart();
	I2CWritebyte(add); // ��ַ�������ã�д��add��Ӧ��ַ

	I2CWritebyte(CODE[value]); // ��add��ַд����
	I2CStop();

	I2CStart();
	I2CWritebyte(0x8C); // ��ʾ�����������ʾ��������Ϊ11/16.
	I2CStop();
}

/************�������������������ݵ�λ��ǰ��λ�ں�************/
void key_process()
{
	unsigned char temp;
	temp = read_key(); // ��ȡ��������ֵ
	if (temp != 0xff)
	{
		disp0(TAB); // ����
		switch (temp)
		{
		case 0xf7:
			disp(0xc0, 1);
			break; // K1��SG1��Ӧ��������,��ʾ1
		case 0xf6:
			disp(0xc1, 2);
			break; // K1��SG2��Ӧ��������,��ʾ2
		case 0xf5:
			disp(0xc2, 3);
			break; // K1��SG3��Ӧ��������,��ʾ3
		case 0xf4:
			disp(0xc3, 4);
			break; // K1��SG4��Ӧ��������,��ʾ4
		case 0xef:
			disp(0xc4, 5);
			break; // K2��SG1��Ӧ��������,��ʾ5
		case 0xee:
			disp(0xc5, 6);
			break; // K2��SG2��Ӧ��������,��ʾ6
		case 0xed:
			disp(0xc0, 7);
			break; // K2��SG3��Ӧ��������,��ʾ7
		default:
			break;
		}
	}
}

void main()
{

	disp0(CODE); // �ϵ��������ʾ0~5
	delay_nms(1);
	while (1) // ��������ʾ��������
	{
		key_process();
		delay_nms(100);
	}
}