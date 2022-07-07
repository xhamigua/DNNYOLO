# AGANPlayer
AGANPlayer存放各视觉相关的工程，注意代码可能不是最新但会更新的。

## yolo文件夹
基于AB大神的darknet代码衍生一个代码整理版本 为了学习一下过程做了一些代码整理。训练和检测速度都挺好的。
将darknet模块在GPU依赖之间宏分离到各文件中整理了一下。因官方有了yolov4的升级将不再自己单独折腾，
目前训练和检测好用就不管了可能不是最完美的，有兴趣的的自己玩。

编译的成品下载(因包含模型和依赖文件有点大git不能放) 
链接：链接：https://pan.baidu.com/s/1tAAUZS4mN0x6S299HtiQ1g 提取码：dvvf
双击解包后在data文件夹有两个CS图标的 YoloCPU64 YoloGPU64程序,
在根目录里我写好了脚本可以参考类似predict_digger.cmd 里面的命令。

### darknet整合好后，开始训练起来
![Image text](https://raw.githubusercontent.com/xhamigua/DNNYOLO/master/IMG/darknet_lotus.png)







