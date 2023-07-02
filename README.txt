USage

使用命令 /run.sh 运行脚本。
更改脚本中的采样数和测试语句，根据testcases/.txt的场景信息文件和mesh/.obj物体信息文件来生成bmp图像，保存在output文件夹中。

基础代码结构来自课程 base code，一些实现参考了开源代码。具体功能：

include文件夹中，
AABB.hpp实现包围盒检测，
kdtree.hpp实现高效存储三位面片和求交，
curve和revsurface是曲面和旋转曲面，
mystuff包括了一些自己定义的代码工具，

还有其余摄像头、场景、三维物体、材质、纹理等类信息。

渲染逻辑在 src/main.cpp 中，使用了蒙特卡洛光线追踪。

deps中的代码是课程实验给出已经写好的功能结构体和函数。