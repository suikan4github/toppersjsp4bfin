#include "t_services.h"
#include "ad1836a.h"
#include <cdefBF533.h>
#include <ccblkfn.h>

void spi_handler(void)
{
    *pDMA5_IRQ_STATUS = DMA_DONE;       // SPI DMA���荞�݂��N���A
    ssync();
    isig_sem( spi_sem );
}

