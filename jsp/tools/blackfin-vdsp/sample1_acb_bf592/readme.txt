TOPPERS/JSPのsample1アプリケーションをEZ-KIT Lite BF592
移植した。

ビルドに先立って、jsp/config/blackfin/ezkit_bf592/libkernel.dpjを
ビルドして、libekernel.dlbを作っておくこと。

また、jsp/utils/blackfin-vdsp/offset.hは、必要に応じて
作り直すこと。

VisualDSP++のICEを使ってロードする場合には、実行直前に次の
二つのレジスタの値に注意すること。

sample1.ldfは、VisualDSP++に作らせたあと、自動更新を
停止し、crtを削除したものである。

異なるシステム依存部用に改造する場合は、プロジェクトの
Cコンパイラ、およびアセンブラのインクルード・パスを必ず
変更すること。

2012/07/20追加
Visual DSP++ 5.0 Update 10でビルド＆動作確認
