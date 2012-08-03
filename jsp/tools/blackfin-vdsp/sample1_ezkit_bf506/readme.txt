TOPPERS/JSPのsample1アプリケーションをEZ-KIT Lite BF506
移植した。

ビルドに先立って、jsp/config/blackfin/ezkit_bf506/libkernel.dpjを
ビルドして、libekernel.dlbを作っておくこと。

また、jsp/utils/blackfin-vdsp/offset.hは、必要に応じて
作り直すこと。

VisualDSP++のICEを使ってロードする場合には、実行直前に次の
二つのレジスタの値に注意すること。

PLL_CTL : 0x1400
EBIU_SDBCTL.EBE : 0

TOPPERS/JSP for Blackfinはこの二つをチェックして、もし違う
値であると外部でPLLとSDRAMを変更したと認識してPLLの初期化を
中止する。これはクロックに依存するデバイスの動作を保護する
ためである。

sample1.ldfは、VisualDSP++に作らせたあと、自動更新を
停止し、crtを削除したものである。

異なるシステム依存部用に改造する場合は、プロジェクトの
Cコンパイラ、およびアセンブラのインクルード・パスを必ず
変更すること。

2012/07/20追加
Visual DSP++ 5.0 Update 10でビルド＆動作確認

sample1では、キャッシュをONにすると、L1-SRAMに収まらないので、
OFFにしている。キャッシュをONにして使用する場合、sample1.ldfの
メモリエリアの指定を変更して、カーネルの一部をFLASHに配置する。
例えば、OSとして緊急性の低いchip_dump.cの関数をFLASHに配置するなど。
