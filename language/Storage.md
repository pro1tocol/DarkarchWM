## Partition Creation Instructions
#### Taking /dev/sda as an example

``` shell
# Create partitions using parted
parted /dev/sda
mklabel gpt
mkpart ESP 4096s 1024M
mkpart primary 1024M -1
set 1 boot on
p
q
# Create LVM Logical Volume
pvcreate /dev/sda2
vgcreate System /dev/sda2
lvcreate -l +100%FREE System -n DarkarchWM
mkfs.fat -F 32 /dev/sda1
mkfs.btrfs /dev/mapper/System-DarkarchWM
# mkfs.xfs /dev/mapper/System-DarkarchWM # options
# Mount Partition
mount /dev/mapper/System-DarkarchWM /mnt
mount --mkdir /dev/sda1 /mnt/boot
# Verification result
lvs
df -h
```
