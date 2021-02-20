#include "qpainterwrapper.h"

QVector<QRgb> QPainterWrapper::cmap = {
    0xff000003,
    0xff000004,
    0xff000006,
    0xff010007,
    0xff010109,
    0xff01010b,
    0xff02020d,
    0xff02020f,
    0xff030311,
    0xff040313,
    0xff040415,
    0xff050417,
    0xff060519,
    0xff07051b,
    0xff08061d,
    0xff09071f,
    0xff0a0722,
    0xff0b0824,
    0xff0c0926,
    0xff0d0a28,
    0xff0e0a2a,
    0xff0f0b2c,
    0xff100c2f,
    0xff110c31,
    0xff120d33,
    0xff140d35,
    0xff150e38,
    0xff160e3a,
    0xff170f3c,
    0xff180f3f,
    0xff1a1041,
    0xff1b1044,
    0xff1c1046,
    0xff1e1049,
    0xff1f114b,
    0xff20114d,
    0xff221150,
    0xff231152,
    0xff251155,
    0xff261157,
    0xff281159,
    0xff2a115c,
    0xff2b115e,
    0xff2d1060,
    0xff2f1062,
    0xff301065,
    0xff321067,
    0xff341068,
    0xff350f6a,
    0xff370f6c,
    0xff390f6e,
    0xff3b0f6f,
    0xff3c0f71,
    0xff3e0f72,
    0xff400f73,
    0xff420f74,
    0xff430f75,
    0xff450f76,
    0xff470f77,
    0xff481078,
    0xff4a1079,
    0xff4b1079,
    0xff4d117a,
    0xff4f117b,
    0xff50127b,
    0xff52127c,
    0xff53137c,
    0xff55137d,
    0xff57147d,
    0xff58157e,
    0xff5a157e,
    0xff5b167e,
    0xff5d177e,
    0xff5e177f,
    0xff60187f,
    0xff61187f,
    0xff63197f,
    0xff651a80,
    0xff661a80,
    0xff681b80,
    0xff691c80,
    0xff6b1c80,
    0xff6c1d80,
    0xff6e1e81,
    0xff6f1e81,
    0xff711f81,
    0xff731f81,
    0xff742081,
    0xff762181,
    0xff772181,
    0xff792281,
    0xff7a2281,
    0xff7c2381,
    0xff7e2481,
    0xff7f2481,
    0xff812581,
    0xff822581,
    0xff842681,
    0xff852681,
    0xff872781,
    0xff892881,
    0xff8a2881,
    0xff8c2980,
    0xff8d2980,
    0xff8f2a80,
    0xff912a80,
    0xff922b80,
    0xff942b80,
    0xff952c80,
    0xff972c7f,
    0xff992d7f,
    0xff9a2d7f,
    0xff9c2e7f,
    0xff9e2e7e,
    0xff9f2f7e,
    0xffa12f7e,
    0xffa3307e,
    0xffa4307d,
    0xffa6317d,
    0xffa7317d,
    0xffa9327c,
    0xffab337c,
    0xffac337b,
    0xffae347b,
    0xffb0347b,
    0xffb1357a,
    0xffb3357a,
    0xffb53679,
    0xffb63679,
    0xffb83778,
    0xffb93778,
    0xffbb3877,
    0xffbd3977,
    0xffbe3976,
    0xffc03a75,
    0xffc23a75,
    0xffc33b74,
    0xffc53c74,
    0xffc63c73,
    0xffc83d72,
    0xffca3e72,
    0xffcb3e71,
    0xffcd3f70,
    0xffce4070,
    0xffd0416f,
    0xffd1426e,
    0xffd3426d,
    0xffd4436d,
    0xffd6446c,
    0xffd7456b,
    0xffd9466a,
    0xffda4769,
    0xffdc4869,
    0xffdd4968,
    0xffde4a67,
    0xffe04b66,
    0xffe14c66,
    0xffe24d65,
    0xffe44e64,
    0xffe55063,
    0xffe65162,
    0xffe75262,
    0xffe85461,
    0xffea5560,
    0xffeb5660,
    0xffec585f,
    0xffed595f,
    0xffee5b5e,
    0xffee5d5d,
    0xffef5e5d,
    0xfff0605d,
    0xfff1615c,
    0xfff2635c,
    0xfff3655c,
    0xfff3675b,
    0xfff4685b,
    0xfff56a5b,
    0xfff56c5b,
    0xfff66e5b,
    0xfff6705b,
    0xfff7715b,
    0xfff7735c,
    0xfff8755c,
    0xfff8775c,
    0xfff9795c,
    0xfff97b5d,
    0xfff97d5d,
    0xfffa7f5e,
    0xfffa805e,
    0xfffa825f,
    0xfffb8460,
    0xfffb8660,
    0xfffb8861,
    0xfffb8a62,
    0xfffc8c63,
    0xfffc8e63,
    0xfffc9064,
    0xfffc9265,
    0xfffc9366,
    0xfffd9567,
    0xfffd9768,
    0xfffd9969,
    0xfffd9b6a,
    0xfffd9d6b,
    0xfffd9f6c,
    0xfffda16e,
    0xfffda26f,
    0xfffda470,
    0xfffea671,
    0xfffea873,
    0xfffeaa74,
    0xfffeac75,
    0xfffeae76,
    0xfffeaf78,
    0xfffeb179,
    0xfffeb37b,
    0xfffeb57c,
    0xfffeb77d,
    0xfffeb97f,
    0xfffebb80,
    0xfffebc82,
    0xfffebe83,
    0xfffec085,
    0xfffec286,
    0xfffec488,
    0xfffec689,
    0xfffec78b,
    0xfffec98d,
    0xfffecb8e,
    0xfffdcd90,
    0xfffdcf92,
    0xfffdd193,
    0xfffdd295,
    0xfffdd497,
    0xfffdd698,
    0xfffdd89a,
    0xfffdda9c,
    0xfffddc9d,
    0xfffddd9f,
    0xfffddfa1,
    0xfffde1a3,
    0xfffce3a5,
    0xfffce5a6,
    0xfffce6a8,
    0xfffce8aa,
    0xfffceaac,
    0xfffcecae,
    0xfffceeb0,
    0xfffcf0b1,
    0xfffcf1b3,
    0xfffcf3b5,
    0xfffcf5b7,
    0xfffbf7b9,
    0xfffbf9bb,
    0xfffbfabd,
    0xfffbfcbf,
};