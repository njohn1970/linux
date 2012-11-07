/*
 *  linux/arch/arm/mach-bcm2708/pcm_audio.c
 *
 *  Copyright (C) 2012 Neil Johnson
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/slab.h>

#include <mach/pcm_audio.h>

#define DRIVER_NAME BCM_PCM_DRIVER_NAME

struct bcm_pcm_drv_context
{
    void __iomem *reg_base;
};

struct bcm_pcm_drv_context* bcm_pcm_alloc_drv_context(void)
{
    return NULL;
}

static int bcm_pcm_probe(struct platform_device *pdev)
{
    int ret = 0;
    struct bcm_pcm_drv_context* drv_context;
	struct resource* pcm_res = NULL;

    drv_context = bcm_pcm_alloc_drv_context();
    if( IS_ERR(drv_context) )
    {
        ret = PTR_ERR(drv_context);
        drv_context = NULL;
        goto out;
    }
    kfree( drv_context );
    drv_context = NULL;

    pcm_res = platform_get_resource( pdev, IORESOURCE_MEM, 0 );
    if(!pcm_res)
    {
        printk(KERN_ERR DRIVER_NAME": failed to get IO_MEM resource\n");
        ret = -ENODEV;
        goto out;
    }

    printk(KERN_INFO DRIVER_NAME": IO_MEM Start:0x%08X Size:0x%08X\n", pcm_res->start,
            resource_size(pcm_res));

out:

    if( !ret )
    {
        /*Clean up*/

        if( drv_context )
        {
            kfree( drv_context );
        }
    }

    return ret;
}

static int bcm_pcm_remove(struct platform_device *pdev)
{

    return 0;
}


static struct platform_driver bcm_pcm_driver = {
	.probe = bcm_pcm_probe,
	.remove = bcm_pcm_remove,

	.driver = {
		   .name = DRIVER_NAME,
		   .owner = THIS_MODULE,
		   },
};


/*****************************************************************************\
 *									     *
 * Driver init/exit							     *
 *									     *
\*****************************************************************************/
static int __init bcm_pcm_drv_init(void)
{
	int ret;

	ret = platform_driver_register(&bcm_pcm_driver);
	if (ret != 0) {
		printk(KERN_ERR DRIVER_NAME ": failed to register "
		       "on platform\n");
	}

	return ret;
}

static void __exit bcm_pcm_drv_exit(void)
{
	platform_driver_unregister(&bcm_pcm_driver);
}

module_init(bcm_pcm_drv_init);
module_exit(bcm_pcm_drv_exit);

MODULE_AUTHOR("Neil Johnson <grayg@broadcom.com>");
MODULE_DESCRIPTION("PCM/I2S Audtio driver");
MODULE_LICENSE("GPL");


