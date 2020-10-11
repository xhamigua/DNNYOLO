#ifndef YOLO_INTFACE_H
#define YOLO_INTFACE_H

#include <vector>
#include "yolodef.h"
#include "box.h"

class SQCPP_API yolo_mo
{
public:
    yolo_mo();
    ~yolo_mo();
public:
    //��ʼ����ȡģ��
    void initcfg(char* datacfg, char* cfgfile, char* weightfile, float thresh, int slen);
    void morelease(void);
    //���Ҫ�Ž������߳�����
    void yolo_detect(unsigned char* buffimg, std::vector<box>& boxs);
private:
    float thresh;
    float hier_thresh;
    int ext_output;
    int letter_box;
    int len;                //ͼƬsize
};





#endif


