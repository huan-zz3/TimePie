#include "GT1151.h"

GT1151_Dev Dev_Now, Dev_Old;
UBYTE GT_Gesture_Mode = 0;

// 定义一个名为 GT_Reset 的函数，用于重置设备
void GT_Reset(void)
{
	TRST_1;
	DEV_Delay_ms(100);
	TRST_0;
	DEV_Delay_ms(100);
	TRST_1;
	DEV_Delay_ms(100);
}

void GT_Write(UWORD Reg, char *Data, UBYTE len)
{
	I2C_Write_Byte(Reg, Data, len);
}

void GT_Read(UWORD Reg, char *Data, UBYTE len)
{
	I2C_Read_Byte(Reg, Data, len);
}

void GT_ReadVersion(void)
{
	char buf[4];
	GT_Read(0x8140, buf, 4);
	printf("Product ID is %c %c %c %c \r\n", buf[0], buf[1], buf[2], buf[3]);
}

void GT_Init(void)
{
	GT_Reset();
	GT_ReadVersion();
}

// 灭屏后进入 Gesture 模式
void GT_Gesture(void)
{
	char buf[3] = {0x08, 0x00, 0xf8};
	GT_Write(0x8040, &buf[0], 1);
	GT_Write(0x8041, &buf[1], 1);
	GT_Write(0x8042, &buf[2], 1);
	GT_Gesture_Mode = 1;
	printf("into gesture mode \r\n");
	DEV_Delay_ms(100);
}
// 在手势模式下检测是否有双击手势。如果有双击手势，模组会退出手势模式并复位，同时保存当前的触摸坐标和大小。如果没有检测到双击手势，则清除手势识别结果，以便下一次检测。
void GT_Gesture_Scan(void)
{
	char buf;
	GT_Read(0x814c, &buf, 1); // 读取手势识别结果
	if (buf == 0xcc)		  // 判断是否为双击手势
	{
		printf("gesture mode exiting \r\n"); // 打印退出手势模式的信息
		GT_Gesture_Mode = 0;				 // 退出手势模式
		GT_Reset();							 // 复位模组
		Dev_Old.X[0] = Dev_Now.X[0];		 // 保存当前的X坐标
		Dev_Old.Y[0] = Dev_Now.Y[0];		 // 保存当前的Y坐标
		Dev_Old.S[0] = Dev_Now.S[0];		 // 保存当前的触摸大小
	}
	else
	{
		buf = 0x00;				   // 清除手势识别结果
		GT_Write(0x814c, &buf, 1); // 写回0x814c寄存器
	}
}

// 这段代码的主要功能是在检测到触摸时，根据模组当前的工作模式（手势模式或非手势模式）进行不同的处理。
// 在手势模式下，调用手势模式扫描函数；在非手势模式下，读取触摸数据并解析，然后清除数据标志位。
// 如果触摸点个数不合理或没有新的触摸数据，代码会清除数据标志位并返回 1。
// 如果触摸点个数合理且存在新的触摸数据，代码会解析触摸数据并返回 0。
UBYTE GT_Scan(void)
{
	char buf[100];
	char mask[1] = {0x00};

	// if(DEV_Digital_Read(INT) == 0) { // 如果检测到触摸
	// 	Dev_Now.Touch = 1; // 标记为有触摸
	// 	static size_t i = 0;
	// 	Debug( "Touched: %d\n", i++);
	// } else {
	// 	Dev_Now.Touch = 0; // 否则标记为无触摸
	// }
	// Debug("enter GT_Scan \n");
	// printf("enter GT_Scan \n");
	// Debug("Dev_Now address is %p (GT1151)\n", (void *)&Dev_Now);

	if (Dev_Now.Touch == 1)
	{
		// Dev_Now.Touch = 0;
		if (GT_Gesture_Mode == 1)
		{
			GT_Gesture_Scan();
			Debug("GT_Gesture_Scan \n");
			return 1;
		}
		else
		{
			GT_Read(0x814E, buf, 1);
			if ((buf[0] & 0x80) == 0x00)// 读取bit7 BufferStatus，1 表示坐标（或按键）已经准备好，主控可以读取；0 表示未就绪，数据无效。
			{							   
				GT_Write(0x814E, mask, 1); // 整个字节写为0
				DEV_Delay_ms(100);
				// Debug("buffers status is 0 \n");
				return 1;
			}
			else
			{
				// Debug("buffers status is 1 \n");
				Dev_Now.TouchpointFlag = buf[0] & 0x80;
				Dev_Now.TouchCount = buf[0] & 0x0f;
				if (Dev_Now.TouchCount > 5 || Dev_Now.TouchCount < 1)
				{
					GT_Write(0x814E, mask, 1);
					// Debug("TouchCount number is wrong \n");
					return 1;
				}
				GT_Read(0x814F, &buf[1], Dev_Now.TouchCount * 8); // 读取手势辅助信息
				GT_Write(0x814E, mask, 1);

				Dev_Old.X[0] = Dev_Now.X[0];
				Dev_Old.Y[0] = Dev_Now.Y[0];
				Dev_Old.S[0] = Dev_Now.S[0];

				for (UBYTE i = 0; i < Dev_Now.TouchCount; i++)
				{
					Dev_Now.Touchkeytrackid[i] = buf[1 + 8 * i];
					Dev_Now.X[i] = ((UWORD)buf[3 + 8 * i] << 8) + buf[2 + 8 * i];
					Dev_Now.Y[i] = ((UWORD)buf[5 + 8 * i] << 8) + buf[4 + 8 * i];
					Dev_Now.S[i] = ((UWORD)buf[7 + 8 * i] << 8) + buf[6 + 8 * i];
				}

				for (UBYTE i = 0; i < Dev_Now.TouchCount; i++)
					Debug("Point %d: X is %d, Y is %d, Size is %d \n", i + 1, Dev_Now.X[i], Dev_Now.Y[i], Dev_Now.S[i]);
				return 0;
			}
		}
	}
	return 1;
}

// 为避免自定义修改影响原有函数工作，新增一个函数 GT_Scan_2，功能与 GT_Scan 相同
UBYTE GT_Scan_2(void)
{
	char buf[100];
	char mask[1] = {0x00};

	if(DEV_Digital_Read(INT) == 0) { // 如果检测到触摸
		Dev_Now.Touch = 1; // 标记为有触摸
		static size_t i = 0;
		// Debug( "Touched: %d\n", i++);
	} else {
		Dev_Now.Touch = 0; // 否则标记为无触摸
	}

	// Debug("Dev_Now address is %p (GT1151)\n", (void *)&Dev_Now);

	if (Dev_Now.Touch == 1)
	{
		// Dev_Now.Touch = 0;
		if (GT_Gesture_Mode == 1)
		{
			GT_Gesture_Scan();
			Debug("GT_Gesture_Scan \n");
			return 1;
		}
		else
		{
			GT_Read(0x814E, buf, 1);
			if ((buf[0] & 0x80) == 0x00)// 读取bit7 BufferStatus，1 表示坐标（或按键）已经准备好，主控可以读取；0 表示未就绪，数据无效。
			{							   
				GT_Write(0x814E, mask, 1); // 整个字节写为0
				DEV_Delay_ms(100);
				// Debug("buffers status is 0 \n");
				return 1;
			}
			else
			{
				// Debug("buffers status is 1 \n");
				Dev_Now.TouchpointFlag = buf[0] & 0x80;
				Dev_Now.TouchCount = buf[0] & 0x0f;
				if (Dev_Now.TouchCount > 5 || Dev_Now.TouchCount < 1)
				{
					GT_Write(0x814E, mask, 1);
					// Debug("TouchCount number is wrong \n");
					return 1;
				}
				GT_Read(0x814F, &buf[1], Dev_Now.TouchCount * 8); // 读取手势辅助信息
				GT_Write(0x814E, mask, 1);

				Dev_Old.X[0] = Dev_Now.X[0];
				Dev_Old.Y[0] = Dev_Now.Y[0];
				Dev_Old.S[0] = Dev_Now.S[0];

				for (UBYTE i = 0; i < Dev_Now.TouchCount; i++)
				{
					Dev_Now.Touchkeytrackid[i] = buf[1 + 8 * i];
					Dev_Now.X[i] = ((UWORD)buf[3 + 8 * i] << 8) + buf[2 + 8 * i];
					Dev_Now.Y[i] = ((UWORD)buf[5 + 8 * i] << 8) + buf[4 + 8 * i];
					Dev_Now.S[i] = ((UWORD)buf[7 + 8 * i] << 8) + buf[6 + 8 * i];
				}

				for (UBYTE i = 0; i < Dev_Now.TouchCount; i++)
					Debug("Point %d: X is %d, Y is %d, Size is %d \n", i + 1, Dev_Now.X[i], Dev_Now.Y[i], Dev_Now.S[i]);
				return 0;
			}
		}
	}
	return 1;
}