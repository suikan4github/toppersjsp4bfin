#
#  TOPPERS/JSP Kernel
#      Toyohashi Open Platform for Embedded Real-Time Systems/
#      Just Standard Profile Kernel
# 
#  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
#                              Toyohashi Univ. of Technology, JAPAN
#  Copyright (C) 2005 by Embedded and Real-Time Systems Laboratory
#              Graduate School of Information Science, Nagoya Univ., JAPAN
# 
#  上記著作権者は，以下の (1)〜(4) の条件か，Free Software Foundation 
#  によって公表されている GNU General Public License の Version 2 に記
#  述されている条件を満たす場合に限り，本ソフトウェア（本ソフトウェア
#  を改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
#  利用と呼ぶ）することを無償で許諾する．
#  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
#      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
#      スコード中に含まれていること．
#  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
#      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
#      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
#      の無保証規定を掲載すること．
#  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
#      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
#      と．
#    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
#        作権表示，この利用条件および下記の無保証規定を掲載すること．
#    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
#        報告すること．
#  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
#      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
# 
#  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
#  よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
#  含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
#  接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
# 
#  @(#) $Id: Makefile,v 1.8 2012/01/21 02:32:02 suikan Exp $
# 

#
#  ターゲットの指定（Makefile.config で上書きされるのを防ぐため）
#
all:

#
#  ターゲット名の定義
#
CPU = @(CPU)
SYS = @(SYS)
TOOL = @(TOOL)

#
#  プログラミング言語の定義
#
PROGRAM_LANG = @(LANG)
ifeq ($(PROGRAM_LANG),c++)
    USE_CXX = true
    CXXLIBS = 
    CXXRTS  = cxxrt.o  newlibrt.o cpu_malloc.o
endif

#
#  ソースファイルのディレクトリの定義
#
SRCDIR = @(SRCDIR)

#
#  オブジェクトファイル名の拡張子の設定
#
OBJEXT = @(OBJEXT)

#
#  実行環境の定義（どれにも該当しない場合は，すべてコメントアウトする）
#		 （ターゲット依存に上書きされる場合がある）
#
DBGENV := GDB_STUB

#
#  カーネルライブラリ（libkernel.a）のディレクトリ名
#  （カーネルライブラリも make 対象にする時は，空に定義する）
#
KERNEL_LIB = @(KERNEL_LIB)

#
#  ターゲット依存の定義のインクルード
#
ifdef TOOL
    ifdef SYS
        include $(SRCDIR)/config/$(CPU)-$(TOOL)/$(SYS)/Makefile.config
    endif
    include $(SRCDIR)/config/$(CPU)-$(TOOL)/Makefile.config
else
    ifdef SYS
        include $(SRCDIR)/config/$(CPU)/$(SYS)/Makefile.config
    endif
    include $(SRCDIR)/config/$(CPU)/Makefile.config
endif

#
#  共通コンパイルオプションの定義
#
COPTS := $(COPTS)
CDEFS := $(CDEFS)
INCLUDES := -I. -I$(SRCDIR)/include $(INCLUDES)
LDFLAGS := -nostdlib $(LDFLAGS)
LIBS := $(LIBS) $(CXXLIBS) -lgcc 
CFLAGS = $(COPTS) $(CDEFS) $(INCLUDES)

#
#  アプリケーションプログラムに関する定義
#
UNAME = @(UNAME)
UTASK_CFG = $(UNAME).cfg

UTASK_DIR = $(SRCDIR)/library
UTASK_ASMOBJS =
ifdef USE_CXX
    UTASK_CXXOBJS = $(UNAME).o @(UTASK)
    UTASK_COBJS =
else
    UTASK_COBJS = $(UNAME).o @(UTASK)
endif
UTASK_CFLAGS =
UTASK_LIBS =

#
#  システムサービスに関する定義
#
STASK_DIR := $(STASK_DIR):$(SRCDIR)/systask:$(SRCDIR)/library
STASK_ASMOBJS := $(STASK_ASMOBJS)
STASK_COBJS := $(STASK_COBJS) timer.o serial.o logtask.o \
	      log_output.o vasyslog.o t_perror.o strerror.o \
	      $(CXXRTS)
STASK_CFLAGS := $(STASK_CFLAGS) -I$(SRCDIR)/systask
STASK_LIBS := $(STASK_LIBS)

#
#  カーネルに関する定義
#
#  KERNEL_ASMOBJS: カーネルライブラリに含める，ソースがアセンブリ言語の
#		   オブジェクトファイル．
#  KERNEL_COBJS: カーネルのライブラリに含める，ソースがC言語で，ソース
#		 ファイルと1対1に対応するオブジェクトファイル．
#  KERNEL_LCSRCS: カーネルのライブラリに含めるC言語のソースファイルで，
#		  1つのソースファイルから複数のオブジェクトファイルを生
#		  成するもの（Makefile.kernel で定義）．
#  KERNEL_LCOBJS: 上のソースファイルから生成されるオブジェクトファイル
#		  （Makefile.kernel で定義）．
#  KERNEL_AUX_COBJS: ロードモジュールに含めないが，カーネルのソースファ
#		     イルと同じオプションを適用してコンパイルすべきファ
#		     イル．
#
KERNEL = $(SRCDIR)/kernel
KERNEL_DIR := $(KERNEL_DIR):$(KERNEL)
KERNEL_ASMOBJS := $(KERNEL_ASMOBJS)
KERNEL_COBJS := startup.o banner.o $(KERNEL_COBJS)
KERNEL_CFLAGS := $(KERNEL_CFLAGS) -I$(KERNEL)
ifdef OMIT_MAKEOFFSET
    OFFSET_H =
    KERNEL_AUX_COBJS = kernel_chk.o
else
    OFFSET_H = offset.h
    KERNEL_AUX_COBJS = makeoffset.o kernel_chk.o
endif

#
#  オブジェクトファイル名の定義
#
OBJNAME = jsp
ifdef OBJEXT
    OBJFILE = $(OBJNAME).$(OBJEXT)
else
    OBJFILE = $(OBJNAME)
endif

#
#  ターゲットファイル（複数を同時に選択してはならない）
#
all: $(OBJFILE)
#all: $(OBJNAME).out
#all: $(OBJNAME).bin
#all: $(OBJNAME).srec

#
#  カーネルのコンフィギュレーションファイルの生成
#
kernel_cfg.c kernel_id.h kernel_chk.c: $(UTASK_CFG)
	$(CC) -E $(INCLUDES) $(CDEFS) -x c-header $(UTASK_CFG) > tmpfile1
	$(SRCDIR)/cfg/cfg -s tmpfile1 -c -obj -cpu $(CPU) -system $(SYS)
	rm -f tmpfile1

##### 以下は編集しないこと #####

#
#  環境に依存するコンパイルオプションの定義
#
ifdef DBGENV
    CDEFS := $(CDEFS) -D$(DBGENV)
endif

#
#  カーネルライブラリに関連する定義
#
ifdef KERNEL_LIB
    MAKE_KERNEL =
    LIBKERNEL = $(KERNEL_LIB)/libkernel.a
else
    MAKE_KERNEL = libkernel.a
    LIBKERNEL = $(MAKE_KERNEL)
endif

#
#  カーネルのファイル構成の定義
#
include $(KERNEL)/Makefile.kernel

#
#  $(OBJNAME).chk の生成規則（静的APIのパラメータチェック）
#
$(OBJNAME).chk: kernel_chk.s $(SRCDIR)/utils/gencheck
	$(PERL) $(SRCDIR)/utils/gencheck kernel_chk.s > tmpfile2
	mv tmpfile2 $(OBJNAME).chk

#
#  offset.h の生成規則（構造体内のオフセット値の算出）
#
offset.h: makeoffset.s $(SRCDIR)/utils/genoffset
	$(PERL) $(SRCDIR)/utils/genoffset makeoffset.s > tmpfile3
	mv tmpfile3 offset.h

#
#  ソースファイルのあるディレクトリに関する定義
#
vpath %.c $(KERNEL_DIR):$(STASK_DIR):$(UTASK_DIR)
vpath %.S $(KERNEL_DIR):$(STASK_DIR):$(UTASK_DIR)

#
#  コンパイルのための変数の定義
#
KERNEL_LIB_OBJS = $(KERNEL_ASMOBJS) $(KERNEL_COBJS) $(KERNEL_LCOBJS)
STASK_OBJS = $(STASK_ASMOBJS) $(STASK_COBJS)
UTASK_OBJS = $(UTASK_ASMOBJS) $(UTASK_COBJS) $(UTASK_CXXOBJS)
TASK_OBJS = $(UTASK_OBJS) $(STASK_OBJS) kernel_cfg.o
ALL_OBJS = $(START_OBJS) $(CXX_BEGIN_OBJS) $(TASK_OBJS) $(CXX_END_OBJS) $(END_OBJS) 
ALL_LIBS = $(UTASK_LIBS) $(STASK_LIBS) $(LIBKERNEL) $(LIBS)

ifdef TEXT_START_ADDRESS
    LDFLAGS := $(LDFLAGS) -Wl,-Ttext,$(TEXT_START_ADDRESS)
endif
ifdef DATA_START_ADDRESS
    LDFLAGS := $(LDFLAGS) -Wl,-Tdata,$(DATA_START_ADDRESS)
endif
ifdef LDSCRIPT
    LDFLAGS := $(LDFLAGS) -T $(SRCDIR)/config/$(LDSCRIPT)
endif

#
#  カーネルライブラリファイルの生成
#
libkernel.a: $(OFFSET_H) $(KERNEL_LIB_OBJS)
	rm -f libkernel.a
	$(AR) -rcs libkernel.a $(KERNEL_LIB_OBJS)
	$(RANLIB) libkernel.a

#
#  全体のリンク
#  $(OBJCOPY) -R ... はGDB用に定義したデバッグ用MMRのメモリ実体を剥ぎ取り、シンボルだけ残すためのもの。
#
$(OBJFILE): Makefile.depend $(ALL_OBJS) $(MAKE_KERNEL) $(OBJNAME).chk
	$(LINK) $(CFLAGS) $(LDFLAGS) -o $(OBJFILE) \
			$(START_OBJS) $(CXX_BEGIN_OBJS) $(TASK_OBJS) $(ALL_LIBS) $(CXX_END_OBJS) $(END_OBJS)
	$(NM) $(OBJFILE) > $(OBJNAME).syms
	$(OBJCOPY) -O srec -S $(OBJFILE) $(OBJNAME).srec
	$(SRCDIR)/cfg/chk -m $(OBJNAME).syms,$(OBJNAME).srec \
			-obj -cs $(OBJNAME).chk -cpu $(CPU) -system $(SYS)

#
#  バイナリファイルの生成
#
$(OBJNAME).bin: $(OBJFILE)
	$(OBJCOPY) -O binary -S $(OBJFILE) $(OBJNAME).bin

#
#  Sレコードファイルの生成
#
$(OBJNAME).srec: $(OBJFILE)
	$(OBJCOPY) -O srec -S $(OBJFILE) $(OBJNAME).srec

#
#  コンパイル結果の消去
#
clean:
	rm -f \#* *~ *.o tmpfile?
	rm -f $(MAKE_KERNEL) $(OBJNAME)
	rm -f $(OBJNAME).syms $(OBJNAME).srec $(OBJNAME).chk
	rm -f $(OBJNAME).exe $(OBJNAME).bin $(OBJNAME).out
	rm -f kernel_cfg.c kernel_chk.c kernel_chk.s kernel_id.h kernel_obj.dat
	rm -f makeoffset.s offset.h

cleankernel:
	rm -rf $(KERNEL_LIB_OBJS)
	rm -f makeoffset.s offset.h

cleandep:
	rm -f Makefile.depend

realclean: cleandep clean

#
#  kernel_cfg.c のコンパイルルールと依存関係作成ルールの定義
#
#  kernel_cfg.c は，アプリケーションプログラム用，システムサービス用，
#  カーネル用のすべてのオプションを付けてコンパイルする．
#
KERNEL_CFG_CFLAGS = $(UTASK_CFLAGS) $(STASK_CFLAGS) $(KERNEL_CFLAGS)

kernel_cfg.o: kernel_cfg.c
	$(CC) -c $(CFLAGS) $(KERNEL_CFG_CFLAGS) $<

kernel_cfg.s: kernel_cfg.c
	$(CC) -S $(CFLAGS) $(KERNEL_CFG_CFLAGS) $<

kernel_cfg.d: kernel_cfg.c
	@$(PERL) $(SRCDIR)/utils/makedep -C $(CC) \
		-O "$(CFLAGS) $(KERNEL_CFG_CFLAGS)" $< >> Makefile.depend

#
#  特別な依存関係の定義
#
banner.o: $(filter-out banner.o,$(KERNEL_LIB_OBJS))

#
#  特殊な依存関係作成ルールの定義
#
kernel_id.d: $(UTASK_CFG)
	@$(PERL) $(SRCDIR)/utils/makedep -C $(CC) -X \
		-T "kernel_cfg.c kernel_id.h kernel_chk.c" \
		-O "$(INCLUDES)" $< >> Makefile.depend

makeoffset.d: makeoffset.c
	@$(PERL) $(SRCDIR)/utils/makedep -s -C $(CC) \
		-O "$(CFLAGS) $(KERNEL_CFLAGS)" $< >> Makefile.depend

kernel_chk.d: kernel_chk.c
	@$(PERL) $(SRCDIR)/utils/makedep -s -C $(CC) \
		-O "$(CFLAGS) $(KERNEL_CFLAGS)" $< >> Makefile.depend

#
#  依存関係ファイルの生成
#
gendepend:
	@echo "Generating Makefile.depend."

ifdef KERNEL_LIB
depend: cleandep kernel_cfg.c gendepend kernel_id.d \
		kernel_chk.d $(ALL_OBJS:.o=.d)
else
depend: cleandep $(OFFSET_H) kernel_cfg.c gendepend kernel_id.d \
		$(KERNEL_AUX_COBJS:.o=.d) $(KERNEL_ASMOBJS:.o=.d) \
		$(KERNEL_COBJS:.o=.d) $(KERNEL_LCSRCS:.c=.d) $(ALL_OBJS:.o=.d)
endif

#
#  依存関係ファイルをインクルード
#
-include Makefile.depend

#
#  開発ツールのコマンド名の定義
#
ifndef TOOL
    #
    #  GNU開発環境用
    #
    ifdef TARGET
        TARGET_PREFIX = $(TARGET)-
    else
        TARGET_PREFIX =
    endif
    CC = $(TARGET_PREFIX)gcc
    CXX = $(TARGET_PREFIX)g++
    AS = $(TARGET_PREFIX)as
    LD = $(TARGET_PREFIX)ld
    AR = $(TARGET_PREFIX)ar
    NM = $(TARGET_PREFIX)nm
    RANLIB = $(TARGET_PREFIX)ranlib
    OBJCOPY = $(TARGET_PREFIX)objcopy
    OBJDUMP = $(TARGET_PREFIX)objdump
else
    TARGET_PREFIX =
endif

ifdef USE_CXX
    LINK = $(CXX)
else
    LINK = $(CC)
endif

PERL = @(PERL)

#
#  コンパイルルールの定義
#
KERNEL_ALL_COBJS = $(KERNEL_COBJS) $(KERNEL_AUX_COBJS)

$(KERNEL_ALL_COBJS): %.o: %.c
	$(CC) -c $(CFLAGS) $(KERNEL_CFLAGS) $<

$(KERNEL_ALL_COBJS:.o=.s): %.s: %.c
	$(CC) -S $(CFLAGS) $(KERNEL_CFLAGS) $<

$(KERNEL_LCOBJS): %.o:
	$(CC) -D__$(*F) -o $@ -c $(CFLAGS) $(KERNEL_CFLAGS) $<

$(KERNEL_LCOBJS:.o=.s): %.s:
	$(CC) -D__$(*F) -o $@ -S $(CFLAGS) $(KERNEL_CFLAGS) $<

$(KERNEL_ASMOBJS): %.o: %.S
	$(CC) -c $(CFLAGS) $(KERNEL_CFLAGS) $<

$(STASK_COBJS): %.o: %.c
	$(CC) -c $(CFLAGS) $(STASK_CFLAGS) $<

$(STASK_COBJS:.o=.s): %.s: %.c
	$(CC) -S $(CFLAGS) $(STASK_CFLAGS) $<

$(STASK_ASMOBJS): %.o: %.S
	$(CC) -c $(CFLAGS) $(STASK_CFLAGS) $<

$(UTASK_COBJS): %.o: %.c
	$(CC) -c $(CFLAGS) $(UTASK_CFLAGS) $<

$(UTASK_COBJS:.o=.s): %.s: %.c
	$(CC) -S $(CFLAGS) $(UTASK_CFLAGS) $<

$(UTASK_CXXOBJS): %.o: %.cpp
	$(CXX) -c $(CFLAGS) $(UTASK_CFLAGS) $<

$(UTASK_CXXOBJS:.o=.s): %.s: %.cpp
	$(CXX) -S $(CFLAGS) $(UTASK_CFLAGS) $<

$(UTASK_ASMOBJS): %.o: %.S
	$(CC) -c $(CFLAGS) $(UTASK_CFLAGS) $<

#
#  依存関係作成ルールの定義
#
$(KERNEL_COBJS:.o=.d): %.d: %.c
	@$(PERL) $(SRCDIR)/utils/makedep -C $(CC) \
		-O "$(CFLAGS) $(KERNEL_CFLAGS)" $< >> Makefile.depend

$(KERNEL_LCSRCS:.c=.d): %.d: %.c
	@$(PERL) $(SRCDIR)/utils/makedep -C $(CC) -T "$($*)" \
		-O "$(foreach sym,$($*),-D__$(sym:.o=)) \
		$(CFLAGS) $(KERNEL_CFLAGS)" $< >> Makefile.depend

$(KERNEL_LCOBJS:.o=.d): %.d:
	@$(PERL) $(SRCDIR)/utils/makedep -C $(CC) -T $*.o \
		-O "-D__$(*F) $(CFLAGS) $(KERNEL_CFLAGS)" $< >> Makefile.depend

$(KERNEL_ASMOBJS:.o=.d): %.d: %.S
	@$(PERL) $(SRCDIR)/utils/makedep -C $(CC) \
		-O "$(CFLAGS) $(KERNEL_CFLAGS)" $< >> Makefile.depend

$(STASK_COBJS:.o=.d): %.d: %.c
	@$(PERL) $(SRCDIR)/utils/makedep -C $(CC) \
		-O "$(CFLAGS) $(STASK_CFLAGS)" $< >> Makefile.depend

$(STASK_ASMOBJS:.o=.d): %.d: %.S
	@$(PERL) $(SRCDIR)/utils/makedep -C $(CC) \
		-O "$(CFLAGS) $(STASK_CFLAGS)" $< >> Makefile.depend

$(UTASK_COBJS:.o=.d): %.d: %.c
	@$(PERL) $(SRCDIR)/utils/makedep -C $(CC) \
		-O "$(CFLAGS) $(UTASK_CFLAGS)" $< >> Makefile.depend

$(UTASK_CXXOBJS:.o=.d): %.d: %.cpp
	@$(PERL) $(SRCDIR)/utils/makedep -C $(CXX) \
		-O "$(CFLAGS) $(UTASK_CFLAGS)" $< >> Makefile.depend

$(UTASK_ASMOBJS:.o=.d): %.d: %.S
	@$(PERL) $(SRCDIR)/utils/makedep -C $(CC) \
		-O "$(CFLAGS) $(UTASK_CFLAGS)" $< >> Makefile.depend

#
#  デフォルトコンパイルルールを上書き
#
%.o: %.c
	@echo "*** Default compile rules should not be used."
	$(CC) -c $(CFLAGS) $<

%.s: %.c
	@echo "*** Default compile rules should not be used."
	$(CC) -S $(CFLAGS) $<

%.o: %.cpp
	@echo "*** Default compile rules should not be used."
	$(CXX) -c $(CFLAGS) $<

%.s: %.cpp
	@echo "*** Default compile rules should not be used."
	$(CXX) -S $(CFLAGS) $<

%.o: %.S
	@echo "*** Default compile rules should not be used."
	$(CC) -c $(CFLAGS) $<
