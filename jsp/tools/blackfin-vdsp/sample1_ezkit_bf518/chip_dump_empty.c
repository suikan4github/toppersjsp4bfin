/**
 * \file chip_dump_dummy.c
* \brief ADSP-BF518用のポストモーテムダンプルーチン群(ダミー)
 *
 * chip_dump.cはコードサイズが大きく、例外時にしか必要としない機能のため、
 * sample1では機能を無効にしてフットプリントを少なくしている
 * chip_dump.cを使用する場合、chip_dump.cのみSDRAMに配置するなど対策が必要
 */
#include "jsp_kernel.h"
#include <cdefBF518.h>

/**
 * \brief ハードウェア・エラー・ハンドラ
 *
 * ハードウェア・エラー時に呼び出されて、ハードウェア・エラー・割り込みのポストモーテム処理を行う。
 * 最初にFPを手繰って、割り込みのスタックフレームを探す。次にすべての割り込みを禁止し、
 * UART0を占有したあと、ポーリングを使ってスタックに保存された各レジスタのダンプを行う。
 * DEF_INH(INHNO_HW_ERROR, { TA_HLNG, hwei_handler });
 *
 */
void spurious_int_handler()
{
}

/**
 * \brief CPU例外ハンドラ
 *
 * CPU例外ハンドラとしてcfgファイルに登録する。 hwei_handler()は呼ばれたら戻ってこないが、
 * そのあとにもexpFlagに値を代入しているのは、最適化によってunlink命令の値がルーチン呼び出しの
 * 前に移動することを防ぐためである。
 *
 * DEF_EXC(CPUEXC1, { TA_HLNG, excp_handler} );
 *
 */
void spurious_exc_handler(VP p_excinf)
{
}

