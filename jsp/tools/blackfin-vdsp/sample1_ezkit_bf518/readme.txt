TOPPERS/JSPのsample1アプリケーションをEZ-KIT Lite BF518
移植した。

ビルドに先立って、jsp/config/blackfin/ezkit_bf518/libkernel.dpjを
ビルドして、libekernel.dlbを作っておくこと。

また、jsp/utils/blackfin-vdsp/offset.hは、必要に応じて
作り直すこと。

VisualDSP++のICEを使ってロードする場合には、実行直前に次の
二つのレジスタの値に注意すること。

PLL_CTL : 0x0a00 (Rev.0.1の場合) / 0x0b00 (Rev.0.2の場合)
EBIU_SDBCTL.EBE : 0

TOPPERS/JSP for Blackfinはこの二つをチェックして、もし違う
値であると外部でPLLとSDRAMを変更したと認識してPLLの初期化を
中止する。これは外部SDRAMなどクロックに依存するデバイスの
動作を保護するためである。

sample1.ldfは、VisualDSP++に作らせたあと、自動更新を
停止し、crtを削除したものである。

異なるシステム依存部用に改造する場合は、プロジェクトの
Cコンパイラ、およびアセンブラのインクルード・パスを必ず
変更すること。

2012/07/20追加
Visual DSP++ 5.0 Update 10でビルド＆動作確認

sample1では、インストラクションキャッシュをONにすると、L1-SRAMに
収まらないので、OFFにしている。
キャッシュをONにして使用する場合、sample1.ldfのメモリエリアの指定を
変更して、カーネルの一部をSDRAMに配置する。
例えば、OSとして緊急性の低いchip_dump.cの関数をSDRAMに配置するなど。
