#ifndef PI
#define PI     3.1415926536
#endif // PI
/**
基本绘图：
用于GUI内容绘制的各种绘图函数
在指定Layer上用指定Pen进行绘制
基本绘图函数有：
点（实际效果是直径为Pen宽度的圆）
线段
空心圆
矩形
圆角矩形
油漆桶（封闭区域填充）

将myLayerArray中所有Enable并且Visible的Layer进行混合，输出到一个最终显示用的Layer上
创建内存DC和bitmap，使用BitBlt将最终Layer显示至窗口。
*/


