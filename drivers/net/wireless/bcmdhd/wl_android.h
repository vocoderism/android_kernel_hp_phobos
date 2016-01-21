/*
 * Linux cfg80211 driver - Android related functions
 *
 * $Copyright Open Broadcom Corporation$
 *
 * $Id: wl_android.h 440872 2013-12-04 05:25:35Z $
 */

#include <linux/module.h>
#include <linux/netdevice.h>
#include <wldev_common.h>

/* If any feature uses the Generic Netlink Interface, put it here to enable WL_GENL
 * automatically
 */
#if defined(WL_SDO) || defined(BCMCCX_S69)
#define WL_GENL
#endif


#ifdef WL_GENL
#include <net/genetlink.h>
#endif

/**
 * Android platform dependent functions, feel free to add Android specific functions here
 * (save the macros in dhd). Please do NOT declare functions that are NOT exposed to dhd
 * or cfg, define them as static in wl_android.c
 */

/**
 * wl_android_init will be called from module init function (dhd_module_init now), similarly
 * wl_android_exit will be called from module exit function (dhd_module_cleanup now)
 */
int wl_android_init(void);
int wl_android_exit(void);
void wl_android_post_init(void);
int wl_android_wifi_on(struct net_device *dev);
int wl_android_wifi_off(struct net_device *dev);
int wl_android_priv_cmd(struct net_device *net, struct ifreq *ifr, int cmd);

#if defined(CONFIG_WIFI_CONTROL_FUNC)
int wl_android_wifictrl_func_add(void);
void wl_android_wifictrl_func_del(void);
void* wl_android_prealloc(int section, unsigned long size);

int wifi_get_irq_number(unsigned long *irq_flags_ptr);
int wifi_set_power(int on, unsigned long msec);
int wifi_get_mac_addr(unsigned char *buf);
void *wifi_get_country_code(char *ccode);
#endif /* CONFIG_WIFI_CONTROL_FUNC */

#ifdef WL_GENL
typedef struct bcm_event_hdr {
	u16 event_type;
	u16 len;
} bcm_event_hdr_t;

/* attributes (variables): the index in this enum is used as a reference for the type,
 *             userspace application has to indicate the corresponding type
 *             the policy is used for security considerations
 */
enum {
	BCM_GENL_ATTR_UNSPEC,
	BCM_GENL_ATTR_STRING,
	BCM_GENL_ATTR_MSG,
	__BCM_GENL_ATTR_MAX
};
#define BCM_GENL_ATTR_MAX (__BCM_GENL_ATTR_MAX - 1)

/* commands: enumeration of all commands (functions),
 * used by userspace application to identify command to be ececuted
 */
enum {
	BCM_GENL_CMD_UNSPEC,
	BCM_GENL_CMD_MSG,
	__BCM_GENL_CMD_MAX
};
#define BCM_GENL_CMD_MAX (__BCM_GENL_CMD_MAX - 1)

/* Enum values used by the BCM supplicant to identify the events */
enum {
	BCM_E_UNSPEC,
	BCM_E_SVC_FOUND,
	BCM_E_DEV_FOUND,
	BCM_E_DEV_LOST,
#ifdef BCMCCX_S69
	BCM_E_DEV_S69RESP,
#endif
	BCM_E_MAX
};

s32 wl_genl_send_msg(struct net_device *ndev, u32 event_type,
	u8 *string, u16 len, u8 *hdr, u16 hdrlen);
#endif /* WL_GENL */
#ifdef WLAIBSS
s32 wl_netlink_send_msg(int pid, int seq, void *data, int size);
#endif /* WLAIBSS */
