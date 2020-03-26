# Boot2Android For windows

Temporarily modify UEFI boot entry on Windows platform  
用于在Windows平台临时修改UEFI启动项为Android  

Its principle is very simple. Look for the option starting with Android in the UEFI boot item, and set the BootNext to this option. Because the BootNext will only be used once, it will not permanently change your UEFI boot order.  
它的原理很简单，在UEFI启动项里找以Android开头的启动项，然后将BootNext设为这个启动项，BootNext只是用于临时设定下次启动的启动项，不会永久修改启动顺序  

I use it on my Surface Go to enter the Android x86 system, because Surface Go can't call up the UEFI boot entry selector, and I don't like grub (because it doesn't support touch screen).  
我用这玩意来进入我在Surface Go上安装的Android x86系统，因为Surface Go没法子调出来UEFI启动项选择器（BIOS里面也没有Android的启动项不知道为啥），不用Grub是因为那玩意不支持触屏而且默认主题贼丑我也懒得改= =  

结果现在我每次开Surface Go第一件事就是进Android打游戏了233333我寻思我一开始买这玩意是当生产力工具来着    