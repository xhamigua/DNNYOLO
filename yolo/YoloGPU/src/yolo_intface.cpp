
#include "stdafx.h"
#include "yolo_intface.h"
#include "data.h"
#include "image.h"
#include "network.h"
#include "http_stream.h"

#include "region_layer.h"
#include "cost_layer.h"
#include "utils.h"
#include "parser.h"
#include "demo.h"
#include "option_list.h"

struct YNET
{
    static YNET* Inst()
    {
        if (NULL == _instance)
            _instance = new YNET();
        return _instance;
    };
    network net;
    list* options;
    char** names;
    image** alphabet;
protected:
    YNET(void)
    {
    };
private:
    static YNET* _instance;
};

YNET* YNET::_instance = 0;

yolo_mo::yolo_mo():thresh(.25)
, hier_thresh(.5)
, ext_output(0)
, letter_box(0)
{
    YNET::Inst();
}

yolo_mo::~yolo_mo()
{
}

void yolo_mo::initcfg(char* datacfg, char* cfgfile, char* weightfile, float thresh,int slen)
{
    len = slen;
    // thresh .25  hier_thresh .5 ext_output 0 letter_box 0
    YNET::Inst()->options = read_data_cfg(datacfg);
    char* name_list = option_find_str(YNET::Inst()->options, "names", "data/names.list");
    int names_size = 0;
    YNET::Inst()->names = get_labels_custom(name_list, &names_size);
    YNET::Inst()->alphabet = load_alphabet();
    //º”‘ÿyolo≈‰÷√
    auto& net = YNET::Inst()->net;
    net = parse_network_cfg_custom(cfgfile, 1, 1);
    //º”‘ÿ»®÷ÿŒƒº˛
    if (weightfile)
        load_weights(&net, weightfile);
    fuse_conv_batchnorm(net);
    calculate_binary_weights(net);
    if (net.layers[net.n - 1].classes != names_size)
    {
        if (net.layers[net.n - 1].classes > names_size)
            return;
    }
}

void yolo_mo::morelease(void)
{
    // free memory
    free_ptrs((void**)YNET::Inst()->names, YNET::Inst()->net.layers[YNET::Inst()->net.n - 1].classes);
    free_list_contents_kvp(YNET::Inst()->options);
    free_list(YNET::Inst()->options);
    if (len == 0)
    {
        const int nsize = 8;
        for (int j = 0; j < nsize; ++j)
        {
            for (int i = 32; i < 127; ++i)
                free_image(YNET::Inst()->alphabet[j][i]);
            free(YNET::Inst()->alphabet[j]);
        }
        free(YNET::Inst()->alphabet);
    }
    free_network(YNET::Inst()->net);
}

void yolo_mo::yolo_detect(unsigned char* buffimg, std::vector<box>& boxs)
{
    float nms = .45;    // 0.4F
    image im;
    if (len == 0)
        im = load_image((char*)buffimg, 0, 0, YNET::Inst()->net.c);
    else
        //ƒ⁄¥Ê∂¡»°Õº∆¨
        im = load_image_buf(buffimg, len);
    image sized;
    if (letter_box)
        sized = letterbox_image(im, YNET::Inst()->net.w, YNET::Inst()->net.h);
    else
        sized = resize_image(im, YNET::Inst()->net.w, YNET::Inst()->net.h);
    layer l = YNET::Inst()->net.layers[YNET::Inst()->net.n - 1];
    float* X = sized.data;
    double time = get_time_point();
    //…Ó∂»Õ¯¬ÁºÏ≤‚
    network_predict(YNET::Inst()->net, X);
    printf("Predicted in %lf milli-seconds.\n", ((double)get_time_point() - time) / 1000);
    int nboxes = 0;
    detection* dets = get_network_boxes(&YNET::Inst()->net, im.w, im.h, thresh, hier_thresh, 0, 1, &nboxes, letter_box);
    if (nms)
        do_nms_sort(dets, nboxes, l.classes, nms);
    //º∆À„ºÏ≤‚◊¯±Í
    int selected_detections_num;
    detection_with_class* selected_detections = get_actual_detections(dets, nboxes, thresh, &selected_detections_num, YNET::Inst()->names);
    // image output
    qsort(selected_detections, selected_detections_num, sizeof(*selected_detections), compare_by_probs);
    boxs.clear();
    for (int i = 0; i < selected_detections_num; ++i)
    {
        box b = selected_detections[i].det.bbox;
        box boxout;
        int left = (b.x - b.w / 2.) * im.w;
        int right = (b.x + b.w / 2.) * im.w;
        int top = (b.y - b.h / 2.) * im.h;
        int bot = (b.y + b.h / 2.) * im.h;
        if (left < 0)
            left = 0;
        if (right > im.w - 1)
            right = im.w - 1;
        if (top < 0)
            top = 0;
        if (bot > im.h - 1)
            bot = im.h - 1;
        boxout.x = left;
        boxout.y = top;
        boxout.w = right - left;
        boxout.h = bot - top;
        //ºÚµ• ‰≥ˆ
        boxs.push_back(boxout);
    }
    free(selected_detections);
    if (len == 0)
    {
        //ªÊ÷∆ºÏ≤‚Õº∆¨
        draw_detections_v3(im, dets, nboxes, thresh, YNET::Inst()->names, YNET::Inst()->alphabet, l.classes, ext_output);
        //±£¥ÊºÏ≤‚Õº∆¨
        //save_image(im, "predictions");
        show_image(im, "predictions");
        wait_until_press_key_cv();
        destroy_all_windows_cv();
    }
    free_detections(dets, nboxes);
    free_image(im);
    free_image(sized);
}



