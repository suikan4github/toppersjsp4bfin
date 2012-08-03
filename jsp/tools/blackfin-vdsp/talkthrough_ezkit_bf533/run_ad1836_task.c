#include "t_services.h"
#include "s_services.h"
#include <cdefBF533.h>
#include "ad1836a.h"



#define pFLASHA_PORTA_OUT ((volatile unsigned char * )0x20270004)
#define pFLASHA_PORTA_DIR ((volatile unsigned char * )0x20270006)


struct DMA_DESCRIPTOR{
    struct DMA_DESCRIPTOR * next;
    void * start;
    unsigned short config;
    unsigned short x_count;
    short x_modify;
};


// CODEC �������f�[�^��
static short sCodec1836TxRegs[] =
{                                   
                    DAC_CONTROL_1   | 0x000,
                    DAC_CONTROL_2   | 0x000,
                    DAC_VOLUME_0    | 0x3ff,
                    DAC_VOLUME_1    | 0x3ff,
                    DAC_VOLUME_2    | 0x3ff,
                    DAC_VOLUME_3    | 0x3ff,
                    DAC_VOLUME_4    | 0x3ff,
                    DAC_VOLUME_5    | 0x3ff,
                    ADC_CONTROL_1   | 0x000,
                    ADC_CONTROL_2   | 0x180,
                    ADC_CONTROL_3   | 0x000
                    
};

// �I�[�f�B�I�o�b�t�@
// 1�T���v��������8�f�[�^��]������B�_�u���o�b�t�@�\���Ȃ̂ł���ɂ���2�{�K�v
static struct CODEC_BUFFER TxBuffer[2], RxBuffer[2];

static struct DMA_DESCRIPTOR tDescA, tDescB, rDescA, rDescB;

void run_ad1836_task(VP_INT extinf)
{
    ena_int( INTNO_SPI );           // SPI DMA���荞�݃}�X�N���͂��� 
    ena_int( INTNO_SPORT0_RX );     // SPORT0 DMA���荞�݃}�X�N���͂��� 

//--------------------------------------------------------
//          AD1836�̃��Z�b�g 
//
    *pFLASHA_PORTA_DIR |= 0x01;     // CODEC ���Z�b�g�M�����o�͂�   
    *pFLASHA_PORTA_OUT &= 0xFE;     // CODEC ���Z�b�g���A�T�[�g 
    tslp_tsk( 1 );                  // ���Z�b�g=L�p���X����� 
    *pFLASHA_PORTA_OUT |= 0x01;     // CODEC ���Z�b�g���f�A�T�[�g 
    tslp_tsk( 1 );                  // ���Z�b�g����̉񕜎��Ԃ�^���� 

//--------------------------------------------------------
//          SPI�ݒ� 
//  
    // PF4��AD1836��SPI SS�s�� 
    *pSPI_FLG = FLS4;
    // SPI�r�b�g���[�g = SCLK/(2*SPIBAUD) :���悻 2MHz  
    *pSPI_BAUD = 32;
    // SPI DMA �������݂ɂ��g���K, 16bit �f�[�^, MSB first, �}�X�^
    *pSPI_CTL = TIMOD | SIZE | MSTR;

    
    
//--------------------------------------------------------
//           SPI DMA �ݒ� 
//
    // 16bit �f�[�^�A����������ǂݏo���A�I���㊄�荞��
    *pDMA5_CONFIG = WDSIZE_16 | DI_EN;
    // CODEC ������������̃A�h���X 
    *pDMA5_START_ADDR = sCodec1836TxRegs;
    // DMA �]���J�E���g 
    *pDMA5_X_COUNT = sizeof( sCodec1836TxRegs ) / sizeof( short );
    // DMA ���� 
    *pDMA5_X_MODIFY = sizeof( short );
    

//--------------------------------------------------------
//           SPI �J�n
    // DMA �J�n 
    *pDMA5_CONFIG |= DMAEN;
    // SPI �J�n 
    *pSPI_CTL |= SPE;

    
    // DMA���o�I����҂� 
    wai_sem( spi_sem );
    // DMA�I����SPI���M�I���ł͂Ȃ��̂ŁA������Ƒ҂� 
    tslp_tsk( 1 );

//--------------------------------------------------------
//      SPORT0 �ݒ� 
//          �}���`�`�����l���̏ꍇ�A��� SPORTx_yCR1.LATFS = 0
    // Sport0 ��M�ݒ� 
    // �O���N���b�N, �O�������M��, MSB�t�@�[�X�g 
    // 32-bit �f�[�^ 
    *pSPORT0_RCR1 = RFSR;
    *pSPORT0_RCR2 = 31;     // �f�[�^�� 32
    
    // Sport0 ���M�ݒ�
    // �O���N���b�N, �O�������M��, MSB�t�@�[�X�g 
    // 32�r�b�g�f�[�^ 
    *pSPORT0_TCR1 = TFSR;
    *pSPORT0_TCR2 = 31;     // �f�[�^�� 32 
    
    // �t���[��������8�X���b�g�̃f�[�^�𑗎�Ŏg�� 
    *pSPORT0_MTCS0 = 0x000000FF;
    *pSPORT0_MRCS0 = 0x000000FF;
    
    // �}���`�`�����l���ݒ�
    *pSPORT0_MCMC1 = 0x0000; // �I�t�Z�b�g = 0, �E�C���h�E�T�C�Y = 8
    *pSPORT0_MCMC2 = 0x1000 | MCMEN | MCDRXPE | MCDTXPE; // MFD = 1;

//--------------------------------------------------------
//          SPORT DMA �ݒ� 
//
    // DMA1�ݒ� (SPORT0 RX)
    rDescA.next = &rDescB;
    rDescA.start = RxBuffer[0].data;
    rDescA.config = 0x7700 | WNR | WDSIZE_32 | DI_EN | DMAEN;   // Large List, 7 short word.
    rDescA.x_count = 8 * SAMPLE_PER_INTR;
    rDescA.x_modify = 4;
    
    rDescB.next = &rDescA;
    rDescB.start = RxBuffer[1].data;
    rDescB.config = 0x7700 | WNR | WDSIZE_32 | DI_EN | DMAEN;   // Large List, 7 short word.
    rDescB.x_count = 8 * SAMPLE_PER_INTR;
    rDescB.x_modify = 4;
    
    
    // DMA2�ݒ� (SPORT0 TX)
    tDescA.next = &tDescB;
    tDescA.start = TxBuffer[0].data;
    tDescA.config = 0x7700 | WDSIZE_32 | DMAEN; // Large List, 7 short word.
    tDescA.x_count = 8 * SAMPLE_PER_INTR;
    tDescA.x_modify = 4;
    
    tDescB.next = &tDescA;
    tDescB.start = TxBuffer[1].data;
    tDescB.config = 0x7700 | WDSIZE_32 | DMAEN; // Large List, 7 short word.
    tDescB.x_count = 8 * SAMPLE_PER_INTR;
    tDescB.x_modify = 4;


    *pDMA2_NEXT_DESC_PTR = &tDescA;
    *pDMA1_NEXT_DESC_PTR = &rDescA;
    *pDMA2_CONFIG = 0x7700 | WDSIZE_32;
    *pDMA1_CONFIG = 0x7700 | WNR | WDSIZE_32;
    
    
//--------------------------------------------------------
//           SPORT0 �J�n
    // DMA �J�n 
    *pDMA2_CONFIG |= DMAEN;
    *pDMA1_CONFIG |= DMAEN;
    asm("ssync;");
    // SPORT2 �J�n 
    *pSPORT0_TCR1 |= TSPEN;
    *pSPORT0_RCR1 |= RSPEN;

//

    while( 1 ){
        int sample, slot, bufTx, bufRx;
        struct CODEC_BUFFER * BufToBeTransmit; 
    
                // ��MDMA�I�����荞�݂Ɠ���
        wai_sem( sport0_sem);
    
                // �v���Z�b�T���g���Ă悢�o�b�t�@������o�� 
        bufTx = ( &tDescA == *pDMA2_NEXT_DESC_PTR) ? 0 : 1;
        bufRx = ( &rDescA == *pDMA1_NEXT_DESC_PTR) ? 0 : 1;
                
        
        processData(&RxBuffer[bufRx], &TxBuffer[bufTx]);
                
    }

}

