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

#include <mach/pcm_audio.h>

#define DRIVER_NAME BCM_PCM_DRIVER_NAME


static int bcm_pcm_probe(struct platform_device *pdev)
{


    return -1;
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


